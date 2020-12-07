#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWindow>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <qfiledialog.h>
#include "Utils/log.h"

struct UserDemo : QObjectUserData {
    int nID;  // ID
    QString strName;  // 用户名
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_bScreenCut = false;
    this->setMouseTracking(true);
    // 实现无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(400,400);
    setWindowState(Qt::WindowActive);
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
    QObject::connect(ui->toolBtn_ShareClient,SIGNAL(clicked()),this,SLOT(Slots_ShareMemoryClient()));
    QObject::connect(ui->toolBtn_ShareServer,SIGNAL(clicked()),this,SLOT(Slots_ShareMemoryServer()));
}

void MainWindow::Init()
{
    Log::GetInstace().SetLogName("QScreenCut",true);
    Log::GetInstace().WriteLog("--------LogInit----------");
    m_ShareMemory = nullptr;
}

void MainWindow::Slots_ScreenAll()
{
    Log::GetInstace().WriteLog("-------截取全图--------",LOGSTATE::COMMON,true);
    QWindow * myScreenWindow = windowHandle();
    QScreen * myScreen =myScreenWindow->screen();
    QPixmap pixmap = myScreen->grabWindow(0);
    // 获取保存路径
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
            QMessageBox::information(this,"Save","PhotoPath:"+strSavePath,QMessageBox::Yes);
        }
    }
}

//
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // 设置快捷键方式 Ctrl+指定按键
    // Ctrl+Shift+T 截取全屏
    // Ctrl+Shift+Y 自定义截图
    Qt::KeyboardModifiers modi = event->modifiers();
    if(modi & Qt::ControlModifier && Qt::ShiftModifier)
    {
        int key = event->key();
        switch(key)
        {
        case Qt::Key_T:
        {
            Slots_ScreenAll();
            break;
        }
        case Qt::Key_Y:
        {
            Slots_ScreenCut();
            break;
        }
        default:
            break;
        }
    }
    return QMainWindow::keyReleaseEvent(event);
}

void MainWindow::Slots_ScreenCut()
{
    // 设置鼠标跟踪
    setMouseTracking(true);
    // 最小化
    window()->showMinimized();
    // Qt获取整张屏幕
    // 1. 获取整张图片
    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    m_WinPixMap = pixmap;
    m_width = pixmap.width();
    m_height = pixmap.height();
    m_bScreenCut = true;
    // 2. 显示覆盖整张屏幕

}

void MainWindow::Slots_ShareMemoryClient()
{
    QSharedMemory sp;
    sp.setKey("KeyWord");
    sp.lock();
    QString strpp;
    strpp.append((QString*)(sp.data()));
    Log::GetInstace().WriteLog(strpp);
    sp.unlock();
    sp.detach();
}

void MainWindow::Slots_ShareMemoryServer()
{
    if(m_ShareMemory == nullptr)
    {
        //Log::GetInstace().WriteLog("初始化共享内存");
        m_ShareMemory = new QSharedMemory(this);
    }
    m_ShareMemory->setKey("KeyWord");
    m_ShareMemory->create(2048);
    // 加载数据
    m_ShareMemory->lock(); //上锁
    char * to = (char*)(m_ShareMemory->data());
    QString data_ = "sasaasxxaqvaax";
    memcpy(to,data_.data(),m_ShareMemory->size());
    ShowContext("SetKey:KeyWord");
    m_ShareMemory->unlock();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_movePoint = event->pos();
    }
    return QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPressed = false;
    return QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPressed)
    {
        move(event->pos()  + pos()- m_movePoint);
    }
    return QMainWindow::mouseMoveEvent(event);
}


QRect MainWindow::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this);
    if(m_bScreenCut == true)
    {
        ui->btn_ScreenAll->setVisible(false);
        ui->btn_ScreenCut->setVisible(false);
        setFixedSize(m_width,m_height);
        m_painter.drawPixmap(0,0,m_WinPixMap);
    }
    m_painter.end();

    return QMainWindow::paintEvent(event);
}

void MainWindow::ShowContext(const QString &strContent)
{
    ui->lbl_ShowContext->setText(strContent);
}
