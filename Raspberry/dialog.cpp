#include "dialog.h"
#include "ui_dialog.h"
#include "processthread.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tempValue->setFont(QFont("FibotoLt",20));
    ui->humValue->setFont(QFont("FibotoLt",20));
    ui->dustValue->setFont(QFont("FibotoLt",20));
    pthread = new processThread(this);
    connect(pthread, SIGNAL(setValue(int, int, int)), this, SLOT(showValue(int, int, int)));
    pthread->start();
}
void Dialog::showValue(int temp, int hum, int dust)
{
    ui->tempValue->setText(QString::number(temp) + "°C");       // tempValue 라벨 텍스트 설정
    ui->tempValue->setAlignment(Qt::AlignCenter);               // 가운데 정렬
    ui->humValue->setText(QString::number(hum) + '%');
    ui->humValue->setAlignment(Qt::AlignCenter);
    ui->dustValue->setText(QString::number(dust) + "㎍/㎥");
    ui->dustValue->setAlignment(Qt::AlignCenter);
}
Dialog::~Dialog()
{
    delete ui;
}
