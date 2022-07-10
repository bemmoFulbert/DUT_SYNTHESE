#include "mainwindow.h"

#include <QApplication>
#include <QToolBar>

#include "modele/BD.h"
#include "traitement/Auteur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.addToolBar(new QToolBar(&w));
    Auteur::ajouter("philip","jirand");

    //w.show();
    return a.exec();
}
