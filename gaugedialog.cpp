#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTransform>


static int rotation_value=0;
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

  QPixmap needle_pix(":/img/img/gauge-needle.png");
  int w=ui->needle_label->width();
      int h=ui->needle_label->height();
  //    ui->needle_label->setPixmap(needle_pix.scaled(w,h,Qt::KeepAspectRatio));
//  int w=ui->needle_label->width();
//  int h=ui->needle_label->height();
//  ui->needle_label->setPixmap(needle_pix.scaled(w,h,Qt::KeepAspectRatio));
//  ui->needle_label->setAttribute(Qt::WA_TranslucentBackground);
//   ui->needle_label->repaint();
  QPixmap rotate(needle_pix.scaled(w,h,Qt::KeepAspectRatio));


//  QPainter p(&rotate);


  QTransform transform;

  transform.translate(rotate.size().width()/2,rotate.size().height()/2);
//  p.setRenderHint(QPainter::Antialiasing);
//  p.setRenderHint(QPainter::SmoothPixmapTransform);
//  p.setRenderHint(QPainter::HighQualityAntialiasing);
//  p.translate(rotate.size().width()/2,rotate.size().height()/2);
//  p.rotate(rotation_value);
  transform.rotate(rotation_value+=10);
//  p.translate(-rotate.size().width()/2,-rotate.size().height()/2);
 transform.translate(-rotate.size().width()/2,-rotate.size().height()/2);

// p.drawPixmap(0,0,needle_pix);
//p.end();

ui->needle_label->setPixmap(rotate.transformed(transform));

//ui->needle_label->repaint();


}
