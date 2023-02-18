/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "drawablewindow.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionclose;
    QAction *openimage;
    QAction *zoomin;
    QAction *zoomout;
    QAction *left;
    QAction *right;
    QAction *up;
    QAction *down;
    QAction *actionHomeView;
    QAction *actionlink;
    QAction *actionsave;
    QAction *actionopenGrid;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    DrawableWindow *canvas;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1156, 564);
        MainWindow->setMouseTracking(true);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        openimage = new QAction(MainWindow);
        openimage->setObjectName(QString::fromUtf8("openimage"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Assets/Buttons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openimage->setIcon(icon);
        zoomin = new QAction(MainWindow);
        zoomin->setObjectName(QString::fromUtf8("zoomin"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Assets/Buttons/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomin->setIcon(icon1);
        zoomout = new QAction(MainWindow);
        zoomout->setObjectName(QString::fromUtf8("zoomout"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Assets/Buttons/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomout->setIcon(icon2);
        left = new QAction(MainWindow);
        left->setObjectName(QString::fromUtf8("left"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Assets/Buttons/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        left->setIcon(icon3);
        right = new QAction(MainWindow);
        right->setObjectName(QString::fromUtf8("right"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Assets/Buttons/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        right->setIcon(icon4);
        up = new QAction(MainWindow);
        up->setObjectName(QString::fromUtf8("up"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Assets/Buttons/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        up->setIcon(icon5);
        down = new QAction(MainWindow);
        down->setObjectName(QString::fromUtf8("down"));
        down->setEnabled(true);
        QIcon icon6;
        QString iconThemeName = QString::fromUtf8("What");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8(":/Assets/Buttons/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        down->setIcon(icon6);
        actionHomeView = new QAction(MainWindow);
        actionHomeView->setObjectName(QString::fromUtf8("actionHomeView"));
        actionlink = new QAction(MainWindow);
        actionlink->setObjectName(QString::fromUtf8("actionlink"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionopenGrid = new QAction(MainWindow);
        actionopenGrid->setObjectName(QString::fromUtf8("actionopenGrid"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMouseTracking(true);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        canvas = new DrawableWindow(centralWidget);
        canvas->setObjectName(QString::fromUtf8("canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(200);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(canvas->sizePolicy().hasHeightForWidth());
        canvas->setSizePolicy(sizePolicy);
        canvas->setMinimumSize(QSize(60, 0));
        canvas->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(canvas);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        splitter->addWidget(tableWidget);

        horizontalLayout->addWidget(splitter);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setStyleSheet(QString::fromUtf8(""));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1156, 22));
        menuBar->setStyleSheet(QString::fromUtf8(""));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);

        mainToolBar->addAction(openimage);
        mainToolBar->addAction(zoomin);
        mainToolBar->addAction(zoomout);
        mainToolBar->addAction(left);
        mainToolBar->addAction(right);
        mainToolBar->addAction(up);
        mainToolBar->addAction(down);
        mainToolBar->addAction(actionlink);
        mainToolBar->addAction(actionHomeView);
        mainToolBar->addAction(actionsave);
        mainToolBar->addAction(actionopenGrid);
        mainToolBar->addAction(actionclose);
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(down);
        menu->addAction(up);
        menu->addAction(right);
        menu->addAction(left);
        menu->addAction(zoomout);
        menu->addAction(zoomin);
        menu->addAction(openimage);
        menu->addAction(actionclose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionclose->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        actionclose->setToolTip(QCoreApplication::translate("MainWindow", "\320\267\320\260\320\272\321\200\321\213\321\202\321\214 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionclose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        openimage->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\260\321\201\321\202\321\200", nullptr));
#if QT_CONFIG(tooltip)
        openimage->setToolTip(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\200\320\260\321\201\321\202\321\200\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        openimage->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        zoomin->setText(QCoreApplication::translate("MainWindow", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        zoomin->setToolTip(QCoreApplication::translate("MainWindow", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\320\262\320\260\320\265\321\202 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        zoomin->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+\320\256", nullptr));
#endif // QT_CONFIG(shortcut)
        zoomout->setText(QCoreApplication::translate("MainWindow", "\320\243\320\274\320\265\320\275\321\214\321\210\320\270\321\202\321\214", nullptr));
        left->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        right->setText(QCoreApplication::translate("MainWindow", "->", nullptr));
        up->setText(QCoreApplication::translate("MainWindow", "/\\", nullptr));
        down->setText(QCoreApplication::translate("MainWindow", "\\/", nullptr));
        actionHomeView->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        actionlink->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\262\321\217\320\267\320\260\321\202\321\214", nullptr));
        actionsave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\273\320\270\320\275\320\270\321\216", nullptr));
#if QT_CONFIG(tooltip)
        actionsave->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\273\320\270\320\275\320\270\321\216", nullptr));
#endif // QT_CONFIG(tooltip)
        actionopenGrid->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\263\321\200\320\270\320\264", nullptr));
        canvas->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\321\202\320\276\321\207\320\272\320\260 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\321\202\320\276\321\207\320\272\320\260 2", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\262\321\217\320\267\320\260\321\202\321\214", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
