#ifndef ADHHEADERMODEL_H
#define ADHHEADERMODEL_H

#include <QIdentityProxyModel>

class AdhHeaderModel : public QIdentityProxyModel
{
public:
    AdhHeaderModel(QObject *parent = nullptr);
    QVariant headerData(int section,Qt::Orientation orientation,int role) const;
};

#endif // ADHHEADERMODEL_H
