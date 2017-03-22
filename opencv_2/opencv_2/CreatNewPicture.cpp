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
#include <fstream>
#include "Header.h"

CascadeClassifier face_cascade;
String test_PATH = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_result/";
String test_New = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_new/";
using namespace std;
using namespace cv;

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
    face_cascade.detectMultiScale( img_gray, faces, 1.3, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    
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

Mat detectandgive( string path)
{
//    cout<<path<<endl;
    Mat img = imread(path);
//    imshow("d",img);
    std::vector<Rect> faces;
    Mat img_gray;
    cvtColor( img, img_gray, COLOR_BGR2GRAY );
    equalizeHist( img_gray, img_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( img_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    
//    imshow("test", img_gray)
    Mat roi_img;
    for( size_t i = 0; i < faces.size(); i++ )
    {
//        Point rec( faces[i].x, faces[i].y );
        try {
            Point rec2( faces[i].x + faces[i].width, faces[i].y + faces[i].height );
            roi_img = img( Range(faces[i].y +5 ,faces[i].y+ 80), Range(faces[i].x +5,faces[i].x+80) );
        } catch (Exception e) {
//            roi_img = 
//            imshow("error", img);
            
//            cvWaitKey();
    
            roi_img = Mat(75,75, CV_8UC3);
            imshow("error", roi_img);
            //cvWaitKey();
        }
        
            
//        imshow("roi_img", roi_img);
        return roi_img;
    }
//    cvWaitKey();
    return roi_img;
}

int test3()
{
//        if( !face_cascade.load( "/Users/xiaopeng/Downloads/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml") ){ printf("--(!)Error loading\n"); return -1; };
    //    cout<<"cut……OK！"<<endl;
    //    detectAndCut("/Users/xiaopeng/Downloads/att_faces/s1/1.jpg", "/Users/xiaopeng/Desktop/", "1_c.png");
    //    test2();
    get_color_new_picture("/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_result/141220004.JPG.txt");
//    return comparetest(0,0);
    return 0;
}

bool Control_new_Picture()
{
    vector<string> files;
    
    ////获取该路径下的所有文件
    struct dirent *mydir;
    DIR * dp = opendir(test_PATH.c_str());
    while((mydir = readdir(dp) )!= NULL)
    {
        if(mydir->d_type==8)
        {
            TestLine temp;
            temp.Name = mydir->d_name;
            if(temp.Name==".DS_Store")
                continue;
            temp.Path = test_PATH + string(mydir->d_name);
            get_color_new_picture(temp.Path);
            
        }
    }
    closedir(dp);
    return 0;
}


bool get_color_new_picture(string Path)
{
    if( !face_cascade.load( "/Users/xiaopeng/Downloads/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml") ){ printf("--(!)Error loading\n"); return -1; };
    ifstream fin(Path);
    Mat file[K_NUMB];
    bool first = true;
    string titile;
    for(int i = 0;i<K_NUMB;i++)
    {
        string temp;
        fin>>temp;
        if(first)
        {
            titile = temp;
            first = false;
        }
        fin>>temp;
        fin>>temp;
        file[i] = detectandgive(temp);//循环读入文件
    }
    fin.close();
    
//    
//    Mat img(file[0]);
//    for(int i = 1 ; i < K_NUMB;i++)
//    {
//        img = img*(1-1/K_NUMB) + file[i]/K_NUMB;
//    }
    
   // 线性叠加
    Mat img = file[0];
//    double alpha = 1 - double(1/(double)K_NUMB);
    double alpha = 0.1;
    double beta;
    beta = (1.0 - alpha);
    for(int i = 1;i < K_NUMB;i++)
    {
        Mat temp;
        addWeighted(file[i], alpha, img, beta, 0.0, temp);

        img = temp;
    }
    //平均叠加
//    Mat aftImgnum(75,75,CV_32FC1);
//    Mat img;  //存放平均值
//    img.convertTo(aftImgnum,CV_32FC1,1,0);
//    for(int i = 0; i < K_NUMB; i ++)
//    {
//        accumulate(file[i],aftImgnum);  //将所有图像叠加
//    }
//    aftImgnum = aftImgnum / K_NUMB; //求出平均图像
//    aftImgnum.convertTo(img,CV_8UC1,1,0); //将平均图像存储在mergy中
//    for (int row = 0; row < img.rows; row++)
//    {
//        for (int col = 0; col < img.cols; col++)
//        {
//            //主要是这里的代码
//            if(*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) > 128)
//            {
//                *(img.data + img.step[0] * row + img.step[1] * col) = *(img.data + img.step[0] * row + img.step[1] * col)/K_NUMB;
//                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) = *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1())/K_NUMB;
//                *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()*2) = *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()*2)/K_NUMB;
//            }
//        }
//    }
//    for (int row = 0; row < img.rows; row++)
//    {
//        for (int col = 0; col < img.cols; col++)
//        {
//            //主要是这里的代码
//            if(*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) > 128)
//            {
//                //[row, col]像素的第 1 通道地址被 * 解析(blue通道)
//                for(int i = 1;i < K_NUMB;i++)
//                {
//                    *(img.data + img.step[0] * row + img.step[1] * col) += *(file[i].data + file[i].step[0] * row + file[i].step[1] * col);
//                }
//               
//                //[row, col]像素的第 2 通道地址被 * 解析(green通道), 关于elemSize1函数的更多描述请见 Fn1 里所列的博文链接
//                for(int i = 1;i < K_NUMB;i++)
//                {
//                    *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) += *(file[i].data + file[i].step[0] * row + file[i].step[1] * col + file[i].elemSize1());
//                }
//                //[row, col]像素的第 3 通道地址被 * 解析(red通道)
//                for(int i = 1;i < K_NUMB;i++)
//                {
//                    *(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()*2) += *(file[i].data + file[i].step[0] * row + file[i].step[1] * col + file[i].elemSize1()*2);
//                }
//                
//            }
//        }
//    }
    imshow("Lena Modified", img);
//    cvWaitKey();
    imwrite( test_New+titile, img );

    
    return true;
    
}
