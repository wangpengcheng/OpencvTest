#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/****************************************************************************
** @projectName   OpencvTest
** QT Version    5.11.3
** This file is part of the OpencvTest project.
** @file          mainwindow.h
** @brief         主要用来实现主界面
** @details       与mainwindow.ui绑定实现界面的显示
** @author
** @QQ            673018396
** @email
** @address
** @date          2019-03-30 周六  10:48:08
** @example
**
**
**
*****************************************************************************/
#include <fstream>
#include <iostream>
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
    void InitArg();//
    void WriteToLogEdit(QString log_string);//将行输出到日制
    void CleanLogEdit();//清理日制面板
    void ReadLogFile(QString file_full_path);//读取日制文件
    //槽函数
public slots:
     void on_add_img_button_clicked();//添加图片按钮点击事件
   //信号函数
signals:

private slots:
     void on_delete_img_button_clicked();//删除图片按钮函数

     void on_clean_imgs_button_clicked();//清除图片按钮函数

     void on_change_arc_button_clicked();//更改参数图片按钮函数

     void on_channce_changebutton_clicked();//取消按钮函数

     void on_confirm_change_button_clicked();//确定按钮函数

     void on_stitch_img_button_clicked();//拼接图像按钮函数

     void on_save_img_button_clicked();//保存图像按钮函数

private:
    Ui::MainWindow *ui;
    std::vector<cv::String> images;
    MyStitcher my_stitcher_;//设置stitcher
    QStandardItemModel *img_list_view_model_=new QStandardItemModel(this);//设置图片展示列表
    bool arg_is_change_able=false;
    bool is_show_log=true;
   // int last_position;
};

#endif // MAINWINDOW_H
