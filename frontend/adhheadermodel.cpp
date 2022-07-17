#include "adhheadermodel.h"
#include "backend/adherent.h"

AdhHeaderModel::AdhHeaderModel(QObject * parent):QIdentityProxyModel(parent){}

QVariant AdhHeaderModel::headerData(int section,Qt::Orientation orientation,int role) const{
    vector<string> champs = Adherent::getVChamps_full();
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            switch (section) {
                case 0: return QString::fromStdString(champs[section]); break;
                case 1: return QString::fromStdString(champs[section]); break;
                case 2: return QString::fromStdString(champs[section]); break;
                case 3: return QString::fromStdString(champs[section]); break;
                case 4: return QString::fromStdString(champs[section]); break;
                case 5: return QString::fromStdString(champs[section]); break;
                case 6: return QString::fromStdString(champs[section]); break;
            }
    }else if(orientation == Qt::Vertical) return QVariant(section+1);
    }
    return QVariant();
}
