/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *dateValue;
    QLabel *timeValue;
    QHBoxLayout *horizontalLayout;
    QLabel *tempIcon;
    QLabel *humIcon;
    QLabel *dustIcon;
    QLabel *lightIcon;
    QHBoxLayout *horizontalLayout_2;
    QLabel *tempValue;
    QLabel *humValue;
    QLabel *dustValue;
    QVBoxLayout *verticalLayout;
    QPushButton *onButton;
    QPushButton *offButton;
    QLabel *isConnectedValue;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(402, 273);
        Dialog->setAutoFillBackground(false);
        Dialog->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayoutWidget_2 = new QWidget(Dialog);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 30, 401, 241));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        dateValue = new QLabel(verticalLayoutWidget_2);
        dateValue->setObjectName(QStringLiteral("dateValue"));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        dateValue->setFont(font);
        dateValue->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(dateValue);

        timeValue = new QLabel(verticalLayoutWidget_2);
        timeValue->setObjectName(QStringLiteral("timeValue"));
        timeValue->setFont(font);
        timeValue->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(timeValue);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tempIcon = new QLabel(verticalLayoutWidget_2);
        tempIcon->setObjectName(QStringLiteral("tempIcon"));

        horizontalLayout->addWidget(tempIcon);

        humIcon = new QLabel(verticalLayoutWidget_2);
        humIcon->setObjectName(QStringLiteral("humIcon"));

        horizontalLayout->addWidget(humIcon);

        dustIcon = new QLabel(verticalLayoutWidget_2);
        dustIcon->setObjectName(QStringLiteral("dustIcon"));

        horizontalLayout->addWidget(dustIcon);

        lightIcon = new QLabel(verticalLayoutWidget_2);
        lightIcon->setObjectName(QStringLiteral("lightIcon"));

        horizontalLayout->addWidget(lightIcon);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tempValue = new QLabel(verticalLayoutWidget_2);
        tempValue->setObjectName(QStringLiteral("tempValue"));

        horizontalLayout_2->addWidget(tempValue);

        humValue = new QLabel(verticalLayoutWidget_2);
        humValue->setObjectName(QStringLiteral("humValue"));

        horizontalLayout_2->addWidget(humValue);

        dustValue = new QLabel(verticalLayoutWidget_2);
        dustValue->setObjectName(QStringLiteral("dustValue"));
        dustValue->setScaledContents(false);

        horizontalLayout_2->addWidget(dustValue);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        onButton = new QPushButton(verticalLayoutWidget_2);
        onButton->setObjectName(QStringLiteral("onButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(onButton->sizePolicy().hasHeightForWidth());
        onButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        onButton->setFont(font1);
        onButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        onButton->setCheckable(false);
        onButton->setChecked(false);
        onButton->setAutoRepeat(false);

        verticalLayout->addWidget(onButton);

        offButton = new QPushButton(verticalLayoutWidget_2);
        offButton->setObjectName(QStringLiteral("offButton"));
        sizePolicy.setHeightForWidth(offButton->sizePolicy().hasHeightForWidth());
        offButton->setSizePolicy(sizePolicy);
        offButton->setFont(font1);
        offButton->setStyleSheet(QStringLiteral("background:rgb(255,255,255)"));

        verticalLayout->addWidget(offButton);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        isConnectedValue = new QLabel(Dialog);
        isConnectedValue->setObjectName(QStringLiteral("isConnectedValue"));
        isConnectedValue->setGeometry(QRect(7, 0, 381, 22));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Homekeeper", nullptr));
        dateValue->setText(QApplication::translate("Dialog", "TextLabel", nullptr));
        timeValue->setText(QApplication::translate("Dialog", "TextLabel", nullptr));
        tempIcon->setText(QString());
        humIcon->setText(QString());
        dustIcon->setText(QString());
        lightIcon->setText(QString());
        tempValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">temp</p></body></html>", nullptr));
        humValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">hum</p></body></html>", nullptr));
        dustValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">dust</p></body></html>", nullptr));
        onButton->setText(QApplication::translate("Dialog", "on", nullptr));
        offButton->setText(QApplication::translate("Dialog", "off", nullptr));
        isConnectedValue->setText(QApplication::translate("Dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
