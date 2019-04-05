# OpencvTest
opencv stitcher with qt
## set GUI by Qt with OpenCVStitcher
*refrence*: [OPenCV stitching and stitching_detailed](https://blog.csdn.net/czl389/article/details/60767654);[cv::Stitcher Class Reference](https://docs.opencv.org/3.4.0/d2/d8d/classcv_1_1Stitcher.html);[sift全景图拼接完整的项目](https://blog.csdn.net/wys2011101169/article/details/53925377);[论文参考文献](https://docs.opencv.org/3.4.0/d0/de3/citelist.html#CITEREF_BL07)


主要mainWindow.cpp参数解释，方便设置参数
```c++
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
```