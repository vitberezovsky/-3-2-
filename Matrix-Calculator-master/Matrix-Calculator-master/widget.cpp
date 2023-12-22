#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent){
  setFixedSize(800,500);
  setWindowTitle("Матричний калькулятор");
  //BOXES FOR MATRICES
  QLabel* l1 = new QLabel(this);
  l1->setGeometry(50,0,300,300);
  l1->setFrameStyle(QFrame::Box | QFrame::Raised);
  QLabel* l2 = new QLabel(this);
  l2->setGeometry(450,0,300,300);
  l2->setFrameStyle(QFrame::Box | QFrame::Raised);
  //MATRICS
  matriceSelect=0;
  mat[0]=new matriceGui(matrice(9,9),300,this);
  mat[1]=new matriceGui(matrice(9,9),300,this);
  mat[0]->x=50;
  mat[1]->x=450;
  mat[0]->setGeometry(mat[0]->x,0,300,300);
  mat[1]->setGeometry(mat[1]->x,0,300,300);
  //SLIDER Y.1
  Smat1_y=new QSlider(Qt::Vertical,this);
  Smat1_y->setValue(9);
  Smat1_y->setRange(1,16);
  Smat1_y->setGeometry(10,50,30,250);
  Dmat1_y=new QLCDNumber(2,this);
  Dmat1_y->setGeometry(10,10,30,30);
  connect(Smat1_y,SIGNAL(valueChanged(int)),Dmat1_y,SLOT(display(int)));
  connect(Smat1_y,SIGNAL(valueChanged(int)),this,SLOT(sizeYmat1changed(int)));
  //SLIDER X.1
  Smat1_x=new QSlider(Qt::Horizontal,this);
  Smat1_x->setValue(9);
  Smat1_x->setRange(1,16);
  Smat1_x->setGeometry(50,310,300,30);
  Dmat1_x=new QLCDNumber(2,this);
  Dmat1_x->setGeometry(10,310,30,30);
  connect(Smat1_x,SIGNAL(valueChanged(int)),Dmat1_x,SLOT(display(int)));
  connect(Smat1_x,SIGNAL(valueChanged(int)),this,SLOT(sizeXmat1changed(int)));
  //SLIDER Y.2
  Smat2_y=new QSlider(Qt::Vertical,this);
  Smat2_y->setValue(9);
  Smat2_y->setRange(1,16);
  Smat2_y->setGeometry(760,50,30,250);
  Dmat2_y=new QLCDNumber(2,this);
  Dmat2_y->setGeometry(760,10,30,30);
  connect(Smat2_y,SIGNAL(valueChanged(int)),Dmat2_y,SLOT(display(int)));
  connect(Smat2_y,SIGNAL(valueChanged(int)),this,SLOT(sizeYmat2changed(int)));
  //SLIDER X.2
  Smat2_x=new QSlider(Qt::Horizontal,this);
  Smat2_x->setValue(9);
  Smat2_x->setRange(1,16);
  Smat2_x->setGeometry(450,310,300,30);
  Dmat2_x=new QLCDNumber(2,this);
  Dmat2_x->setGeometry(760,310,30,30);
  connect(Smat2_x,SIGNAL(valueChanged(int)),Dmat2_x,SLOT(display(int)));
  connect(Smat2_x,SIGNAL(valueChanged(int)),this,SLOT(sizeXmat2changed(int)));
  emit Smat1_y->valueChanged(9);
  emit Smat1_x->valueChanged(9);
  emit Smat2_y->valueChanged(9);
  emit Smat2_x->valueChanged(9);
  //BINARY OPERATORS (ADDITION, SUBTRACTION, PRODUCT)
  somma=new QPushButton(tr("+"),this);
  somma->setGeometry(375,50,50,50);
  somma->setFont(QFont("Times",20));
  connect(somma,SIGNAL(pressed()),this,SLOT(opSomma()));
  sottrazione=new QPushButton(tr("-"),this);
  sottrazione->setGeometry(375,125,50,50);
  sottrazione->setFont(QFont("Times",20));
  connect(sottrazione,SIGNAL(pressed()),this,SLOT(opSottrazione()));
  prodotto=new QPushButton(tr("x"),this);
  prodotto->setGeometry(375,200,50,50);
  prodotto->setFont(QFont("Times",20));
  connect(prodotto,SIGNAL(pressed()),this,SLOT(opProdotto()));
  //WINDOWS FOR SELECTIONS
  activeMatComboBox=new QComboBox(this);
  activeMatComboBox->addItem(tr("Ліва матриця"));
  activeMatComboBox->addItem(tr("Права матриця"));
  activeMatComboBox->setGeometry(450,350+30,120,25);
  connect(activeMatComboBox,SIGNAL(activated(int)),this,SLOT(activeMatChanged()));
  typeMatComboBox=new QComboBox(this);
  typeMatComboBox->addItem(tr("Стандартна матриця"));
  typeMatComboBox->addItem(tr("Квадратна матриця"));
  typeMatComboBox->addItem(tr("Бінарна матриця"));
  typeMatComboBox->setGeometry(630,350+30,120,25);
  connect(typeMatComboBox,SIGNAL(activated(int)),this,SLOT(typeMatChanged()));
  //UNARY OPERATORS
  trasposta=new QPushButton(tr("T"),this);
  trasposta->setGeometry(40,10+350,50,50);
  trasposta->setFont(QFont("Times",20));
  connect(trasposta,SIGNAL(pressed()),this,SLOT(opTrasposta()));
  inversa=new QPushButton(tr("Inv"),this);
  inversa->setGeometry(130,10+350,50,50);
  inversa->setFont(QFont("Times",15));
  connect(inversa,SIGNAL(pressed()),this,SLOT(opInversa()));
  fill=new QPushButton(tr("Fill"),this);
  fill->setGeometry(220,10+350,50,50);
  fill->setFont(QFont("Times",15));
  connect(fill,SIGNAL(pressed()),this,SLOT(opFill()));
  clear=new QPushButton(tr("Clr"),this);
  clear->setGeometry(40,80+350,50,50);
  clear->setFont(QFont("Times",15));
  connect(clear,SIGNAL(pressed()),this,SLOT(opClear()));
  copia=new QPushButton(tr("="),this);
  copia->setGeometry(130,80+350,50,50);
  copia->setFont(QFont("Times",20));
  connect(copia,SIGNAL(pressed()),this,SLOT(opCopia()));
  random=new QPushButton(tr("Rand"),this);
  random->setGeometry(220,80+350,50,50);
  random->setFont(QFont("Times",15));
  connect(random,SIGNAL(pressed()),this,SLOT(opRandom()));
  //SPECIAL OPERATORS
  quadratoMagico=new QPushButton(tr("M"),this);
  quadratoMagico->setGeometry(310,10+350,50,50);
  quadratoMagico->setFont(QFont("Times",20));
  quadratoMagico->setEnabled(0);
  quadratoMagico->hide();
  connect(quadratoMagico,SIGNAL(pressed()),this,SLOT(opQuadratoMagico()));
  sudoku=new QPushButton(tr("S"),this);
  sudoku->setGeometry(310,80+350,50,50);
  sudoku->setFont(QFont("Times",20));
  sudoku->setEnabled(0);
  sudoku->hide();
  connect(sudoku,SIGNAL(pressed()),this,SLOT(opSudoku()));
  labirinto=new QPushButton(tr("L"),this);
  labirinto->setGeometry(310,10+350,50,50);
  labirinto->setFont(QFont("Times",20));
  labirinto->setEnabled(0);
  labirinto->hide();
  connect(labirinto,SIGNAL(pressed()),this,SLOT(opLabirinto()));
  //WINDOW FOR ERROR MESSAGES
  display=new QLineEdit(" ",this);
  display->setGeometry(450,350+100,300,25);
  display->setReadOnly(true);
  display->setAlignment(Qt::AlignLeft);
}

