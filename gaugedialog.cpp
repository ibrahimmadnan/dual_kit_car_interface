#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>

GaugeDialog::GaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaugeDialog)
{
    ui->setupUi(this);
}

GaugeDialog::~GaugeDialog()
{
    delete ui;
}

