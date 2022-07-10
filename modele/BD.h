#ifndef BD_H
#define BD_H

#include <QtSql/QSqlDatabase>

#define BD_NAME "dut_puc2442_proj.db"

class BD: public QSqlDatabase{
    BD();
}
#endif // BD_H

