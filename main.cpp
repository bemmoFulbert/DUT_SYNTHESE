#include "mainwindow.h"

#include <QApplication>

#include "backend/BDR_SQLite3.h"
#include "backend/root.h"

#include "backend/auteur.h"
#include "backend/livre.h"
#include "backend/adherent.h"
#include "backend/util.h"

using namespace std;
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    BDR_SQLite3 bd("dut_puc2442_proj.db");
    Root::chargerBD(bd);

    //vector<AdherentData> v;
    //Adherent::consulter(v);

    vector<LivreData> v;
    Livre::consulter(v);
    Livre::exportToFile("Livres.txt");

   //AdherentData::affiche_adherentData(v);

    LivreData::affiche_livreData(v);

    //w.show();
    //return a.exec();
    return 0;
}
