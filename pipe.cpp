// pipe.cpp : Defines the entry point for the console application.
//https://blog.csdn.net/piaoxuezhong/article/details/54588270

#include "stdafx.h"
#include <iostream>
#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\opencv.hpp"
#include "Histogram1D.h"

using namespace std;
using namespace cv;

string ad = "C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\";

Mat combineImages(vector<Mat> imgs, int col, int row, bool hasMargin);//函数声明

int main()
{

//------------------------------------------------------------------------//
//-----------------------------------------------------------------------//
	Mat in = imread(ad + "original image\\05.jpg");
	//Mat in = imread(ad + "original image\\.jpg");
//------------------------------------------------------------------------//
//-----------------------------------------------------------------------//

	if (!in.data) { cout << "Error loading lena.bmp" << endl; return -1; }
	cout << "****************************************************************************************" << endl;
	cout << "Input Image size: " << in.dataend - in.datastart << endl;
	cout << "height: " << in.rows << endl << "width: " << in.cols << endl << "depth: " << in.channels() << endl;
	cout << "height*width*depth: " << in.rows*in.cols*in.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;
	//**************************************************************************************************************
	//**************************************************************************************************************
	////////////////////////////////////blue////////////////////////////////////////////////////////////////////////
	//-----------------------------------get false color Image -----------------------------------------------------
	Mat mv[3];
	split(in, mv);

	Mat bp = imread(ad + "colormaps\\blue.bmp");
	cv::cvtColor(bp, bp, cv::COLOR_BGR2RGB);

	cv::Mat image_blue_3c;//Blue
	cv::cvtColor(mv[0], image_blue_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_blue;
	cv::LUT(image_blue_3c, bp, image_color_blue);
	Mat b[3];
	split(image_color_blue, b);
	//applyColorMap(mv[0], im_color_b, COLORMAP_RAINBOW);//b

	cv::Mat image_green_3c;
	cv::cvtColor(mv[1], image_green_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_green;//Green
	cv::LUT(image_green_3c, bp, image_color_green);
	Mat g[3];
	split(image_color_green, g);
	//applyColorMap(mv[1], im_color_g, COLORMAP_RAINBOW);//g
	//imshow("im_color_g", im_color_g);

	cv::Mat image_red_3c;//Red
	cv::cvtColor(mv[2], image_red_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_red;
	cv::LUT(image_red_3c, bp, image_color_red);
	Mat r[3];
	split(image_color_red, r);
	//applyColorMap(mv[2], im_color_r, COLORMAP_RAINBOW);//r
	//imshow("im_color_r", im_color_r);


	Mat im_color;
	vector<Mat> src;     //合并false color image
	src.push_back(b[0]);
	src.push_back(g[1]);
	src.push_back(r[2]);
	merge(src, im_color);
	//imshow("False Color Image", im_color);
	imwrite(ad + "scheme2\\blue\\False_Image(blue).bmp", im_color);

	//----------------------------------get BGR Channels HistogramImage	------------------------------------------------------//
	/*
	//example hist(132),hist(144)
	Mat image3 = mv[0];  //读取B
	Histogram1D h3;
	imshow("channel blue", image3);
	imshow("histogram blue", h3.getHistogramImage(image3));
	cout << "hist(132)=" << h3.getSpecifyValue(mv[0], 132.0) << endl << "hist(144)=" << h3.getSpecifyValue(mv[0], 144.0) << endl;
	*/
	Histogram1D h0;
	Histogram1D h1;
	Histogram1D h2;

	Mat image0 = mv[0];  //读取B
	Mat image1 = mv[1];  //读取G
	Mat image2 = mv[2];  //读取R

						 /*
						 Mat image0 = mv[0];  //读取B
						 Histogram1D h0;
						 imshow("channel blue", image0);
						 imshow("histogram blue", h0.getHistogramImage(image0));
						 int sum0 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h0.getSpecifyValue(image0, i) << endl;
						 sum0 = sum0 + h0.getSpecifyValue(image0, i);
						 }
						 cout << endl << endl << sum0 << endl << endl;


						 Mat image1 = mv[1];  //读取G
						 Histogram1D h1;
						 imshow("channel green", image1);
						 imshow("histogram green", h1.getHistogramImage(image1));
						 int sum1 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h1.getSpecifyValue(image1, i) << endl;
						 sum1 = sum1 + h1.getSpecifyValue(image1, i);
						 }
						 cout << endl << endl << sum1 << endl << endl;


						 Mat image2 = mv[2];  //读取R
						 cout << image2.rows << image2.cols << image2.channels() << endl;
						 cout << mv[2].rows << mv[2].cols << mv[2].channels() << endl;
						 Histogram1D h2;
						 imshow("channel red", image2);
						 imshow("histogram red", h2.getHistogramImage(image2));
						 int sum2 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h2.getSpecifyValue(image2, i) << endl;
						 sum2 = sum2 + h2.getSpecifyValue(image2, i);
						 }
						 cout << endl << endl << sum2 << endl << endl;
						 */

						 //----------------------------------------jpeg compression----------------------------------------------------------------//
	vector<uchar> buff;//buffer for coding
	vector<int> param = vector <int>(2);
	param[0] = CV_IMWRITE_JPEG_QUALITY;
	param[1] = 95;//default(95)0-100
				  //jpeg encode and decode
	imencode(".jpg", im_color, buff, param);
	cout << "****************************************************************************************" << endl;
	cout << "coded file size(jpg): " << buff.size() << endl;
	Mat jpegimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	imwrite(ad + "scheme2\\blue\\diencodeb.bmp", jpegimage);

	cout << endl << endl;
	cout << "JPEG Encoded-Decoded False Image size: " << jpegimage.dataend - jpegimage.datastart << endl;
	cout << "height: " << jpegimage.rows << endl << "width: " << jpegimage.cols << endl << "depth: " << jpegimage.channels() << endl;
	cout << "height*width*depth: " << jpegimage.rows*jpegimage.cols*jpegimage.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;

	//--------------------------------Inverse False Coloring,get I'(step 8)---------------------------------------------------//

	////////////////////////////fi'////////////////////////////
	bp.convertTo(bp, CV_32F);
	//cout << bp << endl;
	int n1 = bp.rows;
	int nc = bp.cols*bp.channels();

	Mat Fig = jpegimage;
	//imshow("sys", Fig);
	Fig.convertTo(Fig, CV_32F);
	//Fig.convertTo(Fig, CV_8U);
	//imshow("sys1", Fig);
	int fn1 = Fig.rows;
	int fnc = Fig.cols*Fig.channels();
	if (Fig.isContinuous())
	{
		fnc = fn1 * fnc;
		fn1 = 1;
	}
	float *f;
	////////////////////////////b//////////////////////////////////////////////
	for (int j = 0; j < fn1; j++)
	{
		f = Fig.ptr<float>(j);
		for (int i = 0; i < fnc; i = i + 3)//changed for test
		{
			//cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1 = bp.rows;
			int nc = bp.cols*bp.channels();
			if (bp.isContinuous())
			{
				nc = n1 * nc;
				n1 = 1;
			}
			float bmin = 255;
			float bpmin = 255;
			float *p;
			for (int n = 0; n < n1; n++)
			{
				p = bp.ptr<float>(j);
				for (int m = 0; m < nc; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p[m] - f[i]) >= 0)//判断差值是否为正值
					{

						/*
						if (p[m] - f[i] == bmin)//如果存在多解，判断直方图
						{
						//cout << "m="<< m<<", bmin="<<bmin<<", bpmin="<<bpmin << endl;

						if (h0.getSpecifyValue(image0,m) >= h0.getSpecifyValue(image0, bpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						cout << m <<","<< h0.getSpecifyValue(image0, m)<<","<< h0.getSpecifyValue(image0, bpmin) endl;
						//bmin = p[m] - f[i];
						//bpmin = m;
						}
						}
						*/
						if ((p[m] - f[i]) < bmin)//寻找最小差值
						{
							bmin = p[m] - f[i];
							bpmin = m;
						}

						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p[m] - f[i]) < 0)//判断差值是否为负值
					{
						if ((f[i] - p[m]) < bmin)//取反,寻找最小差值
						{
							bmin = p[m] - f[i];
							bpmin = m;
						}
						/*
						else if (f[i] - p[m] == bmin)//如果存在多解，判断直方图
						{
						if (h0.getSpecifyValue(image0, m) >= h0.getSpecifyValue(image0, bpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						bmin = p[m] - f[i];
						bpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f[i] = bpmin;
			//cout<<f[i]<<":";//
			//cout <<":"<<bpmin << ")";//
		}
	}

	///////////////////////////////////////g////////////////////////////////////////////////////////////
	//cout << endl << endl;//
	for (int j = 0; j < fn1; j++)
	{
		f = Fig.ptr<float>(j);
		for (int i = 1; i < fnc; i = i + 3)//changed for test
		{
			//	cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1 = bp.rows;
			int nc = bp.cols*bp.channels();
			if (bp.isContinuous())
			{
				nc = n1 * nc;
				n1 = 1;
			}
			float gmin = 255;
			float gpmin = 255;
			float *p;
			for (int n = 0; n < n1; n++)
			{
				p = bp.ptr<float>(j);
				for (int m = 1; m < nc; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p[m] - f[i]) >= 0)//判断差值是否为正值
					{
						if ((p[m] - f[i]) < gmin)//寻找最小差值
						{
							gmin = p[m] - f[i];
							gpmin = m;
						}
						/*
						else if (p[m] - f[i] == gmin)//如果存在多解，判断直方图
						{
						if (h1.getSpecifyValue(image1, m) >= h1.getSpecifyValue(image1, gpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						gmin = p[m] - f[i];
						gpmin = m;
						}
						}
						*/
						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p[m] - f[i]) < 0)//判断差值是否为负值
					{
						if ((f[i] - p[m]) < gmin)//取反,寻找最小差值
						{
							gmin = p[m] - f[i];
							gpmin = m;
						}
						/*
						else if (f[i] - p[m] == gmin)//如果存在多解，判断直方图
						{
						if (h1.getSpecifyValue(image1, m) >= h1.getSpecifyValue(image1, gpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						gmin = p[m] - f[i];
						gpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f[i] = gpmin;
			//cout<<f[i]<<")";//
		}
	}

	////////////////////////////////////r////////////////////////////////////////////////////////////
	//cout << endl << endl;//
	for (int j = 0; j < fn1; j++)
	{
		f = Fig.ptr<float>(j);
		for (int i = 2; i < fnc; i = i + 3)//changed for test
		{
			//cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1 = bp.rows;
			int nc = bp.cols*bp.channels();
			if (bp.isContinuous())
			{
				nc = n1 * nc;
				n1 = 1;
			}
			float rmin = 255;
			float rpmin = 255;
			float *p;
			for (int n = 0; n < n1; n++)
			{
				p = bp.ptr<float>(j);
				for (int m = 2; m < nc; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p[m] - f[i]) >= 0)//判断差值是否为正值
					{
						if ((p[m] - f[i]) < rmin)//寻找最小差值
						{
							rmin = p[m] - f[i];
							rpmin = m;
						}
						/*
						else if (p[m] - f[i] == rmin)//如果存在多解，判断直方图
						{
						if (h2.getSpecifyValue(image2, m) >= h2.getSpecifyValue(image2, rpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						rmin = p[m] - f[i];
						rpmin = m;
						}
						}
						*/
						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p[m] - f[i]) < 0)//判断差值是否为负值
					{
						if ((f[i] - p[m]) < rmin)//取反,寻找最小差值
						{
							rmin = p[m] - f[i];
							rpmin = m;
						}
						/*
						else if (f[i] - p[m] == rmin)//如果存在多解，判断直方图
						{
						if (h2.getSpecifyValue(image2, m) >= h2.getSpecifyValue(image2, rpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						rmin = p[m] - f[i];
						rpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f[i] = rpmin;
			//cout<<f[i]<<")";//
		}
	}

	Fig.convertTo(Fig, CV_8U);
	//imshow("Reversed Image", Fig);
	imwrite(ad + "scheme2\\blue\\Reversed_Image.bmp", Fig);
	//cout << Fig << endl;



	//get Difference Image di
	Mat di1, di2, di;
	subtract(in, Fig, di1);
	subtract(Fig, in, di2);
	add(di1, di2, di);
	imwrite(ad + "scheme2\\blue\\Difference_Image.bmp", di);
	//imshow("Difference Image", di);

	//get Sign Matrix di2
	Mat_<Vec3b>::iterator it = di2.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = di2.end<Vec3b>();
	while (it != itend)
	{
		if ((*it)[0] > 0)
			(*it)[0] = 255;
		else
			(*it)[0] = 0;
		if ((*it)[1] > 0)
			(*it)[1] = 255;
		else
			(*it)[1] = 0;

		if ((*it)[2] > 0)
			(*it)[2] = 255;
		else
			(*it)[2] = 0;
		it++;
	}

	Mat signim = di2;
	imwrite(ad + "scheme2\\blue\\Sign_Image.bmp", di2);
	di2.convertTo(di2, CV_32FC3);
	Mat B(di2.rows, di2.cols, CV_32FC3, cv::Scalar::all(1.0 / 255.0));
	Mat A = di2.mul(B);
	imwrite(ad + "scheme2\\blue\\Sign_Matrix.bmp", A);
	//cout << A << endl;


	//----------------show image---------------------//
	//imshow("Input Image", in);
	//imshow("False Color Image", im_color);
	//imshow("Reversed Image", Fig);
	//imshow("Difference Image", di);
	//imshow("Sign Image", signim);



	


	////////////////////////////////////green_pink////////////////////////////////////////////////////////////////////////
	//-----------------------------------get false color Image -----------------------------------------------------
	//Mat mv[3];
	//split(in, mv);

	Mat bp_green_pink = imread(ad + "colormaps\\green_pink.bmp");
	cv::cvtColor(bp_green_pink, bp_green_pink, cv::COLOR_BGR2RGB);

	cv::Mat image_green_pink_3c;//Blue
	cv::cvtColor(mv[0], image_green_pink_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_blue_green_pink;
	cv::LUT(image_green_pink_3c, bp_green_pink, image_color_blue_green_pink);
	Mat b_green_pink[3];
	split(image_color_blue_green_pink, b_green_pink);
	//applyColorMap(mv[0], im_color_b, COLORMAP_RAINBOW);//b

	cv::Mat image_green_pink_green_3c;
	cv::cvtColor(mv[1], image_green_pink_green_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_green_green_pink;//Green
	cv::LUT(image_green_pink_green_3c, bp_green_pink, image_color_green_green_pink);
	Mat g_green_pink[3];
	split(image_color_green_green_pink, g_green_pink);
	//applyColorMap(mv[1], im_color_g, COLORMAP_RAINBOW);//g
	//imshow("im_color_g", im_color_g);

	cv::Mat image_red_green_pink_3c;//Red
	cv::cvtColor(mv[2], image_red_green_pink_3c, cv::COLOR_GRAY2RGB);
	cv::Mat image_color_red_green_pink;
	cv::LUT(image_red_green_pink_3c, bp_green_pink, image_color_red_green_pink);
	Mat r_green_pink[3];
	split(image_color_red_green_pink, r_green_pink);
	//applyColorMap(mv[2], im_color_r, COLORMAP_RAINBOW);//r
	//imshow("im_color_r", im_color_r);


	Mat im_color_green_pink;
	vector<Mat> src_green_pink;     //合并false color image
	src_green_pink.push_back(b_green_pink[0]);
	src_green_pink.push_back(g_green_pink[1]);
	src_green_pink.push_back(r_green_pink[2]);
	merge(src_green_pink, im_color_green_pink);
	//imshow("False Color Image", im_color);
	imwrite(ad + "scheme2\\green_pink\\False_Image(green_pink).bmp", im_color_green_pink);

	//----------------------------------get BGR Channels HistogramImage	------------------------------------------------------//
	/*
	//example hist(132),hist(144)
	Mat image3 = mv[0];  //读取B
	Histogram1D h3;
	imshow("channel blue", image3);
	imshow("histogram blue", h3.getHistogramImage(image3));
	cout << "hist(132)=" << h3.getSpecifyValue(mv[0], 132.0) << endl << "hist(144)=" << h3.getSpecifyValue(mv[0], 144.0) << endl;
	*/
//	Histogram1D h0;
//	Histogram1D h1;
//	Histogram1D h2;

//	Mat image0 = mv[0];  //读取B
//	Mat image1 = mv[1];  //读取G
//	Mat image2 = mv[2];  //读取R

						 /*
						 Mat image0 = mv[0];  //读取B
						 Histogram1D h0;
						 imshow("channel blue", image0);
						 imshow("histogram blue", h0.getHistogramImage(image0));
						 int sum0 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h0.getSpecifyValue(image0, i) << endl;
						 sum0 = sum0 + h0.getSpecifyValue(image0, i);
						 }
						 cout << endl << endl << sum0 << endl << endl;


						 Mat image1 = mv[1];  //读取G
						 Histogram1D h1;
						 imshow("channel green", image1);
						 imshow("histogram green", h1.getHistogramImage(image1));
						 int sum1 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h1.getSpecifyValue(image1, i) << endl;
						 sum1 = sum1 + h1.getSpecifyValue(image1, i);
						 }
						 cout << endl << endl << sum1 << endl << endl;


						 Mat image2 = mv[2];  //读取R
						 cout << image2.rows << image2.cols << image2.channels() << endl;
						 cout << mv[2].rows << mv[2].cols << mv[2].channels() << endl;
						 Histogram1D h2;
						 imshow("channel red", image2);
						 imshow("histogram red", h2.getHistogramImage(image2));
						 int sum2 = 0;
						 for (int i = 0; i < 256; i++)
						 {
						 cout << i << ":" << h2.getSpecifyValue(image2, i) << endl;
						 sum2 = sum2 + h2.getSpecifyValue(image2, i);
						 }
						 cout << endl << endl << sum2 << endl << endl;
						 */

						 //----------------------------------------jpeg compression----------------------------------------------------------------//
	vector<uchar> buff_green_pink;//buffer for coding
	vector<int> param_green_pink = vector <int>(2);
	param_green_pink[0] = CV_IMWRITE_JPEG_QUALITY;
	param_green_pink[1] = 95;//default(95)0-100
				  //jpeg encode and decode
	imencode(".jpg", im_color_green_pink, buff_green_pink, param_green_pink);
	cout << "****************************************************************************************" << endl;
	cout << "coded file size(jpg): " << buff_green_pink.size() << endl;
	Mat jpegimage_green_pink = imdecode(Mat(buff_green_pink), CV_LOAD_IMAGE_COLOR);
	imwrite(ad + "scheme2\\green_pink\\diencodeb.bmp", jpegimage_green_pink);

	cout << endl << endl;
	cout << "JPEG Encoded-Decoded False Image size: " << jpegimage_green_pink.dataend - jpegimage_green_pink.datastart << endl;
	cout << "height: " << jpegimage_green_pink.rows << endl << "width: " << jpegimage_green_pink.cols << endl << "depth: " << jpegimage_green_pink.channels() << endl;
	cout << "height*width*depth: " << jpegimage_green_pink.rows*jpegimage_green_pink.cols*jpegimage_green_pink.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;

	//--------------------------------Inverse False Coloring,get I'(step 8)---------------------------------------------------//

	////////////////////////////fi'////////////////////////////
	bp_green_pink.convertTo(bp_green_pink, CV_32F);
	//cout << bp << endl;
	int n1_green_pink = bp_green_pink.rows;
	int nc_green_pink = bp_green_pink.cols*bp_green_pink.channels();

	Mat Fig_green_pink = jpegimage_green_pink;
	//imshow("sys", Fig);
	Fig_green_pink.convertTo(Fig_green_pink, CV_32F);
	//Fig.convertTo(Fig, CV_8U);
	//imshow("sys1", Fig);
	int fn1_green_pink = Fig_green_pink.rows;
	int fnc_green_pink = Fig_green_pink.cols*Fig_green_pink.channels();
	if (Fig_green_pink.isContinuous())
	{
		fnc_green_pink = fn1_green_pink * fnc_green_pink;
		fn1_green_pink = 1;
	}
	float *f_green_pink;
	////////////////////////////b//////////////////////////////////////////////
	for (int j = 0; j < fn1_green_pink; j++)
	{
		f_green_pink = Fig_green_pink.ptr<float>(j);
		for (int i = 0; i < fnc_green_pink; i = i + 3)//changed for test
		{
			//cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1_green_pink = bp_green_pink.rows;
			int nc_green_pink = bp_green_pink.cols*bp_green_pink.channels();
			if (bp_green_pink.isContinuous())
			{
				nc_green_pink = n1_green_pink * nc_green_pink;
				n1_green_pink = 1;
			}
			float bmin_green_pink = 255;
			float bpmin_green_pink = 255;
			float *p_green_pink;
			for (int n = 0; n < n1_green_pink; n++)
			{
				p_green_pink = bp_green_pink.ptr<float>(j);
				for (int m = 0; m < nc_green_pink; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p_green_pink[m] - f_green_pink[i]) >= 0)//判断差值是否为正值
					{

						/*
						if (p[m] - f[i] == bmin)//如果存在多解，判断直方图
						{
						//cout << "m="<< m<<", bmin="<<bmin<<", bpmin="<<bpmin << endl;

						if (h0.getSpecifyValue(image0,m) >= h0.getSpecifyValue(image0, bpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						cout << m <<","<< h0.getSpecifyValue(image0, m)<<","<< h0.getSpecifyValue(image0, bpmin) endl;
						//bmin = p[m] - f[i];
						//bpmin = m;
						}
						}
						*/
						if ((p_green_pink[m] - f_green_pink[i]) < bmin_green_pink)//寻找最小差值
						{
							bmin_green_pink = p_green_pink[m] - f_green_pink[i];
							bpmin_green_pink = m;
						}

						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p_green_pink[m] - f_green_pink[i]) < 0)//判断差值是否为负值
					{
						if ((f_green_pink[i] - p_green_pink[m]) < bmin_green_pink)//取反,寻找最小差值
						{
							bmin_green_pink = p_green_pink[m] - f_green_pink[i];
							bpmin_green_pink = m;
						}
						/*
						else if (f[i] - p[m] == bmin)//如果存在多解，判断直方图
						{
						if (h0.getSpecifyValue(image0, m) >= h0.getSpecifyValue(image0, bpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						bmin = p[m] - f[i];
						bpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f_green_pink[i] = bpmin_green_pink;
			//cout<<f[i]<<":";//
			//cout <<":"<<bpmin << ")";//
		}
	}

	///////////////////////////////////////g////////////////////////////////////////////////////////////
	//cout << endl << endl;//
	for (int j = 0; j < fn1_green_pink; j++)
	{
		f_green_pink = Fig_green_pink.ptr<float>(j);
		for (int i = 1; i < fnc_green_pink; i = i + 3)//changed for test
		{
			//	cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1_green_pink = bp_green_pink.rows;
			int nc_green_pink = bp_green_pink.cols*bp_green_pink.channels();
			if (bp_green_pink.isContinuous())
			{
				nc_green_pink = n1_green_pink * nc_green_pink;
				n1_green_pink = 1;
			}
			float gmin_green_pink = 255;
			float gpmin_green_pink = 255;
			float *p_green_pink;
			for (int n = 0; n < n1_green_pink; n++)
			{
				p_green_pink = bp_green_pink.ptr<float>(j);
				for (int m = 1; m < nc_green_pink; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p_green_pink[m] - f_green_pink[i]) >= 0)//判断差值是否为正值
					{
						if ((p_green_pink[m] - f_green_pink[i]) < gmin_green_pink)//寻找最小差值
						{
							gmin_green_pink = p_green_pink[m] - f_green_pink[i];
							gpmin_green_pink = m;
						}
						/*
						else if (p[m] - f[i] == gmin)//如果存在多解，判断直方图
						{
						if (h1.getSpecifyValue(image1, m) >= h1.getSpecifyValue(image1, gpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						gmin = p[m] - f[i];
						gpmin = m;
						}
						}
						*/
						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p_green_pink[m] - f_green_pink[i]) < 0)//判断差值是否为负值
					{
						if ((f_green_pink[i] - p_green_pink[m]) < gmin_green_pink)//取反,寻找最小差值
						{
							gmin_green_pink = p_green_pink[m] - f_green_pink[i];
							gpmin_green_pink = m;
						}
						/*
						else if (f[i] - p[m] == gmin)//如果存在多解，判断直方图
						{
						if (h1.getSpecifyValue(image1, m) >= h1.getSpecifyValue(image1, gpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						gmin = p[m] - f[i];
						gpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f_green_pink[i] = gpmin_green_pink;
			//cout<<f[i]<<")";//
		}
	}

	////////////////////////////////////r////////////////////////////////////////////////////////////
	//cout << endl << endl;//
	for (int j = 0; j < fn1_green_pink; j++)
	{
		f_green_pink = Fig_green_pink.ptr<float>(j);
		for (int i = 2; i < fnc_green_pink; i = i + 3)//changed for test
		{
			//cout <<"("<< f[i] << ":";//
			//cout << "1" << i << endl;
			int n1_green_pink = bp_green_pink.rows;
			int nc_green_pink = bp_green_pink.cols*bp_green_pink.channels();
			if (bp_green_pink.isContinuous())
			{
				nc_green_pink = n1_green_pink * nc_green_pink;
				n1_green_pink = 1;
			}
			float rmin_green_pink = 255;
			float rpmin_green_pink = 255;
			float *p_green_pink;
			for (int n = 0; n < n1_green_pink; n++)
			{
				p_green_pink = bp_green_pink.ptr<float>(j);
				for (int m = 2; m < nc_green_pink; m = m + 3)//changed for test
				{
					//cout << p[m] << " ";

					if ((p_green_pink[m] - f_green_pink[i]) >= 0)//判断差值是否为正值
					{
						if ((p_green_pink[m] - f_green_pink[i]) < rmin_green_pink)//寻找最小差值
						{
							rmin_green_pink = p_green_pink[m] - f_green_pink[i];
							rpmin_green_pink = m;
						}
						/*
						else if (p[m] - f[i] == rmin)//如果存在多解，判断直方图
						{
						if (h2.getSpecifyValue(image2, m) >= h2.getSpecifyValue(image2, rpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						rmin = p[m] - f[i];
						rpmin = m;
						}
						}
						*/
						//cout <<"("<< "1:" << " " << p[m] - f[i] <<")"<<" ";
					}
					else if ((p_green_pink[m] - f_green_pink[i]) < 0)//判断差值是否为负值
					{
						if ((f_green_pink[i] - p_green_pink[m]) < rmin_green_pink)//取反,寻找最小差值
						{
							rmin_green_pink = p_green_pink[m] - f_green_pink[i];
							rpmin_green_pink = m;
						}
						/*
						else if (f[i] - p[m] == rmin)//如果存在多解，判断直方图
						{
						if (h2.getSpecifyValue(image2, m) >= h2.getSpecifyValue(image2, rpmin))//如果当前像素数大于原最小值时的像素数，则更新
						{
						rmin = p[m] - f[i];
						rpmin = m;
						}
						}
						*/
						//cout << "(" << "-1:" << " " << p[m] - f[i] << ")" << " ";
					}
					//cout << "2"<<m<<" ";
				}
			}
			f_green_pink[i] = rpmin_green_pink;
			//cout<<f[i]<<")";//
		}
	}

	Fig_green_pink.convertTo(Fig_green_pink, CV_8U);
	//imshow("Reversed Image", Fig);
	imwrite(ad + "scheme2\\green_pink\\Reversed_Image.bmp", Fig_green_pink);
	//cout << Fig << endl;



	//get Difference Image di
	Mat di1_green_pink, di2_green_pink, di_green_pink;
	subtract(in, Fig_green_pink, di1_green_pink);
	subtract(Fig_green_pink, in, di2_green_pink);
	add(di1_green_pink, di2_green_pink, di_green_pink);
	imwrite(ad + "scheme2\\green_pink\\Difference_Image.bmp", di_green_pink);
	//imshow("Difference Image", di);

	//get Sign Matrix di2
	Mat_<Vec3b>::iterator it_green_pink = di2_green_pink.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend_green_pink = di2_green_pink.end<Vec3b>();
	while (it_green_pink != itend_green_pink)
	{
		if ((*it_green_pink)[0] > 0)
			(*it_green_pink)[0] = 255;
		else
			(*it_green_pink)[0] = 0;
		if ((*it_green_pink)[1] > 0)
			(*it_green_pink)[1] = 255;
		else
			(*it_green_pink)[1] = 0;

		if ((*it_green_pink)[2] > 0)
			(*it_green_pink)[2] = 255;
		else
			(*it_green_pink)[2] = 0;
		it_green_pink++;
	}

	Mat signim_green_pink = di2_green_pink;
	imwrite(ad + "scheme2\\green_pink\\Sign_Image.bmp", di2_green_pink);
	di2_green_pink.convertTo(di2_green_pink, CV_32FC3);
	Mat B_green_pink(di2_green_pink.rows, di2_green_pink.cols, CV_32FC3, cv::Scalar::all(1.0 / 255.0));
	Mat A_green_pink = di2_green_pink.mul(B_green_pink);
	imwrite(ad + "scheme2\\green_pink\\Sign_Matrix.bmp", A_green_pink);
	//cout << A << endl;


	//----------------show image---------------------//
	//imshow("Input Image", in);
	//imshow("False Color Image", im_color);
	//imshow("Reversed Image", Fig);
	//imshow("Difference Image", di);
	//imshow("Sign Image", signim);



