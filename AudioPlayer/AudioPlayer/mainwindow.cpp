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
#include <QTime>
#include <QMimeData>
#include <QQuickItem>

QMediaPlayer* _player;
QMediaPlaylist* _playlist;
QAudioInput* audioInput;
QQuickWidget* _quickWid;
QAudioProbe* _probe;
QObject* _qmlObject;
QObject* _redSquare;
QObject* _particles;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QUrl source("../AudioPlayer/rotationsquare.qml");
    _quickWid = new QQuickWidget();
    _quickWid->resize(400, 400);
    _quickWid->setResizeMode(QQuickWidget::SizeRootObjectToView);
    _quickWid->setSource(source);
    ui->setupUi(this);
    //ui->mdiArea->addSubWindow(quickWid);

    _probe = new QAudioProbe();
    ui->mp3List->acceptDrops();
    //ui->mp3List->setDragDropMode(QAbstractItemView::InternalMove);
    ui->mp3List->setSelectionMode(QAbstractItemView::SingleSelection);
    _quickWid->show();

    _player = new QMediaPlayer();
    _playlist = new QMediaPlaylist();

    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->loadFolderButton, SIGNAL(clicked()), this, SLOT(loadFolder()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->volumeSlider, SIGNAL(sliderMoved(int)),this,SLOT(changeVolume()));
    connect(_player, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)));
    connect(_player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(updateMp3ListIndex(QMediaContent)));
    connect(ui->mp3List, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(jump(QModelIndex)));
    connect(ui->position, SIGNAL(valueChanged(int)), this, SLOT(changePosition(int)));
    connect(_probe,SIGNAL(audioBufferProbed(QAudioBuffer)),this,SLOT(processBuffer(QAudioBuffer)));
    connect(ui->next,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->previous,SIGNAL(clicked()),this,SLOT(previous()));
    connect(_player,SIGNAL(positionChanged(qint64)), this, SLOT(musicPositionChanged(qint64)));
    connect(_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(updateButtonIcons(QMediaPlayer::State)));
    connect(ui->repeatButton, SIGNAL(clicked()), this, SLOT(changePlaybackMode()));
    connect(_playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(updateMp3List(int, int)));

    _probe->setSource(_player);
    _player->setVolume(80);

    _player->setPlaylist(_playlist);

    this->setAcceptDrops(true);

    _qmlObject = _quickWid->rootObject();
    _redSquare = _qmlObject->children().at(2);
    _particles = _qmlObject->children().at(1);
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::processBuffer(const QAudioBuffer& buf){
   const quint8* data = buf.data<quint8>();
   qint64 len = buf.byteCount();
   if(len > 50)
       len = 50;
    int j = 0;
    int sum = 0;

    while(j < 160)
       sum += data[j++];

    _redSquare->setProperty("d", sum/160);
    _particles->setProperty("size", sum/320);
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

        _playlist->addMedia(QUrl::fromLocalFile(dir.path()+"/" + f));

    }
}

void MainWindow::loadFile() {
    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Music"),
                                             QDir::homePath(),
                                             tr("Music Files (*.mp3);;"));
    if (_fileName.isEmpty())
        return;

    _playlist->addMedia(QUrl(_fileName));

}

void MainWindow::play() {
    if (_player->state() == QMediaPlayer::PlayingState){
        _player->pause();
    }
    else {
        if(!_playlist->isEmpty()){
            if(!(_playlist->currentIndex() >= 0))
                _playlist->setCurrentIndex(0);

            _player->play();
        }
    }
}

void MainWindow::next(){
    if(_playlist->currentIndex() != _playlist->mediaCount() - 1)
        _playlist->next();
    else
        stop();
}

void MainWindow::previous(){
    if(_playlist->currentIndex() != 0)
       _playlist->previous();
    else
        stop();
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

void MainWindow::changeVolume(){
    int vol = ui->volumeSlider->value();
    _player->setVolume(vol);
}

void MainWindow::musicPositionChanged(qint64 position){
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->timeLabel->setText(duration.toString(tr("mm:ss")));
    ui->position->setValue(position);
}

void MainWindow::updateDuration(qint64 duration){
    ui->position->setRange(0, duration);
    ui->position->setEnabled(duration > 0);
    ui->position->setPageStep(duration / 10);
}

void MainWindow::changePosition(int position){
    if (qAbs(_player->position() - position) > 99)
        _player->setPosition(position);
}

void MainWindow::updateButtonIcons(QMediaPlayer::State state){
    if(state == QMediaPlayer::PlayingState)
        ui->playButton->setIcon(QIcon(":png/pause15.png"));

    else
        ui->playButton->setIcon(QIcon(":/png/play43.png"));
}

void MainWindow::changePlaybackMode() {
    if(_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Loop){
        _playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
        ui->repeatButton->setIcon(QIcon(":/png/looping1.png"));
    }
    else if(_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::CurrentItemInLoop){
        _playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
        ui->repeatButton->setIcon(QIcon(":/png/intersecting4.png"));
    }
    else if(_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Random){
        _playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
        ui->repeatButton->setIcon(QIcon(":/png/right31.png"));
    }
    else if(_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential){
        _playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
        ui->repeatButton->setIcon(QIcon(":/png/two122.png"));
    }
}

void MainWindow::updateMp3List(int start, int end) {
    qDebug() << "updaeteList mediacount: " << _playlist->mediaCount();
    int index = _playlist->mediaCount() - 1;
    qDebug() << "objectname: " << _playlist->media(index).canonicalUrl().fileName();
    ui->mp3List->addItem(_playlist->media(index).canonicalUrl().fileName());
}

void MainWindow::updateMp3ListIndex(QMediaContent content) {
    if(!_playlist->isEmpty())
        ui->mp3List->item(_playlist->currentIndex())->setSelected(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event){
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls()){
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size() && i < 32; ++i) {
            QUrl url = urlList.at(i).url();
            _playlist->addMedia(QMediaContent(url));
        }
    }
    event->acceptProposedAction();
}
