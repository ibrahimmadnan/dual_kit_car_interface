#ifndef GAUGEDIALOG_H
#define GAUGEDIALOG_H

#include <QDialog>

namespace Ui {
class GaugeDialog;
}

class GaugeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaugeDialog(QWidget *parent = nullptr);
    void rotate(int angle);
    ~GaugeDialog();

private slots:
    void on_GaugeDialog_finished(int result);

    void on_forward_button_clicked();

private:
    Ui::GaugeDialog *ui;
};

#endif // GAUGEDIALOG_H
