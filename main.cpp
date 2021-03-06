/*
* zqf 
* 2018-04-08
*
*/

#include "stdafx.h"
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"

using namespace std;
using namespace cv;

string ad = "C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\";

Mat combineImages(vector<Mat> imgs, int col, int row, bool hasMargin);//函数声明

int main()
{
	Mat src, srcOfMerge;
	Mat mv[3];
	Mat im_color;

//------------------------------------------------------------------------//
//----------------------------------------------------------------------- //
	src = imread(ad+"original image\\lena.bmp");
	//src = imread(ad + "original image\\me.jpg");
	//src = imread(ad + "original image\\05.jpg");
//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//


	if (!src.data) { cout << "Error loading lena.bmp" << endl; return -1; }
	cout << "****************************************************************************************" << endl;
	cout << "Input Image size: " << src.dataend - src.datastart << endl;
	cout << "height: " << src.rows << endl << "width: " << src.cols << endl << "depth: " << src.channels() << endl;
	cout << "height*width*depth: " << src.rows*src.cols*src.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;
	split(src, mv);
	srcOfMerge = 0.0722*mv[0] + 0.7152*mv[1] + 0.216*mv[2];
	//cout << mv[2] << " ";
	//imshow("srcOfMerge", srcOfMerge);
	//imshow("origin image", src);
	//imshow("b", mv[0]);
	//imshow("g", mv[1]);
	//imshow("g", mv[2]);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------opencv 自带的colormaps------------------------------------------------------
	applyColorMap(srcOfMerge, im_color, COLORMAP_RAINBOW);//false color
	imwrite(ad+"scheme1\\COLORMAP_RAINBOW\\False_Color_Image.bmp",im_color);
	
	//jpeg compression(COLORMAP_JET)
	vector<uchar> buff;//buffer for coding
	vector<int> param = vector <int>(2);
	param[0] = CV_IMWRITE_JPEG_QUALITY;
	param[1] = 95;//default(95)0-100
	//jpeg encode and decode
	imencode(".jpg", im_color, buff, param);
	cout << "****************************************************************************************" << endl;
	cout << "coded file size(jpg): " << buff.size() << endl;
	Mat jpegimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
	imwrite(ad+"scheme1\\COLORMAP_RAINBOW\\JPEG_Encoded-Decoded_False_Image.bmp", jpegimage);
	cout << endl << endl;
	cout << "JPEG Encoded-Decoded False Image size: " << jpegimage.dataend - jpegimage.datastart << endl;
	cout << "height: " << jpegimage.rows << endl << "width: " << jpegimage.cols << endl << "depth: " << jpegimage.channels() << endl;
	cout << "height*width*depth: " << jpegimage.rows*jpegimage.cols*jpegimage.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;
	//get Difference Image di
	Mat di1, di2, di;
	subtract(src, jpegimage, di1);
	subtract(jpegimage, src, di2);
	add(di1, di2, di);
	imwrite(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp", di);
	imwrite(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.jpg", di);
	//cout << di << endl;

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
	imwrite(ad+"scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp",di2);
	Mat di2_rainbow = di2;
	di2.convertTo(di2, CV_32FC3);
	Mat B(di2.rows, di2.cols, CV_32FC3, cv::Scalar::all(1.0 / 255.0));
	Mat A=di2.mul(B);
	imwrite(ad + "scheme1\\COLORMAP_RAINBOW\\Save.bmp", A);
	//cout << di2 << endl;

//---------------------------Show Specify Image-------------------------------------------------//
	
    //imshow("Input image", src);//show Input image
	//imshow("False Image(COLORMAP_JET)", im_color);//show False Image
	//imshow("JPEG Encoded-Decoded False Image", jpegimage);//show JPEG Encoded-Decoded False Image
	//imshow("Difference Image", di);//show Difference Image
	//imshow("Sign Image", di2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------自定义Color Palette(blues)-------------------------------------------------------------------------
	cv::Mat im_color_blue, blue, srcOfMerge_3c;
	cv::cvtColor(srcOfMerge, srcOfMerge_3c, cv::COLOR_GRAY2RGB);
	blue = imread(ad + "colormaps\\blue.bmp");
	//blue = imread(ad + "colormaps\\green_pink.bmp");

	if (!blue.data) { cout << "Error load the blue colormap" << endl; return -1; }
	//cout << blue << endl;
	cv::cvtColor(blue, blue, cv::COLOR_BGR2RGB);
	//cout << blue << endl;
	cv::LUT(srcOfMerge_3c, blue, im_color_blue);
//  imwrite("C:\\Users\\zhuan\\Desktop\\image_cpp\\data\\blue\\Color Palette(blue).bmp", blue);
	imwrite(ad + "scheme1\\blue\\False_Color_Image(blue).bmp", im_color_blue);
	//imwrite(ad + "scheme1\\green_pink\\False_Color_Image(green_pink).bmp", im_color_blue);

	//jpeg compression(blue)
	vector<uchar> buff_blue;//buffer for coding
	vector<int> param_blue = vector <int>(2);
	param_blue[0] = CV_IMWRITE_JPEG_QUALITY;
	param_blue[1] = 95;//default(95)0-100
					   //jpeg encode and decode
	imencode(".jpg", im_color_blue, buff_blue, param_blue);
	cout << "****************************************************************************************" << endl;
	cout << "coded file size(jpg)(blue): " << buff_blue.size() << endl;
	Mat jpegimage_blue = imdecode(Mat(buff_blue), CV_LOAD_IMAGE_COLOR);
	imwrite(ad + "scheme1\\blue\\JPEG_Encoded-Decoded_False_Image(blue).bmp", jpegimage_blue);
//	imwrite(ad + "scheme1\\green_pink\\JPEG_Encoded-Decoded_False_Image(green_pink).bmp", jpegimage_blue);
	
	cout << endl << endl;
	cout << "JPEG Encoded-Decoded False Image size(blue): " << jpegimage_blue.dataend - jpegimage_blue.datastart << endl;
	cout << "height: " << jpegimage_blue.rows << endl << "width: " << jpegimage_blue.cols << endl << "depth: " << jpegimage_blue.channels() << endl;
	cout << "height*width*depth: " << jpegimage_blue.rows*jpegimage_blue.cols*jpegimage_blue.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;
	//get Difference Image di（blue)
	Mat di1_blue, di2_blue, di_blue;
	subtract(src, jpegimage_blue, di1_blue);
	subtract(jpegimage_blue, src, di2_blue);
	add(di1_blue, di2_blue, di_blue);
	imwrite(ad + "scheme1\\blue\\Difference_Image(blue).bmp", di_blue);
//	imwrite(ad + "scheme1\\green_pink\\Difference_Image(green_pink).bmp", di_blue);

	//cout << di << endl;

	//get Sign Matrix di2（blue)
	Mat_<Vec3b>::iterator it_blue = di2_blue.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend_blue = di2_blue.end<Vec3b>();
	while (it_blue != itend_blue)
	{
		if ((*it_blue)[0] > 0)
			(*it_blue)[0] = 255;
		else
			(*it_blue)[0] = 0;
		if ((*it_blue)[1] > 0)
			(*it_blue)[1] = 255;
		else
			(*it_blue)[1] = 0;

		if ((*it_blue)[2] > 0)
			(*it_blue)[2] = 255;
		else
			(*it_blue)[2] = 0;
		it_blue++;
	}
	imwrite(ad + "scheme1\\blue\\Sign_Matrix(blue).bmp", di2_blue);
	Mat signblue = di2_blue;
//	imwrite(ad + "scheme1\\green_pink\\Sign_Matrix(green_pink).bmp", di2_blue);

	di2_blue.convertTo(di2_blue, CV_32FC3);
	Mat B_blue(di2_blue.rows, di2_blue.cols, CV_32FC3, cv::Scalar::all(1.0 / 255.0));
	Mat A_blue = di2_blue.mul(B_blue);
	imwrite(ad + "scheme1\\blue\\Save(blue).bmp", A_blue);
//	imwrite(ad + "scheme1\\green_pink\\Save(green_pink).bmp", A_blue);


//---------------------------Show Specify Image-------------------------------------------------//
	
	//imshow("Input image", src);//show Input image
	//imshow("False Color Image(blue)", im_color_blue);
	//imshow("JPEG Encoded-Decoded False Image(blue)", jpegimage_blue);//show JPEG Encoded-Decoded False Image
	//imshow("Difference Image(blue)", di_blue);
	//imshow("Sign Image", di2_blue);




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------自定义Color Palette(green-pink)-------------------------------------------------------------------------
	cv::Mat im_color_green, green, srcOfMerge_3c_green;
	cv::cvtColor(srcOfMerge, srcOfMerge_3c_green, cv::COLOR_GRAY2RGB);
	//	blue = imread(ad + "colormaps\\blue.bmp");
	green = imread(ad + "colormaps\\green_pink.bmp");

	if (!green.data) { cout << "Error load the blue colormap" << endl; return -1; }
	//cout << blue << endl;
	cv::cvtColor(green, green, cv::COLOR_BGR2RGB);
	//cout << blue << endl;
	cv::LUT(srcOfMerge_3c_green,green, im_color_green);
	//imwrite("C:\\Users\\zhuan\\Desktop\\image_cpp\\data\\blue\\Color Palette(blue).bmp", blue);
	//	imwrite(ad + "scheme1\\blue\\False_Color_Image(blue).bmp", im_color_blue);
	imwrite(ad + "scheme1\\green_pink\\False_Color_Image(green_pink).bmp", im_color_green);

	//jpeg compression(green)
	vector<uchar> buff_green;//buffer for coding
	vector<int> param_green = vector <int>(2);
	param_green[0] = CV_IMWRITE_JPEG_QUALITY;
	param_green[1] = 95;//default(95)0-100
					   //jpeg encode and decode
	imencode(".jpg", im_color_green, buff_green, param_green);
	cout << "****************************************************************************************" << endl;
	cout << "coded file size(jpg)(green): " << buff_green.size() << endl;
	Mat jpegimage_green = imdecode(Mat(buff_green), CV_LOAD_IMAGE_COLOR);
	//	imwrite(ad + "scheme1\\blue\\JPEG_Encoded-Decoded_False_Image(blue).bmp", jpegimage_blue);
	imwrite(ad + "scheme1\\green_pink\\JPEG_Encoded-Decoded_False_Image(green_pink).bmp", jpegimage_green);

	cout << endl << endl;
	cout << "JPEG Encoded-Decoded False Image size(green): " << jpegimage_green.dataend - jpegimage_green.datastart << endl;
	cout << "height: " << jpegimage_green.rows << endl << "width: " << jpegimage_green.cols << endl << "depth: " << jpegimage_green.channels() << endl;
	cout << "height*width*depth: " << jpegimage_green.rows*jpegimage_green.cols*jpegimage_green.channels() << endl << endl;
	cout << "****************************************************************************************" << endl;
	//get Difference Image di（green)
	Mat di1_green, di2_green, di_green;
	subtract(src, jpegimage_green, di1_green);
	subtract(jpegimage_green, src, di2_green);
	add(di1_green, di2_green, di_green);
	//	imwrite(ad + "scheme1\\blue\\Difference_Image(blue).bmp", di_blue);
	imwrite(ad + "scheme1\\green_pink\\Difference_Image(green_pink).bmp", di_green);

	//cout << di << endl;

	//get Sign Matrix di2（green)
	Mat_<Vec3b>::iterator it_green = di2_green.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend_green = di2_green.end<Vec3b>();
	while (it_green != itend_green)
	{
		if ((*it_green)[0] > 0)
			(*it_green)[0] = 255;
		else
			(*it_green)[0] = 0;
		if ((*it_green)[1] > 0)
			(*it_green)[1] = 255;
		else
			(*it_green)[1] = 0;

		if ((*it_green)[2] > 0)
			(*it_green)[2] = 255;
		else
			(*it_green)[2] = 0;
		it_green++;
	}
	//	imwrite(ad + "scheme1\\blue\\Sign_Matrix(blue).bmp", di2_blue);
	imwrite(ad + "scheme1\\green_pink\\Sign_Matrix(green_pink).bmp", di2_green);
	Mat signgreen = di2_green;
	di2_green.convertTo(di2_green, CV_32FC3);
	Mat B_green(di2_green.rows, di2_green.cols, CV_32FC3, cv::Scalar::all(1.0 / 255.0));
	Mat A_green = di2_green.mul(B_green);
	//	imwrite(ad + "scheme1\\blue\\Save(blue).bmp", A_blue);
	imwrite(ad + "scheme1\\green_pink\\Save(green_pink).bmp", A_green);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//combine images
	vector<Mat> imgs(12);//设置需要显示的图片组
	imgs[0] = src;//imread(ad + "original image\\lena.bmp");
	imgs[1] = im_color;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\False_Color_Image.bmp");
	imgs[2] = di;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp");
	imgs[3] = di2_rainbow;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp");
	
	imgs[4] = src;// imread(ad + "original image\\lena.bmp");
	imgs[5] = im_color_blue;// imread(ad + "scheme1\\blue\\False_Color_Image(blue).bmp");
	imgs[6] = di_blue;// imread(ad + "scheme1\\blue\\Difference_Image(blue).bmp");
	imgs[7] = signblue;// imread(ad + "scheme1\\blue\\Sign_Matrix(blue).bmp");

	imgs[8] = src;// imread(ad + "original image\\lena.bmp");
	imgs[9] = im_color_green;//imread(ad + "scheme1\\green_pink\\False_Color_Image(green_pink).bmp");
	imgs[10] = di_green;// imread(ad + "scheme1\\green_pink\\Difference_Image(green_pink).bmp");
	imgs[11] = signgreen;// imread(ad + "scheme1\\green_pink\\Sign_Matrix(green_pink).bmp");

	//调用组合图片函数，第二和第三个参数可以改变来获得不同效果，但两数相乘不能小于图片数量，否则不足以显示图片，程序会报错
	Mat m = combineImages(imgs, 4, 3, false);
	namedWindow("original image--False_Color_Image--Difference_Image--Sign Image",0);
	imshow("original image--False_Color_Image--Difference_Image--Sign Image", m);
	//imwrite("D:/research/Test1/rawimage/0.jpg", m);
	
	waitKey(0);
	return 0;
}//main end


/*
//output difference Image txt
ofstream File6("D://data//DI.txt", ios::out | ios::binary);
for (unsigned int nrow = 0; nrow<di.rows; nrow++)
{
for (unsigned int ncol = 0; ncol<di.cols; ncol++)
{
Vec3i bgr = di.at<Vec3b>(nrow, ncol);
File6 << "(" << bgr.val[0] << "," << bgr.val[1] << "," << bgr.val[2] << ")";

}
File6 << endl << endl;

}
File6.close();
cout << "false_image: " << endl << "   rows: " << im_color.rows << endl << "   cols: " << im_color.cols << endl << endl;
*/



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
