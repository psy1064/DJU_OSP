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
    void showTime();					// 화면에 현재 날짜 시간 출력

    void newConnection();				// 서버에 소켓이 접속했을 때 실행
    void readData();					// 데이터 수신 함수
    void disConnected();				// 소켓 연결 해제 시 실행
    void sendValue(int temp, int hum, int dust, int human);	// 수집된 센서 데이터 어플리케이션에 송신

    void cctv_center();
    void cctv_right();
    void cctv_left();                   // cctv 위치 조정
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
    int rad;    // 서보모터 각도
};

#endif // DIALOG_H
