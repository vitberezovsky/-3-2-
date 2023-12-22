#ifndef MATRICEQUADRATA_H
#define MATRICEQUADRATA_H
#include "matrice.h"

class matriceQuadrata: public matrice{
private:
  static bool check_full(const matriceQuadrata&);
  static bool check_sudoku(const matriceQuadrata&);
  static bool risolvi_sudoku(matriceQuadrata&);
  static matriceQuadrata quadratoMagicoDispari(matriceQuadrata);
  static matriceQuadrata quadratoMagicoPari(matriceQuadrata);
  static matriceQuadrata quadratoMagicoPariDiv4(matriceQuadrata);
public:
  matriceQuadrata(int x=0, int d=0);
  matriceQuadrata& operator+(const matrice&);
  matriceQuadrata& operator-(const matrice&);
  matriceQuadrata& operator*(const matrice&);
  matriceQuadrata sudoku();//riempie tutti gli spazi con le regole del sudoku
  matriceQuadrata quadratoMagico();//riempie tutti gli spazi con le regole del quadrato magico (solo per grandezza >2)
  matriceQuadrata* clone() const;
};

#endif // MATRICEQUADRATA_H
