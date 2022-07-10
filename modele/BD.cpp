#include "BD.h"

#include <QMessageBox>
#include <QString>

BD::BD(QString data_base_type):QSqlDatabase(data_base_type){
    this->addDatabase(data_base_type);
    this->setHostName("localhost");
    this->setDatabaseName(BD_NAME);
    this->setUserName("root");
    this->setPassword("");
    if(!this->open()){
        QMessageBox::critical(NULL,"erreur de BD","la connexion a la base de donnees a echoue");
    }
}
BD::~BD(){

}
