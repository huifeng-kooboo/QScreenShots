#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QScreen>
#include <QKeyEvent>
#include <QRect>

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

public slots:
    // 截取全图
    void Slots_ScreenAll();
    // 部分截图
    void Slots_ScreenCut();

private:
    Ui::MainWindow *ui;
    bool m_bScreenCut;//截图功能
    QRect m_ScreenRect; // 截图坐标
    QPoint m_beginPos; // 初始点
};

#endif // MAINWINDOW_H
