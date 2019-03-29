#ifndef MYSTITCHER_H
#define MYSTITCHER_H
/****************************************************************************
** @projectName   OpencvTest
** QT Version    5.11.3
** This file is part of the OpencvTest project.
** @file          mystitcher.h
** @brief         OpenCV中对sticthing模块细节的QT封装，方便设置信号和槽函数
** @details       利用参数成员变量，设置相关参数。再利用stitchImages函数进行图像拼接
** @author
** @QQ            673018396
** @email
** @address
** @date          2019-03-28 周四  10:14:05
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QObject>
#include <QFile>
#include <QDir>
#include <QtDebug>
#include <QDateTime>
#include <QObject>
#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching/detail/autocalib.hpp>
#include <opencv2/stitching/detail/blenders.hpp>
#include <opencv2/stitching/detail/timelapsers.hpp>
#include <opencv2/stitching/detail/camera.hpp>
#include <opencv2/stitching/detail/exposure_compensate.hpp>
#include <opencv2/stitching/detail/matchers.hpp>
#include <opencv2/stitching/detail/motion_estimators.hpp>
#include <opencv2/stitching/detail/seam_finders.hpp>
#include <opencv2/stitching/detail/warpers.hpp>
#include <opencv2/stitching/warpers.hpp>

#define ENABLE_LOG 1 //设置是否输出错误
#define LOG(msg) std::cout << msg //输出错误
#define LOGLN(msg) std::cout << msg << std::endl //输出错误

using namespace std;
using namespace cv;
using namespace cv::detail;

class MyStitcher : public QObject
{
    Q_OBJECT
public:
    explicit MyStitcher(QObject *parent = nullptr);
    void Init();//初始化参数函数
    int StitchImages();
    /*get and set strat */
    inline std::vector<String> img_names(){return img_names_;}//图片路径
    inline void set_img_names(std::vector<String> image_names){img_names_=image_names;}
    inline bool preview(){return is_preview_;}//是否开启preveiw
    inline void set_preview(bool preview){is_preview_=preview;}
    inline bool try_cuda(){return try_cuda_;}//是否使用cuda
    inline void set_cuda(bool is_cuda){try_cuda_=is_cuda;}
    inline double work_megapix(){return work_megapix_;}//图像配准步骤的分辨率
    inline void set_work_megapix(double work_megapix){work_megapix_=work_megapix;}
    inline double seam_megapix(){return seam_megapix_;}//缝隙拼接的分辨率
    inline void set_seam_megapix(double seam_megapix){seam_megapix_=seam_megapix;}
    inline double compose_megapix(){return compose_megapix_;}//合成步骤的解析度
    inline void set_compose_megapix(double compose_megapix){compose_megapix_=compose_megapix;}
    inline float conf_thresh(){return  conf_thresh_;}//阈值相同时的全局置信度
    inline void set_conf_thresh(float conf_thresh){conf_thresh_=conf_thresh;}
    inline std::string features_type(){ return features_type_;}//特征函数类型
    inline void set_features_type(std::string features_type){features_type_=features_type;}

    inline std::string matcher_type(){return matcher_type_;}//配准模式
    inline void set_matcher_type(std::string matcher_type){matcher_type_=matcher_type;}
    inline std::string estimator_type() {return estimator_type_;}//变换估计量类型
    inline void set_estimator_type(std::string estimator_type){estimator_type_=estimator_type;}
    inline std::string ba_cost_func(){return ba_cost_func_; }//回调成本函数
    inline void set_ba_cost_func(std::string ba_cost_func){ba_cost_func_=ba_cost_func;}
    inline std::string ba_refine_mask() {return ba_refine_mask_;}
    inline void set_ba_refine_mask(std::string ba_refine_mask){ba_refine_mask_=ba_refine_mask;}

    inline bool do_wave_correct(){return do_wave_correct_;}//是否启用波纹矫正
    inline void set_do_wave_correct(bool is_wave){do_wave_correct_=is_wave;}
    inline WaveCorrectKind wave_correct(){return wave_correct_;}//波纹矫正方向
    void set_wave_correct(std::string type){
        if(type=="no"){
            do_wave_correct_ = false;
        }else if (type=="horiz") {
            wave_correct_=detail::WAVE_CORRECT_HORIZ;
        }else if(type=="vert"){
            wave_correct_=detail::WAVE_CORRECT_VERT;
        };
    }

    inline std::string warp_type() {return warp_type_;}//合成类型
    inline void set_warp_type(std::string warp_type){warp_type_=warp_type;}

    inline int expos_comp_type(){return expos_comp_type_;}//曝光补偿类型
    void set_expos_comp_type(std::string type){
        //0:NO, 1:GAIN 2:GAIN_BLOCKS
        if (type == "no"){
            expos_comp_type_ = ExposureCompensator::NO;
        }else if (type== "gain"){
            expos_comp_type_ = ExposureCompensator::GAIN;
        }else if (type== "gain_blocks"){
            expos_comp_type_ = ExposureCompensator::GAIN_BLOCKS;
        }else{
            cout << "Bad exposure compensation method\n";
        }
    }

    inline float match_conf(){return match_conf_;}//特征匹配步骤的置信率
    inline void set_match_conf(float match_conf){match_conf_=match_conf;}
    inline std::string seam_find_type(){return seam_find_type_;}//拼接缝隙的方法
    inline void set_seam_find_type(std::string seam_find_type){seam_find_type_=seam_find_type ;}
    inline int blend_type(){return blend_type_;}//图片融合方法
    void set_blend_type(std::string blend_type){
            if(blend_type=="no"){
                blend_type = Blender::NO;}
            else if (blend_type == "feather"){
                blend_type = Blender::FEATHER;
            }else if (blend_type== "multiband"){
                blend_type = Blender::MULTI_BAND;
            }else{
                cout << "Bad blending method\n";
            }
        }
    inline float blend_strength(){return blend_strength_;}//融合强度
    inline void set_blend_strength(float blend_strength){blend_strength_=blend_strength;}
    inline int range_width(){return range_width_;}
    inline void set_range_width(int range_width){range_width_=range_width;}
    inline bool is_show_image(){return is_show_img_;}
    inline void set_show_image(bool is_show){is_show_img_=is_show;}
    inline bool timelapse(){return timelapse_;}
    inline void set_timelapse(bool timelapse){timelapse_=timelapse;}
    inline int timelapse_type(){return timelapse_type_;}
    void set_timelapse_type(std::string type){
        if(type=="as_is"){
            timelapse_type_=Timelapser::AS_IS;
        }else if(type=="crop"){
            timelapse_type_=Timelapser::CROP;
        }else{
            std::cout<<"Unkonw timelapse_type"<<std::endl;
        }
    }
    //设置图片存储函数
    void SaveImage(std::string file_path);//输入图片路径存储图片
    /*get and set end */
    void ImgNamesClean();//图片清除
    int CreateLogFile();//创建日志文件
    inline bool is_log(){return is_log_;}
    inline void set_is_log(bool is_log){is_log_=is_log;}
    inline std::string log_file_path(){return log_file_path_;}
