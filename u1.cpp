#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include "u1.hpp"
#include<vector>

int size = 16;
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
  
	  //     for (x[3]=0;x[3]<mSize;x[3]++)
                    for (d=0;d<3;d++)
	                    link[x[0]][x[1]][d]=1;
    return;    
}
void U1GaugeLattice::RandomStart()
{
  U1GaugeLattice::ColdStart();
  U1GaugeLattice::Update(0.0);
  
}
void U1GaugeLattice::PrintLattice()
  {
    int x[2],d;
    for (x[0]=0;x[0]<size;x[0]++)
        for (x[1]=0;x[1]<size;x[1]++)
            
	  //     for (x[3]=0;x[3]<mSize;x[3]++)
                    for (d=0;d<2;d++)
		      std::cout<<"ijkd "<<x[0]<<x[1]<<x[2]<<d<<" "<<link[x[0]][x[1]][d]<<std::endl;
    return;    
}

int U1GaugeLattice::CountPlaquettes(){
  int x[2],d,dperp;
  int count = 0;
  for (x[0]=0; x[0]<size; x[0]++){
    for (x[1]=0; x[1]<size; x[1]++){
      
          
	count++;}}
  return count;}

std::complex<double> U1GaugeLattice::Plaquette(int x, int y)
{
  
  std::complex<double> plaq = exp(std::complex<double> (0.0,(link[x][y][0]+link[(x+1)%size][y][1]-(link[x][(y+1)%size][0])-(link[x][y][1]) ) ) );
  return plaq;}

double U1GaugeLattice::Action(double beta){
  double action = 0.0;
  
  for(int i=0;i<size;i++){
    for(int j =0;j<size;j++){
     
	action -= real(Plaquette(j,i));
      action +=1.0;
    }
  }
  

 
  // action*=beta;
  return action;
      
      
}
//330 340 351 451 440 430 3

std::complex<double> U1GaugeLattice::WilsonLoop(int start_y, int start_t, int y, int t){
  int x[2];
  std::complex<double> total = std::complex<double>(1.0,0.0);
  for(x[0]=0;x[0]<t;x[0]++){
    int index_t = x[0]+start_t;
    int index_y= start_y;
    total*=exp(std::complex<double>(0.0,link[index_t][index_y][0]) );
    //  std::cout<<index_t<<index_y<<std::endl;
  }
  for(x[1]=0;x[1]<y;x[1]++){
    int index_t = t+start_t;
    int index_y= x[1]+start_y;
    total*=exp(std::complex<double>(0.0,link[index_t][index_y][1]) );
    //  std::cout<<index_t<<index_y<<std::endl;
  }

  for(x[0]=0;x[0]<t;x[0]++){
    int index_t = t+start_t-x[0]-1;
    int index_y= y+start_y;
    total*=exp(std::complex<double>(0.0,-link[index_t][index_y][0]) );
    //  std::cout<<index_t<<index_y<<std::endl;
  }

  for(x[1]=0;x[1]<y;x[1]++){
    int index_t = start_t;
    int index_y= y+start_y-x[1]-1;
    total*=exp(std::complex<double>(0.0,-link[index_t][index_y][1]) );
    // std::cout<<index_t<<index_y<<std::endl;
  }
    
  return total;
  }
std::vector<int> U1GaugeLattice::Update(double beta)
{
/* do a Monte Carlo sweep; return energy */
  // std::cout<<"starting..."<<std::endl;
  int x[2],d,dperp;
  std::vector<int> output;
  double stapleangle,angle1sum,angle2sum;    
  double bplus,bminus,action=0.0;
  int count,accept=0;
  bool dbg =false;
  for (x[0]=0; x[0]<size; x[0]++)
    for (x[1]=0; x[1]<size; x[1]++)
          for (d=0; d<2; d++) {
         
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
		//	std::cout<<x[0]<<x[1]<<dperp<<std::endl;
		//	std::cout<<x[0]<<x[1]<<d<<std::endl;
                stapleangle= -link[x[0]][x[1]][dperp]+link[x[0]][x[1]][d];
                MoveUp(x,d);
		//	std::cout<<x[0]<<x[1]<<dperp<<std::endl;
                stapleangle+=link[x[0]][x[1]][dperp];  
                MoveUp(x,dperp);
                angle1sum=stapleangle;
                /* plaquette 1456 */
                stapleangle=link[x[0]][x[1]][dperp];
                MoveUp(x,dperp);
                MoveDown(x,d);
                stapleangle-=link[x[0]][x[1]][d];
                MoveDown(x,dperp);
                stapleangle-=link[x[0]][x[1]][dperp];
                angle2sum=stapleangle;
		//	if(dbg){std::cout<<"staplesum "<<staplesum<<std::endl;}
              }
	        }
        

	     // Metropolis step
	    if(true){
	      double rando = drand48()*2.0*pi;
	      double theta = link[x[0]][x[1]][d];
	      double weight = 0.1;
	      double link_new =abs(weight*rando+theta);
	   
	      double delta_s = beta*(-cos(-link_new+angle1sum) -cos(link_new+angle2sum) +cos(theta-angle1sum)+cos(theta+angle2sum));
	    if(dbg){std::cout<<"prob "<<exp(-delta_s)<<std::endl;}
	    
	      double p_accept = fmin(1.0, exp(-delta_s));
	      double draw = drand48(); 
	      if( draw < p_accept){accept++;
	    // Accept: keep this sample
		  link[x[0]][x[1]][d] = link_new;
	      } count++;
	      
		  // Reject: overwrite proposed state with last samplepass
	      
	       }//metropolis if
	    //std::cout<<cos(link[x[0]][x[1]][d]-angle1sum)<<" "<<cos(link[x[0]][x[1]][d]+angle2sum)<<std::endl;
	    action+=cos(link[x[0]][x[1]][d]-angle1sum);
	    //action+=cos(link[x[0]][x[1]][d]+angle2sum);
	      
	      
          } /* loop on d */

  

  action/=(size*size*2);
  double ratio = (double)accept/count;
  output.push_back(count);
  output.push_back(accept);
  output.push_back(2.0-action);
 
  if(dbg){std::cout<<"accepted "<<output[0]<<" count "<<output[1]<<std::endl;}
  return output;
 
}

      


