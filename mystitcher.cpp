#include "mystitcher.h"

MyStitcher::MyStitcher(QObject *parent) : QObject(parent)
{
    Init();
}
int MyStitcher::StitchImages(){
    //根据是否输出日志决定是否开启时钟计时
#if ENABLE_LOG
	int64 app_start_time = getTickCount();
#endif

#if 0
	cv::setBreakOnError(true);
#endif

	// Check if have enough images
	int num_images = static_cast<int>(img_names_.size());//获取image图片数量
    //图片小于2输出警告
	if (num_images < 2)
	{
		LOGLN("Need more images...");
		return -1;
	}
	//设置相关参数，若按原图片大小进行拼接时，会在曝光补偿时造成内存溢出，所以在计算时缩小图像尺寸变为work_megapix*10000
	double work_scale = 1, seam_scale = 1, compose_scale = 1;
	bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

	//开始寻找特征点
	LOGLN("Find image feature...");
#if ENABLE_LOG
	int64 t = getTickCount();
#endif
    //根据输入参数，决定特征点找寻函数类型
	Ptr<FeaturesFinder> finder;
	if (features_type_ == "surf")
	{
#ifdef HAVE_OPENCV_XFEATURES2D
		if (try_cuda_ && cuda::getCudaEnabledDeviceCount() > 0)
			finder = makePtr<SurfFeaturesFinderGpu>();
		else
#endif
			finder = makePtr<SurfFeaturesFinder>();
	}
	else if (features_type_ == "orb")
	{
		finder = makePtr<OrbFeaturesFinder>();
	}
    //opencv 3.4.0 没有SiftFeaturesFinder;使用3.4.4以上版本可以使用
//	else if (features_type == "sift") {
//		finder = makePtr<SiftFeaturesFinder>();
//	}
	else
	{
		cout << "Unknown 2D features type: '" << features_type_ << "'.\n";
		return -1;
	}

	Mat full_img, img;//设置图像矩阵
	vector<ImageFeatures> features(num_images);//设置特征向量
	vector<Mat> images(num_images);//设置图像Vector
	vector<Size> full_img_sizes(num_images);//设置全图像尺寸
	double seam_work_aspect = 1;

	for (int i = 0; i < num_images; ++i)
	{
		full_img = imread(img_names_[i]);//读取图片
		full_img_sizes[i] = full_img.size();//未缩放图片大小
        //图片读取失败，输出参数
		if (full_img.empty())
		{
			LOGLN("Can't open image " << img_names_[i]);
			return -1;
		}
		//如果图像配准分配率小于0则不进行缩放
		if (work_megapix_< 0)
		{
			img = full_img;
			work_scale = 1;
			is_work_scale_set = true;
		}
		else
		{
			if (!is_work_scale_set)//是否允许图像缩放，
			{
				//将图像压缩到work_megapix*10^6以下,加快运算速度
				work_scale = min(1.0, sqrt(work_megapix_ * 1e6 / full_img.size().area()));
				is_work_scale_set = true;
			}
			cv::resize(full_img, img, Size(), work_scale, work_scale, INTER_LINEAR_EXACT);
		}
		if (!is_seam_scale_set)
		{
			seam_scale = min(1.0, sqrt(seam_megapix_ * 1e6 / full_img.size().area()));
			seam_work_aspect = seam_scale / work_scale;
			is_seam_scale_set = true;
		}
		// 计算图像特征点，以及计算特征点描述子，并将img_idx设置为i
		(*finder)(img, features[i]);
		features[i].img_idx = i;
        //输出计算出的图像特征
		LOGLN("Features in image #" << i + 1 << ": " << features[i].keypoints.size());
        //重新进行缩放，方便下面的计算
		cv::resize(full_img, img, Size(), seam_scale, seam_scale, INTER_LINEAR_EXACT);
		images[i] = img.clone();//拷贝最终结果
	}
    //释放finder内存空间
	finder->collectGarbage();
	full_img.release();//释放内存
	img.release();//释放内存
    //输出找寻开始时间
	LOGLN("Finding features, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");
    //开始图片之间的两两特征匹配
	LOG("Pairwise matching...\n");
#if ENABLE_LOG
	t = getTickCount();
#endif
	//使用最近邻和次近邻匹配，对任意两幅图进行匹配
	vector<MatchesInfo> pairwise_matches;//初始化匹配结果信息
	Ptr<FeaturesMatcher> matcher;//初始化匹配指针
    //根据选择参数，选择匹配算子构造函数
	if (matcher_type_ == "affine")
		matcher = makePtr<AffineBestOf2NearestMatcher>(false, try_cuda_, match_conf_);
	else if (range_width_== -1)//
		matcher = makePtr<BestOf2NearestMatcher>(try_cuda_, match_conf_);
	else
		matcher = makePtr<BestOf2NearestRangeMatcher>(range_width_, try_cuda_, match_conf_);
	//对pairwise_matches中大于0的进行匹配
	(*matcher)(features, pairwise_matches);
    //释放matcher内存
	matcher->collectGarbage();
    //输出所用时间
	LOGLN("Pairwise matching, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	// 是否需要存储特征
	if (save_graph_)
	{
		LOGLN("Saving matches graph...");
		ofstream f(save_graph_to_.c_str());
		f << cv::detail::matchesGraphAsString(img_names_, pairwise_matches, conf_thresh_);
	}

	//将置信度高于设置门限的留下来，其他的删除
	vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh_);//根据执行度筛选匹配特征值
	vector<Mat> img_subset;
	vector<String> img_names_subset;
	vector<Size> full_img_sizes_subset;
    //处理筛选后的结果
	for (size_t i = 0; i < indices.size(); ++i)
	{
		img_names_subset.push_back(img_names_[indices[i]]);
		img_subset.push_back(images[indices[i]]);
		full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
	}

	images = img_subset;
	img_names_ = img_names_subset;
	full_img_sizes = full_img_sizes_subset;

	// 确认删除后是否还是剩余足够的图片
	num_images = static_cast<int>(img_names_.size());
	if (num_images < 2)
	{
		LOGLN("need more images...");
		return -1;
	}
	//基于单应性矩阵H的估计
	Ptr<Estimator> estimator;
	if (estimator_type_ == "affine")
		estimator = makePtr<AffineBasedEstimator>();
	else
		estimator = makePtr<HomographyBasedEstimator>();
	//设置相机参数
	vector<CameraParams> cameras;
	if (!(*estimator)(features, pairwise_matches, cameras))
	{
		cout << "Homography estimation failed.\n";
		return -1;
	}
	//计算出R矩阵
	for (size_t i = 0; i < cameras.size(); ++i)
	{
		Mat R;
		cameras[i].R.convertTo(R, CV_32F);//转换Mat矩阵值的格式
		cameras[i].R = R;
		LOGLN("Initial camera intrinsics #" << indices[i] + 1 << ":\nK:\n" << cameras[i].K() << "\nR:\n" << cameras[i].R);
	}
	//捆绑调整方法精确求取变换参数
	Ptr<detail::BundleAdjusterBase> adjuster;
	//选择相机参数矫正方式；并建立对应矫正相机
	if (ba_cost_func_ == "reproj") adjuster = makePtr<detail::BundleAdjusterReproj>();
	else if (ba_cost_func_ == "ray") adjuster = makePtr<detail::BundleAdjusterRay>();
	else if (ba_cost_func_ == "affine") adjuster = makePtr<detail::BundleAdjusterAffinePartial>();
	else if (ba_cost_func_ == "no") adjuster = makePtr<NoBundleAdjuster>();
	else
	{
		cout << "Unknown bundle adjustment cost function: '" << ba_cost_func_ << "'.\n";
		return -1;
	}
	//设置矫正阈值
	adjuster->setConfThresh(conf_thresh_);
	//计算掩膜
	Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
	if (ba_refine_mask_[0] == 'x') refine_mask(0, 0) = 1;
	if (ba_refine_mask_[1] == 'x') refine_mask(0, 1) = 1;
	if (ba_refine_mask_[2] == 'x') refine_mask(0, 2) = 1;
	if (ba_refine_mask_[3] == 'x') refine_mask(1, 1) = 1;
	if (ba_refine_mask_[4] == 'x') refine_mask(1, 2) = 1;
	adjuster->setRefinementMask(refine_mask);
	if (!(*adjuster)(features, pairwise_matches, cameras))//cameras存储求精后的变换参数
	{
		cout << "Camera parameters adjusting failed.\n";
		return -1;
	}

	// 找到中间focals长度
	//存入相机像素
	vector<double> focals;
	for (size_t i = 0; i < cameras.size(); ++i)
	{
		LOGLN("Camera #" << indices[i] + 1 << ":\nK:\n" << cameras[i].K() << "\nR:\n" << cameras[i].R);
		focals.push_back(cameras[i].focal);
	}

	sort(focals.begin(), focals.end());
	float warped_image_scale;
    if (focals.size() % 2 == 1){
		warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
    }else{
		warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;
    }
    //设置波形矫正
	if (do_wave_correct_)
	{
		vector<Mat> rmats;
		for (size_t i = 0; i < cameras.size(); ++i)
			rmats.push_back(cameras[i].R.clone());
		waveCorrect(rmats, wave_correct_);//进行波形矫正
		for (size_t i = 0; i < cameras.size(); ++i)
			cameras[i].R = rmats[i];
	}
    //开始图像弯曲和融合
	LOGLN("Warping images (auxiliary)... ");//弯曲图像
#if ENABLE_LOG
	t = getTickCount();
#endif

	vector<Point> corners(num_images);//统一坐标后的顶点
	vector<UMat> masks_warped(num_images);
	vector<UMat> images_warped(num_images);
	vector<Size> sizes(num_images);//图像大小
	vector<UMat> masks(num_images);//融合掩码

	// 准备图像融合掩码
	for (int i = 0; i < num_images; ++i)
	{
		masks[i].create(images[i].size(), CV_8U);//mask 为模，和图像大小一样，设置为白色，在上面进行融合
		masks[i].setTo(Scalar::all(255));
	}

	//弯曲图像和融合掩码
	Ptr<WarperCreator> warper_creator;
	//是否开启GPU模式
#ifdef HAVE_OPENCV_CUDAWARPING
	if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
	{
		if (warp_type == "plane")
			warper_creator = makePtr<cv::PlaneWarperGpu>();
		else if (warp_type == "cylindrical")
			warper_creator = makePtr<cv::CylindricalWarperGpu>();
		else if (warp_type == "spherical")
			warper_creator = makePtr<cv::SphericalWarperGpu>();
	}
	else
#endif
	{
		//选择弯曲方式
		if (warp_type_ == "plane")
			warper_creator = makePtr<cv::PlaneWarper>();
		else if (warp_type_ == "affine")
			warper_creator = makePtr<cv::AffineWarper>();
		else if (warp_type_ == "cylindrical")
			warper_creator = makePtr<cv::CylindricalWarper>();
		else if (warp_type_ == "spherical")
			warper_creator = makePtr<cv::SphericalWarper>();
		else if (warp_type_ == "fisheye")
			warper_creator = makePtr<cv::FisheyeWarper>();
		else if (warp_type_ == "stereographic")
			warper_creator = makePtr<cv::StereographicWarper>();
		else if (warp_type_ == "compressedPlaneA2B1")
			warper_creator = makePtr<cv::CompressedRectilinearWarper>(2.0f, 1.0f);
		else if (warp_type_ == "compressedPlaneA1.5B1")
			warper_creator = makePtr<cv::CompressedRectilinearWarper>(1.5f, 1.0f);
		else if (warp_type_ == "compressedPlanePortraitA2B1")
			warper_creator = makePtr<cv::CompressedRectilinearPortraitWarper>(2.0f, 1.0f);
		else if (warp_type_ == "compressedPlanePortraitA1.5B1")
			warper_creator = makePtr<cv::CompressedRectilinearPortraitWarper>(1.5f, 1.0f);
		else if (warp_type_ == "paniniA2B1")
			warper_creator = makePtr<cv::PaniniWarper>(2.0f, 1.0f);
		else if (warp_type_ == "paniniA1.5B1")
			warper_creator = makePtr<cv::PaniniWarper>(1.5f, 1.0f);
		else if (warp_type_ == "paniniPortraitA2B1")
			warper_creator = makePtr<cv::PaniniPortraitWarper>(2.0f, 1.0f);
		else if (warp_type_ == "paniniPortraitA1.5B1")
			warper_creator = makePtr<cv::PaniniPortraitWarper>(1.5f, 1.0f);
		else if (warp_type_ == "mercator")
			warper_creator = makePtr<cv::MercatorWarper>();
		else if (warp_type_ == "transverseMercator")
			warper_creator = makePtr<cv::TransverseMercatorWarper>();
	}

	if (!warper_creator)
	{
		cout << "Can't create the following warper '" << warp_type_ << "'\n";
		return 1;
	}
	//warped_image_scale焦距中值;
	Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));
    //根据前面的选择参数，对图像进行计算和弯曲
	for (int i = 0; i < num_images; ++i)
	{
		Mat_<float> K;
		cameras[i].K().convertTo(K, CV_32F);
		float swa = (float)seam_work_aspect;
		K(0, 0) *= swa; K(0, 2) *= swa;
		K(1, 1) *= swa; K(1, 2) *= swa;

		corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
		sizes[i] = images_warped[i].size();

		warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
	}

	vector<UMat> images_warped_f(num_images);
	for (int i = 0; i < num_images; ++i)
		images_warped[i].convertTo(images_warped_f[i], CV_32F);
	//输出弯曲变换时间
	LOGLN("Warping images, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");
    //图像补偿和修复
	Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(expos_comp_type_);
    //开始图像补偿
	compensator->feed(corners, images_warped, masks_warped);
	//查找图片之间的拼缝
	Ptr<SeamFinder> seam_finder;
	if (seam_find_type_ == "no")
		seam_finder = makePtr<detail::NoSeamFinder>();
	else if (seam_find_type_ == "voronoi")
		seam_finder = makePtr<detail::VoronoiSeamFinder>();
	else if (seam_find_type_ == "gc_color")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR);
	}
	else if (seam_find_type_ == "gc_colorgrad")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
	}
	else if (seam_find_type_ == "dp_color")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR);
	else if (seam_find_type_ == "dp_colorgrad")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR_GRAD);
	if (!seam_finder)
	{
		cout << "Can't create the following seam finder '" << seam_find_type_ << "'\n";
		return 1;
	}

	seam_finder->find(images_warped_f, corners, masks_warped);

	// 释放未使用内存
	images.clear();
	images_warped.clear();
	images_warped_f.clear();
	masks.clear();
	//图像融合
	LOGLN("Compositing...");
