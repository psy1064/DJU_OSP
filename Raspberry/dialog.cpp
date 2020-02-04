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

#define SERVO 1

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QDialog::showFullScreen();  // 실행화면 전체화면으로 설정
    tcpInit();	// 소켓 서버 오픈 및 초기화
    con = 0;
    red.setColor(QPalette::Active, QPalette::WindowText, Qt::red);
    orange.setColor(QPalette::Active, QPalette::WindowText, QColor(255,127,0)); // 주황색
    blue.setColor(QPalette::Active, QPalette::WindowText, Qt::blue);
    green.setColor(QPalette::Active, QPalette::WindowText, Qt::green);      	// Palette에 색 설정

    lightIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/lightbulb.png");
    tempIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/temperature.png");
    humIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/hum.png");
    dustIconPicture.load("/home/pi/Github/DJU_OSP/Raspberry/picture/dust.png");		// Icon에 넣을 사진 경로 지정

    ui->lightIcon->setPixmap(lightIconPicture.scaled(256,256,Qt::KeepAspectRatio));
    ui->tempIcon->setPixmap(tempIconPicture.scaled(256,256,Qt::KeepAspectRatio));
    ui->humIcon->setPixmap(humIconPicture.scaled(256,256,Qt::KeepAspectRatio));
    ui->dustIcon->setPixmap(dustIconPicture.scaled(256,256,Qt::KeepAspectRatio));	// Icon에 사진 넣기

    ui->lightIcon->setAlignment(Qt::AlignCenter);
    ui->tempIcon->setAlignment(Qt::AlignCenter);
    ui->humIcon->setAlignment(Qt::AlignCenter);
    ui->dustIcon->setAlignment(Qt::AlignCenter);				// 사진 가운데 정렬

    ui->tempValue->setFont(QFont("FibotoLt",66));
    ui->humValue->setFont(QFont("FibotoLt",66));
    ui->dustValue->setFont(QFont("FibotoLt",66));	// 데이터 출력 값 폰트, 글자 크기 설정

    if(wiringPiSetup()==-1) exit(1);

    softPwmCreate(SERVO, 0, 100);
    softPwmWrite(SERVO, 15);
    pinMode(SERVO, INPUT);		// 서보모터 Arm 중간 위치

    pthread = new processThread(this);	// 센서 데이터 수집 쓰레드 동적 할당
    connect(pthread, SIGNAL(setValue(int, int, int, int)), this, SLOT(showValue(int, int, int)));	// 센서 데이터 수집 쓰레드의 setValue 함수에서 값을 읽어와 showValue에 넣음

    pthread->start();	// 쓰레드 run

    timer = new QTimer(this);	// 화면에 시간을 표시할 타이머 설정
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));	// 설정한 시간마다 showTime() 실행
    showTime();	// 처음 한번 현재 시간 출력
    timer->start(1000);	// 1초 간격으로 timer 동작
}
void Dialog::showValue(int temp, int hum, int dust)
{
    std::cout << "showValue\n";
    ui->tempValue->setText(QString::number(temp) + "°C");       // tempValue 라벨 텍스트 설정
    ui->tempValue->setAlignment(Qt::AlignCenter);               // 가운데 정렬
    ui->humValue->setText(QString::number(hum) + "%");
    ui->humValue->setAlignment(Qt::AlignCenter);
    ui->dustValue->setAlignment(Qt::AlignCenter);

    if(dust >= 0 && dust <= 30)
    {
        ui->dustValue->setPalette(blue);
        ui->dustValue->setText("좋음\n(" + QString::number(dust) + "㎍/㎥)");
    }
    else if(dust > 30 && dust <= 80)
    {
        ui->dustValue->setPalette(green);
        ui->dustValue->setText("보통\n(" + QString::number(dust) + "㎍/㎥)");
    }
    else if(dust > 80 && dust <= 150)
    {
        ui->dustValue->setPalette(orange);
        ui->dustValue->setText("나쁨\n(" + QString::number(dust) + "㎍/㎥)");
    }
    else if(dust > 150)
    {
        ui->dustValue->setPalette(red);
        ui->dustValue->setText("매우나쁨\n(" + QString::number(dust) + "㎍/㎥)");
    }
    // 미세먼지 범위에 따라 색 변경
} // 센서 데이터 화면에 출력
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
    delay(1000);
    pinMode(SERVO, INPUT);	// 서보모터 떨림 현상 방지
    delay(500);
} // 화면의 On 버튼을 눌렀을 때 서보모터로 전등  On
void Dialog::on_offButton_clicked()
{
    std::cout << "turnoff\n";

    pinMode(SERVO, OUTPUT);
    softPwmCreate(SERVO, 0, 50);
    softPwmWrite(SERVO, 18);
    delay(100);
    softPwmWrite(SERVO, 15);
    delay(1000);
    pinMode(SERVO, INPUT);	// 서보모터 떨림 현상 방지
    delay(500);
} // 화면의 Off 버튼을 눌렀을 때 서보모터로 전등  Off
void Dialog::showTime()
{
    QTime time = QTime::currentTime();	// 현재 시간
    QDate date = QDate::currentDate();	// 현재 날짜
    QString dateText;
    QString timeText;

    dateText = date.toString("yy년 MM월 dd일");	// 19년 12월 02일 형식으로 출력
    if(time.second()%2==0)      timeText = time.toString("AP hh : mm : ss   ");
    else                        timeText = time.toString("AP hh   mm   ss   ");

    ui->dateValue->setText(dateText);
    ui->timeValue->setText(timeText);
} // 화면에 현재 날짜 시간 출력
void Dialog::tcpInit()
{
    QHostAddress hostAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0 ; i < ipAddressesList.size() ; ++i)
    {
        if(ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            hostAddress = ipAddressesList.at(i);
            break;
        }
    }

    if(hostAddress.toString().isEmpty())    hostAddress = QHostAddress(QHostAddress::LocalHost);

    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(hostAddress, 9999))	// 서버 오픈 ip : hostaddress, port : 9999
    {
        std::cout << "connect Failed\n";
        close();
    }
    else std::cout << "Tcp Server Open\n";
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));	// 서버에 소켓이 접속했을 때 newConnection() 실행
} // tcp 소켓 통신 서버 오픈 및 초기화
void Dialog::newConnection()
{
    std::cout << "connected" << con << std::endl;

    if(con!=0)
    {
        client->close();
        con--;
    } // 접속되어 있던 소켓 연결 해제
    client = tcpServer->nextPendingConnection();
    con++;
    connect(pthread, SIGNAL(setValue(int, int, int, int)), this, SLOT(sendValue(int, int, int, int)));    // 수집된 센서 데이터 송신
    connect(client,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disConnected()));
} // 서버에 소켓이 접속했을 때 실행
void Dialog::sendValue(int temp, int hum, int dust,int human)
{
    std::cout << "sendData\n";
    QByteArray tempbyte = QByteArray::number(temp);
    QByteArray humbyte = QByteArray::number(hum);
    QByteArray dustbyte = QByteArray::number(dust);
    QByteArray humanbyte = QByteArray::number(human);

    client->write(tempbyte+","+humbyte+","+dustbyte+","+humanbyte);
} // 수집된 센서 데이터 어플리케이션에 송신
void Dialog::readData()
{
    std::cout << "readData\n";
    if(client->bytesAvailable()>=0)
    {
        QByteArray data = client->readAll();
        if(data.toStdString() == "On")          on_onButton_clicked();
        else if(data.toStdString() == "Off")    on_offButton_clicked();
        else if(data.toStdString() == "cctvOn")    system("sudo motion");
        else if(data.toStdString() == "cctvOff")   system("sudo killall -15 motion");
    }
} // 데이터 수신 함수
void Dialog::disConnected()
{
    std::cout << "disconnected\n";
    client->close();
    --con;

    disconnect(pthread, SIGNAL(setValue(int, int, int, int)), this, SLOT(sendValue(int, int, int, int)));    // 수집된 센서 데이터 송신
} // 소켓 연결 해제
