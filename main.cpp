#include "mainwindow.h"

#include <QApplication>
#include <QVBoxLayout>

#include "backend/BDR_SQLite3.h"
#include "backend/root.h"

#include "backend/auteur.h"
#include "backend/livre.h"
#include "backend/adherent.h"
#include "backend/util.h"

using namespace std;
int main(int argc, char *argv[])
{
    BDR_SQLite3 bd("dut_puc2442_proj.db");
    Root::chargerBD(bd);
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
