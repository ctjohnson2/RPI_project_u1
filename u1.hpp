#ifndef U1HEADERDEF
#define U1HEADERDEF



class U1GaugeLattice
{
public:
    /* the lattice is of dimensions SIZE**2  */
  
    double link[6][6][2]; /* last index gives link direction */
  //int ensem[SIZE][SIZE][SIZE][SIZE][4][confignum];
    void MoveUp(int x[],int d);
    void MoveDown(int x[], int d);
    void ColdStart();
    void RandomStart();
  std::vector<double> Update(double beta);
  int CountPlaquettes();
private:
    
}; 

#endif
