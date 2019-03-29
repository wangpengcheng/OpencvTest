#include "mainwindow.h"
#include "ui_mainwindow.h"
static int last_position=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete img_list_view_model_;
    img_list_view_model_=nullptr;
}
void MainWindow::Init()
{
    //添加图片按钮
    //connect(ui->add_img_button,SIGNAL(clicked()),this,SLOT(on_add_img_button_clicked()));
    if(img_list_view_model_!=nullptr){
        ui->image_list_view->setModel(img_list_view_model_);
    };
    ui->image_list_view->setEnabled(false);
    //set unable Args;
    DisableArg(false);
    InitArg();
    last_position=0;
    //ReadLogFile("F:/Qt_worksapce/build-OpencvTest-Desktop_Qt_5_11_3_MSVC2015_64bit-Debug/2019-03-29-13-51-26-996.txt");


}

void MainWindow::on_add_img_button_clicked()
{
   // qDebug()<<"hello word!!!";
    QString cur_path=QDir::homePath();//get application file path
    QString dialog_title=QStringLiteral("选择一个文件");
    QString filter=QStringLiteral("图片文件(*.jpg *.png);;所有文件(*.*)");
    QUrl file_path=QFileDialog::getOpenFileUrl(this,dialog_title,cur_path,filter);
    if(!file_path.isEmpty()){
        cv::String temp_path=file_path.toString().replace("file:///","").toStdString();//change file path;
        QStandardItem *temp_item=new QStandardItem(file_path.toString().replace("file:///",""));//删减字符串格式
        img_list_view_model_->appendRow(temp_item);
        images.push_back(temp_path);
       // std::cout<<temp_path<<std::endl;
    }else {
        qDebug()<<"Can not open File";
    }
}

void MainWindow::on_delete_img_button_clicked()
{
    //删除图片列表的图片
    if(img_list_view_model_->rowCount()!=0){
       // qDebug()<<img_list_view_model_->rowCount()-1;
       // qDebug()<<img_list_view_model_->rowCount();
        bool is_sucess=img_list_view_model_->removeRows(img_list_view_model_->rowCount()-1,1);
       // qDebug()<<is_sucess;
        //ui->image_list_view->update();
    }else {
        qDebug()<<"there is no row";
    }
}

