#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/stitching.hpp>
using namespace cv;
using namespace std;
std::vector<Mat> imgs;
int main(int argc, char *argv[])
{
	// QApplication a(argc, argv);
	// MainWindow w;
	// w.show();
	// return a.exec();

	//string imageName("F:\\Qt_worksapce\\OpencvTest\\26.png"); // 图片在电脑中的绝对地址
	//
	Stitcher::Mode mode = Stitcher::PANORAMA;
	bool try_use_gpu = false;
	cv::Mat image1, image2, image3;
	image1 = cv::imread("F:\\Qt_worksapce\\OpencvTest\\1.jpg");
	image2 = cv::imread("F:\\Qt_worksapce\\OpencvTest\\2.jpg");
	image3 = cv::imread("F:\\Qt_worksapce\\OpencvTest\\3.jpg");
	imgs.push_back(image1);
	imgs.push_back(image2);
	imgs.push_back(image3);
	cv::Mat Dst;

	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	Stitcher::Status status = stitcher.stitch(imgs, pano);
		//stitch(imgs, pano);
	if (status != Stitcher::OK) {
		cout << "图像相似度太差，拼接失败！" << endl;
	}
	else {
		cv::imshow("结果",pano);//out.jpg
	}
	waitKey(0);
	return  0;
}



