#include "mainwindow.h"

#include <QApplication>

#include "backend/livre.h"
//#include "backend/auteurdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    vector<LivreData> v;
    Livre::consulter(v);
    LivreData::affiche_livreData(v);

    w.show();
    return a.exec();
}
