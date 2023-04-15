#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>

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


    m_videoWidget = new QVideoWidget(this);
    setCentralWidget(m_videoWidget);

    // メディアプレイヤーの作成
    m_player = new QMediaPlayer(this);
    m_player->setVideoOutput(m_videoWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Video Files (*.mp4)"));
    if (!fileName.isEmpty()) {
        m_player->setSource(QUrl::fromLocalFile(fileName));
        m_player->play();
    }
}
