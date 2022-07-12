#include "mainwindow.h"

#include <QApplication>

#include "backend/auteur.h"
#include "backend/util.h"

using namespace std;
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    vector<AuteurData> v;
    Auteur::exportToFile("backup_auteur.txt","---");
    //cout << Auteur::importToDB("backup_auteur.txt","--");

    //w.show();
    //return a.exec();
    return 0;
}
