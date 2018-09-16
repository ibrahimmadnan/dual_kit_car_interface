﻿#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTransform>
#include <QThread>

#define NEEDLE_PATH ":/img/img/drag_pointer.png"
#define INPUT_START 156.0
#define INPUT_END 428.0
#define OUTPUT_START    0.0
#define OUTPUT_END      120.0


int angle_to_speed(int angle);
int speed_to_angle(int speed);

static int rotation_value=INPUT_START;
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

int angle_to_speed(int angle)
{
    float speed;
    float input_start=INPUT_START;
    float input_end=INPUT_END;
    float output_start=OUTPUT_START;
    float output_end=OUTPUT_END;

    speed = output_start + (((output_end - output_start) / (input_end - input_start)) * (angle - input_start));
    return (int)speed;
}

int speed_to_angle(int speed)
{

    float angle;
    float input_start=INPUT_START;
    float input_end=INPUT_END;
    float output_start=OUTPUT_START;
    float output_end=OUTPUT_END;

    angle = input_start + (((input_end - input_start) / (output_end - output_start)) * (speed - output_start));
    return (int)angle;


}
