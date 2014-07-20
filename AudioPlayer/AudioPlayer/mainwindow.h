#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QSlider>
#include <QAudioProbe>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString _fileName;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fileName(QString name) { _fileName = name; }
    QString fileName() { return _fileName; }

public slots:
    void loadFile();
    void play();
    void stop();
    void changeVolume();
    void processBuffer(const QAudioBuffer& buf);
    void loadMp3();
    void loadAndPlayMp3();
    void playNext();
    void loadFolder();
    void next();
    void previous();
    void jump(const QModelIndex& index);
    void musicPositionChanged(qint64 position);
    void updateDuration(qint64 position);
    void changePosition(int position);
    void updateButtonIcons(QMediaPlayer::State state);
    void changePlaybackMode();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
