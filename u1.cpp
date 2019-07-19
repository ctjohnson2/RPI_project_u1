#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "u1.hpp"
#include<vector>

int size = 6;
const double pi = 3.14159265358979323846;
// return type vector

void U1GaugeLattice::MoveUp(int x[], int d)
{
    x[d]+=1;
    if (x[d]>=size) x[d]-=size; 
    return;
}

void U1GaugeLattice::MoveDown(int x[], int d)
{
    x[d]-=1;
    if (x[d]<0) x[d]+=size;
    return;
}
void U1GaugeLattice::ColdStart()
{
    int x[2],d;
    for (x[0]=0;x[0]<size;x[0]++)
        for (x[1]=0;x[1]<size;x[1]++)
          //  for (x[2]=0;x[2]<mSize;x[2]++)
	  //     for (x[3]=0;x[3]<mSize;x[3]++)
                    for (d=0;d<2;d++)
	                    link[x[0]][x[1]][d]=1;
    return;    
}

int U1GaugeLattice::CountPlaquettes(){
  int x[2],d,dperp;
  int count = 0;
  for (x[0]=0; x[0]<size; x[0]++){
    for (x[1]=0; x[1]<size; x[1]++){
          for (d=0; d<2; d++) {
            for (dperp=0;dperp<2;dperp++){std::cout<<count<<std::endl;
	      count++;}}}}
  return count;}
  

std::vector<double> U1GaugeLattice::Update(double beta)
{
/* do a Monte Carlo sweep; return energy */
  // std::cout<<"starting..."<<std::endl;
  int x[2],d,dperp;
  std::vector<double> output;
  double staple,staplesum;    
  double bplus,bminus,action=0.0;
  int count,accept=0;
  bool dbg =false;
  for (x[0]=0; x[0]<size; x[0]++)
    for (x[1]=0; x[1]<size; x[1]++)
          for (d=0; d<2; d++) {
            staplesum=0;
            for (dperp=0;dperp<2;dperp++){
              if (dperp!=d){

		if(dbg){std::cout<<"x0= "<<x[0]<<" x1= "<<x[1]<<" d= "<<d<<" dperp= "<<dperp<<std::endl;}
                /*  move around thusly:
                    dperp        6--5
                    ^            |  |
                    |            1--4
                    |            |  |
                    -----> d     2--3  */
                /* plaquette 1234 */
                MoveDown(x,dperp);
                staple=link[x[0]][x[1]][dperp]
                  *link[x[0]][x[1]][d];
                MoveUp(x,d);
                staple*=link[x[0]][x[1]][dperp];  
                MoveUp(x,dperp);
                staplesum+=staple;
                /* plaquette 1456 */
                staple=link[x[0]][x[1]][dperp];
                MoveUp(x,dperp);
                MoveDown(x,d);
                staple*=link[x[0]][x[1]][d];
                MoveDown(x,dperp);
                staple*=link[x[0]][x[1]][dperp];
                staplesum+=staple;
		if(dbg){std::cout<<"staplesum "<<staplesum<<std::endl;}
              }
	        }
            /* calculate the Boltzmann weight */
	    //        bplus=exp(beta*staplesum);
		//     bminus=1/bplus;
	    //     bplus=bplus/(bplus+bminus);
	    // if(dbg){std::cout<<"bplus " << bplus << std::endl;}
	    //std::cout<<"Betaboltz "<<bplus<<std::endl;
	     // the heatbath algorithm 
	    /*      if ( drand48() < bplus ){
              link[x[0]][x[1]][d]=1;
              action+=staplesum;
            }
            else{ 
              link[x[0]][x[1]][d]=-1;
              action-=staplesum;
	      } */

	     // Metropolis step
	    if(true){
	      double rando = drand48()*2.0*pi;
	      double theta = acos(link[x[0]][x[1]][d]);
	      double weight = 0.3;
	      double link_new = cos((weight*rando+theta));
            double delta_s = beta*staplesum*(link_new - link[x[0]][x[1]][d]);
	    if(dbg){std::cout<<"prob "<<exp(-delta_s)<<std::endl;}
	    
	      double p_accept = fmin(1.0, exp(-delta_s));
	      double draw = drand48(); 
	      if( draw < p_accept){accept++;
	    // Accept: keep this sample
		  link[x[0]][x[1]][d] = link_new;
	      } count++;
	      
		  // Reject: overwrite proposed state with last samplepass

		  action += staplesum*link[x[0]][x[1]][d]; }//metropolis if
	    
	    if(dbg){std::cout<<"action " << action<< std::endl;}
          } /* loop on d */
  action /= (size*size*4*6);
  output.push_back(1.-action);
  double ratio = (double)accept/count;
  output.push_back(ratio);
  if(dbg){std::cout<<"act "<<output[0]<<" ratio "<<output[1]<<std::endl;}
  return output;
 
}
