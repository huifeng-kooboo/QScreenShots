#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 绑定槽函数
void MainWindow::InitSlots()
{
    QObject::connect(ui->btn_ScreenAll,SIGNAL(clicked()),this,SLOT(Slots_ScreenAll()));
}

void MainWindow::Slots_ScreenAll()
{
    QMessageBox::about(this,"标题","文字");
}
