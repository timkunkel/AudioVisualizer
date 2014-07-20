#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListView>
#include <QQuickWidget>
#include <QQuickItem>
#include <QStringList>
#include <QStringListModel>
#include <QTime>

QMediaPlayer* _player;
QMediaPlaylist* _playList;
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
    _player = new QMediaPlayer();

    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(_player, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)),this,SLOT(changeVolume()));
    connect(ui->positionSlider, SIGNAL(valueChanged(int)), this, SLOT(changePosition(int)));
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(musicPositionChanged(qint64)));


    _player->setVolume(80);
    _playList = new QMediaPlaylist();
    _playList->setPlaybackMode(QMediaPlaylist::Loop);

    _player->setPlaylist(_playList);


    QStringList List;
    List << "string1" << "string2" << "string3";
    QStringListModel* model = new QStringListModel(this);
    model->setStringList(List);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile() {
    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Music"),
                                             QDir::currentPath(),
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

void MainWindow::changePosition(int position){
    if (qAbs(_player->position() - position) > 99)
        _player->setPosition(position);
}

void MainWindow::musicPositionChanged(qint64 position){
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->timeLabel->setText(duration.toString(tr("mm:ss")));
    ui->positionSlider->setValue(position);
}

void MainWindow::updateDuration(qint64 duration){
    ui->positionSlider->setRange(0, duration);
    ui->positionSlider->setEnabled(duration > 0);
    ui->positionSlider->setPageStep(duration / 10);
}
