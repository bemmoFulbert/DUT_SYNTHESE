#ifndef ADHERENTTABLEMODEL_H
#define ADHERENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QModelIndex>
#include <QVariant>

#include "backend/adherent.h"

class AdherentTableModel : public QAbstractTableModel
{
private:
    QStringList ids, addresses, nbreLivresEmprunters, prenoms, emails, dateDeNaissances, sexes;
    enum{ idsPos=0, addressesPos=1, nbreLivresEmpruntersPos=2, prenomsPos=3, emailsPos=4, dateDeNaissancesPos=5, sexesPos=6, nbrColums = sexesPos+1};

public:
    AdherentTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex())const;
    int columnCount(const QModelIndex &parent = QModelIndex())const;
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value,int role);
    Qt::ItemFlags flags(const QModelIndex &index)const;
};

#endif // ADHERENTTABLEMODEL_H
