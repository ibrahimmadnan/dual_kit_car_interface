#include "gaugedialog.h"
#include "ui_gaugedialog.h"
#include <mainwindow.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTransform>
#include <QThread>
#include "gauge_conversions.h"
#include "XPlaneUDPClient.h"

#include <QDebug>
#include <QString>
#include <string.h>
#include "XPlaneBeaconListener.h"
using namespace std;


#define NEEDLE_PATH ":/img/img/drag_pointer.png"

// our callback for changed values.
string host;
uint16_t port;
static bool found = false;

void receiverCallbackFloat(std::string dataref, float value) {
    qDebug() << "receiverCallbackFloat got ["<< QString::fromStdString(dataref) << "] and [" << QString::number(value);

}

void receiverCallbackString(std::string dataref, std::string value) {
     qDebug() << "receiverCallbackString got [" <<QString::fromStdString(dataref) << "] and [" << &value<< "]" ;
}

void receiverBeaconCallback(XPlaneBeaconListener::XPlaneServer server,
        bool exists) {
    qDebug() << "receiverBeaconCallback got [" << QString::fromStdString(server.toString()) << " is " << (exists ? "alive" : "dead") << "]";
    host = server.host;
    port = server.receivePort;
    found = true;
}


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



void GaugeDialog::on_button_udp_clicked()
{

  //  XPlaneBeaconListener* test = new XPlaneBeaconListener ();

    XPlaneBeaconListener::getInstance()->registerNotificationCallback(
            std::bind(receiverBeaconCallback, std::placeholders::_1,
                    std::placeholders::_2));
    XPlaneBeaconListener::getInstance()->setDebug(0);

    qDebug() << "Press Control-C to abort.";

    // wait for a server
    while (!found) {
        //sleep (1);
         QThread::msleep(1000);
    }

    qDebug() << "Found server " <<QString::fromStdString(host) << ":" << QString::number(port);


    XPlaneUDPClient xp(host, port,
            std::bind(receiverCallbackFloat, std::placeholders::_1,
                    std::placeholders::_2),
            std::bind(receiverCallbackString, std::placeholders::_1,
                    std::placeholders::_2));
    xp.setDebug(0);

    xp.subscribeDataRef("sim/aircraft/view/acf_descrip[0][40]", 1);
    xp.subscribeDataRef("sim/cockpit2/engine/actuators/throttle_ratio[0]", 10);

    xp.sendCommand("sim/flight_controls/flaps_down");
    xp.sendCommand("sim/flight_controls/flaps_down");

    float r = 0;
    float i = 0.01;

    while (1) {
    //	usleep (1000 * 50);
 QThread::msleep(50);
        xp.setDataRef("sim/multiplayer/controls/engine_throttle_request[0]", r);
        r += i;

        if (r > 1) {
            i = -0.01;
        } else if (r < 0) {
            i = 0.01;
        }

    }


}

void GaugeDialog::on_testdebug_clicked()
{
    qDebug()<< "testing debug";
}
