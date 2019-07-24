#include <iostream>
#include <stdlib.h>
#include "u1.hpp"
#include<vector>

/******************************/
int sizee = 192;
int main(int argc, char* argvp[])
{
  double beta, dbeta, percent;
  std::vector<int> out;
  double action, action2;
    srand48(1234L);  /* initialize random number generator */
  
    /* do your experiment here; this example is a thermal cycle */
    U1GaugeLattice lat;
    Z2GaugeLattice lat2;
    bool dbg = false;
    bool heatcycle = true;
    bool therm = false;
    dbeta=.01;
    lat.ColdStart();
    if(dbg==true){ int A=1e4;
      for(int i=0;i<A;i++){
	lat.Update(5.0);
	action = lat.Action(5.0);
	action /=(sizee*sizee);
	if(i%200==0){std::cout<< action<<std::endl;}
      }
     
    }
    
       // cool it down 
      if(dbg==false && heatcycle == true){ for (beta=0.0; beta<10.0; beta+=dbeta){
        lat.Update(beta);
	action = lat.Action(beta);
	action = action/(sizee*sizee);
	action*=beta;
        std::cout << beta << "\t" << action << "\n";
  }
  
    // heat it up 
    for (beta=10.0; beta>0.0; beta-=dbeta){
      lat.Update(beta);
        action = lat.Action(beta);
	action = action/(sizee*sizee);
	action*=beta;
        std::cout << beta << "\t" << action<< "\n";
    }
    std::cout << "\n\n"; } 
    // here we will try to run a thermalization
      if(dbg==false && therm ==true){   beta = 5.0;double block[5];
	int N[5];
	for(int j=0;j<5;j++){N[j]=0;
	  block[j]=0.0;}
	   int confignum = 5e4;
	   double Z=0.0;
	   double plaq = 0.0;
	   std::complex<double> num = std::complex<double>(0.0,0.0);
	   std::complex<double> denum = std::complex<double>(0.0,0.0);
	   for(int i=0;i<confignum;i++){

       lat.Update(beta);
      double action = lat.Action(beta);
      action/=(sizee*sizee);
      
	   
      //action = action/(sizee*sizee);
    
      if(i%100==0 && i >2000){std::cout<<i<<" "<<real(lat.WilsonLoop(30,30,1,1))<<std::endl;
	double rand = drand48()*5.0;
	if(rand<1){block[0]+=real(lat.WilsonLoop(30,30,5,2));N[0]++;}
	if(rand<2 && rand >= 1){block[1]+=real(lat.WilsonLoop(30,30,5,2));N[1]++;}
	if(rand<3 && rand >= 2){block[2]+=real(lat.WilsonLoop(30,30,5,2));N[2]++;}
	if(rand<4 && rand >= 3){block[3]+=real(lat.WilsonLoop(30,30,5,2));N[3]++;}
	if(rand >= 4){block[4]+=real(lat.WilsonLoop(30,30,5,2));N[4]++;}
	//else{block[1]+=real(lat.Plaquette(6,6));N[1]++;}
      }
	  
	   }
	   double n[5];
	   for(int i=0;i<5;i++){n[i]=(double)N[i];}
	   for(int i=0;i<5;i++){
	     std::cout<<block[i]/n[i]<<" "<<N[i]<<std::endl;}
	    /*	   lat.ColdStart();

	   double err = 0.0;
	 
	   	   for(int i=0;i<confignum;i++){

      out = lat.Update(beta);
      double action = lat.Action(beta);
      action/=(sizee*sizee);
      
	   
      //action = action/(sizee*sizee);
      
      if(i%200==0 && i >1500){err+=pow(real(lat.Plaquette(6,6))-(plaq/n),2);
	std::cout<<i<<std::endl;
	
      }
	  
	}
	std::cout<<plaq/n<<" "<<sqrt(err/(n-1.0))<<std::endl; */
	   
	/*
      
      lat.ColdStart(); 
       for(int i=0;i<confignum;i++){out = lat.Update(beta);
      double action = lat.Action(beta);
      action/=sizee*sizee;
      if(i%50==0 &&i >50){denum+=lat.WilsonLoop(6,6,2,7);
		std::cout<<lat.WilsonLoop(6,6,2,7)<<std::endl;
	num+=lat.WilsonLoop(6,6,2,8); } }
    double n = (double)N;
    //  std::cout<< num/n<<std::endl;
    //   std::cout<<denum/n<<std::endl;
    lat.ColdStart();
    std::complex<double> errnu  = std::complex<double>(0.0,0.0);
    std::complex<double> errde  = std::complex<double>(0.0,0.0);
    for(int i=0;i<confignum;i++){out = lat.Update(beta);
      double action = lat.Action(beta);
      action/=sizee*sizee;
      if(i%50==0 &&i >50){errnu+=pow((real(lat.WilsonLoop(6,6,2,8)))-real(num/n),2);
	errde+=pow((real(lat.WilsonLoop(6,6,2,7)))-real(denum/n),2);} }
    
    errnu/=(N-1);
    
    errde/=(N-1);
    //   std::cout<<sqrt(errnu)<<std::endl;
    //   std::cout<<sqrt(errde)<<std::endl;
    
    */
       }
       
    

   
  std::cout << "\n\n";
  return 0;
}

