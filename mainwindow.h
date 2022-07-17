#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>

#include "frontend/adherenttablemodel.h"
#include "frontend/adhheadermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *filter;
    AdherentTableModel *adhTableModel;
    AdhHeaderModel *adhHeaderModel;

};


#endif // MAINWINDOW_H
