#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QScreen>
#include <QKeyEvent>
#include <QRect>
#include <QPainter>
#include <QSharedMemory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 信号与槽绑定
    void InitSlots();

    // 初始化
    void Init();

    // 键盘快捷键重写
    void keyReleaseEvent(QKeyEvent *event);

    // 鼠标按压事件
    void mousePressEvent(QMouseEvent * event);
    // 鼠标释放时间
    void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动
    void mouseMoveEvent(QMouseEvent * event);
    // 绘制界面
    void paintEvent(QPaintEvent * event);

    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);

    void ShowContext(const QString& strContent);

public slots:
    // 截取全图
    void Slots_ScreenAll();
    // 部分截图
    void Slots_ScreenCut();
    // 槽函数之共享内存服务端
    void Slots_ShareMemoryServer();
    void Slots_ShareMemoryClient();
private:
    Ui::MainWindow *ui;
    bool m_bScreenCut;//截图功能
    QPoint m_beginPos; // 初始点
    QPoint m_endPos; // 结束点
    QPainter m_painter; // 画笔
    // 无边框可移动
    bool m_bPressed; // 判断是否按压
    QPoint m_movePoint; // 移动点
    QPixmap m_WinPixMap;  // 整个桌面的---
    int m_width;
    int m_height;
    QSharedMemory* m_ShareMemory;
};

#endif // MAINWINDOW_H
