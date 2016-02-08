
#include "stuff.h"

#define AxisColor 128
#define LineColor 0
#define BackGroundColor 255

#define FindXY(len,dir) sincos((dir/57.3),&sind,&cosd);\
                        x = x0 + ((cosd*(float)len)/(float)max)*(xaxissize);\
                        y =  y0 + ((sind*(float)len)/(float)max)*(yaxissize);




#define HistX 600
#define HistY 600
#define Bound 20



MakeCircHist(hist,max)
    int *hist,max;
    {

      extern  int PostscriptOut;
      
        register j,i;

        double dir,sind,cosd;
       
        int getopt(),ch,
            x0,y0,
            x,y,
            lastx,lasty,
            firstx,firsty,
            len,
            xaxissize,yaxissize;
	
	byte *hist_image; 


        if(PostscriptOut)
            {
            printf("\n%%! ");
            printf("\n 305 396 translate ");
            printf("\n  90 rotate ");
          
            xaxissize = HistX/2;;
            yaxissize = HistY/2;
            x0 = 0;
            y0 = 0;
            }
        else
            {
            hist_image = (byte *) malloc( sizeof (byte) *  HistX * HistY ) ;
            for (j = 0; j < HistX*HistY; ++j )
                hist_image[j] = BackGroundColor;
            
            x0 = HistX/2;
            y0 = HistX/2;

            xaxissize = x0- Bound;
            yaxissize = y0 - Bound;

            rline(hist_image,Bound,y0, HistX - Bound, y0, AxisColor, 
		  HistX, HistY);
            rline(hist_image, x0,Bound,x0,HistY- Bound, AxisColor, 
		  HistX, HistY);
            }

        FindXY(hist[0],0);
        firstx = x;
        firsty = y;
        lastx = x;
        lasty = y;

        if(PostscriptOut)
            {
            printf("\n newpath ");
            printf("\n %d %d moveto",x,y);
            }
        
        for(i=0; i<360; ++i)
            {
            FindXY(hist[i],i);
            if(x>max || y>max)
	      {
		printf("\n\n %d %d %d ",x,y,max);
	      }
	    
            if(PostscriptOut)
                printf("\n %d %d lineto",x,y);
            else                
                rline(hist_image,x,y,lastx,lasty,LineColor,HistX,HistY);
            lastx = x;
            lasty = y;
            } 
        if(PostscriptOut)
            {
/*
            printf("\n %d %d lineto ", firstx,firsty);
            printf("\n 0 setlinewidth ");
*/
            printf("\n closepath");
            printf("\n 0.5 setgray ");
            printf("\n fill ");
/*
            printf("\n stroke");
*/

            MakePostscriptAxes(xaxissize,yaxissize);
            printf("\n showpage \n");
            }
        else
            {
            rline(hist_image,firstx,firsty,lastx,lasty,LineColor,HistX,HistY);
            Imsave( hist_image, "", HistX,HistY) ;
            }
}


MakePostscriptAxes(x,y)
int x,y;
{
    printf("\n  /axes ");
    printf("\n  {newpath ");
    printf("\n  0 setgray ");
    printf("\n  1 setlinewidth ");
    printf("\n  %d 0 moveto ",-x);
    printf("\n  %d 0  lineto ",x);
    printf("\n  0 %d moveto ",y);
    printf("\n  0 %d lineto",-y);
    printf("\n  stroke}def ");
    printf("\n  axes ");
    printf("\n  /Helvetica findfont 30 scalefont setfont");
    printf("\n  -11 260 moveto");
    printf("\n  (N) show");
    
}

