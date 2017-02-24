//
//  main.cpp
//  FbyCharacterNormalization

//
//  Created by Boyuan Feng on 13-1-24.

//  Copyright (c) 2013年 Boyuan Feng. All rights reserved.

//
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <fstream>
using namespace std;
using namespace cv;
void colorReduce(Mat& inputImage, Mat& outputImage, int div);
int main()
{
    Mat image = imread("/Users/xiaopeng/Desktop/1.png");
    imshow("源图像",image);
    Mat result;//用来保存结果
    result.create(image.rows,image.cols,image.type());//它的大小、类型与原图片相匹配
    double duration;
    duration = static_cast<double>(cv::getTickCount());
    
    colorReduce(image,result,64);
    
    duration = static_cast<double>(cv::getTickCount())-duration;
    duration /= cv::getTickFrequency(); // the elapsed time in m
    cout<<"time is"<<duration<<endl;
    
    imshow("显示结果",result);
    waitKey(0);
}