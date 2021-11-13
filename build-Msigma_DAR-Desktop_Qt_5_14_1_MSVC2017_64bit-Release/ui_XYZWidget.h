/********************************************************************************
** Form generated from reading UI file 'XYZWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XYZWIDGET_H
#define UI_XYZWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XYZWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *xcomboBox;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okpushButton;
    QPushButton *cancelpushButton;

    void setupUi(QWidget *XYZWidget)
    {
        if (XYZWidget->objectName().isEmpty())
            XYZWidget->setObjectName(QString::fromUtf8("XYZWidget"));
        XYZWidget->resize(225, 172);
        verticalLayout_3 = new QVBoxLayout(XYZWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(XYZWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label = new QLabel(XYZWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(XYZWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        doubleSpinBox = new QDoubleSpinBox(XYZWidget);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        verticalLayout_2->addWidget(doubleSpinBox);

        xcomboBox = new QComboBox(XYZWidget);
        xcomboBox->addItem(QString());
        xcomboBox->addItem(QString());
        xcomboBox->setObjectName(QString::fromUtf8("xcomboBox"));

        verticalLayout_2->addWidget(xcomboBox);

        label_4 = new QLabel(XYZWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okpushButton = new QPushButton(XYZWidget);
        okpushButton->setObjectName(QString::fromUtf8("okpushButton"));

        horizontalLayout->addWidget(okpushButton);

        cancelpushButton = new QPushButton(XYZWidget);
        cancelpushButton->setObjectName(QString::fromUtf8("cancelpushButton"));

        horizontalLayout->addWidget(cancelpushButton);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(XYZWidget);

        QMetaObject::connectSlotsByName(XYZWidget);
    } // setupUi

    void retranslateUi(QWidget *XYZWidget)
    {
        XYZWidget->setWindowTitle(QCoreApplication::translate("XYZWidget", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("XYZWidget", "\345\256\232\351\207\217\345\217\202\346\225\260\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("XYZWidget", "X\350\275\264\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("XYZWidget", "Y\350\275\264\357\274\232", nullptr));
        xcomboBox->setItemText(0, QCoreApplication::translate("XYZWidget", "\351\242\221\347\216\207", nullptr));
        xcomboBox->setItemText(1, QCoreApplication::translate("XYZWidget", "\350\247\222\345\272\246", nullptr));

        label_4->setText(QCoreApplication::translate("XYZWidget", "RCS", nullptr));
        okpushButton->setText(QCoreApplication::translate("XYZWidget", "\347\241\256\345\256\232", nullptr));
        cancelpushButton->setText(QCoreApplication::translate("XYZWidget", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XYZWidget: public Ui_XYZWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XYZWIDGET_H