///////////////////////////////////////show//////////////////////////////////////////////////////
//---------------combine images------------------//
	vector<Mat> imgs(8);//设置需要显示的图片组
	imgs[0] = in;// imread(ad + "original image\\lena.bmp");
	imgs[1] = im_color;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\False_Color_Image.bmp");
	imgs[2] = di;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp");
	imgs[3] = signim;// (ad + "scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp");
	//调用组合图片函数，第二和第三个参数可以改变来获得不同效果，但两数相乘不能小于图片数量，否则不足以显示图片，程序会报错
	//imgs[4] = Fig;
	imgs[4] = in;// imread(ad + "original image\\lena.bmp");
	imgs[5] = im_color_green_pink;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\False_Color_Image.bmp");
	imgs[6] = di_green_pink;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp");
	imgs[7] = signim_green_pink;// (ad + "scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp");
					 //调用组合图片函数，第二和第三个参数可以改变来获得不同效果，但两数相乘不能小于图片数量，否则不足以显示图片，程序会报错
	//imgs[9] = Fig_green_pink;
	Mat m = combineImages(imgs, 4, 2, false);
	namedWindow("original image--False_Color_Image--Difference_Image--Sign Image--Reversed Image", 0);
	imshow("original image--False_Color_Image--Difference_Image--Sign Image--Reversed Image", m);
	//imwrite("D:/research/Test1/rawimage/0.jpg", m);

	
	/*
	vector<Mat> t2(4);
	t2[0] = in;
	t2[1] = Fig;
	t2[2] = in;
	t2[3] = Fig_green_pink;
	Mat m0 = combineImages(t2, 2, 2, false);
	namedWindow("original image--Reversed Image", 0);
	imshow("original image--Reversed Image", m0);
	//imwrite("D:/research/Test1/rawimage/0.jpg", m);
	*/

	waitKey(0);
    return 0;
}

