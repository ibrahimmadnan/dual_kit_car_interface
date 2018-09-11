#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTransform>

#define NEEDLE_PATH ":/img/img/drag_pointer.png"

static int rotation_value=0;
//static QPixmap * p_needle;
GaugeDialog::GaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaugeDialog)
{
    ui->setupUi(this);
    ui->needle_label->setPixmap(QPixmap(NEEDLE_PATH));


}

GaugeDialog::~GaugeDialog()
{
    delete ui;
}


void GaugeDialog::on_forward_button_clicked()
{

  QPixmap needle_pix(NEEDLE_PATH);
  QPixmap rotate(needle_pix.size());
  rotate.fill(Qt::transparent);

  QPainter p(&rotate);

p.setRenderHint(QPainter::Antialiasing);
p.setRenderHint(QPainter::HighQualityAntialiasing);
p.setRenderHint(QPainter::SmoothPixmapTransform);

p.translate(rotate.size().width()/2,rotate.size().height()/2);
p.rotate(rotation_value+=45);
p.translate(-rotate.size().width()/2,-rotate.size().height()/2);

p.drawPixmap(0,0,needle_pix);

p.end();
ui->needle_label->setPixmap(rotate);
ui->needle_label->repaint();


}
