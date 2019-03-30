#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T13:27:56
#
#-------------------------------------------------

QT    += core gui

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
#CONFIG += console
#CONFIG -= app_bundle
SOURCES += \
        main.cpp \
        mainwindow.cpp \
        mystitcher.cpp

HEADERS += \
        mainwindow.h \
        mystitcher.h \
       # mytool.h

FORMS += \
        mainwindow.ui
INCLUDEPATH +=  $$PWD/3rdparty/libopencv/include \
#                3rdparty/libopencv/include/opeencv2 \
#                3rdparty/libopencv/include/opeencv2
#                E:/opencv3.4.0/install/include/opencv\
#                E:/opencv3.4.0/install/include/opencv2

LIBS += -L$$PWD/3rdparty/libopencv/lib/ -lopencv_aruco340d  \
        -lopencv_bgsegm340d -lopencv_bioinspired340d -lopencv_calib3d340d \
        -lopencv_ccalib340d -lopencv_core340d -lopencv_datasets340d \
        -lopencv_dnn340d -lopencv_dpm340d -lopencv_face340d \
        -lopencv_features2d340d -lopencv_flann340d -lopencv_fuzzy340d \
        -lopencv_highgui340d -lopencv_img_hash340d -lopencv_imgcodecs340d \
        -lopencv_imgproc340d -lopencv_line_descriptor340d -lopencv_ml340d \
        -lopencv_objdetect340d -lopencv_optflow340d -lopencv_phase_unwrapping340d \
        -lopencv_photo340d -lopencv_plot340d -lopencv_reg340d \
        -lopencv_rgbd340d -lopencv_saliency340d -lopencv_shape340d \
        -lopencv_stereo340d -lopencv_stitching340d -lopencv_structured_light340d \
        -lopencv_superres340d -lopencv_surface_matching340d -lopencv_text340d \
        -lopencv_tracking340d -lopencv_video340d -lopencv_videoio340d \
        -lopencv_videostab340d -lopencv_xfeatures2d340d -lopencv_ximgproc340d \
        -lopencv_xobjdetect340d -lopencv_xphoto340d

# E:/opencv3.4.5/opencv/build/x64/vc14/lib/opencv_world345d.lib
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
