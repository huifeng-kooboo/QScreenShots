#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QScreen>

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

public slots:
    // 截取全图
    void Slots_ScreenAll();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
