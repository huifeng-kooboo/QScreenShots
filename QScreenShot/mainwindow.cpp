#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWindow>
#include <QLabel>
#include <qfiledialog.h>
#include "Utils/log.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
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

void MainWindow::Init()
{
    Log::GetInstace().SetLogName("sas",true);
}

void MainWindow::Slots_ScreenAll()
{
    QWindow * myScreenWindow = windowHandle();
    QScreen * myScreen =myScreenWindow->screen();
    QPixmap pixmap = myScreen->grabWindow(0);
    QString strFolderPath = QFileDialog::getExistingDirectory(this,"Choose To Save File","/");
    QString strSavePath = "";
    if(strFolderPath.isEmpty())
    {
        return ;
    }
    else {
        strSavePath = strFolderPath +"/ScreenAll.jpg";
        bool bSave = pixmap.save(strSavePath);
        if(bSave)
        {
            QMessageBox::information(this,"Save","Path:"+strSavePath,QMessageBox::Yes);
        }
    }
}
