#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWindow>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <qfiledialog.h>
#include "Utils/log.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_bScreenCut = false;
    this->setMouseTracking(true);
    // 实现无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(200,200);
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
    m_bScreenCut = true;
    window()->showMinimized();
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
    //    if(m_bScreenCut == false)
    //    {
    //        m_painter.begin(this);
    //        QPen pen;
    //        pen.setWidth(5);
    //        pen.setColor(QColor(Qt::GlobalColor::red));
    //        pen.setStyle(Qt::DashDotLine);
    //        m_painter.setPen(pen);
    //        m_painter.drawLine(50,50,150,50);
    //        m_painter.drawLine(50,50,50,150);
    //        //创建画刷
    //        QBrush brush;
    //        brush.setColor(Qt::black);
    //        brush.setStyle(Qt::Dense6Pattern);

    //        m_painter.setBrush(brush);

    //        // 画矩形；
    //        m_painter.drawRect(150,150,100,50);

    //        //画圆形
    //        m_painter.drawEllipse(250,250,40,40);
    //        m_painter.end();
    //    }
    //    else {

    //    }
    return QMainWindow::paintEvent(event);
}

