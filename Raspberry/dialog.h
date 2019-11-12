#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPixmap>
#include "processthread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void showValue(int temp,int hum, int dust);

    void on_onButton_clicked();

    void on_offButton_clicked();

    void showTime();

private:
    Ui::Dialog *ui;
    QTimer* timer;
    processThread* pthread;
    QPalette red, orange, green, blue;      // 글자 색
    QPixmap tempIconPicture, humIconPicture, dustIconPicture, lightIconPicture;
};

#endif // DIALOG_H