#if ENABLE_LOG
	t = getTickCount();
#endif

	Mat img_warped, img_warped_s;
	Mat dilated_mask, seam_mask, mask, mask_warped;
	Ptr<Blender> blender;
	Ptr<Timelapser> timelapser;
	//double compose_seam_aspect = 1;
	double compose_work_aspect = 1;

	for (int img_idx = 0; img_idx < num_images; ++img_idx)
	{
		LOGLN("Compositing image #" << indices[img_idx] + 1);

		// 如果必要重新读入并计算图片
		//full_img = imread(samples::findFile(img_names[img_idx]));
		full_img = imread(img_names_[img_idx]);
		if (!is_compose_scale_set)
		{
            //融合解析
			if (compose_megapix_ > 0)
				compose_scale = min(1.0, sqrt(compose_megapix_ * 1e6 / full_img.size().area()));
			is_compose_scale_set = true;

			// 计算缩放比例
			//compose_seam_aspect = compose_scale / seam_scale;
			compose_work_aspect = compose_scale / work_scale;

			// 更新弯曲图像比例
			warped_image_scale *= static_cast<float>(compose_work_aspect);
			warper = warper_creator->create(warped_image_scale);

			// 更新 corners and sizes参数
			for (int i = 0; i < num_images; ++i)
			{
				// 更新相机属性
				cameras[i].focal *= compose_work_aspect;
				cameras[i].ppx *= compose_work_aspect;
				cameras[i].ppy *= compose_work_aspect;

				// 更新 corner and size
				Size sz = full_img_sizes[i];
				if (std::abs(compose_scale - 1) > 1e-1)
				{
					sz.width = cvRound(full_img_sizes[i].width * compose_scale);
					sz.height = cvRound(full_img_sizes[i].height * compose_scale);
				}
				//corners和sizes
				Mat K;
				cameras[i].K().convertTo(K, CV_32F);
				Rect roi = warper->warpRoi(sz, K, cameras[i].R);
				corners[i] = roi.tl();
				sizes[i] = roi.size();
			}
		}
		if (abs(compose_scale - 1) > 1e-1)
			cv::resize(full_img, img, Size(), compose_scale, compose_scale, INTER_LINEAR_EXACT);
		else
			img = full_img;
		full_img.release();
		Size img_size = img.size();

		Mat K;
		cameras[img_idx].K().convertTo(K, CV_32F);

		// 扭曲当前图像
		warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

		// 扭曲当前图像掩膜
		mask.create(img_size, CV_8U);
		mask.setTo(Scalar::all(255));
		warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

		// 曝光补偿
		compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);
        //转换图片格式
		img_warped.convertTo(img_warped_s, CV_16S);
        //释放内存
		img_warped.release();
		img.release();
		mask.release();

		cv::dilate(masks_warped[img_idx], dilated_mask, Mat());
		cv::resize(dilated_mask, seam_mask, mask_warped.size(), 0, 0, INTER_LINEAR_EXACT);
		mask_warped = seam_mask & mask_warped;
		//初始化blender
		if (!blender && !timelapse_)
		{
			blender = Blender::createDefault(blend_type_, try_cuda_);
			Size dst_sz = resultRoi(corners, sizes).size();
			float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength_ / 100.f;
			if (blend_width < 1.f)
				blender = Blender::createDefault(Blender::NO, try_cuda_);
			else if (blend_type_ == Blender::MULTI_BAND)
			{
				MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(blender.get());
				mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));
				LOGLN("Multi-band blender, number of bands: " << mb->numBands());
			}
			else if (blend_type_ == Blender::FEATHER)
			{
				FeatherBlender* fb = dynamic_cast<FeatherBlender*>(blender.get());
				fb->setSharpness(1.f / blend_width);
				LOGLN("Feather blender, sharpness: " << fb->sharpness());
			}
			//根据corners顶点和图像的大小确定最终全景图的尺寸
			blender->prepare(corners, sizes);
		}
		else if (!timelapser && timelapse_)
		{
			timelapser = Timelapser::createDefault(timelapse_type_);
			timelapser->initialize(corners, sizes);
		}

		//
		if (timelapse_)
		{
			timelapser->process(img_warped_s, Mat::ones(img_warped_s.size(), CV_8UC1), corners[img_idx]);
			String fixedFileName;
			size_t pos_s = String(img_names_[img_idx]).find_last_of("/\\");
			if (pos_s == String::npos)
			{
				fixedFileName = "fixed_" + img_names_[img_idx];
			}
			else
			{
				fixedFileName = "fixed_" + String(img_names_[img_idx]).substr(pos_s + 1, String(img_names_[img_idx]).length() - pos_s);
			}

			imwrite(fixedFileName, timelapser->getDst());
		}
		else
		{
			// 融合当前图像
			blender->feed(img_warped_s, mask_warped, corners[img_idx]);
		}
	}
	//输出时间
	if (!timelapse_)
	{
		Mat result, result_mask;
		blender->blend(result, result_mask);

		LOGLN("Compositing, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

		imwrite(result_name_, result);
		result.convertTo(result_img_, CV_8UC1);
		imshow(result_name_,result_img_);
	}

	LOGLN("Finished, total time: " << ((getTickCount() - app_start_time) / getTickFrequency()) << " sec");
	//waitKey(0);
    return 0;
}
void MyStitcher::Init(){
    /*准备数据*/
    //将图片路径存入图片img_names vector
	String img0 = "F:/Qt_worksapce/OpencvTest/data/building/0.png";
	String img1 = "F:/Qt_worksapce/OpencvTest/data/building/1.png";
	String img2 = "F:/Qt_worksapce/OpencvTest/data/building/2.png";
	String img3 = "F:/Qt_worksapce/OpencvTest/data/building/3.png";
	String img4 = "F:/Qt_worksapce/OpencvTest/data/building/4.png";
	img_names_.push_back(img0);
	img_names_.push_back(img1);
	img_names_.push_back(img2);
	img_names_.push_back(img3);
    img_names_.push_back(img4);
    //创建日制文件
    if(is_log_){
        CreateLogFile();
        qDebug()<<"hello word";
    }
}
void MyStitcher::SaveImage(std::string file_path){
    if(!result_img_.empty()){
        cv::imwrite(file_path, result_img_);
    }
}
void MyStitcher::ImgNamesClean()
{
    if(!img_names_.empty()){
        img_names_.clear();
    }else {
        LOGLN("this image names is empty");
    }
}
int MyStitcher::CreateLogFile()
{
    QString filePath=QDir::currentPath();
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString fileName=current_date_time.toString("yyyy-MM-dd-hh-mm-ss-zzz")+".txt";
    QString file_full_path=filePath+"/"+fileName;
    log_file_path_=file_full_path.toStdString();
    std::cout<<log_file_path_<<std::endl;
    qDebug()<<file_full_path;
    QFileInfo file_mesage(filePath+'/'+fileName);
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"不存在该路径"<<endl;
        tempDir.mkpath(filePath);
    }
    QFile temp_file(file_full_path);
    //判断文件是否存在
        if(temp_file.exists())
        {
            qDebug()<<"文件已经存在！";
        }else{
            //存在打开，不存在创建
            temp_file.open(QIODevice::ReadWrite | QIODevice::Text);
            //写入内容,这里需要转码，否则报错。
            QByteArray str = fileName.toUtf8();
            //写入QByteArray格式字符串
            temp_file.write(str);

            //提示成功
            qDebug()<<"创建文件,文件创建成功";
        }
        //关闭文件
        temp_file.close();
        return 0;

}
