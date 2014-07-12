#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>

QMediaPlayer* _player;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
   connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
   connect(ui->pauseButton, SIGNAL(clicked()),this,SLOT(pause()));
   connect(ui->stopButton, SIGNAL(clicked()),this,SLOT(stop()));

    //connect(ui->horizontalSlider)
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile() {
    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Music"),
                                             QDir::homePath(),
                                             tr("Music Files (*.mp3);;"));
    if (_fileName.isEmpty())
        return;

    _player->setMedia(QUrl(_fileName));
}

void MainWindow::play() {
    _player->play();
}

void MainWindow::pause(){

    _player->pause();

}

void MainWindow::stop(){
    _player->stop();
}

