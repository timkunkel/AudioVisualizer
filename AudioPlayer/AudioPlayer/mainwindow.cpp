#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QQuickWidget>

QMediaPlayer* _player;

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


    quickWid->show();

    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->volumeSlider, SIGNAL(sliderMoved(int)),this,SLOT(changeVolume()));


    _player = new QMediaPlayer();
    _player->setVolume(80);
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

