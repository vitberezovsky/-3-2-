#include <QtWidgets>
#include "matricegui.h"

matriceGui::cell::cell(int v, QWidget *parent): QPushButton(parent){
  setNumText(v);
}

void matriceGui::cell::setNumText(int n){
  QString s;
  s.setNum(n);
  setText(s);
}

matriceGui::matriceGui(const matrice& m, int s, QWidget *parent): QWidget(parent),sel_y(0),sel_x(0),size(s),x(0),y(0),matrix(m.clone()){
  columns=m.getColumns();
  rows=m.getRows();
  resize(size,size);
  if(columns>=rows)
    cellSize=size/columns;
  else
    cellSize=size/rows;
  for(int i=0;i<rows;i++)
    for(int j=0;j<columns;j++){
      cel.push_back(new cell(matrix->read(i,j),this));
      cel[i*columns+j]->setGeometry(j*cellSize,i*cellSize,cellSize,cellSize);
      cel[i*columns+j]->setAutoFillBackground(1);//If enabled, this property will cause Qt to fill the background of the widget before invoking the paint event. The color used is defined by the QPalette::Window color role from the widget's palette
      connect(cel[i*columns+j],SIGNAL(pressed()),this,SLOT(selChanged()));
    }
}
matriceGui::~matriceGui() {delete matrix;}

void matriceGui::selChanged(){
  for(int i=0;i<rows;i++)
    for(int j=0;j<columns;j++){
       cel[i*columns+j]->setPalette(QPalette(QColor(255,255,255)));
       if(cel[i*columns+j]->isDown()){
          sel_y=i;
          sel_x=j;
          cel[i*columns+j]->setPalette(QPalette(QColor(0,0,255)));
       }
    }
  if(dynamic_cast<matriceBinaria*>(matrix)){//se la matrice è binaria l'input viene dato solo col mouse (un click cambia il valore della casella)
    if(matrix->read(sel_y,sel_x)==0)matrix->ref(sel_y,sel_x)=1;
    else matrix->ref(sel_y,sel_x)=0;
    cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
  }
}

void matriceGui::keyPressEvent(QKeyEvent *event){
  if(dynamic_cast<matriceBinaria*>(matrix))
    return;
  int digit=-1;
  switch (event->key()) {
    case Qt::Key_0: digit=0;break;
    case Qt::Key_1: digit=1;break;
    case Qt::Key_2: digit=2;break;
    case Qt::Key_3: digit=3;break;
    case Qt::Key_4: digit=4;break;
    case Qt::Key_5: digit=5;break;
    case Qt::Key_6: digit=6;break;
    case Qt::Key_7: digit=7;break;
    case Qt::Key_8: digit=8;break;
    case Qt::Key_9: digit=9;break;
    case Qt::Key_Minus: if(matrix->read(sel_y,sel_x)>0){
        matrix->ref(sel_y,sel_x)=-matrix->read(sel_y,sel_x);
        cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
      }
      break;
    case Qt::Key_Plus: if(matrix->read(sel_y,sel_x)<0){
        matrix->ref(sel_y,sel_x)=-matrix->read(sel_y,sel_x);
        cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
      }
      break;
    case Qt::Key_Backspace:
      if(abs(matrix->read(sel_y,sel_x))<10){
        matrix->ref(sel_y,sel_x)=0;
        cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
      }
      else{
        matrix->ref(sel_y,sel_x)=matrix->read(sel_y,sel_x)/10;
        cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
      }
  }
  if(digit>=0){
    if(matrix->read(sel_y,sel_x)==0){
      matrix->ref(sel_y,sel_x)=digit;
      cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
    }
    else{
      int num;
      if(matrix->read(sel_y,sel_x)<0)
        num=-(abs(matrix->read(sel_y,sel_x))*10+digit);
      else num=matrix->read(sel_y,sel_x)*10+digit;
      matrix->ref(sel_y,sel_x)=num;
      cel[sel_y*columns+sel_x]->setNumText(matrix->read(sel_y,sel_x));
    }
  }
}

int matriceGui::getSize() const{
  return size;
}

int matriceGui::getColumns() const{
  return columns;
}

int matriceGui::getRows() const{
  return rows;
}

void matriceGui::update(){
  for(int i=0;i<columns*rows;i++)
    delete cel[i];
  sel_y=0;sel_x=0;
  columns=matrix->getColumns();
  rows=matrix->getRows();
  if(columns>=rows)cellSize=size/columns;
  else cellSize=size/rows;
  cel.clear();//rimetto le celle con il valore aggiornato
  for(int i=0;i<rows;i++)
    for(int j=0;j<columns;j++){
      cel.push_back(new cell(matrix->read(i,j),this));
      cel[i*columns+j]->setGeometry(j*cellSize,i*cellSize,cellSize,cellSize);
      cel[i*columns+j]->setAutoFillBackground(1);
      connect(cel[i*columns+j],SIGNAL(pressed()),this,SLOT(selChanged()));
      cel[i*columns+j]->show();
    }
}

void matriceGui::setDim(int r,int c){
  matrice* t;
  if(dynamic_cast<matriceQuadrata*>(matrix)){
    t=new matriceQuadrata(r);
  }
  if(dynamic_cast<matriceBinaria*>(matrix)){
    t=new matriceBinaria(r,c);
  }
  if(dynamic_cast<matrice*>(matrix)){
    t=new matrice(r,c);//viene creata una nuova matrice con le nuove dimensioni e mantendo gli stessi valori se possibile
  }
  t->copy(*matrix);
  *matrix=*t;
  update();
  delete t;
}

void matriceGui::markCells(const vector<matriceBinaria::casella> &c){
  for(int i=0;i<rows;i++)
    for(int j=0;j<columns;j++)
       cel[i*columns+j]->setPalette(QPalette(QColor(255,255,255)));
  for(unsigned int i=0;i<c.size();i++){
    cel[c[i].y*columns+c[i].x]->setPalette(QPalette(QColor(0,0,255)));
  }
}

matrice* matriceGui::getMatrix() const{
  return matrix;
}
void matriceGui::writeMatrix(matrice* m){
  matrix=m;
}
