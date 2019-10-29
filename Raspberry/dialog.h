#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "processthread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setValue(int temp, int hum, int dust);
    ~Dialog();
private slots:
    void showValue(int temp,int hum, int dust);

private:
    Ui::Dialog *ui;
    processThread* pthread;
};

#endif // DIALOG_H
