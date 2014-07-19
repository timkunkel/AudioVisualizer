#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QQuickWidget>
#include <QAudioInput>
#include <QAudioProbe>
#include <iostream>
#include <QtGlobal>
#include <fmod.hpp>
#include <fmod_errors.h>




QMediaPlayer* _player;
QAudioInput* audioInput;
QAudioProbe* _probe;

FMOD::System *_system;
FMOD::Sound *_sound;
FMOD::Channel *_channel;
FMOD_RESULT _result;

bool quit = false;
    int i = 0;



void initFMod(){
    FMOD::System_Create(&_system);
    _channel = 0;
    _result =  _system->System::init(32, FMOD_INIT_NORMAL,0);
    if(_result != FMOD_OK)
           {
               qDebug() << "Init"<<FMOD_ErrorString(_result); //// here's the error
           }


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
    connect(quickWid,SIGNAL(),this,SLOT(process()));


    _player = new QMediaPlayer();
    _probe->setSource(_player);
    _player->setVolume(80);




}


MainWindow::~MainWindow()
{   _system->release();
    delete ui;
}



void MainWindow::process(){
   qDebug() << "in process";
}

void MainWindow::loadFile() {

    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Music"),
                                             QDir::homePath(),
                                             tr("Music Files (*.mp3);;"));
    if (_fileName.isEmpty())
        return;

   QByteArray temp = _fileName.toLocal8Bit();

   qDebug()<< temp.data();
    initFMod();
    _result = _system->createSound(temp.data(), FMOD_HARDWARE, 0, &_sound);
    if(_result != FMOD_OK)
           {
               qDebug() << FMOD_ErrorString(_result); //// here's the error
           }




}

void MainWindow::update(){
    qDebug() << "Update";
}

void MainWindow::play() {

    float spectrum[256];
    float wavedata[512];

    _system->getWaveData(wavedata, 256, 0);
    qDebug()<<_system->getSpectrum(spectrum, 256, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE);
    _sound->setMode(FMOD_LOOP_OFF);

   _result =  _system->playSound(FMOD_CHANNEL_FREE, _sound, false, &_channel);
   if(_result != FMOD_OK)
          {
              qDebug() << FMOD_ErrorString(_result); //// here's the error
          }


}

void MainWindow::paintEvent(QPaintEvent *){

}

void MainWindow::stop() {
    _channel->stop();
}
void MainWindow::pause() {
    bool isPaused;
    _channel->getPaused(&isPaused);
    _channel->setPaused(!isPaused);
}

void MainWindow::changeVolume(){
    float vol = ui->volumeSlider->value();
    qDebug()<< vol;
    _channel->setVolume(vol/100.0f);
}

