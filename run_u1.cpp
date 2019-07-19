#include <iostream>
#include <stdlib.h>
#include "u1.hpp"
#include<vector>

/******************************/
int main(int argc, char* argvp[])
{
  double beta, dbeta, percent;
  std::vector<double> out,action;
    srand48(1234L);  /* initialize random number generator */
  
    /* do your experiment here; this example is a thermal cycle */
    U1GaugeLattice lat;
    bool dbg = false;
    dbeta=.01;
    lat.ColdStart();
    if(dbg==true){  
      lat.CountPlaquettes();
    }
    
       // cool it down 
     if(dbg==false){ for (beta=0; beta<20.0; beta+=dbeta){
        action = lat.Update(beta);
        std::cout << beta << "\t" << action[0] << "\n";
  }
  
    // heat it up 
    for (beta=20.0; beta>0.0; beta-=dbeta){
        action = lat.Update(beta);
        std::cout << beta << "\t" << action[0] << "\n";
    }
    std::cout << "\n\n"; } 
    // here we will try to run a thermalization
    /*   if(dbg==false){   beta = 4.0;
    int confignum = 100;
    for(int i=0;i<confignum;i++){

      out = lat.Update(beta);
      double x = lat.MeanPlaquette();
      percent = out[1];
      action = out[0];
      std::cout<<i<<" "<<action<<" "<<std::endl;}
    } */
    

   
  std::cout << "\n\n";
  return 0;
}
