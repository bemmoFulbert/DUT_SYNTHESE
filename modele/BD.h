#ifndef BD_H
#define BD_H

#include <string>

using namespace std;

#include <QtSql/QSqlDatabase>

#define BD_NAME "dut_puc2442_proj.db"

class BD: public QSqlDatabase{
    public:
        BD(QString data_base_type);
        ~BD();
};

#endif // BD_H

