#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton* loadFileButton = new QPushButton("Load Music FIle");

    MainWindow window;
    QWidget* parent = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(parent);
    layout->addWidget(loadFileButton);

//    QObject::connect(loadFileButton, SIGNAL(clicked(),
//                                                &app, SLOT( ))

    parent->show();
    window.show();
    return app.exec();
}
