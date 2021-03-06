// recover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>// Image processing methods for the CPU
//#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

string ad = "C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\";

Scalar getMSSIM(const Mat& I1, const Mat& I2);

int main()
{
	//load data
	Mat di=imread(ad + "scheme2\\blue\\Difference_Image.bmp");
	if (!di.data) { cout << "Error loading Difference_Image.bmp" << endl; return -1; }
	Mat si=imread(ad + "scheme2\\blue\\Sign_Matrix.bmp");
	if (!si.data) { cout << "Error loading Sign_Matrix.bmp" << endl; return -1; }

	//由于I'(Reversed Image)在protect pipe和recover pipe 均用到，为简化程序，故直接采用protect pipe 所得出的结果；
	//Mat fii=imread("C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\blue\\diencodeb.bmp");//FI'
	//Mat bp = imread("C:\\Users\\zhuan\\Desktop\\image_cpp\\pro_false_color\\data\\blue\\blue1.bmp");//P,rgb
	//cv::cvtColor(bp, bp, cv::COLOR_BGR2RGB);//bgr
	Mat ii= imread(ad + "scheme2\\blue\\Reversed_Image.bmp");
	if (!ii.data) { cout << "Error loading Reversed_Image.bmp" << endl; return -1; }

	//get s
	Mat ss = si;
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

	//get R(Recovered Image),R=I'+sDI;
	Mat d, i;
	Mat sd(d.rows, d.cols, CV_32FC3);
	di.convertTo(d, CV_32F);
	sd = s.mul(d);
	ii.convertTo(i, CV_32F);
	Mat r(d.rows, d.cols, CV_32FC3);
	r = i + sd;

	//show Recovered Image
	r.convertTo(r, CV_32F, 1.0 / 255.0);
	imshow("Recovered Image", r);

	//save Recovered Image
	r.convertTo(r, CV_8U,255);
	imwrite(ad + "scheme2\\blue\\Recovered_Image.bmp",r);


	//SSIM
	Mat I1 = imread(ad + "original image\\05.jpg");          // Read the two images
	Mat I2 = imread(ad + "scheme1\\blue\\Recovered_Image(blue).bmp");
	if (!I1.data || !I2.data)           // Check for success
	{
		cout << "Couldn't read the image";
		return -1;
	}
	Scalar x0 = getMSSIM(I1, I2);
	cout << "SSIM\t" << "R:" << x0.val[2] << "\tG:" << x0.val[1] << "\tB:" << x0.val[0] << "\tAVG:" << (x0.val[0] + x0.val[1] + x0.val[2]) / 3 << endl;


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