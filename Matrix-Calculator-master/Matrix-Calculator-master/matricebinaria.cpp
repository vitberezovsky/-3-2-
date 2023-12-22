#include "matricebinaria.h"

//MATRICE BINARIA
matriceBinaria::matriceBinaria(int y,int x, int d): matrice(y,x,d) {
  aggiusta();
}

matriceBinaria matriceBinaria::aggiusta(){
  for(int i=0;i<getRows();i++)
    for(int j=0;j<getColumns();j++){
      if(read(i,j)<0)ref(i,j)=0;
      if(read(i,j)>1)ref(i,j)=1;
    }
  return *this;
}

matriceBinaria& matriceBinaria::operator+(const matrice& m){
    matriceBinaria* x=new matriceBinaria(*this);
    if(!sizeEqual(m))
      throw errSize();
    for(int i=0;i<getRows();i++)
      for(int j=0;j<getColumns();j++)
        x->ref(i,j)+=m.read(i,j);
    x->aggiusta();
    return *x;
}

matriceBinaria& matriceBinaria::operator-(const matrice& m){
    matriceBinaria* x=new matriceBinaria(*this);
    if(!sizeEqual(m))
      throw errSize();
    for(int i=0;i<getRows();i++)
      for(int j=0;j<getColumns();j++)
        x->ref(i,j)-=m.read(i,j);
    x->aggiusta();
    return *x;
}

matriceBinaria& matriceBinaria::operator*(const matrice& m){
    matriceBinaria* ris=new matriceBinaria(getRows(),m.getColumns());
    if(!(getColumns()==m.getRows() && getRows()==m.getColumns()))
      throw errSizeProd();
    for(int i=0;i<ris->getRows();i++)
      for(int j=0;j<ris->getColumns();j++){
        int somma=0;
        for(int k=0;k<getColumns();k++)
          somma+=read(i,k)*m.read(k,j);
        if(somma>1)somma=1;
        if(somma<0)somma=0;
        ris->ref(i,j)=somma;
      }
    return *ris;
}

void matriceBinaria::writeAllRandom(){
  matrice::writeAllRandom(0,1);
}

void matriceBinaria::reverse(){
  for(int i=0;i<getRows();i++)
    for(int j=0;j<getColumns();j++)
      if(read(i,j)==1)ref(i,j)=0;
      else ref(i,j)=1;
}

matriceBinaria& matriceBinaria::operator=(const matrice& m){
  matrice::operator=(m);
  aggiusta();
  return *this;
}

vector<matriceBinaria::casella> matriceBinaria::labirinto(int ys,int xs,int ye,int xe) const{
  if(ye==0)ye=getRows()-1;
  if(xe==0)xe=getColumns()-1;
  vector<casella> p;//questo vector memorizza le caselle del percorso migliore al termine dell'esecuzione di risolvi_lab
  int minmosse=getColumns()*getRows()+1;//al termine dell'esecuzione di risolvi_lab memorizzerà la distanza del percorso più breve
  int old_minmosse=minmosse;
  matrice m(*this);//siccome la funzione risolvi_lab ha bisogno di utilizzare altri valori all'interno della matrice allora uso una matrice normale
  risolvi_lab(m,ys,xs,ye,xe,minmosse,p);
  if(old_minmosse==minmosse){
    throw errLabirinto();
  }
  p.push_back(casella(ys,xs));//aggiungo la posizione di partenza al vettore del percorso
  return p;
}

matriceBinaria* matriceBinaria::clone() const {
  return new matriceBinaria(*this);
}

//QUESTE FUNZIONI SONO USATE PER RISOLVERE IL LABIRINTO
bool matriceBinaria::fine_lab(int y,int x,int ye,int xe){
  if(y==ye && x==xe)
    return true;
  return false;
}

bool matriceBinaria::bloccato(const matrice& m,int y,int x){
  int n=0;
  if(m.read(y+1,x)==1 || m.read(y+1,x)==3 || y+1>=m.getRows())n++;
  if(m.read(y-1,x)==1 || m.read(y-1,x)==3 || y-1<0)n++;
  if(m.read(y,x+1)==1 || m.read(y,x+1)==3 || x+1>=m.getColumns())n++;
  if(m.read(y,x-1)==1 || m.read(y,x-1)==3 || x-1<0)n++;
  if(n==4)return true;
  return false;
}

bool matriceBinaria::is_best_path(const vector<matriceBinaria::casella>& p,int y,int x){
  for(unsigned int i=0;i<p.size();i++)
    if(y==p[i].y && x==p[i].x)
      return true;//ritorna true se le coordinate (y,x) si trovano su una casella che appartiene al percorso più breve finora trovato
  return false;
}

bool matriceBinaria::risolvi_lab(matrice& m,int y,int x,int ye,int xe,int &minmosse,vector<matriceBinaria::casella>& p,int mosse){
  int r=m.getRows();
  int c=m.getColumns();
  if(fine_lab(y,x,ye,xe) && mosse<minmosse){
    p.clear();
    minmosse=mosse;//salva il migliore percorso nell'array p
    for(int i=0;i<r;i++)
      for(int j=0;j<c;j++)
        if(m.read(i,j)==2)
          p.push_back(matriceBinaria::casella(i,j));
    return true;
  }
  if(bloccato(m,y,x) || m.read(y,x)==1)
      return false;
  for(int i=0;i<4;i++){
    int k1,k2;
    if(i==0){k1=1;k2=0;}//basso
    if(i==1){k1=0;k2=1;}//destra
    if(i==2){k1=-1;k2=0;}//alto
    if(i==3){k1=0;k2=-1;}//sinistra
    if(m.read(y+k1,x+k2)==0 && y+k1<r && x+k2<c && y+k1>=0 && x+k2>=0){
      m.ref(y+k1,x+k2)=2;
      if(!risolvi_lab(m,y+k1,x+k2,ye,xe,minmosse,p,mosse+1) && !is_best_path(p,y+k1,x+k2))
          m.ref(y+k1,x+k2)=3;
      else
          m.ref(y+k1,x+k2)=0;
    }
  }
  return false;
}
