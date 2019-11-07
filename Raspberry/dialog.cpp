#include "dialog.h"
#include "ui_dialog.h"
#include "processthread.h"
//#include <QImage>
#include <QPixmap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    red.setColor(QPalette::Active, QPalette::WindowText, Qt::red);
    yellow.setColor(QPalette::Active, QPalette::WindowText, Qt::yellow);
    blue.setColor(QPalette::Active, QPalette::WindowText, Qt::blue);
    green.setColor(QPalette::Active, QPalette::WindowText, Qt::green);      	// Palette에 색 설정

    tempIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/temperature.png");
    humIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/hum.png");
    dustIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/dust.png");		// Icon에 넣을 사진 경로 지정

    ui->tempIcon->setPixmap(tempIconPicture.scaled(128,128,Qt::KeepAspectRatio));
    ui->humIcon->setPixmap(humIconPicture.scaled(128,128,Qt::KeepAspectRatio));
    ui->dustIcon->setPixmap(dustIconPicture.scaled(128,128,Qt::KeepAspectRatio));	// Icon에 사진 넣기

    ui->tempIcon->setAlignment(Qt::AlignCenter);
    ui->humIcon->setAlignment(Qt::AlignCenter);
    ui->dustIcon->setAlignment(Qt::AlignCenter);				// 사진 가운데 정렬

    ui->tempValue->setFont(QFont("FibotoLt",20));
    ui->humValue->setFont(QFont("FibotoLt",20));
    ui->dustValue->setFont(QFont("FibotoLt",20));	// 각 센세 데이터 출력 값 폰트, 글자 크기 설정

    pthread = new processThread(this);			// 센서 데이터 수집 쓰레드 동적 할당
    connect(pthread, SIGNAL(setValue(int, int, int)), this, SLOT(showValue(int, int, int)));	// 센서 데이터 수집 쓰레드의 setValue 함수에서 값을 읽어와 showValue에 넣음
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
    if(dust >= 0 && dust <= 30)         ui->dustValue->setPalette(blue);
    else if(dust > 30 && dust <= 80)    ui->dustValue->setPalette(green);
    else if(dust > 80 && dust <= 150)   ui->dustValue->setPalette(yellow);
    else if(dust > 150)                 ui->dustValue->setPalette(red);
    // 미세먼지 범위에 따라 색 변경

}
Dialog::~Dialog()
{
    delete ui;
}