void MainWindow::on_clean_imgs_button_clicked()
{
    //清空列表面板
    img_list_view_model_->clear();
    //清空图片名字向量
    images.clear();
}
void MainWindow::DisableArg(bool is_able){

    if(is_able){
        ui->featurestype_combobox->setEnabled(true);
        ui->matchertype_combobox->setEnabled(true);
        ui->bacosttype_combobox->setEnabled(true);
        ui->wavecorrecttype_combobox->setEnabled(true);
        ui->warptype_combobox->setEnabled(true);
        ui->exposcomptype_combobox->setEnabled(true);
        ui->seamfindtype_combobox->setEnabled(true);
        ui->blendtype_combobox->setEnabled(true);
        ui->workmegapix_spinbox->setEnabled(true);
        ui->blendstrength_spinbox->setEnabled(true);
        ui->composemegapix_spinbox->setEnabled(true);
        ui->confthresh_spinbox->setEnabled(true);
        ui->matchconf_spinbox->setEnabled(true);
        ui->seammegapix_spinbox->setEnabled(true);
        ui->preview_checkbox->setEnabled(true);
        ui->saveimage_checkbox->setEnabled(true);
        ui->wavecorrect_checkbox->setEnabled(true);
        ui->showimg_checkbox->setEnabled(true);
        ui->showlog_checkbox->setEnabled(true);
        arg_is_change_able=true;
    }else if (!is_able) {
        ui->featurestype_combobox->setEnabled(false);
        ui->matchertype_combobox->setEnabled(false);
        ui->bacosttype_combobox->setEnabled(false);
        ui->wavecorrecttype_combobox->setEnabled(false);
        ui->warptype_combobox->setEnabled(false);
        ui->exposcomptype_combobox->setEnabled(false);
        ui->seamfindtype_combobox->setEnabled(false);
        ui->blendtype_combobox->setEnabled(false);
        ui->workmegapix_spinbox->setEnabled(false);
        ui->blendstrength_spinbox->setEnabled(false);
        ui->composemegapix_spinbox->setEnabled(false);
        ui->confthresh_spinbox->setEnabled(false);
        ui->matchconf_spinbox->setEnabled(false);
        ui->seammegapix_spinbox->setEnabled(false);
        ui->preview_checkbox->setEnabled(false);
        ui->saveimage_checkbox->setEnabled(false);
        ui->wavecorrect_checkbox->setEnabled(false);
        ui->showimg_checkbox->setEnabled(false);
        ui->showlog_checkbox->setEnabled(false);
        arg_is_change_able=false;
    }
}
void MainWindow::InitArg(){
    //设置featurestype
    ui->featurestype_combobox->addItem(QString("surf"));
    ui->featurestype_combobox->addItem(QString("orb"));
    //ui->featurestype_combobox->setCurrentIndex(0);
    //设置matchertype
    ui->matchertype_combobox->addItem(QString("homography"));
    ui->matchertype_combobox->addItem(QString("affine"));
    //设置ba_cost_func type
    ui->bacosttype_combobox->addItem(QString("ray"));
    ui->bacosttype_combobox->addItem(QString("reproj"));
    ui->bacosttype_combobox->addItem(QString("affine"));
    ui->bacosttype_combobox->addItem(QString("no"));
    //设置wavecorrecttype
    ui->wavecorrecttype_combobox->addItem(QString("horiz"));
    ui->wavecorrecttype_combobox->addItem(QString("vert"));
    ui->wavecorrecttype_combobox->addItem(QString("no"));
    //设置warptype
    ui->warptype_combobox->addItem(QString("spherical"));
    ui->warptype_combobox->addItem(QString("plane"));
    ui->warptype_combobox->addItem(QString("affine"));
    ui->warptype_combobox->addItem(QString("cylindrical"));
    ui->warptype_combobox->addItem(QString("fisheye"));
    ui->warptype_combobox->addItem(QString("stereographic"));
    ui->warptype_combobox->addItem(QString("compressedPlaneA2B1"));
    ui->warptype_combobox->addItem(QString("compressedPlaneA1.5B1"));
    ui->warptype_combobox->addItem(QString("compressedPlanePortraitA2B1"));
    ui->warptype_combobox->addItem(QString("compressedPlanePortraitA1.5B1"));
    ui->warptype_combobox->addItem(QString("paniniA2B1"));
    ui->warptype_combobox->addItem(QString("paniniA1.5B1"));
    ui->warptype_combobox->addItem(QString("paniniPortraitA2B1"));
    ui->warptype_combobox->addItem(QString("paniniPortraitA1.5B1"));
    ui->warptype_combobox->addItem(QString("mercator"));
    ui->warptype_combobox->addItem(QString("transverseMercator"));
    //exposcomptype
    ui->exposcomptype_combobox->addItem(QString("gain_blocks"));
    ui->exposcomptype_combobox->addItem(QString("gain"));
    ui->exposcomptype_combobox->addItem(QString("no"));
    //seamfindtype
    ui->seamfindtype_combobox->addItem(QString("gc_color"));
    ui->seamfindtype_combobox->addItem(QString("voronoi"));
    ui->seamfindtype_combobox->addItem(QString("gc_colorgrad"));
    ui->seamfindtype_combobox->addItem(QString("dp_color"));
    ui->seamfindtype_combobox->addItem(QString("dp_colorgrad"));
    ui->seamfindtype_combobox->addItem(QString("no"));
    //blendtype
    ui->blendtype_combobox->addItem(QString("multiband"));
    ui->blendtype_combobox->addItem(QString("feather"));
    ui->blendtype_combobox->addItem(QString("no"));
    //sin_box start
    //workmegapix
    ui->workmegapix_spinbox->setValue(0.6);
    //seammegapix
    ui->seammegapix_spinbox->setValue(0.1);
    //composemegapix
    ui->composemegapix_spinbox->setMinimum(-10);
    ui->composemegapix_spinbox->setValue(-1);
    //confthresh
    ui->confthresh_spinbox->setValue(1.0);
    //matchconf
    ui->matchconf_spinbox->setValue(0.3);
    ui->blendstrength_spinbox->setValue(5);
    //sin_box end
    //check box
    ui->wavecorrect_checkbox->setCheckState(Qt::CheckState::Checked);
    ui->showimg_checkbox->setCheckState(Qt::CheckState::Checked);
    ui->saveimage_checkbox->setCheckState(Qt::CheckState::Checked);
    ui->preview_checkbox->setCheckState(Qt::CheckState::Unchecked);
    ui->showlog_checkbox->setCheckState(Qt::CheckState::Checked);
}

