#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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

private:
    Ui::Dialog *ui;
    processThread* pthread;
    QPalette red, yellow, green, blue;      // 글자 색
    QPixmap tempIconPicture, humIconPicture, dustIconPicture, lightIconPicture;
};

#endif // DIALOG_H
