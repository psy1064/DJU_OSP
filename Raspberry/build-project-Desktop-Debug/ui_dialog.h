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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *dateValue;
    QLabel *timeValue;
    QHBoxLayout *horizontalLayout;
    QLabel *tempIcon;
    QLabel *humIcon;
    QLabel *dustIcon;
    QHBoxLayout *horizontalLayout_2;
    QLabel *tempValue;
    QLabel *humValue;
    QLabel *dustValue;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1121, 515);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        Dialog->setAutoFillBackground(false);
        Dialog->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        dateValue = new QLabel(Dialog);
        dateValue->setObjectName(QStringLiteral("dateValue"));
        QFont font;
        font.setPointSize(66);
        font.setBold(true);
        font.setWeight(75);
        dateValue->setFont(font);
        dateValue->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(dateValue);

        timeValue = new QLabel(Dialog);
        timeValue->setObjectName(QStringLiteral("timeValue"));
        timeValue->setFont(font);
        timeValue->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(timeValue);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tempIcon = new QLabel(Dialog);
        tempIcon->setObjectName(QStringLiteral("tempIcon"));
        tempIcon->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(tempIcon);

        humIcon = new QLabel(Dialog);
        humIcon->setObjectName(QStringLiteral("humIcon"));

        horizontalLayout->addWidget(humIcon);

        dustIcon = new QLabel(Dialog);
        dustIcon->setObjectName(QStringLiteral("dustIcon"));

        horizontalLayout->addWidget(dustIcon);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tempValue = new QLabel(Dialog);
        tempValue->setObjectName(QStringLiteral("tempValue"));
        tempValue->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(tempValue);

        humValue = new QLabel(Dialog);
        humValue->setObjectName(QStringLiteral("humValue"));

        horizontalLayout_2->addWidget(humValue);

        dustValue = new QLabel(Dialog);
        dustValue->setObjectName(QStringLiteral("dustValue"));
        dustValue->setScaledContents(false);

        horizontalLayout_2->addWidget(dustValue);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


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
        tempValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">temp</p></body></html>", nullptr));
        humValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">hum</p></body></html>", nullptr));
        dustValue->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\">dust</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
