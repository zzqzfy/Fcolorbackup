// testrecover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>// Image processing methods for the CPU

using namespace std;
using namespace cv;

string ad = "C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\";
Mat combineImages(vector<Mat> imgs, int col, int row, bool hasMargin);//函数声明
Scalar getMSSIM(const Mat& I1, const Mat& I2);

int main()
{

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
	//Mat I1 = imread(ad + "original image\\me.jpg");
	//Mat I1 = imread(ad + "original image\\lena.bmp");
	Mat I1 = imread(ad + "original image\\05.jpg");
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//


//load FI',DI,SI data
	Mat di = imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.jpg");//load DI(Difference_Image) data
	if (!di.data) { cout << "Error loading Difference_Image.bmp" << endl; return -1; }
	Mat si = imread(ad + "scheme1\\COLORMAP_RAINBOW\\Save.bmp");//load SI data
	if (!si.data) { cout << "Error loading Sign Matrix" << endl; return -1; }
	Mat fi = imread(ad + "scheme1\\COLORMAP_RAINBOW\\JPEG_Encoded-Decoded_False_Image.bmp");//load FI'(JPEG_Encoded-Decoded_False_Image)data
	if (!fi.data) { cout << "Error loading JPEG_Encoded-Decoded_False_Image.bmp" << endl; return -1; }

//get s
	Mat ss(si);
	Mat_<Vec3b>::iterator it = ss.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = ss.end<Vec3b>();
	while (it != itend)
	{
		if ((*it)[0] == 0)
			(*it)[0] = 3;

		if ((*it)[1] == 0)
			(*it)[1] = 3;

		if ((*it)[2] == 0)
			(*it)[2] = 3;

		it++;
	}
	ss.convertTo(ss, CV_32FC3);
	Mat m(ss.rows, ss.cols, CV_32FC3, cv::Scalar::all(2.0));
	Mat s(ss.rows, ss.cols, CV_32FC3);
	s = ss - m;
	//cout << s << endl;

//get R(Recovered Image),R=FI'+s*DI
	Mat d,f;
	Mat sd(d.rows, d.cols, CV_32FC3);
	di.convertTo(d, CV_32F);
	sd = s.mul(d);
	fi.convertTo(f, CV_32F);
	Mat r(d.rows, d.cols, CV_32FC3);
	r = f + sd;
	
//show Recovered Image
	r.convertTo(r, CV_32F, 1.0 / 255.0);
	//imshow("Recovered Image", r);
	//Mat signr1 = r;

//save Recovered Image
	//r.convertTo(r, CV_32F, 1);
	r.convertTo(r, CV_8U,255);
	imwrite(ad + "scheme1\\COLORMAP_RAINBOW\\Recovered_Image.bmp",r);
	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//blue color palette


	//load FI',DI,SI data
	Mat di_blue = imread(ad + "scheme1\\blue\\Difference_Image(blue).bmp");//load DI(Difference_Image) data
	if (!di_blue.data) { cout << "Error loading Difference_Image(blue).bmp" << endl; return -1; }
	Mat si_blue = imread(ad + "scheme1\\blue\\Save(blue).bmp");//load SI data
	if (!si_blue.data) { cout << "Error loading Sign Matrix" << endl; return -1; }
	Mat fi_blue = imread(ad + "scheme1\\blue\\JPEG_Encoded-Decoded_False_Image(blue).bmp");//load FI'(JPEG_Encoded-Decoded_False_Image)data
	if (!fi_blue.data) { cout << "Error loading JPEG_Encoded-Decoded_False_Image(blue).bmp" << endl; return -1; }

	//get s
	Mat ss_blue(si_blue);
	Mat_<Vec3b>::iterator it_blue = ss_blue.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend_blue = ss_blue.end<Vec3b>();
	while (it_blue != itend_blue)
	{
		if ((*it_blue)[0] == 0)
			(*it_blue)[0] = 3;

		if ((*it_blue)[1] == 0)
			(*it_blue)[1] = 3;

		if ((*it_blue)[2] == 0)
			(*it_blue)[2] = 3;

		it_blue++;
	}
	ss_blue.convertTo(ss_blue, CV_32FC3);
	Mat m_blue(ss_blue.rows, ss_blue.cols, CV_32FC3, cv::Scalar::all(2.0));
	Mat s_blue(ss_blue.rows, ss_blue.cols, CV_32FC3);
	s_blue = ss_blue - m_blue;
	//cout << s_blue << endl;

	//get R(Recovered Image),R=FI'+s*DI
	Mat d_blue, f_blue;
	Mat sd_blue(d_blue.rows, d_blue.cols, CV_32FC3);
	di_blue.convertTo(d_blue, CV_32F);
	sd_blue = s_blue.mul(d_blue);
	fi_blue.convertTo(f_blue, CV_32F);
	Mat r_blue(d_blue.rows, d_blue.cols, CV_32FC3);
	r_blue = f_blue + sd_blue;

	//show Recovered Image
	r_blue.convertTo(r_blue, CV_32F, 1.0 / 255.0);
	//namedWindow("Recovered Image(blue)", 0);
	//imshow("Recovered Image(blue)", r_blue);
	//Mat signr2 = r_blue;

	//save Recovered Image
	//r_blue.convertTo(r_blue, CV_32F, 1);
	r_blue.convertTo(r_blue, CV_8U,255);
	imwrite(ad + "scheme1\\blue\\Recovered_Image(blue).bmp",r_blue);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//green_pink color palette


	//load FI',DI,SI data
	Mat di_green_pink = imread(ad + "scheme1\\green_pink\\Difference_Image(green_pink).bmp");//load DI(Difference_Image) data
	if (!di_green_pink.data) { cout << "Error loading Difference_Image(green_pink).bmp" << endl; return -1; }
	Mat si_green_pink = imread(ad + "scheme1\\green_pink\\Save(green_pink).bmp");//load SI data
	if (!si_green_pink.data) { cout << "Error loading Sign Matrix" << endl; return -1; }
	Mat fi_green_pink = imread(ad + "scheme1\\green_pink\\JPEG_Encoded-Decoded_False_Image(green_pink).bmp");//load FI'(JPEG_Encoded-Decoded_False_Image)data
	if (!fi_green_pink.data) { cout << "Error loading JPEG_Encoded-Decoded_False_Image(green_pink).bmp" << endl; return -1; }

	//get s
	Mat ss_green_pink(si_green_pink);
	Mat_<Vec3b>::iterator it_green_pink = ss_green_pink.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend_green_pink = ss_green_pink.end<Vec3b>();
	while (it_green_pink != itend_green_pink)
	{
		if ((*it_green_pink)[0] == 0)
			(*it_green_pink)[0] = 3;

		if ((*it_green_pink)[1] == 0)
			(*it_green_pink)[1] = 3;

		if ((*it_green_pink)[2] == 0)
			(*it_green_pink)[2] = 3;

		it_green_pink++;
	}
	ss_green_pink.convertTo(ss_green_pink, CV_32FC3);
	Mat m_green_pink(ss_green_pink.rows, ss_green_pink.cols, CV_32FC3, cv::Scalar::all(2.0));
	Mat s_green_pink(ss_green_pink.rows, ss_green_pink.cols, CV_32FC3);
	s_green_pink = ss_green_pink - m_green_pink;
	//cout << s_blue << endl;

	//get R(Recovered Image),R=FI'+s*DI
	Mat d_green_pink, f_green_pink;
	Mat sd_green_pink(d_green_pink.rows, d_green_pink.cols, CV_32FC3);
	di_green_pink.convertTo(d_green_pink, CV_32F);
	sd_green_pink = s_green_pink.mul(d_green_pink);
	fi_green_pink.convertTo(f_green_pink, CV_32F);
	Mat r_green_pink(d_green_pink.rows, d_green_pink.cols, CV_32FC3);
	r_green_pink = f_green_pink + sd_green_pink;

	//show Recovered Image
	r_green_pink.convertTo(r_green_pink, CV_32F, 1.0 / 255.0);
	//namedWindow("Recovered Image(blue)", 0);
	//imshow("Recovered Image(blue)", r_blue);
	//Mat signr2 = r_blue;

	//save Recovered Image
	//r_blue.convertTo(r_blue, CV_32F, 1);
	r_green_pink.convertTo(r_green_pink, CV_8U, 255);
	imwrite(ad + "scheme1\\green_pink\\Recovered_Image(green_pink).bmp", r_green_pink);





//******************************************************************************************************
//******************************************************************************************************
//SSIM
//	Mat I1 = imread(ad + "original image\\lena.bmp");          // Read the two images
//	Mat I1 = imread(ad + "original image\\me.jpg");
	Mat I2 = r;// imread(ad + "scheme1\\blue\\Recovered_Image(blue).bmp");
	Mat I3 = r_blue;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Recovered_Image.bmp");
	Mat I4 = r_green_pink;// imread(ad + ad + "scheme1\\green_pink\\Recovered_Image(green_pink).bmp");
	if (!I1.data || !I2.data ||!I3.data |!I4.data)        // Check for success
	{
		cout << "Couldn't read the image";
		return -1;
	}

	Scalar x2 = getMSSIM(I1, I2);
	Scalar x1 = getMSSIM(I1, I3);
	Scalar x3 = getMSSIM(I1, I4);
	cout << "****************************************************************************************" << endl;
	
	cout << "SSIM       \t" << "R:" << x1.val[2] << "\tG:" << x1.val[1] << "\tB:" << x1.val[0] << "\tAVG:" << (x1.val[0] + x1.val[1] + x1.val[2]) / 3 << endl;
	
	cout << "****************************************************************************************" << endl;

	cout << "SSIM（blue)\t" << "R:" << x2.val[2] << "\tG:" << x2.val[1] << "\tB:" << x2.val[0] << "\tAVG:" << (x2.val[0] + x2.val[1] + x2.val[2]) / 3 << endl;

	cout << "****************************************************************************************" << endl;

	cout << "SSIM（green_pink)\t" << "R:" << x3.val[2] << "\tG:" << x3.val[1] << "\tB:" << x3.val[0] << "\tAVG:" << (x3.val[0] + x3.val[1] + x3.val[2]) / 3 << endl;

	cout << "****************************************************************************************" << endl;

	//combine images
	vector<Mat> imgs(6);//设置需要显示的图片组
	imgs[0] = I1;// imread(ad + "original image\\lena.bmp");
	imgs[1] = r;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\False_Color_Image.bmp");
	imgs[2] = I1;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp");
	imgs[3] = r_blue;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp");
	imgs[4] = I1;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Difference_Image.bmp");
	imgs[5] = r_green_pink;// imread(ad + "scheme1\\COLORMAP_RAINBOW\\Sign_Matrix.bmp");
	//调用组合图片函数，第二和第三个参数可以改变来获得不同效果，但两数相乘不能小于图片数量，否则不足以显示图片，程序会报错
	Mat ms = combineImages(imgs, 2, 3, false);
	namedWindow("original image--Reversed Image", 0);
	imshow("original image--Reversed Image", ms);
	//imwrite("D:/research/Test1/rawimage/0.jpg", m);


	waitKey(0);
    return 0;
}

Scalar getMSSIM(const Mat& i1, const Mat& i2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	/***************************** INITS **********************************/
	int d = CV_32F;

	Mat I1, I2;
	i1.convertTo(I1, d);           // cannot calculate on one byte large values
	i2.convertTo(I2, d);

	Mat I2_2 = I2.mul(I2);        // I2^2
	Mat I1_2 = I1.mul(I1);        // I1^2
	Mat I1_I2 = I1.mul(I2);        // I1 * I2

								   /*************************** END INITS **********************************/

	Mat mu1, mu2;   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);

	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);

	Mat sigma1_2, sigma2_2, sigma12;

	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;

	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;

	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	///////////////////////////////// FORMULA ////////////////////////////////
	Mat t1, t2, t3;

	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

	Mat ssim_map;
	divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

	Scalar mssim = mean(ssim_map); // mssim = average of ssim map
	return mssim;
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
