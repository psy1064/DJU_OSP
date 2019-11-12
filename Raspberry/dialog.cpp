#include "dialog.h"
#include "ui_dialog.h"
#include "processthread.h"

#include <QPixmap>
#include <QColor>
#include <QTimer>
#include <QDateTime>
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

#define SERVO 2

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    red.setColor(QPalette::Active, QPalette::WindowText, Qt::red);
    orange.setColor(QPalette::Active, QPalette::WindowText, QColor(255,127,0)); //
    blue.setColor(QPalette::Active, QPalette::WindowText, Qt::blue);
    green.setColor(QPalette::Active, QPalette::WindowText, Qt::green);      	// Palette에 색 설정

    lightIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/lightbulb.png");
    tempIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/temperature.png");
    humIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/hum.png");
    dustIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/dust.png");		// Icon에 넣을 사진 경로 지정

    ui->lightIcon->setPixmap(lightIconPicture.scaled(64,64,Qt::KeepAspectRatio));
    ui->tempIcon->setPixmap(tempIconPicture.scaled(64,64,Qt::KeepAspectRatio));
    ui->humIcon->setPixmap(humIconPicture.scaled(64,64,Qt::KeepAspectRatio));
    ui->dustIcon->setPixmap(dustIconPicture.scaled(64,64,Qt::KeepAspectRatio));	// Icon에 사진 넣기

    ui->lightIcon->setAlignment(Qt::AlignCenter);
    ui->tempIcon->setAlignment(Qt::AlignCenter);
    ui->humIcon->setAlignment(Qt::AlignCenter);
    ui->dustIcon->setAlignment(Qt::AlignCenter);				// 사진 가운데 정렬

    ui->tempValue->setFont(QFont("FibotoLt",16));
    ui->humValue->setFont(QFont("FibotoLt",16));
    ui->dustValue->setFont(QFont("FibotoLt",16));	// 데이터 출력 값 폰트, 글자 크기 설정

    if(wiringPiSetup()==-1) exit(1);

    softPwmCreate(SERVO, 0, 100);
    softPwmWrite(SERVO, 15);
    pinMode(SERVO, INPUT);

    pthread = new processThread(this);			// 센서 데이터 수집 쓰레드 동적 할당
    connect(pthread, SIGNAL(setValue(int, int, int)), this, SLOT(showValue(int, int, int)));	// 센서 데이터 수집 쓰레드의 setValue 함수에서 값을 읽어와 showValue에 넣음

    pthread->start();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    showTime();
    timer->start(1000);
}
void Dialog::showValue(int temp, int hum, int dust)
{
    ui->tempValue->setText(QString::number(temp) + "°C");       // tempValue 라벨 텍스트 설정
    ui->tempValue->setAlignment(Qt::AlignCenter);               // 가운데 정렬
    ui->humValue->setText(QString::number(hum) + "%");
    ui->humValue->setAlignment(Qt::AlignCenter);
    ui->dustValue->setText(QString::number(dust) + "\n㎍/㎥");
    ui->dustValue->setAlignment(Qt::AlignCenter);
    if(dust >= 0 && dust <= 30)         ui->dustValue->setPalette(blue);
    else if(dust > 30 && dust <= 80)    ui->dustValue->setPalette(green);
    else if(dust > 80 && dust <= 150)   ui->dustValue->setPalette(orange);
    else if(dust > 150)                 ui->dustValue->setPalette(red);
    // 미세먼지 범위에 따라 색 변경
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_onButton_clicked()
{
    std::cout << "turnon\n";

    pinMode(SERVO, OUTPUT);
    softPwmCreate(SERVO, 0, 50);
    softPwmWrite(SERVO, 12);
    delay(100);
    softPwmWrite(SERVO, 15);
    delay(100);
    pinMode(SERVO, INPUT);
}

void Dialog::on_offButton_clicked()
{
    std::cout << "turnoff\n";

    pinMode(SERVO, OUTPUT);
    softPwmCreate(SERVO, 0, 50);
    softPwmWrite(SERVO, 18);
    delay(100);
    softPwmWrite(SERVO, 15);
    delay(100);
    pinMode(SERVO, INPUT);
}

void Dialog::showTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString dateText;
    QString timeText;

    dateText = date.toString("  yyyy-MM-dd");
    if(time.second()%2==0)  timeText = time.toString("hh:mm:ss");
    else                    timeText = time.toString("hh mm ss");

    ui->dateValue->setText(dateText);
    ui->timeValue->setText(timeText);
}
