#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPixmap>
#include <QtNetwork>
#include "processthread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void tcpInit();		// tcp 소켓 통신 서버 오픈 및 초기화
    ~Dialog();
private slots:
    void showValue(int temp, int hum, int dust);	// 센서 데이터 화면에 출력
    void on_onButton_clicked(); 			// 화면의 On 버튼을 눌렀을 때 서보모터로 전등 On
    void on_offButton_clicked();			// 화면의 Off 버튼을 눌렀을 때 서보모터로 전등 Off
    void showTime();					// 화면에 현재 날짜 시간 출력

    void newConnection();				// 서버에 소켓이 접속했을 때 실행
    void readData();					// 데이터 수신 함수
    void disConnected();				// 소켓 연결 해제 시 실행
    void sendValue(int temp, int hum, int dust, int human);	// 수집된 센서 데이터 어플리케이션에 송신
private:
    Ui::Dialog *ui;
    QTimer* timer;				// Timer 변수
    processThread* pthread;			// 센서 데이터 수집 프로세스 쓰레드
    QPalette red, orange, green, blue;      	// 글자 색
    QPixmap tempIconPicture, humIconPicture, dustIconPicture, lightIconPicture;	// 아이콘 사진 지정 변수

    QTcpServer* tcpServer;			// Tcp 서버
    QTcpSocket* client;				// Tcp socket

    int con; // server 접속한 소켓 수
    int temp, hum, dust, human; // 받아온 센서 데이터 저장용
};

#endif // DIALOG_H
