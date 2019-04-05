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
//禁止参数面板函数
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
    /*
     * featurestype 设置MyStitcher 类中的features_type_参数
     * featurestype主要功能是选择寻找图片特征点的算子：surf或者orb
     */
    ui->featurestype_combobox->addItem(QString("surf"));
    ui->featurestype_combobox->addItem(QString("orb"));
    //ui->featurestype_combobox->setCurrentIndex(0);
    //设置matchertype
    /*
     *matchertype 主要功能是选择，两两图片之间的特征匹配算子种类
     */
    ui->matchertype_combobox->addItem(QString("homography"));
    ui->matchertype_combobox->addItem(QString("affine"));
    //设置ba_cost_func type
    /*
     * ba_cost_func type设置MyStitcher类中的ba_cost_func参数 ；
     * 即设置图片融合中调整相机时的阀值矫正代价函数
     * 并结合计算掩膜，对相似图片进行，阀值分割，合并重叠部分
     * 主要是进行代价补偿，使得迭代计算能够收敛；
     */
    ui->bacosttype_combobox->addItem(QString("ray"));
    ui->bacosttype_combobox->addItem(QString("reproj"));
    ui->bacosttype_combobox->addItem(QString("affine"));
    ui->bacosttype_combobox->addItem(QString("no"));
    //设置wavecorrecttype
    /*
     * wavecorrecttype设置MyStitcher类中的wave_correct_参数 ；
     * wavecorrecttype:选择波纹矫正的类型：即波纹矫正的方向；
     * 水平或者竖直；或者不进行矫正
     */
    ui->wavecorrecttype_combobox->addItem(QString("horiz"));
    ui->wavecorrecttype_combobox->addItem(QString("vert"));
    ui->wavecorrecttype_combobox->addItem(QString("no"));
    //设置warptype
    /*
     * warptype 设置MyStitcher类中的warp_type_参数 ；设置弯曲（warp）格式，
     * 即最终合成图片是，需要在相机中对，拼接的图片进行，一定程度的弯曲；使得平面图片，映射到三维实际空间中；
     * 再结合相机的参数，实现三维的立体图像平面投影映射。
     *这个参数，就是将拼接平面大图，作为贴图映射到立体模型表面的函数种类选择，如球形，鱼眼，水平等效果
     */
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
    //设置exposcomptype
    /*
     * exposcomptype 设置MyStitcher类中的expos_comp_type_参数
     * exposcomptype 曝光补偿函数类型，主要对图片融合时后，在弯曲时，对图像进行曝光补偿
     * 类似于图形学中的添加光照，使得图像更加真实
     */
    ui->exposcomptype_combobox->addItem(QString("gain_blocks"));
    ui->exposcomptype_combobox->addItem(QString("gain"));
    ui->exposcomptype_combobox->addItem(QString("no"));
    //设置seamfindtype
    /*
     *
     * 设置MyStitcher类 中的seam_find_type_ 参数；帮助构造SeamFinder 类
     * 主要用于选择图像拼接时的拼接缝隙函数选择，选择合适的缝隙拼接方式
     * 参考链接：https://docs.opencv.org/3.4.0/d7/d09/classcv_1_1detail_1_1SeamFinder.html
     *
     */
    ui->seamfindtype_combobox->addItem(QString("gc_color"));
    ui->seamfindtype_combobox->addItem(QString("voronoi"));
    ui->seamfindtype_combobox->addItem(QString("gc_colorgrad"));
    ui->seamfindtype_combobox->addItem(QString("dp_color"));
    ui->seamfindtype_combobox->addItem(QString("dp_colorgrad"));
    ui->seamfindtype_combobox->addItem(QString("no"));
    //设置blendtype
   /*
    * belendtype 设置MyStitcher类中的图像融合方法，主要是使得图像拼接的缝隙平滑，结合seam_find_type参数共同使用
    * NO, FEATHER,(特征) MULTI_BAND（多连接）
    * 参考：https://blog.csdn.net/baishuo8/article/details/80932786
    */
    ui->blendtype_combobox->addItem(QString("multiband"));
    ui->blendtype_combobox->addItem(QString("feather"));
    ui->blendtype_combobox->addItem(QString("no"));
    //sin_box start
    //数字输入框
    //设置workmegapix
    /*
     * workmegapix 设置MyStitcher 类中的work_megapix_ 参数
     * 该参数的主要作用是设置图像配准步骤的图像压缩分辨率
     * 将图像尺寸压缩到work_megapix*10^6以下,加快运算速度
     */
    ui->workmegapix_spinbox->setValue(0.6);
    //设置seammegapix
    /*
     * seammegapix 设置MyStitcher 类中的work_megapix_参数
     * 该参数的主要作用是在不允许图像缩放时，计算缩放参数
     * 将图片进行压缩，方便计算；主要是对图片进行缩放，方便下一步的计算
     *
     */
    ui->seammegapix_spinbox->setValue(0.1);
    //设置composemegapix
    /*
     * composemegapix 设置MyStitcher 类中的compose_megapix_参数
     * 该参数主要设置融合步骤的解析度值，在图像混合（Compositing）时
     * 计算compose_scale，设置图像融合时的图片缩放比例
     */
    //设置允许最小值为-10
    ui->composemegapix_spinbox->setMinimum(-10);
    //设置默认值为-1
    ui->composemegapix_spinbox->setValue(-1);
    //设置confthresh
    /*
     * confthresh 设置MyStitcher 类中的conf_thresh_参数
     */
    ui->confthresh_spinbox->setValue(1.0);
    //设置matchconf
    /*
     * matchconf 设置MyStitcher 类中的conf_thresh_参数
     * 主要用于图片特征匹配（match）步骤中的置信率参数设置
     * 主要用于构造matcher类，结合matchertype使用，设置匹配准确度
     *
     */
    ui->matchconf_spinbox->setValue(0.3);
    /*
     *blendstrength 设置MyStitcher 类中的blend_strength_参数
     * 主要结合blendtype参数使用，主要设置融合的强度，并影响最终融合结果
     */
    ui->blendstrength_spinbox->setValue(5);
    //sin_box end
    //设置check box
    /*
     * 复选框，选择是否开启该项功能；可以开启但是会增加运算时间
     */
    //是否启用波纹矫正，默认是；用波纹矫正；结合wavecorrecttype参数对图像缝隙进行波纹矫正
    ui->wavecorrect_checkbox->setCheckState(Qt::CheckState::Checked);
    //是否弹出最终结果图片窗口
    ui->showimg_checkbox->setCheckState(Qt::CheckState::Checked);
    //是否在计算机保存图片，防止丢失（计算结果马上保存一张result图片，防止结果丢失）
    ui->saveimage_checkbox->setCheckState(Qt::CheckState::Checked);
    //是否预览该过程，（选择该参数会将计算过程中的全部参数，输出到日制文件中，等待完善）
    ui->preview_checkbox->setCheckState(Qt::CheckState::Unchecked);
    //是否在下方的日志面板显示日志（功能不完全，等待完善）
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
    //获取和设置各行数据，并将其传入my_stitcher_成员类中
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
    QString filter=QStringLiteral("图片文件(*.jpg *.png *.bmp);;所有文件(*.*)");
    QUrl file_path=QFileDialog::getSaveFileUrl(this,dialog_title,cur_path,filter);
    //if(file_path.isEmpty()){
    cv::String temp_path=file_path.toString().replace("file:///","").toStdString();//处理获取到的字符串
    my_stitcher_.SaveImage(temp_path);//保存图片
}
