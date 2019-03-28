#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QtDebug>
#include <QStandardItemModel>
#include "mystitcher.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();//初始化函数
    void MainConnect();//主要连接信号和槽函数
    void DisableArg(bool is_able);
    //槽函数
public slots:
     void on_add_img_button_clicked();//添加图片按钮点击事件
   //信号函数
signals:

private slots:
     void on_delete_img_button_clicked();

     void on_clean_imgs_button_clicked();

private:
    Ui::MainWindow *ui;
    MyStitcher my_stitcher_;//设置stitcher
    QStandardItemModel *img_list_view_model_=new QStandardItemModel(this);//
};

#endif // MAINWINDOW_H
