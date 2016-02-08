
/*  fc -- this does a lot of things ..
    
    
    
    
    glen newton
    u of waterloo
    88/02/02
    
    
    */


#include "stuff.h"
#include "search.h"

#include "fc.h"




extern char *optarg;
extern int optind;

char *progname;


main( argc, argv )
int argc ;
char *argv[] ;

{
  
  
  extern IMAGE im_struct;
  
  extern float K;
  
  void usage(), debug(), DebugInfo();
    
  int  ii, jj,  
  initialize(),
  Imsave(), 
  Sobel(), 
  EdgeListBuild(), 
  extend_lines(), 
  CHist(),
  show_edges(),
  getopt(),
  c,
  radius_list[10],
  num_radii = 0;
  
  byte *out_image,
  *FcAverage(),
  *Imread();
  
  
  EDGE_LIST **edges, **strong_edges;
  
  SEGMENTS_LIST *connected(), *strong_list;
  
  
  if (!rindex (argv[0], '/')) progname = argv[0];
  else progname = rindex (argv[0], '/') + 1;
  
  
  
  while ((c = getopt (argc, argv, "pN:V:WS:dD:Ta:Av:R:H:CE:x:y:i:ewht:m:k:ocsP")) != EOF)
    {
      switch (c)
        {
	case 'N':
	  Endpoints = atoi(optarg);
	  break;
	case 'p':
	  OutputListPoints = TRUE;
          CircHist = TRUE;
          Overlay = FALSE;
	  break;
	  
	case 'W':
	  SunView = TRUE;
	  break;
	  
	case 'Z':
	  SelContour = atoi(optarg);
	  break;
	  
	case 'S':
	  Strategy = atoi(optarg);
	  break;
	  
	case 'D':
	  Debug = atoi(optarg);
	  break;
	case 'd':
	  DebugInfo();
	  exit(-1);
	  break;
	  
	case 'T':
	  TraceFlag = TRUE;
	  break;
	case 'a':
	  AverageBlockSize =atoi(optarg);
	case 'A':
	  Average = TRUE;
	  break;
	  
	case 'v':
	  MinValue = atoi(optarg);
	  break;
	
	case 'V':
	  MaxValue = atoi(optarg);
	  break;
	  
	case 'R':
	  RotateHist = atoi(optarg);
	  break;
	  
	case 'H':
	  Hough = TRUE;
	  if(num_radii<10)
	    {
	      radius_list[num_radii] = atoi(optarg);
	      ++num_radii;
	    }
	  
	  break;
	case 'C':
	  CheckContourDir = TRUE;
	  break;
	  
	case 'x':
	  XCheck = atoi(optarg);
	  break;
	  
	case 'y':
	  YCheck = atoi(optarg);
	  break;
	  
	case 'E':
	  EndPointNum = atoi(optarg);
	  break;
	  
        case 't':
          Edge_Thresh = atoi(optarg);
	  break;
	  
	case 'i':
	  OutputSingleContour = atoi(optarg);
	  break;
	  
	  
        case 'w':
	  TmWaterWeight = TRUE;
	  TmThresh = atoi(optarg);
	  break;
	  
        case 'e':
          ExtendLines = TRUE;
	  break;
	  
        case 'm':
          MinOutSize = atoi(optarg);
          break;
	  
        case 'k':
	  printf("\n\n k=%d %f\n\n",K,K);
	  K = atof(optarg)/100.0;
	  K = 0.5;
	  
	  printf("\n\n k=%d %f\n\n",K,K);
	  break;
	  
        case 'o': 
          Overlay = TRUE;
          break;
	  
        case 'c': 
          CircHist = TRUE;
          Overlay = FALSE;
          break;
	  
        case 's':
          SmoothCircHist = TRUE;
          break; 
	  
        case 'P':
	  PostscriptOut = TRUE;
	  CircHist = TRUE;
	  Overlay = FALSE;
	  break;
	  
        default:
          usage ();
          exit (-1);
        }
    }
  
  if(Debug)
    debug("fc - start");
  
  if(image =  
     Imread( argv[optind], 
	    &(im_struct.width), &(im_struct.height)))
    {
      
      initialize();
      edges = (EDGE_LIST**)malloc(sizeof(EDGE_LIST*)*Num_Edge_Types);
      strong_edges = (EDGE_LIST**)malloc(sizeof(EDGE_LIST*));
      
      for (ii=0; ii < Num_Edge_Types; ++ii)
	edges[ii] = NULL;
      
      *strong_edges = NULL; 
      
      Sobel();

/*      free(image);*/
       
      
      /* call 'EdgeListBuild' which returns three values :
	 Superior edges - these are very good edges
	 Inferior edges - these are better than average, but
	 not as good as Superior edges.
	 Other edges    - these are all other edges in the image.
	 */  
      
      EdgeListBuild(edges, strong_edges);
      
      strong_list = connected(strong_edges);
      
      if(ExtendLines==TRUE)
	if(SunView == TRUE)
	  {
	    printf("\n\n sunview \n\n");
	    View_extend_lines(&strong_list,AStar);
	  }
      	else
	  extend_lines( &strong_list, AStar); 

      group(strong_list);
      
      if(CircHist==TRUE)
	{
	  CHist(strong_list);
	}
      else
	{
	  if(!Test)
	    if(Overlay == TRUE)
	      {
		show_edges(strong_list,image);
		out_image = image;
	      }
	    else
	      {
		if(Average)
		  image = FcAverage();
		else
		  {
		    if(TraceFlag)
		      out_image = Trace;
		    else
		      {
			out_image = (byte*)malloc(sizeof(byte)*im_struct.width*im_struct.height);
		    
			for(ii=0;ii<im_struct.width; ++ii)
			  for(jj=0;jj<im_struct.height;++jj)
			    out_image[im_struct.width*jj +ii] = BackGroundColour;
		      }
		    show_edges(strong_list, out_image);
		    image = out_image;
		  }
	      }
	}
      if(!PostscriptOut &&  !Debug && !OutputListPoints)
	Imsave(image , "",  im_struct.width, im_struct.height) ;
    }
  else
    {
      usage();
      exit(-1);
    }
}




