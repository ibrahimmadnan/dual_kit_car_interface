#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTransform>
#include <QThread>
#include "gauge_conversions.h"

#define NEEDLE_PATH ":/img/img/drag_pointer.png"



int angle_to_speed(int angle);
int speed_to_angle(int speed);

 extern int rotation_value;;
GaugeDialog::GaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaugeDialog)
{
    ui->setupUi(this);
    ui->needle_label->setPixmap(QPixmap(NEEDLE_PATH));
//rotate(rotation_value);
rotate(speed_to_angle(0));

}

GaugeDialog::~GaugeDialog()
{
    delete ui;
}


void GaugeDialog::on_forward_button_clicked()
{

//for (int i=rotation_value;i<INPUT_END;i++){
//        rotate(i);
//        ui->lcdNumber->display(QString::number(angle_to_speed(i)));
//        QThread::msleep(10);
//}


    /* test speed */
for (int i=0;i<120;i++){
        rotate(speed_to_angle(i));
        ui->lcdNumber->display(QString::number(i));
        QThread::msleep(10);
}

   // }


}

void GaugeDialog::rotate(int angle)
{

    QPixmap needle_pix(NEEDLE_PATH);
    QPixmap rotate(needle_pix.size());
    rotate.fill(Qt::transparent);

    QPainter p(&rotate);

  p.setRenderHint(QPainter::Antialiasing);
  p.setRenderHint(QPainter::HighQualityAntialiasing);
  p.setRenderHint(QPainter::SmoothPixmapTransform);

  p.translate(rotate.size().width()/2,rotate.size().height()/2);
  p.rotate(angle);
  p.translate(-rotate.size().width()/2,-rotate.size().height()/2);
  p.drawPixmap(0,0,needle_pix);
  p.end();

  ui->needle_label->setPixmap(rotate.scaled(ui->needle_label->width(),ui->needle_label->height(),Qt::KeepAspectRatio));
  ui->needle_label->repaint();


}