Mat combineImages(vector<Mat> imgs,//@parameter1:需要显示的图像组 
	int col,//parameter2:显示的列数
	int row, //parameter3:显示的行数
	bool hasMargin) {//parameter4:是否设置边框
	int imgAmount = imgs.size();//获取需要显示的图像数量
	int width = imgs[0].cols;//本函数默认需要显示的图像大小相同
	int height = imgs[0].rows;//获取图像宽高
	int newWidth, newHeight;//新图像宽高
	if (!hasMargin) {
		newWidth = col * imgs[0].cols;//无边框，新图像宽/高=原图像宽/高*列/行数
		newHeight = row * imgs[0].rows;
	}
	else {
		newWidth = (col + 1) * 20 + col * width;//有边框，要将上边框的尺寸，这里设置边框为20px
		newHeight = (row + 1) * 20 + row * height;
	}

	Mat newImage(newHeight, newWidth, CV_8UC3, Scalar(255, 255, 255));//显示创建设定尺寸的新的大图像；色深八位三通道；填充为白色


	int x, y, imgCount;//x列号，y行号，imgCount图片序号
	if (hasMargin) {//有边框
		imgCount = 0;
		x = 0; y = 0;
		while (imgCount < imgAmount) {
			Mat imageROI = newImage(Rect(x*width + (x + 1) * 20, y*height + (y + 1) * 20, width, height));//创建感兴趣区域
			imgs[imgCount].copyTo(imageROI);//将图像复制到大图中
			imgCount++;
			if (x == (col - 1)) {
				x = 0;
				y++;
			}
			else {
				x++;
			}//移动行列号到下一个位置
		}
	}
	else {//无边框
		imgCount = 0;
		x = 0; y = 0;
		while (imgCount < imgAmount) {
			Mat imageROI = newImage(Rect(x*width, y*height, width, height));
			imgs[imgCount].copyTo(imageROI);
			imgCount++;
			if (x == (col - 1)) {
				x = 0;
				y++;
			}
			else {
				x++;
			}
		}
	}
	return newImage;//返回新的组合图像
};
