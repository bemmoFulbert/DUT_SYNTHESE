#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//----------Adherent-------------------

    adhTableModel = new AdherentTableModel(ui->TViewLiv);
    filter = new QSortFilterProxyModel(ui->TViewLiv);
    filter->setSourceModel(adhTableModel);
    adhHeaderModel = new AdhHeaderModel(ui->TViewLiv);
    adhHeaderModel->setSourceModel(adhTableModel);
    adhHeaderModel->setSourceModel(filter);
    ui->TViewLiv->setModel(adhTableModel);
    ui->TViewLiv->setModel(filter);
    ui->TViewLiv->setModel(adhHeaderModel);
    ui->TViewLiv->setSortingEnabled(true);
    ui->TViewLiv->verticalHeader()->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

