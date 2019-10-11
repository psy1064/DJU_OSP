#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = 0);
    void setData(int h, int t, int d);
private:
    QLabel* tempTitle;
    QLabel* humTiTle;
    QLabel* dustTitle;
    QLabel* temp;
    QLabel* hum;
    QLabel* dust;
    char tempText[2];
    char humText[2];
    char dustText[3];
};

#endif // WIDGET_H
