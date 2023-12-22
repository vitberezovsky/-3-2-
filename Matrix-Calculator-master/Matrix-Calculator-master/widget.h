#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include "matricegui.h"

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private:
  //VARIABILI
  int matriceSelect;
  //MATRICI
  matriceGui *mat[2];
  //slider per modificare le dimensioni delle matrici
  QSlider *Smat1_y;
  QSlider *Smat1_x;
  QSlider *Smat2_y;
  QSlider *Smat2_x;
  //display per visualizzare le dimensioni delle matrici
  QLCDNumber *Dmat1_y;
  QLCDNumber *Dmat1_x;
  QLCDNumber *Dmat2_y;
  QLCDNumber *Dmat2_x;
  //OPERATORI BINARI
  QPushButton *somma;
  QPushButton *sottrazione;
  QPushButton *prodotto;
  //OPERATORI UNARI
  QPushButton *trasposta;
  QPushButton *copia;
  QPushButton *inversa;
  QPushButton *fill;
  QPushButton *random;
  QPushButton *clear;
  //FINESTRE PER SELEZIONI
  QComboBox *activeMatComboBox;
  QComboBox *typeMatComboBox;
  //OPERATORI SPECIALI
  QPushButton *quadratoMagico;
  QPushButton *sudoku;
  QPushButton *labirinto;
  //FINESTRA PER MESSAGGI DI ERRORE
  QLineEdit *display;
  //METODI
  int notActiveMat() const;//ritorna il numero associato alla matrice non selezionata
  void updateDim();//mostra le giuste dimensioni delle matrici

private slots:
  void sizeYmat1changed(int);
  void sizeXmat1changed(int);
  void sizeYmat2changed(int);
  void sizeXmat2changed(int);

  void activeMatChanged();
  void typeMatChanged();

  void opSomma();
  void opSottrazione();
  void opProdotto();

  void opTrasposta();
  void opCopia();
  void opInversa();
  void opFill();
  void opRandom();
  void opClear();

  void opQuadratoMagico();
  void opSudoku();
  void opLabirinto();
};

#endif // WIDGET_H
