#include "mainwindow.h"

#include <QApplication>

#include "backend/auteur.h"
#include "backend/livre.h"
#include "backend/adherent.h"
#include "backend/util.h"

using namespace std;
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    vector<AuteurData> v;
    Adherent::exportToFile("backup_adherent.txt");

    //w.show();
    //return a.exec();
    return 0;
}
