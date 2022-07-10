#include "mainwindow.h"

#include <QApplication>

#include "modele/BD.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    BD bdd("QSQLITE");
    w.show();
    return a.exec();
}
