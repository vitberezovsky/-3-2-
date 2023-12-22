#include "matricequadrata.h"

//MATRICE QUADRATA
matriceQuadrata::matriceQuadrata(int x, int d): matrice(x,x,d) {}

matriceQuadrata& matriceQuadrata::operator+(const matrice& m){
    matriceQuadrata* x=new matriceQuadrata(*this);
    if(!sizeEqual(m))
      throw errSize();
    for(int i=0;i<getRows();i++)
      for(int j=0;j<getRows();j++)
        x->ref(i,j)+=m.read(i,j);
    return *x;
}

matriceQuadrata& matriceQuadrata::operator-(const matrice& m){
    matriceQuadrata* x=new matriceQuadrata(*this);
    if(!sizeEqual(m))
      throw errSize();
    for(int i=0;i<getRows();i++)
      for(int j=0;j<getRows();j++)
        x->ref(i,j)+=m.read(i,j);
    return *x;
}

matriceQuadrata& matriceQuadrata::operator*(const matrice& m){
    matriceQuadrata* ris=new matriceQuadrata(getRows(),m.getRows());
    if(!sizeEqual(m))
      throw errSizeProd();
    for(int i=0;i<ris->getRows();i++)
      for(int j=0;j<ris->getRows();j++){
        int somma=0;
        for(int k=0;k<getRows();k++)
          somma+=read(i,k)*m.read(k,j);
        ris->ref(i,j)=somma;
      }
    return *ris;
}

matriceQuadrata matriceQuadrata::quadratoMagicoDispari(matriceQuadrata m){
  int dim=m.getColumns();
  m.writeAll(0);
  int x=(dim-1)/2,y=0;
  for(int i=1;i<=dim*dim;i++){
    m.ref(y,x)=i;
    int old_x=x,old_y=y;
    y--;
    if(y<0)y=dim-1;
    x++;
    if(x>=dim)x=0;
    if(m.read(y,x)!=0){
      x=old_x;
      y=old_y+1;
    }
  }
  return m;
}

matriceQuadrata matriceQuadrata::quadratoMagicoPari(matriceQuadrata m){
  int hdim=m.getColumns()/2;
  matriceQuadrata t(hdim);
  matriceQuadrata a(quadratoMagicoDispari(t));
  matriceQuadrata b(quadratoMagicoDispari(t));
  b+matriceQuadrata(b.getColumns(),hdim*hdim);
  matriceQuadrata c(quadratoMagicoDispari(t));
  c+matriceQuadrata(c.getColumns(),hdim*hdim*2);
  matriceQuadrata d(quadratoMagicoDispari(t));
  d+matriceQuadrata(d.getColumns(),hdim*hdim*3);
  m.copy(a,0,0);
  m.copy(b,hdim,hdim);
  m.copy(c,0,hdim);
  m.copy(d,hdim,0);
  int hhdim=(hdim-1)/2;
  m.swap(0,0,hdim,0,hhdim,hhdim);
  m.swap(hhdim,1,hhdim+hdim,1,1,hhdim*hhdim);
  m.swap(hhdim+1,0,hhdim+hdim+1,0,hhdim,hhdim);
  return m;
}

matriceQuadrata matriceQuadrata::quadratoMagicoPariDiv4(matriceQuadrata m){
  int hhdim=m.getColumns()/4;
  int dim=m.getColumns();
  for(int i=0;i<m.getColumns();i++)
    for(int j=0;j<m.getColumns();j++)
      if((i<hhdim && (j<hhdim || j>=dim-hhdim)) || (i>=dim-hhdim && (j<hhdim || j>=dim-hhdim)) || (i>=hhdim && i<dim-hhdim && j>=hhdim && j<dim-hhdim))
        m.ref(i,j)=i*dim+j+1;
      else
        m.ref(i,j)=dim*dim-(i*dim+j);
  return m;
 }

matriceQuadrata matriceQuadrata::quadratoMagico(){
  if(getColumns()<3){
    throw errQuadratoMagico();
  }
  if(getColumns()%2==1)
    *this=quadratoMagicoDispari(*this);
  else
    if(getColumns()%4==0)
      *this=quadratoMagicoPariDiv4(*this);
    else
      *this=quadratoMagicoPari(*this);
  return *this;
}

matriceQuadrata matriceQuadrata::sudoku(){
  int rad=sqrt(getColumns());
  if(rad<2){
    throw errSudoku();
  }
  if(rad*rad!=getColumns()){
    throw errSudoku();
  }
  for(int i=0;i<getColumns();i++)
    for(int j=0;j<getColumns();j++)
      if(read(i,j)<0 || read(i,j)>getColumns()){
        throw errSudokuInit();
      }
  matriceQuadrata m(*this);
  if(risolvi_sudoku(m))
    return *this=m;
  throw errSudokuInit();
}

//QUESTE FUNZIONI SONO USATE PER RISOLVERE IL SUDOKU
bool matriceQuadrata::check_full(const matriceQuadrata& m){
  for(int i=0;i<m.getColumns();i++)
    for(int j=0;j<m.getColumns();j++)
      if(m.read(i,j)==0)
        return false;
  return true;
}

bool matriceQuadrata::check_sudoku(const matriceQuadrata& m){
  int dim=sqrt(m.getColumns());
  for(int i=0;i<m.getColumns();i++)
    for(int j=0;j<m.getColumns();j++)
      if(m.read(i,j)!=0)
        for(int k=0;k<m.getColumns();k++){
          if((m.read(i,j)==m.read(i,k) && k!=j) || (m.read(i,j)==m.read(k,j) && k!=i))//ci sono 2 numeri uguali nella stessa riga o colonna
            return false;
          for(int h=0;h<m.getColumns();h++)
            if(m.read(i,j)==m.read(k,h) && k/dim==i/dim && h/dim==j/dim && (k!=i && h!=j))
              return false;
      }
  return true;
}

bool matriceQuadrata::risolvi_sudoku(matriceQuadrata& m){
  if(check_sudoku(m) && check_full(m))
    return true;
  if(!check_sudoku(m))
    return false;
  for(int i=0;i<m.getColumns();i++)
    for(int j=0;j<m.getColumns();j++)
      if(m.read(i,j)==0)
        for(int k=1;k<=m.getColumns();k++){
          m.ref(i,j)=k;
          if(risolvi_sudoku(m))
            return true;
          m.ref(i,j)=0;
          if(m.read(i,j)==0 && k==m.getColumns())
            return false;
    }
  return check_sudoku(m);
}

matriceQuadrata* matriceQuadrata::clone() const {
  return new matriceQuadrata(*this);
}
