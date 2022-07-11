#include "mainwindow.h"

#include <QApplication>

#include "backend/auteur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Auteur::modifierNom(3,"gandou");

    w.show();
    return a.exec();
}
