#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>

#include "process.h"

class processThread : public QThread
{
    Q_OBJECT
public:
    explicit processThread(QObject *parent = 0);

private:
    PROCESS process;
    int temp, dust, hum, human; // process로 부터 받아오는 센서 데이터 값
    int pre_temp, pre_dust, pre_hum, pre_human;     // 변하는 데이터 값 확인
    void run();
signals:
    void setValue(int temp, int hum, int dust, int human);
};

#endif // PROCESSTHREAD_H
