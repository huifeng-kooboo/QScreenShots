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
    Log::GetInstace().WriteLog("12212");
    Log::GetInstace().WriteLog("12sdaa212");
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

//
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // 设置快捷键方式 Ctrl+指定按键
    // Ctrl+Shift+T 截取全屏
    Qt::KeyboardModifiers modi = event->modifiers();
      if(modi & Qt::ControlModifier && Qt::ShiftModifier)
      {//ctrl键按下
          int key = event->key();
          switch(key)
          {
          case Qt::Key_T:
          {
              Slots_ScreenAll();
          }
          default:
              break;
          }
      }
      return QMainWindow::keyReleaseEvent(event);
}
