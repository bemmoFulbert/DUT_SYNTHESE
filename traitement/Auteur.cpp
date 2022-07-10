#include "Auteur.h"

#include "../modele/BD.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QMessageBox>

bool isQueryError(QSqlQuery query){
    QSqlError err = query.lastError();
    if(err.text().isEmpty()) return false;
    else return true;
}

bool Auteur::ajouter(const string nom,const string prenom){
    BD bdd("QSQLITE");
    bool err;

    QSqlQuery query = bdd.exec("insert into auteur(nom,prenom) values(\""+QString::fromStdString(nom)+"\",\""+QString::fromStdString(prenom)+"\")");
    err = isQueryError(query);
    if(err) QMessageBox::information(NULL,"query_err","erreur");

    return err;
}
