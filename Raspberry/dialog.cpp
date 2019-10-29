#include "dialog.h"
#include "ui_dialog.h"
#include "processthread.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pthread = new processThread(this);
    connect(pthread, SIGNAL(setValue(int, int, int)), this, SLOT(showValue(int, int, int)));
    pthread->start();
}
void Dialog::showValue(int temp, int hum, int dust)
{
    ui->tempValue->setText(QString::number(temp));
    ui->humValue->setText(QString::number(hum));
    ui->dustValue->setText(QString::number(dust));
}
Dialog::~Dialog()
{
    delete ui;
}
