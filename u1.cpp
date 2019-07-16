#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "u1.hpp"


void U1GaugeLattice::MoveUp(int x[], int d)
{
    x[d]+=1;
    if (x[d]>=mSize) x[d]-=SIZE; 
    return;
}

void U1GaugeLattice::MoveDown(int x[], int d)
{
    x[d]-=1;
    if (x[d]<0) x[d]+=mSize;
    return;
}
void U1GaugeLattice::ColdStart()
{
    int x[4],d;
    for (x[0]=0;x[0]<mSize;x[0]++)
        for (x[1]=0;x[1]<mSize;x[1]++)
                    for (d=0;d<4;d++)
	                    link[x[0]][x[1]][d]=1;
    return;    
}


double U1GaugeLattice::Update(double beta, int confignum)
{
/* do a Monte Carlo sweep; return energy */
int x[4],d,dperp,staple,staplesum;
 int ensem[SIZE][SIZE][4][confignum];

 double bplus,bminus,action,plaquette=0.0;
   int count = 0;
   for(int i =0; i<confignum; i++){
  for (x[0]=0; x[0]<mSize; x[0]++)
    for (x[1]=0; x[1]<mSize; x[1]++)
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
		//saving links
		       	ensem[x[0]][x[1]][dperp][i] = link[x[0]][x[1]][dperp];
			ensem[x[0]][x[1]][d][i] = link[x[0]][x[1]][d];
                staple=link[x[0]][x[1]][dperp]
                  *link[x[0]][x[1]][d];
                MoveUp(x,d);
			ensem[x[0]][x[1]][dperp][i] = link[x[0]][x[1]][dperp];
                staple*=link[x[0]][x[1]][dperp];  
                MoveUp(x,dperp);
                staplesum+=staple;
                /* plaquette 1456 */
			ensem[x[0]][x[1]][dperp][i] = link[x[0]][x[1]][dperp];
                staple=link[x[0]][x[1]][dperp];
                MoveUp(x,dperp);
                MoveDown(x,d);
				ensem[x[0]][x[1]][d][i]=link[x[0]][x[1]][d];
                staple*=link[x[0]][x[1]][d];
                MoveDown(x,dperp);
				ensem[x[0]][x[1]][dperp][i] = link[x[0]][x[1]][dperp];
                staple*=link[x[0]][x[1]][dperp];
                staplesum+=staple;
              }
	        }
            /* calculate the Boltzmann weight */
	    // std::cout<<"stapelsum " << staplesum << std::endl;
            bplus=exp(beta*staplesum);
            bminus=1/bplus;
            bplus=bplus/(bplus+bminus);
            /* the heatbath algorithm */
	    bool bath = true;
	    if(bath == false){
            if ( drand48() < bplus ){
              link[x[0]][x[1]][d]=1;
              action+=staplesum;
            }
            else{ 
              link[x[0]][x[1]][d]=-1;
              action-=staplesum;
            }
	    }
	    // Metropolis step
	    if(true){
	    double rando = drand48()*2.0 -1.0;
	    int link_new= 0;
	    if(rando>0){link_new+=1;}
	    else{link_new-=1;}
            double delta_s = beta*staplesum*(link_new - link[x[0]][x[1]][d]);


	      double p_accept = fmin(1.0, exp(-delta_s));
	      double draw = drand48(); 
	      if( draw < p_accept){
	    // Accept: keep this sample
		  link[x[0]][x[1]][d] = link_new;
		  count++;}
	      
		  // Reject: overwrite proposed state with last samplepass

		  plaquette += staplesum*link[x[0]][x[1]][d]; }//metropolis if
          } /* loop on d */
  action /= (mSize*mSize*4.*6.);
  action = 1. -action;
  plaquette /= (mSize*mSize*4.*6.);
   plaquette = 1. - plaquette;
   
   std::cout <<i<<" "<<plaquette<<"\n";
  }
  //std::cout << "number accepted "<< count << std::endl;
  //return action;
}
