#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QQuickWidget>
#include <QAudioInput>
#include <QAudioProbe>
#include <iostream>
#include <QtGlobal>
#include <QDebug>
//#include <fmod.hpp>
//#include <fmod.h>



QMediaPlayer* _player;
QAudioInput* audioInput;
QAudioProbe* _probe;

//FMOD::System *_system;
//FMOD::Sound *_sound;
//FMOD::Channel *_channel;
//FMOD_RESULT _result;




void initFMod(){
//     _channel = 0;
//     _system->init(32, FMOD_INIT_NORMAL,0);
//     FMOD::System_Create(&_system);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    initFMod();
   // _fileName = new QString();
    QUrl source("../AudioPlayer/rotationsquare.qml");
    QQuickWidget* quickWid = new QQuickWidget();
    quickWid->resize(400, 400);
    quickWid->setResizeMode(QQuickWidget::SizeRootObjectToView);
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

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::processBuffer(const QAudioBuffer& buf){
   const quint8* data = buf.data<quint8>();
   qint64 len = buf.byteCount();
   if(len > 50)
       len = 50;

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

   QByteArray temp = _fileName.toLocal8Bit();



   _player->setMedia(QUrl(_fileName));
//   qDebug()<< temp.data();
//    _system->createSound(temp.data(), FMOD_HARDWARE, 0, &_sound);

}

void MainWindow::play() {
    _player->play();
//    _sound->setMode(FMOD_LOOP_OFF);
//    _system->playSound(FMOD_CHANNEL_FREE, _sound, false, &_channel);


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