void usage ()
{
  printf("\nfc");
  printf("\n  t - edge threshold for totally rejecting pixel (default %d)",
	 Edge_Thresh);
  printf("\n  k - edge histogram threshold (default %d%%)",(int)K);
  printf("\n  m - minimum length of contour segment to be outputted (default 0)");
  printf("\n  o - overlay edge on original image (default - false)");
  printf("\n  c - make circular histogram of contours (default - false)"); 
  printf("\n  s - smooth circular histogram (default - false)");
  printf("\n  R - rotate circular histogram n degrees (default - 0)");
  printf("\n  e - extend search from end-points (default - false)");
  printf("\n  A - use final edge information to perform averaging of\n      original image (default - false)");
  printf("\n  a - as A above, but followed by a averaging block size (default =3");
  printf("\n  P - postscript output - for circ hist only (default - false)");
  printf("\n  w - weight for water in RS images (default - false)");
  printf("\n  C - see if the contour direction is generally in a certain direction (default - false)");
  printf("\n  x - for C, x range");
  printf("\n  y - for C, y range");
  printf("\n  E - output contours with no more than so many end-points");
  printf("\n  W - put up a Sunview window showing search ");
  printf("\n  p - print out x,y,direction,magnitude of final points in file points.outfile.");
  
  printf ("\n\nusage: %s [-t <thresh>] [-k <hist thresh>] [-m <min out>] \n   [-a <ave.block>] [A] [-o] [-c] [-s] [-R <degrees>] [-w] [P] file\n\n", progname);
}





void DebugInfo()
{
  
  printf("\n\n\n\n\n");
  printf("    *** Debug Values   ***\n\n");
  printf("    5  - print out the joining (in join_lists) of the linking contours.\n");
  printf("         This shows the end points of the contour lists changing as well. Only\n");
  printf("         works if -e (extend) also invoked");

  printf("\n\n\n");
  
}

