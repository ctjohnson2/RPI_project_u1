#include <stdlib.h>
#include <math.h>
#include "z2.hpp"

void Z2GaugeLattice::MoveUp(int x[], int d)
{
    x[d]+=1;
    if (x[d]>=mSize) x[d]-=SIZE; 
    return;
}

void Z2GaugeLattice::MoveDown(int x[], int d)
{
    x[d]-=1;
    if (x[d]<0) x[d]+=mSize;
    return;
}
void Z2GaugeLattice::ColdStart()
{
    int x[4],d;
    for (x[0]=0;x[0]<mSize;x[0]++)
        for (x[1]=0;x[1]<mSize;x[1]++)
            for (x[2]=0;x[2]<mSize;x[2]++)
                for (x[3]=0;x[3]<mSize;x[3]++)
                    for (d=0;d<4;d++)
	                    link[x[0]][x[1]][x[2]][x[3]][d]=1;
    return;    
}

double Z2GaugeLattice::Update(double beta)
{
/* do a Monte Carlo sweep; return energy */
int x[4],d,dperp,staple,staplesum;    
  double bplus,bminus,action=0.0; 
  for (x[0]=0; x[0]<mSize; x[0]++)
    for (x[1]=0; x[1]<mSize; x[1]++)
      for (x[2]=0; x[2]<mSize; x[2]++)
        for (x[3]=0; x[3]<mSize; x[3]++)
          for (d=0; d<4; d++) {
            staplesum=0;
            for (dperp=0;dperp<4;dperp++){
              if (dperp!=d){
                /*  move around thusly:
                    dperp        6--5
                    ^            |  |
                    |            1--4
                    |            |  |
                    -----> d     2--3  */
                /* plaquette 1234 */
                MoveDown(x,dperp);
                staple=link[x[0]][x[1]][x[2]][x[3]][dperp]
                  *link[x[0]][x[1]][x[2]][x[3]][d];
                MoveUp(x,d);
                staple*=link[x[0]][x[1]][x[2]][x[3]][dperp];  
                MoveUp(x,dperp);
                staplesum+=staple;
                /* plaquette 1456 */
                staple=link[x[0]][x[1]][x[2]][x[3]][dperp];
                MoveUp(x,dperp);
                MoveDown(x,d);
                staple*=link[x[0]][x[1]][x[2]][x[3]][d];
                MoveDown(x,dperp);
                staple*=link[x[0]][x[1]][x[2]][x[3]][dperp];
                staplesum+=staple;
              }
	        }
            /* calculate the Boltzmann weight */
            bplus=exp(beta*staplesum);
            bminus=1/bplus;
            bplus=bplus/(bplus+bminus);
            /* the heatbath algorithm */
            if ( drand48() < bplus ){
              link[x[0]][x[1]][x[2]][x[3]][d]=1;
              action+=staplesum;
            }
            else{ 
              link[x[0]][x[1]][x[2]][x[3]][d]=-1;
              action-=staplesum;
            }
          } /* loop on d */
  action /= (mSize*mSize*mSize*mSize*4*6);
  return 1.-action;
}