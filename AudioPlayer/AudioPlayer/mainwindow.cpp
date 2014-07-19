#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QQuickWidget>
#include <QAudioInput>
#include <QAudioProbe>
#include <iostream>
#include <QtGlobal>


QMediaPlayer* _player;
QAudioInput* audioInput;
QAudioProbe* _probe;


void Testmethod(){


    }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // _fileName = new QString();
    QUrl source("../AudioPlayer/rotationsquare.qml");
    QQuickWidget* quickWid = new QQuickWidget();
    quickWid->setSource(source);
    ui->setupUi(this);
    ui->mdiArea->addSubWindow(quickWid);

    _probe = new QAudioProbe();

    quickWid->show();

    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->volumeSlider, SIGNAL(sliderMoved(int)),this,SLOT(changeVolume()));
    connect(_probe,SIGNAL(audioBufferProbed(QAudioBuffer)),this,SLOT(processBuffer(QAudioBuffer)));

    _player = new QMediaPlayer();
    _probe->setSource(_player);
    _player->setVolume(80);
    qDebug()<< "Test " <<_probe->isActive();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processBuffer(const QAudioBuffer& buf){
   const quint8* data = buf.data<quint8>();
   qint64 len = buf.byteCount();
   if(len > 4096)
       len = 4096;

   for (int i=0; i < len; i++ )
       {
       qDebug() << data[i];

       }

   //qDebug()<< buf.format().;
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


void MainWindow::stop() {
    _player->stop();
}
void MainWindow::pause() {
    if(_player->state() == 2)
        _player->play();
    else
        _player->pause();
}

void MainWindow::changeVolume(){
    int vol = ui->volumeSlider->value();
    _player->setVolume(vol);
}

