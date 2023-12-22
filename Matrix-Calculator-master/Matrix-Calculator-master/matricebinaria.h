#ifndef MATRICEBINARIA_H
#define MATRICEBINARIA_H
#include "matrice.h"

class matriceBinaria: public matrice{
public:
  class casella{ //questa classe serve solo per memorizzare il percorso migliore del labirinto
  public:
    int y;
    int x;
    casella(int r=0,int c=0): y(r),x(c) {}
  };
private:
  //QUESTE FUNZIONI SONO USATE PER RISOLVERE IL LABIRINTO
  static bool fine_lab(int y,int x,int ye,int xe);
  static bool bloccato(const matrice& m,int y,int x);
  static bool is_best_path(const vector<matriceBinaria::casella>& p,int y,int x);
  static bool risolvi_lab(matrice& m,int y,int x,int ye,int xe,int &minmosse,vector<matriceBinaria::casella>& p,int mosse=0);
public:
  matriceBinaria(int y=0,int x=0, int d=0);
  matriceBinaria(const matrice& m): matrice(m) {aggiusta();}
  matriceBinaria& operator=(const matrice&);
  matriceBinaria& operator+(const matrice&);
  matriceBinaria& operator-(const matrice&);
  matriceBinaria& operator*(const matrice&);
  void writeAllRandom();//non ereditata da matrice ma funzione nuova perchà cambiati i parametri
  void reverse();
  virtual matriceBinaria aggiusta();
  vector<casella> labirinto(int ys=0,int xs=0,int ye=0,int xe=0) const;//trova un percorso per muoversi dal punto s(y,x) al punto e(y,x), ritorna false se il percorso non esiste
  matriceBinaria* clone() const;
};

#endif // MATRICEBINARIA_H
