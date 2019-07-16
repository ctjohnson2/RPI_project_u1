#ifndef U1HEADERDEF
#define U1HEADERDEF

#define SIZE 12

class U1GaugeLattice
{
public:
    /* the lattice is of dimensions SIZE**2  */

    int link[SIZE][SIZE][4]; /* last index gives link direction */
  //int ensem[SIZE][SIZE][SIZE][SIZE][4][confignum];
    void MoveUp(int x[],int d);
    void MoveDown(int x[], int d);
    void ColdStart();
    void RandomStart();
  double Update(double beta, int confignum);
private:
    int mSize = SIZE;
}; 

#endif