signals:

public slots:
private :
    std::vector<String> img_names_;//图片名称,注意这里使用了Opencv的 string 类
    bool is_preview_ = false;//是否使用perview 模式,使用perview模式能够加快速度
    bool try_cuda_ = false;//是否使用cuda,GPU加速
    double work_megapix_ = 0.6;//图像配准步骤的分辨率 默认值为0.6Mpx
    double seam_megapix_ = 0.1;//缝隙拼接的分辨率
    double compose_megapix_ = -1;//融合步骤的解析度
    float conf_thresh_ = 1.f;//阈值相同时的全局置信度
    std::string features_type_ = "surf";//特征类型算子
    std::string matcher_type_ = "homography";//配准模式
    std::string estimator_type_ = "homography";//变换估计量类型
    std::string ba_cost_func_ = "ray";//回调成本函数
    std::string ba_refine_mask_ = "xxxxx";
    bool do_wave_correct_ = true;//是否启用波纹矫正
    WaveCorrectKind wave_correct_ = detail::WAVE_CORRECT_HORIZ;//波纹矫正方向
    bool save_graph_ = false;//是否存储图片
    std::string save_graph_to_;//保存图片到
    std::string warp_type_ = "spherical";//合成类型
    int expos_comp_type_ = ExposureCompensator::GAIN_BLOCKS;//曝光补偿类型
    float match_conf_ = 0.3f;//特征匹配步骤的置信率
    std::string seam_find_type_ = "gc_color";//拼接缝隙的方法
    int blend_type_ = Blender::MULTI_BAND;//图片融合方法
    float blend_strength_ = 5;//融合强度
    std::string result_name_ = "result.jpg";//结果图片
    int range_width_ = -1;//限制匹配数目
    bool is_show_img_=true;//是否显示图片
    bool timelapse_ = false;//是否使用时间帧
    int timelapse_type_ = Timelapser::AS_IS;//输出时间帧方法
    Mat result_img_;//计算结果图片
    std::string log_file_path_;
    bool is_log_=false;
};

#endif // MYSTITCHER_H
