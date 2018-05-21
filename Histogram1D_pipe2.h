#pragma once
#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Histogram1D {
private:
	int histSize[1];       //�������
	float hranges[2];   //���ص���С�����ֵ
	const float* ranges[1];
	int channels[1];    //���õ�һ��ͨ��
public:
	Histogram1D() {
		//׼��1Dֱ��ͼ�Ĳ���
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;  //Ĭ����������ǿ���0��ͨ��
	}

	//����1Dֱ��ͼ
	MatND getHistogram(const Mat&image)
	{
		MatND  hist;
		//����ֱ��ͼ
		calcHist(&image,
			1,                     //���㵥��ͼ���ֱ��ͼ
			channels,        //ͨ��������
			Mat(),              //��ʹ��ͼ����Ϊ����
			hist,                //���ص�ֱ��ͼ
			1,                    //����1D��ֱ��ͼ
			histSize,         //�������
			ranges            //����ֵ�ķ�Χ
		);
		return hist;
	}

	//����1Dֱ��ͼ��������һ��ͼ��
	Mat getHistogramImage(const Mat &image)
	{
		//���ȼ���ֱ��ͼ
		MatND hist = getHistogram(image);
		//��ȡ���ֵ����Сֵ
		double maxVal = 0;
		double minVal = 0;
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		//��ʾֱ��ͼ��ͼ��
		Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
		//������ߵ�Ϊnbins��90%
		int hpt = static_cast<int>(0.9*histSize[0]);
		//ÿ����Ŀ������һ����ֱ��
		for (int h = 0; h<histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			//����֮�����һ����
			line(histImg, Point(h, histSize[0]),
				Point(h, histSize[0] - intensity),
				Scalar::all(0));
		}
		return histImg;
	}
	
	//�����������ֵ�����ؾ�������ֵ
	int getSpecifyValue(const Mat &im,float y)
	{
		MatND hist = getHistogram(im);
		return hist.at<float>(y);
	}
};
#endif // HISTOGRAM1D_H