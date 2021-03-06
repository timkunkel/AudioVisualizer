#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QSlider>

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
    void pause();
    void changeVolume();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
