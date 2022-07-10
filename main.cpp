#include "mainwindow.h"

#include <QApplication>
#include <QToolBar>

#include "modele/BD.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    BD bdd("QSQLITE");
    w.addToolBar(new QToolBar(&w));

    w.screen();
    w.show();
    return a.exec();
}
