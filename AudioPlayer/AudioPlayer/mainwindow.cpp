#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QQuickWidget>
#include <QQuickItem>

QMediaPlayer* _player;
QQuickWidget* quickWid;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    _fileName = new QString();
    QUrl source("../AudioPlayer/rotationsquare.qml");
    quickWid = new QQuickWidget();
    quickWid->resize(300, 300);
    quickWid->setResizeMode(QQuickWidget::SizeRootObjectToView);
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
    QObject *object = quickWid->rootObject();
    object->children().at(0)->setProperty("color", "black"); // set color of rotating rectangle
    object->children().at(1)->setProperty("color", "yellow");
    object->children().at(0)->setProperty("x", 400);
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

