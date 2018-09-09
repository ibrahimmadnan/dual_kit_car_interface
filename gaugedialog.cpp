#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>


static int rotation_value=10;
//static QPixmap * p_needle;
GaugeDialog::GaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaugeDialog)
{
    ui->setupUi(this);

    QPixmap needlepix(":/img/img/gauge-needle.png");

    int w=ui->needle_label->width();
    int h=ui->needle_label->height();
    ui->needle_label->setPixmap(needlepix.scaled(w,h,Qt::KeepAspectRatio));
    ui->needle_label->setAttribute(Qt::WA_TranslucentBackground);
    ui->needle_label->repaint();

}

GaugeDialog::~GaugeDialog()
{
    delete ui;
}


void GaugeDialog::on_forward_button_clicked()
{
//QPixmap right_rotate(*ui->needle_label->pixmap());
//QMatrix rm;
//rm.rotate(rotation_value);
//   right_rotate=right_rotate.transformed(rm);
//   ui->needle_label->setPixmap(right_rotate);
//   ui->needle_label->setPixmap(needlepix);

  QPixmap needle_pix(*ui->needle_label->pixmap());
//  int w=ui->needle_label->width();
//  int h=ui->needle_label->height();
//  ui->needle_label->setPixmap(needle_pix.scaled(w,h,Qt::KeepAspectRatio));
//  ui->needle_label->setAttribute(Qt::WA_TranslucentBackground);
//   ui->needle_label->repaint();
  QPixmap rotate(needle_pix.size());

  QPainter p(&rotate);
  p.setRenderHint(QPainter::Antialiasing);
  p.setRenderHint(QPainter::SmoothPixmapTransform);
  p.setRenderHint(QPainter::HighQualityAntialiasing);
  p.translate(rotate.size().width()/2,rotate.size().height()/2);
  p.rotate(rotation_value);
  p.translate(-rotate.size().width()/2,-rotate.size().height()/2);

p.drawPixmap(0,0,needle_pix);
p.end();
ui->needle_label->setPixmap(rotate);



}
