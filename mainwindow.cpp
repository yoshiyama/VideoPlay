#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QToolBar> // QToolBar をインクルード
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QTimer>
//#include <QMediaContent>


//ここは超メイン
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *openAction = new QAction(tr("&Open"), this);
//    QAction *openAction = new QAction(this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
//    connect(openAction, &QAction::triggered, this, &MainWindow::handleMediaStatusChanged);
    ui->menuFile->addAction(openAction);

    // Quit アクションの追加
    QAction *quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit the application"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);
    ui->menuFile->addAction(quitAction);

//    // ツールバーの作成
//    QToolBar *toolbar = new QToolBar(this);
//    addToolBar(Qt::TopToolBarArea, toolbar);

//    // Stop ボタンの追加
//    QAction *stopAction = new QAction(tr("Stop"), this);
//    stopAction->setStatusTip(tr("Stop the video"));
//    connect(stopAction, &QAction::triggered, this, &MainWindow::stopVideo);
//    toolbar->addAction(stopAction);

    // ウィジェットを配置する QVBoxLayout を作成
    QVBoxLayout *layout = new QVBoxLayout();

    m_videoWidget = new QVideoWidget(this);
    layout->addWidget(m_videoWidget);

    // "Play" ボタンと "Stop" ボタンを配置する QHBoxLayout を作成
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    // "Play" ボタンを作成
    QPushButton *playButton = new QPushButton("Play", this);
    playButton->setFixedSize(100, 50);  // 幅100px, 高さ50pxに設定
//    layout->addWidget(playButton);
    buttonsLayout->addWidget(playButton);

    // "Stop" ボタンを作成
    QPushButton *stopButton = new QPushButton("Stop", this);
    stopButton->setFixedSize(100, 50);  // 幅100px, 高さ50pxに設定
//    layout->addWidget(stopButton);
    buttonsLayout->addWidget(stopButton);
//    setCentralWidget(m_videoWidget);

    // ボタン配置用の QHBoxLayout を QVBoxLayout に追加
    layout->addLayout(buttonsLayout);

    // メディアプレイヤーの作成
    m_player = new QMediaPlayer(this);
    m_player->setVideoOutput(m_videoWidget);

    // "Play" ボタンの clicked() シグナルをメディアプレイヤーの play() スロットに接続
    connect(playButton, &QPushButton::clicked, m_player, &QMediaPlayer::play);

    // "Stop" ボタンの clicked() シグナルをメディアプレイヤーの pause() スロットに接続
    connect(stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);

    // "Stop" ボタンの clicked() シグナルをメディアプレイヤーの stop() スロットに接続
//    connect(stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
//    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_actionOpen_triggered);

    // タイマーの作成
//    m_timer = new QTimer(this);
//    m_timer->setSingleShot(true); // シングルショットモードに設定
//    connect(m_timer, &QTimer::timeout, this, &MainWindow::handleTimerTimeout);



    // メインウィンドウに QVBoxLayout を設定
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//動画を再生するスロット
void MainWindow::on_actionOpen_triggered()
{
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Video Files (*.mp4)"));
//    if (!fileName.isEmpty()) {
//        m_player->setSource(QUrl::fromLocalFile(fileName));
//        m_player->play();
//    }
    QSettings settings("MyCompany", "MyApp");
    QString lastPath = settings.value("LastPath").toString();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), lastPath, tr("Video Files (*.mp4)"));
    if (!fileName.isEmpty()) {
//        QMediaPlayer mediaContent(QUrl::fromLocalFile(fileName));
        m_player->setSource(QUrl::fromLocalFile(fileName)); // QMediaContentを使わずにQUrlを直接設定

//        m_player->setMedia(mediaContent);

//        m_player->setSource(QUrl::fromLocalFile(fileName));
//        m_timer->start(100); // タイマーを 100ms 後に発火させる

        m_player->play();
//        m_player->setSource();
//        m_player->pause();
//        m_player->setPosition(0); // 動画の位置を先頭に戻す

        QFileInfo fileInfo(fileName);
        settings.setValue("LastPath", fileInfo.absolutePath());
    }
}
void MainWindow::handleTimerTimeout()
{
    m_player->pause(); // 一時停止して、1フレーム目を表示
    m_player->setPosition(0); // 動画の位置を先頭に戻す
}
void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        m_player->play();
        QCoreApplication::processEvents();
//    if (status == QMediaPlayer::BufferedMedia) {
        m_player->pause(); // 一時停止して、1フレーム目を表示
        m_player->setPosition(0); // 動画の位置を先頭に戻す
//        QTimer::singleShot(100, this, [this](){
//                        m_player->pause();
//                        m_player->setPosition(0);
//                    });
//        m_player->pause(); // 一時停止して、1フレーム目を表示
//        m_player->setPosition(0); // 動画の位置を先頭に戻す
    }
}
// 動画の再生をストップ(pause)するスロット
//void MainWindow::stopVideo()
//{
//    m_player->pause();
//}
