#ifndef U1HEADERDEF
#define U1HEADERDEF
#include <complex>


class U1GaugeLattice
{
public:
    /* the lattice is of dimensions SIZE**2  */
  
    double link[192][192][2]; /* last index gives link direction */
  //int ensem[SIZE][SIZE][SIZE][SIZE][4][confignum];
    void MoveUp(int x[],int d);
    void MoveDown(int x[], int d);
    void ColdStart();
    void RandomStart();
  void PrintLattice();
  std::vector<int> Update(double beta);
  // double MeanPlaquette();
  std::complex<double> Plaquette(int x, int y);
  double Action(double beta);
  std::complex<double> WilsonLoop(int start_y, int start_t, int y, int t);
 
  
  
  int CountPlaquettes();
private:
    
};
class Z2GaugeLattice
{
public:
  double link[48][48][2];
  void MoveUp(int x[],int d);
  void MoveDown(int x[], int d);
  double Update(double beta);
  double Plaquette(int x, int y);
  double Action(double beta);
private:
};

#endif
