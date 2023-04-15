#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
//    void handleMediaStatusChanged(QMediaPlayer::State state);
    void handleTimerTimeout();
//    void stopVideo();

private:
    Ui::MainWindow *ui;
    QVideoWidget *m_videoWidget; // m_videoWidget をクラスのメンバ変数として宣言
    QMediaPlayer *m_mediaPlayer;
    QMediaPlayer *m_player;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H
