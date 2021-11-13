/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openaction;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QAction *action_11;
    QAction *action_12;
    QAction *action_13;
    QAction *action_14;
    QAction *action_15;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1118, 592);
        openaction = new QAction(MainWindow);
        openaction->setObjectName(QString::fromUtf8("openaction"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Image/\347\256\255\345\244\264 (1).png"), QSize(), QIcon::Normal, QIcon::On);
        action->setIcon(icon);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Image/\345\234\206.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_2->setIcon(icon1);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../Image/\345\244\247\346\213\254\345\217\267.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_3->setIcon(icon2);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../Image/\345\260\217\346\227\2271.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_4->setIcon(icon3);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_5->setCheckable(false);
        action_5->setChecked(false);
        action_5->setEnabled(true);
        action_5->setVisible(true);
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../Image/\346\222\244\351\224\200.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_6->setIcon(icon4);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../Image/\345\217\226 \346\266\210.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_7->setIcon(icon5);
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../Image/\345\210\240\351\231\244\346\211\200\346\234\211\350\256\260\345\275\225.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_8->setIcon(icon6);
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../Image/\346\244\255\345\234\206 1.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_9->setIcon(icon7);
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QString::fromUtf8("action_10"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../Image/\345\217\214\347\256\255\345\244\264.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_10->setIcon(icon8);
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QString::fromUtf8("action_11"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../Image/\345\267\256\345\274\202.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_11->setIcon(icon9);
        action_12 = new QAction(MainWindow);
        action_12->setObjectName(QString::fromUtf8("action_12"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../Image/\345\205\263\351\224\256\350\212\202\347\202\271.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_12->setIcon(icon10);
        action_13 = new QAction(MainWindow);
        action_13->setObjectName(QString::fromUtf8("action_13"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("../Image/\351\200\220\347\202\271\346\224\276\346\240\267.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_13->setIcon(icon11);
        action_14 = new QAction(MainWindow);
        action_14->setObjectName(QString::fromUtf8("action_14"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("../Image/\346\226\207\346\234\254.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_14->setIcon(icon12);
        action_15 = new QAction(MainWindow);
        action_15->setObjectName(QString::fromUtf8("action_15"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("../Image/\346\267\273\345\212\240\345\233\276\347\211\207.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_15->setIcon(icon13);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1118, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menu->addAction(openaction);
        toolBar->addAction(action_5);
        toolBar->addSeparator();
        toolBar->addAction(action);
        toolBar->addAction(action_2);
        toolBar->addAction(action_3);
        toolBar->addAction(action_4);
        toolBar->addAction(action_9);
        toolBar->addAction(action_10);
        toolBar->addAction(action_11);
        toolBar->addAction(action_12);
        toolBar->addAction(action_13);
        toolBar->addSeparator();
        toolBar->addAction(action_14);
        toolBar->addAction(action_15);
        toolBar->addSeparator();
        toolBar->addAction(action_6);
        toolBar->addAction(action_7);
        toolBar->addSeparator();
        toolBar->addAction(action_8);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openaction->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\347\256\255\345\244\264", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\345\234\206", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\346\213\254\345\217\267", nullptr));
        action_4->setText(QCoreApplication::translate("MainWindow", "\346\227\227\345\270\234", nullptr));
        action_5->setText(QCoreApplication::translate("MainWindow", "\346\240\207\346\263\250\346\226\271\345\274\217", nullptr));
        action_6->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
        action_7->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\346\240\207\346\263\250", nullptr));
        action_8->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\346\234\211\346\240\207\346\263\250", nullptr));
        action_9->setText(QCoreApplication::translate("MainWindow", "\346\244\255\345\234\206\345\270\246\347\256\255\345\244\264", nullptr));
        action_10->setText(QCoreApplication::translate("MainWindow", "\345\217\214\347\256\255\345\244\264", nullptr));
        action_11->setText(QCoreApplication::translate("MainWindow", "\345\271\205\345\200\274\345\267\256\345\274\202", nullptr));
        action_12->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\224\256\350\212\202\347\202\271", nullptr));
        action_13->setText(QCoreApplication::translate("MainWindow", "\351\200\220\347\202\271", nullptr));
        action_14->setText(QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254\346\240\207\346\263\250", nullptr));
        action_15->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\233\276\347\211\207", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
