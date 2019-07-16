#include <iostream>
#include <stdlib.h>
#include "u1.hpp"

/******************************/
int main(int argc, char* argvp[])
{
    double beta, dbeta, action;
    srand48(1234L);  /* initialize random number generator */
  
    /* do your experiment here; this example is a thermal cycle */
    U1GaugeLattice lat;

    dbeta=.01;
    lat.ColdStart();
/*    int confignum = 100;
       // cool it down 
    for (beta=0; beta<1.0; beta+=dbeta){
        action = lat.Update(beta,confignum);
        std::cout << beta << "\t" << action << "\n";
  }
  
    // heat it up 
    for (beta=4; beta>0.0; beta-=dbeta){
        action = lat.Update(beta,confignum);
        std::cout << beta << "\t" << action << "\n";
    }
    std::cout << "\n\n"; 
    // here we will try to run a thermalization
   */ beta = 10.0;
    int confignum = 200;
    
      lat.Update(beta, confignum);
      
    

   
  std::cout << "\n\n";
  return 0;
}
