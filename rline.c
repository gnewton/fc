   
#include "stuff.h"


int rline(image, xa,ya,xb,yb, intensity,x_axis_size, y_axis_size)

byte *image;

int xa,ya,xb,yb,intensity,
  x_axis_size, 
  y_axis_size;


{

    int dx,dy,
        adx,ady,
        pos_slope,
        c,r,f,g,
        inc1,inc2,
        n;

    ya = abs(ya - y_axis_size);
    yb = abs(yb - y_axis_size);

    dx = xb - xa;
    dy = yb - ya;
   
    adx = abs(dx);
    ady = abs(dy);

    if(dx > 0)
        pos_slope = TRUE;
    else
        pos_slope = FALSE;
    if(dy<0)
        if(pos_slope)
            pos_slope = FALSE;
        else
            pos_slope = TRUE;

    /* check to see if it is a gentle slope */ 
    if(adx > ady)
        {
        if(dx > 0)
            {
            c = xa;
            r = ya;
            f = xb;
            }
        else
            {
            c = xb;
            r = yb;
            f = xa;
            }
        inc1 = ady + ady;
        g = ady + ady - adx;
        inc2 = 2 * (ady-adx);
        if(pos_slope)
           {
           while(c <= f)
               {
               n = r *  x_axis_size + c;
               image[n] = intensity;
               ++c;
               if(g>=0)
                  {
                  ++r;
                  g += inc2;
                  }
              else
                  g += inc1;
              }
          }
      else
          {
          while(c <= f)
              {
               n = r *  x_axis_size + c; 
               image[n] = intensity; 
               ++c;
               if(g>0)
                   {
                   --r;
                   g += inc2;
                   }
               else
                   g += inc1;
               }
           }
       }
    else
        {
        if(dy > 0)
            {
            c = ya;
            r = xa;
            f = yb;
            }
        else 
            {
            c = yb;
            r = xb;
            f = ya;
            }
        inc1 = adx + adx;
        g = adx + adx - ady;
        inc2 = 2 * (adx-ady);
        if(pos_slope)
           {
           while(c <= f)
               {
               n = c *  x_axis_size + r;
               image[n] = intensity;
               ++c;
               if(g>=0)
                  {    
                  ++r;
                  g += inc2;
                  }
              else 
                  g += inc1;
              }
          }    
      else 
          {
          while(c <= f)
              {
               n = c *  x_axis_size + r;
               image[n] = intensity;
               ++c;
               if(g>0)
                   {  
                   --r;
                   g += inc2;
                   }
               else 
                   g += inc1;
               }
           }    
       }    
    }
                
