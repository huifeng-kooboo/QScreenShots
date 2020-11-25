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
    m_bScreenCut = false;
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
    QObject::connect(ui->btn_ScreenCut,SIGNAL(clicked()),this,SLOT(Slots_ScreenCut()));
}

void MainWindow::Init()
{
    Log::GetInstace().SetLogName("QScreenCut",true);
    Log::GetInstace().WriteLog("--------LogInit----------");
}

void MainWindow::Slots_ScreenAll()
{
    Log::GetInstace().WriteLog("-------截取全图--------",LOGSTATE::COMMON,true);
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

void MainWindow::Slots_ScreenCut()
{
    // 开启截屏功能
    m_bScreenCut = true;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 左键事件
    if(event->button() == Qt::LeftButton)
    {
        // 开启截图功能
        if(m_bScreenCut)
        {
            Log::GetInstace().WriteLog("-------开始截图--------",LOGSTATE::COMMON,true);
        }
    }
    return QMainWindow::mousePressEvent(event);
}