Widget::~Widget(){
}

void Widget::sizeYmat1changed(int n){
  mat[0]->setDim(n,mat[0]->getColumns());
  if(dynamic_cast<matriceQuadrata*>(mat[0]->getMatrix()))
    Smat1_x->setValue(Smat1_y->value());
}

void Widget::sizeXmat1changed(int n){
  mat[0]->setDim(mat[0]->getRows(),n);
  if(dynamic_cast<matriceQuadrata*>(mat[0]->getMatrix()))
    Smat1_y->setValue(Smat1_x->value());
}

void Widget::sizeYmat2changed(int n){
  mat[1]->setDim(n,mat[1]->getColumns());
  if(dynamic_cast<matriceQuadrata*>(mat[1]->getMatrix()))
    Smat2_x->setValue(Smat2_y->value());
}

void Widget::sizeXmat2changed(int n){
  mat[1]->setDim(mat[1]->getRows(),n);
  if(dynamic_cast<matriceQuadrata*>(mat[1]->getMatrix()))
    Smat2_y->setValue(Smat2_x->value());
}

void Widget::activeMatChanged(){
  matriceSelect=activeMatComboBox->currentIndex();
}

void Widget::opSomma(){
  display->clear();
  try{
    mat[matriceSelect]->writeMatrix(&(*mat[matriceSelect]->getMatrix()+*mat[notActiveMat()]->getMatrix()));
  }
  catch (errSize){
      display->setText("Дві матриці різного розміру не можна додавати разом");}
  emit mat[matriceSelect]->update();
}

void Widget::opSottrazione(){
  display->clear();
  try{
    mat[matriceSelect]->writeMatrix(&(*mat[matriceSelect]->getMatrix()-*mat[notActiveMat()]->getMatrix()));
  }
  catch (errSize){
      display->setText("Не можна віднімати дві матриці різних розмірів");}
  emit mat[matriceSelect]->update();
}

