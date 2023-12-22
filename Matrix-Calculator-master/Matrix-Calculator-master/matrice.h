#ifndef MATRICE_H
#define MATRICE_H
#include <iostream>
#include <vector>
#include <time.h> //usata per generare numeri casuali
#include <math.h>
#include <eccezioni.h>

using std::vector;
using std::cout;
using std::endl;

class matrice{
private:
  int r;
  int c;
  vector<int> pos;
public:
  matrice(int y=0, int x=0, int d=0);
  virtual matrice& operator=(const matrice&);//ridefinito per matrice binaria
  virtual ~matrice() {}
  int read(int y=0, int x=0) const;//ritorna il valore in posizione (x,y)
  int& ref(int y=0,int x=0);//ritorna la posizione (x,y)
  virtual void stampa() const;
  bool sizeEqual(const matrice&) const;//ritorna true se le due matrici hanno le stesse dimensioni
  virtual matrice& operator+(const matrice&);
  virtual matrice& operator-(const matrice&);
  virtual matrice& operator*(const matrice&);
  bool operator==(const matrice&) const;
  bool operator!=(const matrice&) const;
  void writeAll(int n=0);
  virtual void writeAllRandom(int min=0,int max=9);
  void trasposta();
  virtual void reverse();//non calcola l'inversa della matrice ma equivale a moltiplicare per -1
  int getColumns() const;
  int getRows() const;
  matrice copy(matrice t, int yd=0, int xd=0, int yt=0, int xt=0,int sizey=0, int sizex=0);//copia d in *this a partire da specifiche coordinate
  void swap(int y1=0, int x1=0, int y2=0, int x2=0, int sizey=1,int sizex=1);//scambia due aree di una matrice di una certa dimensione
  virtual matrice* clone() const;
  int max() const;//ritornano il numero massimo e minimo nella matrice
  int min() const;
  int mostRepeated() const;//ritorna il valore che compare più volte all'interno della matrice escludendo lo 0
};

#endif // MATRICE_H
