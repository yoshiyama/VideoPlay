#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QToolBar> // QToolBar をインクルード
#include <QPushButton>
#include <QVBoxLayout>
#include <QSettings>

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

    // "Stop" ボタンを作成
    QPushButton *stopButton = new QPushButton("Stop", this);
    stopButton->setFixedSize(100, 50);  // 幅100px, 高さ50pxに設定
    layout->addWidget(stopButton);
//    setCentralWidget(m_videoWidget);

    // メディアプレイヤーの作成
    m_player = new QMediaPlayer(this);
    m_player->setVideoOutput(m_videoWidget);

    // "Stop" ボタンの clicked() シグナルをメディアプレイヤーの stop() スロットに接続
    connect(stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);

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
        m_player->setSource(QUrl::fromLocalFile(fileName));
        m_player->play();

        QFileInfo fileInfo(fileName);
        settings.setValue("LastPath", fileInfo.absolutePath());
    }
}
// 動画の再生をストップ(pause)するスロット
//void MainWindow::stopVideo()
//{
//    m_player->pause();
//}
