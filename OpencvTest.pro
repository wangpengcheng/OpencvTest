#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T13:27:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpencvTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
INCLUDEPATH +=  E:/opencv3.4.0/install/include \
                E:/opencv3.4.0/install/include/opencv\
                E:/opencv3.4.0/install/include/opencv2

LIBS += E:/opencv3.4.0/install/x64/vc14/lib/opencv_aruco340d.lib \
#        /usr/local/lib/libopencv_highgui.so.2.4.9\
#        /usr/local/lib/libopencv_imgproc.so.2.4.9\
#        /usr/local/lib/libopencv_stitching.so.2.4.9\         #图像拼接模块
#        /usr/local/lib/libopencv_nonfree.so.2.4.9\     #SIFT,SURF
#        /usr/local/lib/libopencv_features2d.so.2.4.9   #特征检测
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_aruco340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_bgsegm340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_bioinspired340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_calib3d340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_ccalib340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_core340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_datasets340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_dnn340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_dpm340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_face340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_features2d340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_flann340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_fuzzy340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_highgui340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_img_hash340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_imgcodecs340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_imgproc340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_line_descriptor340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_ml340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_objdetect340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_optflow340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_phase_unwrapping340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_photo340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_plot340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_reg340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_rgbd340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_saliency340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_shape340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_stereo340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_stitching340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_structured_light340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_superres340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_surface_matching340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_text340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_tracking340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_video340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_videoio340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_videostab340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_xfeatures2d340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_ximgproc340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_xobjdetect340d.lib \
        E:/opencv3.4.0/install/x64/vc14/lib/opencv_xphoto340d.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
