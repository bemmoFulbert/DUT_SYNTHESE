#include "adherenttablemodel.h"

AdherentTableModel::AdherentTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    //Adherent::ajouter("jordi","bafoussam","peggy","jordiPeggy@gmail.com","1000-12-02","f");
    //synchronization
    vector<AdherentData> lignes;
    Adherent::consulter(lignes);
    AdherentData::affiche_adherentData(lignes);
    AdherentData::toQStringLists(lignes,ids,addresses,nbreLivresEmprunters,prenoms,emails,dateDeNaissances,sexes);
}

int AdherentTableModel::rowCount(const QModelIndex &parent)const{
    if(parent.isValid()) return 0;
    else return ids.count();
}

int AdherentTableModel::columnCount(const QModelIndex &parent)const{
    if(parent.isValid()) return 0;
    else return nbrColums;
}

QVariant AdherentTableModel::data(const QModelIndex &index,int role)const{
    if(!index.isValid()) return QVariant();
    if(index.row() >= ids.count() || index.column() >= nbrColums){
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        if(index.column() == idsPos) return this->ids.at(index.row());
        else if(index.column() == addressesPos) return this->addresses.at(index.row());
        else if(index.column() == nbreLivresEmpruntersPos) return this->nbreLivresEmprunters.at(index.row());
        else if(index.column() == prenomsPos) return this->prenoms.at(index.row());
        else if(index.column() == emailsPos) return this->emails.at(index.row());
        else if(index.column() == dateDeNaissancesPos) return this->dateDeNaissances.at(index.row());
        else if(index.column() == sexesPos) return this->sexes.at(index.row());
    }
    return QVariant();
}

bool AdherentTableModel::setData(const QModelIndex &index,const QVariant &value,int role){
    if(index.isValid() && role == Qt::EditRole){
        if(index.column() == idsPos) this->ids.replace(index.row(),value.toString());
        else if(index.column() == addressesPos) this->addresses.replace(index.row(),value.toString());
        else if(index.column() == nbreLivresEmpruntersPos) this->nbreLivresEmprunters.replace(index.row(),value.toString());
        else if(index.column() == prenomsPos) this->prenoms.replace(index.row(),value.toString());
        else if(index.column() == emailsPos) this->emails.replace(index.row(),value.toString());
        else if(index.column() == dateDeNaissancesPos) this->dateDeNaissances.replace(index.row(),value.toString());
        else if(index.column() == sexesPos) {
            if(value.toString() == "h" || QString("masculin").contains(value.toString()))
                            this->sexes.replace(index.row(),"masculin");
            else if(value.toString() == "f" || QString("feminin").contains(value.toString()))
                this->sexes.replace(index.row(),"feminin");
            }
        emit(dataChanged(index,index));
        return true;
    }
    return false;
}

Qt::ItemFlags AdherentTableModel::flags(const QModelIndex &index)const{
    if(!index.isValid()) return Qt::ItemIsEnabled;

    if(index.column() == idsPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else if(index.column() == addressesPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    else if(index.column() == nbreLivresEmpruntersPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
    else if(index.column() == prenomsPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    else if(index.column() == emailsPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    else if(index.column() == dateDeNaissancesPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
    else if(index.column() == sexesPos) return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;

    return QAbstractItemModel::flags(index);
}




