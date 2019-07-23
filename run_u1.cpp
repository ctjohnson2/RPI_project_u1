#include <iostream>
#include <stdlib.h>
#include "u1.hpp"
#include<vector>

/******************************/
int sizee = 16;
int main(int argc, char* argvp[])
{
  double beta, dbeta, percent;
  std::vector<int> out;
    double action;
    srand48(1234L);  /* initialize random number generator */
  
    /* do your experiment here; this example is a thermal cycle */
    U1GaugeLattice lat;
    bool dbg = false;
    bool heatcycle = false;
    bool therm = true;
    dbeta=.01;
    lat.RandomStart();
    if(dbg==true){ lat.Update(0.5);
     
     
    }
    
       // cool it down 
      if(dbg==false && heatcycle == true){ for (beta=0.0; beta<5.0; beta+=dbeta){
        lat.Update(beta);
	action = lat.Action(beta);
	action = action/(sizee*sizee);
        std::cout << beta << "\t" << action << "\n";
  }
  
    // heat it up 
    for (beta=5.0; beta>0.0; beta-=dbeta){
      lat.Update(beta);
        action = lat.Action(beta);
	action = action/(sizee*sizee);
        std::cout << beta << "\t" << action<< "\n";
    }
    std::cout << "\n\n"; } 
    // here we will try to run a thermalization
      if(dbg==false && therm ==true){   beta = 0.5;
	 int N=0;
	   int confignum = 1e5;
	   double Z=0.0;
	   double plaq = 0.0;
	   std::complex<double> num = std::complex<double>(0.0,0.0);
	   std::complex<double> denum = std::complex<double>(0.0,0.0);
	   for(int i=0;i<confignum;i++){

       lat.Update(beta);
      double action = lat.Action(beta);
      action/=(sizee*sizee);
      
	   
      //action = action/(sizee*sizee);
      
      if(i%20==0 && i >50){plaq+=real(lat.Plaquette(2,2));N++;
      }
	  
	   }
	      double n = (double)N;
	    std::cout<<plaq/n<<" "<<N<<std::endl;
	   lat.ColdStart();

	   double err = 0.0;
	 
	   	   for(int i=0;i<confignum;i++){

      out = lat.Update(beta);
      double action = lat.Action(beta);
      action/=(sizee*sizee);
      
	   
      //action = action/(sizee*sizee);
      
      if(i%20==0&& i >50){err+=pow(real(lat.Plaquette(2,2))-(plaq/n),2);std::cout<<err<<std::endl;
	//std::cout<<plaq<<std::endl;
      }
	  
	}
	std::cout<<sqrt(err/(n-1.0))<<std::endl; 
	   
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

