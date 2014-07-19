/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QPushButton *playButton;
    QPushButton *stopButton;
    QSlider *volumeSlider;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loadFileButton;
    QLabel *label;
    QPushButton *pauseButton;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(525, 545);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 521, 491));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        playButton = new QPushButton(gridLayoutWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/png/play43.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon);

        gridLayout_2->addWidget(playButton, 3, 2, 1, 1);

        stopButton = new QPushButton(gridLayoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/png/square64.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon1);

        gridLayout_2->addWidget(stopButton, 3, 3, 1, 1);

        volumeSlider = new QSlider(gridLayoutWidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setValue(80);
        volumeSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(volumeSlider, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 5, 1, 1);

        loadFileButton = new QPushButton(gridLayoutWidget);
        loadFileButton->setObjectName(QStringLiteral("loadFileButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/png/four30.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadFileButton->setIcon(icon2);

        gridLayout_2->addWidget(loadFileButton, 1, 0, 1, 6);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        pauseButton = new QPushButton(gridLayoutWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/png/pause15.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon3);

        gridLayout_2->addWidget(pauseButton, 3, 4, 1, 1);

        mdiArea = new QMdiArea(gridLayoutWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        gridLayout_2->addWidget(mdiArea, 0, 0, 1, 5);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        playButton->setText(QString());
        stopButton->setText(QString());
        loadFileButton->setText(QApplication::translate("MainWindow", "Load Music File", 0));
        label->setText(QApplication::translate("MainWindow", "Volume", 0));
        pauseButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
