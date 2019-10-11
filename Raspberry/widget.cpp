#include "widget.h"
#include <stdlib.h>
#include <iostream>
Widget::Widget(QWidget* parent) : QWidget(parent)
{
    tempTitle = new QLabel("Temp",this);
    humTiTle = new QLabel("Hum",this);
    dustTitle = new QLabel("Dust",this);

    temp = new QLabel("30",this);
    hum = new QLabel("70%",this);
    dust = new QLabel("5",this);

    tempTitle->move(0,0);   temp->move(100,0);
    humTiTle->move(0,100);  hum->move(100,100);
    dustTitle->move(0,200); dust->move(100,200);
}
void Widget::setData(int h, int t, int d)
{
    /*temp->setText((const QString&)t);
    hum->setText((const QString&)h);
    dust->setText((const QString&)d);*/
    std::cout << h << t << d << std::endl;
}
