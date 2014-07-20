#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QQuickWidget>
#include <QAudioInput>
#include <QAudioProbe>
#include <iostream>
#include <QtGlobal>


QMediaPlayer* _player;
QMediaPlaylist* _playlist;

QAudioInput* audioInput;

QAudioProbe* _probe;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QUrl source("../AudioPlayer/rotationsquare.qml");
    QQuickWidget* quickWid = new QQuickWidget();
    quickWid->setSource(source);
    ui->setupUi(this);
    //ui->mdiArea->addSubWindow(quickWid);

    _probe = new QAudioProbe();
    ui->mp3List->acceptDrops();
    ui->mp3List->setDragDropMode(QAbstractItemView::InternalMove);
    quickWid->show();

    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->loadFolderButton, SIGNAL(clicked()), this, SLOT(loadFolder()));

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->volumeSlider, SIGNAL(sliderMoved(int)),this,SLOT(changeVolume()));
    connect(ui->mp3List, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(jump(QModelIndex)));
    connect(ui->position, SIGNAL(sliderMoved(int)),this,SLOT(seekToPosition(int)));
    connect(_probe,SIGNAL(audioBufferProbed(QAudioBuffer)),this,SLOT(processBuffer(QAudioBuffer)));
    connect(ui->next,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->previous,SIGNAL(clicked()),this,SLOT(previous()));


    _player = new QMediaPlayer();
    _playlist = new QMediaPlaylist();
    _probe->setSource(_player);
    _player->setVolume(80);
    ui->position->setRange(0,10000);

    _player->setPlaylist(_playlist);



    connect(_player,SIGNAL(positionChanged(qint64)),this,SLOT(updateStatus(qint64)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::seekToPosition(int i){

    _player->setPosition( i * _player->duration()/10000);
}

void MainWindow::updateStatus(qint64 i){


       ui->position->setValue(i * 10000/_player->duration());

}

void MainWindow::processBuffer(const QAudioBuffer& buf){
   const quint8* data = buf.data<quint8>();
   qint64 len = buf.byteCount();
   if(len > 50)
       len = 50;

   for (int i=0; i < len; i++ )
       {
     //  qDebug() << data[i];

       }

}

void MainWindow::playNext(){

    _player->setMedia(QUrl(ui->mp3List->currentItem()->text()));

    _player->play();
}

void MainWindow::loadAndPlayMp3(){
    _player->setMedia(QUrl(ui->mp3List->currentItem()->text()));
    _player->play();

}


void MainWindow::loadMp3(){

    _player->setMedia(QUrl(ui->mp3List->currentItem()->text()));

}

void MainWindow::loadFolder(){
    QString directory =  QFileDialog::getExistingDirectory(this,tr("Select dir for files to import"),QDir::homePath());

    if(directory.isEmpty())
        return;

    QDir dir(directory);
    QStringList files = dir.entryList(QStringList() << "*.mp3",QDir::Files);
    QList<QMediaContent> content;

    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
        QFileInfo fi(f);
        ui->mp3List->addItem(dir.path() + "/" + f);
    }
    _playlist->addMedia(content);
    ui->mp3List->setCurrentRow(_playlist->currentIndex() != -1? _playlist->currentIndex():0);
}

void MainWindow::loadFile() {
    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Music"),
                                             QDir::homePath(),
                                             tr("Music Files (*.mp3);;"));
    if (_fileName.isEmpty())
        return;

    _playlist->addMedia(QUrl(_fileName));

    ui->mp3List->addItem(new QListWidgetItem(_fileName));


}

void MainWindow::play() {

    _player->play();
}



void MainWindow::next(){
    _playlist->next();
}

void MainWindow::previous(){
    _playlist->previous();
}

void MainWindow::jump(const QModelIndex& index){
    if(index.isValid()){
        qDebug() << "Index is Valid";
        _playlist->setCurrentIndex(index.row());
        _player->play();
    }
    qDebug() << "Index is inValid";
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

