#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man game by the goats"));
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setGeometry(0,0,28*30,21*25);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game=new Game();
    ui->graphicsView->setScene(game);
    setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