void Widget::opProdotto(){
  display->clear();
  try{
    mat[matriceSelect]->writeMatrix(&(*mat[matriceSelect]->getMatrix()*(*mat[notActiveMat()]->getMatrix())));
  }
  catch (errSizeProd){
      display->setText("Розміри матриці не відносяться до виробу");}
  emit mat[matriceSelect]->update();
  updateDim();
}

void Widget::opTrasposta(){
  mat[matriceSelect]->getMatrix()->trasposta();
  emit mat[matriceSelect]->update();
  updateDim();
}

void Widget::opInversa(){
  mat[matriceSelect]->getMatrix()->reverse();
  emit mat[matriceSelect]->update();
}

void Widget::opFill(){
  mat[matriceSelect]->getMatrix()->writeAll(mat[matriceSelect]->getMatrix()->mostRepeated());
  emit mat[matriceSelect]->update();
}

void Widget::opClear(){
  mat[matriceSelect]->getMatrix()->writeAll(0);
  emit mat[matriceSelect]->update();
}

void Widget::opCopia(){
  delete mat[matriceSelect]->getMatrix();
  mat[matriceSelect]->writeMatrix(mat[notActiveMat()]->getMatrix()->clone());
  emit mat[matriceSelect]->update();
}

void Widget::opRandom(){
  if(matriceBinaria* b=dynamic_cast<matriceBinaria*>(mat[matriceSelect]->getMatrix())){
    b->writeAllRandom();
    mat[matriceSelect]->writeMatrix(b);
  }
  else
    mat[matriceSelect]->getMatrix()->writeAllRandom(mat[matriceSelect]->getMatrix()->min(),mat[matriceSelect]->getMatrix()->max());
  emit mat[matriceSelect]->update();
}

void Widget::opQuadratoMagico(){
  display->clear();
  matriceQuadrata* m=dynamic_cast<matriceQuadrata*>(mat[matriceSelect]->getMatrix());
  try{
    m->quadratoMagico();}
  catch(errQuadratoMagico){
    display->setText("Матриця повинна мати щонайменше 3 рядки та 3 стовпці");}
  mat[matriceSelect]->writeMatrix(m);
  emit mat[matriceSelect]->update();
}

void Widget::opSudoku(){
  display->clear();
  matriceQuadrata* m=dynamic_cast<matriceQuadrata*>(mat[matriceSelect]->getMatrix());
  try{
    m->sudoku();}
  catch (errSudoku){
    display->setText("Приймаються матриці розміром 4х4, 9х9, 16х16");}
  catch (errSudokuInit){
    display->setText("Початкове судоку неправильне");}
  mat[matriceSelect]->writeMatrix(m);
  emit mat[matriceSelect]->update();
}

void Widget::opLabirinto(){
  display->clear();
  matriceBinaria* m=dynamic_cast<matriceBinaria*>(mat[matriceSelect]->getMatrix());
  vector<matriceBinaria::casella> p;
  try{
    p=m->labirinto();}
  catch(errLabirinto){
    display->setText("Лабіринт неможливий");}
  mat[matriceSelect]->writeMatrix(m);
  mat[matriceSelect]->markCells(p);
}

void Widget::typeMatChanged(){
  quadratoMagico->setEnabled(0);
  quadratoMagico->hide();
  sudoku->setEnabled(0);
  sudoku->hide();
  labirinto->setEnabled(0);
  labirinto->hide();
  for(int i=0;i<2;i++){
    if(typeMatComboBox->currentIndex()==0){//matrice standard
      matrice newMat(mat[i]->getRows(),mat[i]->getColumns());
      newMat.copy(*mat[i]->getMatrix());
      delete mat[i];
      mat[i]=new matriceGui(newMat,300,this);
    }
    if(typeMatComboBox->currentIndex()==1){//matrice quadrata
      quadratoMagico->setEnabled(1);
      quadratoMagico->show();
      sudoku->setEnabled(1);
      sudoku->show();
      int dim=mat[i]->getColumns();
      if(mat[i]->getRows()>mat[i]->getColumns()) dim=mat[i]->getRows();
      matriceQuadrata newMat(dim);
      newMat.copy(*mat[i]->getMatrix());
      delete mat[i];
      mat[i]=new matriceGui(newMat,300,this);
      updateDim();
    }
    if(typeMatComboBox->currentIndex()==2){//matrice binaria
      labirinto->setEnabled(1);
      labirinto->show();
      matriceBinaria newMat(mat[i]->getRows(),mat[i]->getColumns());
      delete mat[i];
      mat[i]=new matriceGui(newMat,300,this);
    }
    if(i==0)mat[i]->x=50;
    else mat[i]->x=450;
    mat[i]->setGeometry(mat[i]->x,0,300,300);
    mat[i]->show();
  }
}

int Widget::notActiveMat() const{
  if(matriceSelect==0)return 1;
  else return 0;
}

void Widget::updateDim(){
  emit Smat1_y->valueChanged(mat[0]->getRows());
  emit Smat1_x->valueChanged(mat[0]->getColumns());
  emit Smat2_y->valueChanged(mat[1]->getRows());
  emit Smat2_x->valueChanged(mat[1]->getColumns());
}
