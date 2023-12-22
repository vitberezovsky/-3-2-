#include "matricebinaria.h"

//QUESTE FUNZIONI SONO USATE PER RISOLVERE IL LABIRINTO
bool fine_lab(int y,int x,int ye,int xe){
  if(y==ye && x==xe)
    return true;
  return false;
}

bool bloccato(const matrice& m,int y,int x){
  int n=0;
  if(m.read(y+1,x)==1 || m.read(y+1,x)==3 || y+1>=m.getRows())n++;
  if(m.read(y-1,x)==1 || m.read(y-1,x)==3 || y-1<0)n++;
  if(m.read(y,x+1)==1 || m.read(y,x+1)==3 || x+1>=m.getColumns())n++;
  if(m.read(y,x-1)==1 || m.read(y,x-1)==3 || x-1<0)n++;
  if(n==4)return true;
  return false;
}

bool is_best_path(const vector<matriceBinaria::casella>& p,int y,int x){
  for(unsigned int i=0;i<p.size();i++)
    if(y==p[i].y && x==p[i].x)
      return true;//ritorna true se le coordinate (y,x) si trovano su una casella che appartiene al percorso più breve finora trovato
  return false;
}

bool risolvi_lab(matrice& m,int y,int x,int ye,int xe,int &minmosse,vector<matriceBinaria::casella>& p,int mosse=0){
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
