#ifndef MATRICEGUI_H
#define MATRICEGUI_H

#include <QColor>
#include <QWidget>
#include <QtWidgets>
#include <QAbstractButton>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QFrame>
#include "matrice.h"
#include "matricequadrata.h"
#include "matricebinaria.h"

class matriceGui : public QWidget
{
  Q_OBJECT
private:
  class cell: public QPushButton{
    public:
      cell(int v=0, QWidget *parent = 0);
      void setNumText(int n=0);
  };
  int sel_y;
  int sel_x;
  QVector<cell*> cel;
  int size;
  int cellSize;
  int rows;
  int columns;
  void keyPressEvent(QKeyEvent *event) override;
  matrice* matrix;

public:
  int x,y;//posizione rispetto al widget parent
  matriceGui(const matrice&, int s=300, QWidget *parent = 0);
  ~matriceGui();
  int getSize() const;
  int getColumns() const;
  int getRows() const;
  void setDim(int r,int c);//cambia le dimensioni della matrice grafica
  void update();//aggiorna la matrice grafica quando vengono cambiati i valori della matrice interna
  void markCells(const vector<matriceBinaria::casella>& c);//dato un insieme di caselle, evidenzia le celle corrispondenti nella matrice grafica
  matrice* getMatrix() const;
  void writeMatrix(matrice* m);
public slots:
  void selChanged();
};

#endif // MATRICEGUI_H
