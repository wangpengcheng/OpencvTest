/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListView *image_list_view;
    QPushButton *add_img_button;
    QPushButton *delete_img_button;
    QPushButton *change_arc_button;
    QPushButton *channce_changebutton;
    QPushButton *confirm_change_button;
    QPushButton *stitch_img_button;
    QPushButton *save_img_button;
    QPushButton *clean_imgs_button;
    QTextEdit *log_edit;
    QCheckBox *wavecorrect_checkbox;
    QCheckBox *showimg_checkbox;
    QCheckBox *saveimage_checkbox;
    QCheckBox *preview_checkbox;
    QDoubleSpinBox *workmegapix_spinbox;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *seammegapix_spinbox;
    QLabel *label_3;
    QDoubleSpinBox *composemegapix_spinbox;
    QLabel *label_4;
    QDoubleSpinBox *confthresh_spinbox;
    QLabel *label_5;
    QDoubleSpinBox *matchconf_spinbox;
    QComboBox *featurestype_combobox;
    QLabel *label_6;
    QComboBox *matchertype_combobox;
    QLabel *label_7;
    QComboBox *bacosttype_combobox;
    QComboBox *wavecorrecttype_combobox;
    QComboBox *warptype_combobox;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *exposcomptype_combobox;
    QLabel *label_11;
    QComboBox *seamfindtype_combobox;
    QLabel *label_12;
    QLabel *label_13;
    QDoubleSpinBox *blendstrength_spinbox;
    QLabel *label_14;
    QComboBox *blendtype_combobox;
    QCheckBox *showlog_checkbox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(598, 738);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        image_list_view = new QListView(centralWidget);
        image_list_view->setObjectName(QString::fromUtf8("image_list_view"));
        image_list_view->setGeometry(QRect(10, 10, 571, 121));
        add_img_button = new QPushButton(centralWidget);
        add_img_button->setObjectName(QString::fromUtf8("add_img_button"));
        add_img_button->setGeometry(QRect(50, 140, 91, 31));
        delete_img_button = new QPushButton(centralWidget);
        delete_img_button->setObjectName(QString::fromUtf8("delete_img_button"));
        delete_img_button->setGeometry(QRect(170, 140, 91, 31));
        change_arc_button = new QPushButton(centralWidget);
        change_arc_button->setObjectName(QString::fromUtf8("change_arc_button"));
        change_arc_button->setGeometry(QRect(460, 140, 91, 31));
        channce_changebutton = new QPushButton(centralWidget);
        channce_changebutton->setObjectName(QString::fromUtf8("channce_changebutton"));
        channce_changebutton->setGeometry(QRect(370, 410, 71, 31));
        confirm_change_button = new QPushButton(centralWidget);
        confirm_change_button->setObjectName(QString::fromUtf8("confirm_change_button"));
        confirm_change_button->setGeometry(QRect(490, 410, 61, 31));
        stitch_img_button = new QPushButton(centralWidget);
        stitch_img_button->setObjectName(QString::fromUtf8("stitch_img_button"));
        stitch_img_button->setGeometry(QRect(150, 480, 91, 31));
        save_img_button = new QPushButton(centralWidget);
        save_img_button->setObjectName(QString::fromUtf8("save_img_button"));
        save_img_button->setGeometry(QRect(340, 480, 91, 31));
        clean_imgs_button = new QPushButton(centralWidget);
        clean_imgs_button->setObjectName(QString::fromUtf8("clean_imgs_button"));
        clean_imgs_button->setGeometry(QRect(310, 140, 91, 31));
        log_edit = new QTextEdit(centralWidget);
        log_edit->setObjectName(QString::fromUtf8("log_edit"));
        log_edit->setGeometry(QRect(10, 520, 571, 191));
        log_edit->setReadOnly(true);
        wavecorrect_checkbox = new QCheckBox(centralWidget);
        wavecorrect_checkbox->setObjectName(QString::fromUtf8("wavecorrect_checkbox"));
        wavecorrect_checkbox->setGeometry(QRect(480, 240, 101, 18));
        QFont font;
        font.setPointSize(10);
        wavecorrect_checkbox->setFont(font);
        showimg_checkbox = new QCheckBox(centralWidget);
        showimg_checkbox->setObjectName(QString::fromUtf8("showimg_checkbox"));
        showimg_checkbox->setGeometry(QRect(480, 270, 91, 18));
        showimg_checkbox->setFont(font);
        saveimage_checkbox = new QCheckBox(centralWidget);
        saveimage_checkbox->setObjectName(QString::fromUtf8("saveimage_checkbox"));
        saveimage_checkbox->setGeometry(QRect(480, 300, 91, 18));
        saveimage_checkbox->setFont(font);
        preview_checkbox = new QCheckBox(centralWidget);
        preview_checkbox->setObjectName(QString::fromUtf8("preview_checkbox"));
        preview_checkbox->setGeometry(QRect(480, 210, 91, 18));
        preview_checkbox->setFont(font);
        workmegapix_spinbox = new QDoubleSpinBox(centralWidget);
        workmegapix_spinbox->setObjectName(QString::fromUtf8("workmegapix_spinbox"));
        workmegapix_spinbox->setGeometry(QRect(400, 210, 64, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 210, 91, 21));
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 240, 91, 21));
        label_2->setFont(font);
        seammegapix_spinbox = new QDoubleSpinBox(centralWidget);
        seammegapix_spinbox->setObjectName(QString::fromUtf8("seammegapix_spinbox"));
        seammegapix_spinbox->setGeometry(QRect(400, 240, 64, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(300, 270, 91, 21));
        label_3->setFont(font);
        composemegapix_spinbox = new QDoubleSpinBox(centralWidget);
        composemegapix_spinbox->setObjectName(QString::fromUtf8("composemegapix_spinbox"));
        composemegapix_spinbox->setGeometry(QRect(400, 270, 64, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(300, 300, 91, 21));
        label_4->setFont(font);
        confthresh_spinbox = new QDoubleSpinBox(centralWidget);
        confthresh_spinbox->setObjectName(QString::fromUtf8("confthresh_spinbox"));
        confthresh_spinbox->setGeometry(QRect(400, 300, 64, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(300, 330, 91, 21));
        label_5->setFont(font);
        matchconf_spinbox = new QDoubleSpinBox(centralWidget);
        matchconf_spinbox->setObjectName(QString::fromUtf8("matchconf_spinbox"));
        matchconf_spinbox->setGeometry(QRect(400, 330, 64, 22));
        featurestype_combobox = new QComboBox(centralWidget);
        featurestype_combobox->setObjectName(QString::fromUtf8("featurestype_combobox"));
        featurestype_combobox->setGeometry(QRect(130, 210, 131, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 210, 91, 21));
        label_6->setFont(font);
        matchertype_combobox = new QComboBox(centralWidget);
        matchertype_combobox->setObjectName(QString::fromUtf8("matchertype_combobox"));
        matchertype_combobox->setGeometry(QRect(130, 240, 131, 21));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 240, 91, 21));
        label_7->setFont(font);
        bacosttype_combobox = new QComboBox(centralWidget);
        bacosttype_combobox->setObjectName(QString::fromUtf8("bacosttype_combobox"));
        bacosttype_combobox->setGeometry(QRect(130, 270, 131, 21));
        wavecorrecttype_combobox = new QComboBox(centralWidget);
        wavecorrecttype_combobox->setObjectName(QString::fromUtf8("wavecorrecttype_combobox"));
        wavecorrecttype_combobox->setGeometry(QRect(130, 300, 131, 21));
        warptype_combobox = new QComboBox(centralWidget);
        warptype_combobox->setObjectName(QString::fromUtf8("warptype_combobox"));
        warptype_combobox->setGeometry(QRect(130, 330, 131, 21));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 270, 101, 21));
        label_8->setFont(font);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 300, 111, 21));
        label_9->setFont(font);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 330, 91, 21));
        label_10->setFont(font);
        exposcomptype_combobox = new QComboBox(centralWidget);
        exposcomptype_combobox->setObjectName(QString::fromUtf8("exposcomptype_combobox"));
        exposcomptype_combobox->setGeometry(QRect(130, 360, 131, 21));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 360, 91, 21));
        label_11->setFont(font);
        seamfindtype_combobox = new QComboBox(centralWidget);
        seamfindtype_combobox->setObjectName(QString::fromUtf8("seamfindtype_combobox"));
        seamfindtype_combobox->setGeometry(QRect(130, 390, 131, 21));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 390, 91, 21));
        label_12->setFont(font);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(300, 360, 91, 21));
        label_13->setFont(font);
        blendstrength_spinbox = new QDoubleSpinBox(centralWidget);
        blendstrength_spinbox->setObjectName(QString::fromUtf8("blendstrength_spinbox"));
        blendstrength_spinbox->setGeometry(QRect(400, 360, 64, 22));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 420, 91, 21));
        label_14->setFont(font);
        blendtype_combobox = new QComboBox(centralWidget);
        blendtype_combobox->setObjectName(QString::fromUtf8("blendtype_combobox"));
        blendtype_combobox->setGeometry(QRect(130, 420, 131, 21));
        showlog_checkbox = new QCheckBox(centralWidget);
        showlog_checkbox->setObjectName(QString::fromUtf8("showlog_checkbox"));
        showlog_checkbox->setGeometry(QRect(480, 330, 91, 18));
        showlog_checkbox->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\233\276\347\211\207\346\213\274\346\216\245\345\231\250", nullptr));
        add_img_button->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\233\276\347\211\207", nullptr));
        delete_img_button->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\233\276\347\211\207", nullptr));
        change_arc_button->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271\345\217\202\346\225\260", nullptr));
        channce_changebutton->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        confirm_change_button->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        stitch_img_button->setText(QApplication::translate("MainWindow", "\346\213\274\346\216\245\345\233\276\347\211\207", nullptr));
        save_img_button->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
        clean_imgs_button->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\345\233\276\347\211\207", nullptr));
        wavecorrect_checkbox->setText(QApplication::translate("MainWindow", "WaveCorrect", nullptr));
        showimg_checkbox->setText(QApplication::translate("MainWindow", "ShowImage", nullptr));
        saveimage_checkbox->setText(QApplication::translate("MainWindow", "SaveImage", nullptr));
        preview_checkbox->setText(QApplication::translate("MainWindow", "Preview", nullptr));
        label->setText(QApplication::translate("MainWindow", "WorkMegapix", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "SeamMegapix", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "ComposeMegapix", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "ConfThresh", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "MatchConf", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "FeaturesType", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "MatcherType", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "BaCostFuncType", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "WaveCorrectType", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "WarpType", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "ExposCompType", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "SeamFindType", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "BlendStrength", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "BlendType", nullptr));
        showlog_checkbox->setText(QApplication::translate("MainWindow", "ShowLog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
