#include "matrice.h"

//MATRICE
matrice::matrice(int y, int x, int d): r(y),c(x) {
  for(int i=0;i<x*y;i++)
    pos.push_back(d);
}

int matrice::read(int y, int x) const{
  return pos[y*c+x];
}

int& matrice::ref(int y,int x){
  return pos[y*c+x];
}

void matrice::stampa() const{
  for(int i=0;i<r;i++){
    for(int j=0;j<c;j++)
        cout<<read(i,j)<<"  ";
    cout<<endl;
  }
}

bool matrice::sizeEqual(const matrice& m) const{
  return c==m.c && r==m.r;
}

matrice& matrice::operator=(const matrice& m){
  if(this!=&m){
    c=m.c;
    r=m.r;
    pos=m.pos;
  }
  return *this;
}

matrice& matrice::operator+(const matrice& m){
  matrice* x=new matrice(*this);
  if(!sizeEqual(m))
    throw errSize();
  for(int i=0;i<getRows();i++)
    for(int j=0;j<getColumns();j++)
      x->ref(i,j)+=m.read(i,j);
  return *x;
}

matrice& matrice::operator-(const matrice& m){
    matrice* x=new matrice(*this);
    if(!sizeEqual(m))
      throw errSize();
    for(int i=0;i<getRows();i++)
      for(int j=0;j<getColumns();j++)
        x->ref(i,j)-=m.read(i,j);
    return *x;
}

matrice& matrice::operator*(const matrice& m){
  matrice* ris=new matrice(getRows(),m.getColumns());
  if(!(getColumns()==m.getRows() && getRows()==m.getColumns()))
    throw errSizeProd();
  for(int i=0;i<ris->getRows();i++)
    for(int j=0;j<ris->getColumns();j++){
      int somma=0;
      for(int k=0;k<getColumns();k++)
        somma+=read(i,k)*m.read(k,j);
      ris->ref(i,j)=somma;
    }
  return *ris;
}

bool matrice::operator==(const matrice& m) const{
  if(!sizeEqual(m))
    return false;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      if(read(i,j)!=m.read(i,j))
        return false;
  return true;
}

bool matrice::operator!=(const matrice& m) const{
  return !(*this==m);
}

void matrice::writeAll(int n){
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      ref(i,j)=n;
}

void matrice::writeAllRandom(int min,int max) {
  srand(time(NULL));
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      ref(i,j)=rand()%(max+1-min)+min;
}

void matrice::trasposta(){
  matrice t(*this);
  int temp=r;
  r=c;
  c=temp;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      ref(i,j)=t.read(j,i);
}

void matrice::reverse(){
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      ref(i,j)=-read(i,j);
}

int matrice::getColumns() const{
  return c;
}
int matrice::getRows() const{
  return r;
}

void matrice::swap(int y1, int x1, int y2, int x2, int sizey, int sizex){
  if(y1<0 || y1>=getRows() || x1<0 || x1>=getColumns() || y2<0 || y2>=getRows() || x2<0 || x2>=getRows() || sizey<0 || sizex<0)
    return;
  matrice temp(*this);
  copy(temp,y1,x1,y2,x2,sizey,sizex);
  copy(temp,y2,x2,y1,x1,sizey,sizex);
}

matrice matrice::copy(matrice t, int yd, int xd, int yt, int xt, int sizey, int sizex){
  if(yd<0 || yd>=getRows() || xd<0 || xd>=getColumns() || yt<0 || yt>=t.getRows() || xt<0 || xt>=t.getRows() || sizey<0 || sizex<0)
    return *this;
  if(sizey==0)sizey=t.getRows();
  if(sizex==0)sizex=t.getColumns();
  for(int i=0;i+yd<getRows() && i<sizey;i++)
    for(int j=0;j+xd<getColumns() && j<sizex;j++)
      ref(yd+i,xd+j)=t.read(yt+i,xt+j);
  return *this;
}

matrice* matrice::clone() const {
  return new matrice(*this);
}

int matrice::max() const{
  int nMax=read(0,0);
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      if(read(i,j)>nMax)
        nMax=read(i,j);
  return nMax;
}

int matrice::min() const{
  int nMin=read(0,0);
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      if(read(i,j)<nMin)
        nMin=read(i,j);
  return nMin;
}

int matrice::mostRepeated() const{
  int mr=read(0,0);
  int tr=0;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      if(read(i,j)!=0){
        int n=0;
        for(int k=0;k<r;k++)
          for(int h=0;h<c;h++)
            if(read(i,j)==read(k,h))
              n++;
        if(n>tr){tr=n;mr=read(i,j);}
        }
  return mr;
}