void MainWindow::on_change_arc_button_clicked()
{

    DisableArg(true);

}

void MainWindow::on_channce_changebutton_clicked()
{
    InitArg();
    DisableArg(false);
}

void MainWindow::on_confirm_change_button_clicked()
{
    //save arg to Mystutcher;
    //获取和设置各行数据
     my_stitcher_.set_img_names(images);
     my_stitcher_.set_features_type(ui->featurestype_combobox->currentText().toStdString());
     my_stitcher_.set_matcher_type(ui->matchertype_combobox->currentText().toStdString());
     my_stitcher_.set_ba_cost_func(ui->bacosttype_combobox->currentText().toStdString());
     my_stitcher_.set_wave_correct(ui->wavecorrecttype_combobox->currentText().toStdString());
     my_stitcher_.set_warp_type(ui->warptype_combobox->currentText().toStdString());
     my_stitcher_.set_expos_comp_type(ui->exposcomptype_combobox->currentText().toStdString());
     my_stitcher_.set_seam_find_type(ui->seamfindtype_combobox->currentText().toStdString());
     my_stitcher_.set_blend_type(ui->seamfindtype_combobox->currentText().toStdString());
     my_stitcher_.set_work_megapix(ui->workmegapix_spinbox->value());
     my_stitcher_.set_seam_megapix(ui->seammegapix_spinbox->value());
     my_stitcher_.set_compose_megapix(ui->composemegapix_spinbox->value());
     my_stitcher_.set_conf_thresh(ui->composemegapix_spinbox->value());
     my_stitcher_.set_match_conf(ui->matchconf_spinbox->value());
     my_stitcher_.set_blend_strength(ui->blendstrength_spinbox->value());
     my_stitcher_.set_do_wave_correct(ui->wavecorrect_checkbox->isChecked());
     my_stitcher_.set_show_image(ui->showimg_checkbox->isChecked());
     DisableArg(false);
}

//将字符串输出到log_edit
void MainWindow::WriteToLogEdit(QString log_string)
{
    ui->log_edit->append(log_string);
    ui->log_edit->update();
}
//清除日制面板
void MainWindow::CleanLogEdit()
{
    ui->log_edit->clear();
}
void MainWindow::ReadLogFile(QString file_full_path)
{
    //int position = 0;
       while(is_show_log) {
           ifstream infile(file_full_path.toStdString());
           infile.seekg(0, ios::end);
           int filesize = infile.tellg();
            for(int n = last_position; n < filesize; n++)
              {
                  infile.seekg(last_position, ios::beg);
                  string line;
                  getline(infile, line);//获取最新行
                  //WriteToLogEdit(line);//获取最新行的内容
                  if(!line.empty()){
                    qDebug()<<QString::fromStdString(line)<<endl;
                  }
                  if(infile.tellg()>0)//这里必须加入这个判断，因为在频繁更新目标文件时，会导致该函数返回-1
                  {
                      n=last_position = infile.tellg();
                  }
              }
       }

}

void MainWindow::on_stitch_img_button_clicked()
{
   // ReadLogFile("F:/Qt_worksapce/build-OpencvTest-Desktop_Qt_5_11_3_MSVC2015_64bit-Debug/2019-03-29-13-51-26-996.txt");

   //开始计算
    WriteToLogEdit("stitcher start");
    my_stitcher_.StitchImages();
    WriteToLogEdit("stitcher end");
}

void MainWindow::on_save_img_button_clicked()
{
    QString cur_path=QDir::homePath();//get application file path
    QString dialog_title=QStringLiteral("选择一个文件");
    QString filter=QStringLiteral("图片文件(*.jpg *.png);;所有文件(*.*)");
    QUrl file_path=QFileDialog::getSaveFileUrl(this,dialog_title,cur_path,filter);
    //if(file_path.isEmpty()){
    cv::String temp_path=file_path.toString().replace("file:///","").toStdString();//change file path;
    my_stitcher_.SaveImage(temp_path);
}
