#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <gaugedialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_gauge_button_clicked()
{
   //hide();
    GaugeDialog *mygauge;
 //   mygauge.setModal(true);
  mygauge =new GaugeDialog(this);
  mygauge->setModal(true);
  mygauge->show();
 // show();

}
