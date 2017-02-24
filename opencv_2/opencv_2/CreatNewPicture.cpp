//
//  CreatNewPicture.cpp
//  opencv_2
//
//  Created by XiaoPeng on 17/2/24.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#include "CreatNewPicture.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>

#include "Header.h"
using namespace cv;
CascadeClassifier face_cascade;

using namespace std;

int test1()
{
    Mat img = imread("/Users/xiaopeng/Desktop/2.png");
    imshow("Lena Original", img);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            //主要是这里的代码
            if(*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) > 128)
            {
                //[row, col]像素的第 1 通道地址被 * 解析(blue通道)
                *(img.data + img.step[0] * row + img.step[1] * col) = 255;
                //[row, col]像素的第 2 通道地址被 * 解析(green通道), 关于elemSize1函数的更多描述请见 Fn1 里所列的博文链接
                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) = 255;
                //[row, col]像素的第 3 通道地址被 * 解析(red通道)
                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) = 255;
            }
        }
    }
    imshow("Lena Modified", img);
    cvWaitKey();
    return 0;
}

int test2()
{
    Mat img = imread("/Users/xiaopeng/Desktop/3_c.png");
    Mat img2 = imread("/Users/xiaopeng/Desktop/5_c.png");
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            //主要是这里的代码
            if(*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) > 128)
            {
                //[row, col]像素的第 1 通道地址被 * 解析(blue通道)
                *(img.data + img.step[0] * row + img.step[1] * col) = (*(img.data + img.step[0] * row + img.step[1] * col) + *(img2.data + img2.step[0] * row + img2.step[1] * col))/2;
                //[row, col]像素的第 2 通道地址被 * 解析(green通道), 关于elemSize1函数的更多描述请见 Fn1 里所列的博文链接
                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) = (*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) + *(img2.data + img2.step[0] * row + img2.step[1] * col + img2.elemSize1()))/2;
                //[row, col]像素的第 3 通道地址被 * 解析(red通道)
                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) = (*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) + *(img2.data + img2.step[0] * row + img2.step[1] * col + img2.elemSize1()))/2;
            }
        }
    }
    imshow("Lena Modified", img);
    cvWaitKey();
    return 0;
}

void detectAndCut( string path ,string dir, string filename)
{
    cout<<"1";
    Mat img = imread(path);
    imshow("d",img);
    
    std::vector<Rect> faces;
    Mat img_gray;
    
    cvtColor( img, img_gray, COLOR_BGR2GRAY );
    equalizeHist( img_gray, img_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( img_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point rec( faces[i].x, faces[i].y );
        Point rec2( faces[i].x + faces[i].width, faces[i].y + faces[i].height );
        Mat roi_img = img( Range(faces[i].y,faces[i].y + faces[i].height), Range(faces[i].x,faces[i].x + faces[i].width) );
        imwrite( dir+"/"+filename, roi_img );
        cout<<"3";
        imshow("roi_img", roi_img);
    }
    cvWaitKey();
}

int test3()
{
    //    if( !face_cascade.load( "/Users/xiaopeng/Downloads/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml") ){ printf("--(!)Error loading\n"); return -1; };
    //    cout<<"cut……OK！"<<endl;
    //    detectAndCut("/Users/xiaopeng/Downloads/att_faces/s1/1.jpg", "/Users/xiaopeng/Desktop/", "1_c.png");
    //    test2();
    return comparetest(0,0);
    return 0;
}
