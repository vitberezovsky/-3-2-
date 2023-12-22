#include "widget.h"
#include "matrice.h"
#include "matricequadrata.h"
#include "matricebinaria.h"
#include "matriceGui.h"
#include <QApplication>


//9 luglio
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}
