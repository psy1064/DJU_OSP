#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);		// QApplication 생성
    Dialog dialog;
    dialog.show();

    return a.exec();			// Qt 결과 화면 출력
}

