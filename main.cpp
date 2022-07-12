#include "mainwindow.h"

#include <QApplication>

#include "backend/auteur.h"
//#include "backend/auteurdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Auteur::exportToFile("backup_auteur.txt");

    w.show();
    return a.exec();
}
