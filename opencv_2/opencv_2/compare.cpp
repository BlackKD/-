//
//  compare.cpp
//  opencv_2
//
//  Created by XiaoPeng on 17/2/21.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#include <stdio.h>
#include <opencv/cv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include "Header.h"
using namespace std;
using namespace cv;

String srcImage ="/Users/xiaopeng/Downloads/14-220/14-220/141220007.JPG" ;
String targetImage = "/Users/xiaopeng/Downloads/14-220/14-220/141220003.JPG";
String cascadeName = "/Users/xiaopeng/Downloads/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml";

IplImage* cutImage(IplImage* src, CvRect rect) {
    cvSetImageROI(src, rect);
    IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),
                                  src->depth,
                                  src->nChannels);
    
    cvCopy(src,dst,0);
    cvResetImageROI(src);
    return dst;
}

IplImage* detect( Mat& img, CascadeClassifier& cascade, double scale)
{
    int i = 0;
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
    
    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );
    
    t = (double)cvGetTickCount();
    cascade.detectMultiScale( smallImg, faces,
                             1.3, 2, CV_HAAR_SCALE_IMAGE,
                             Size(30, 30) );
    t = (double)cvGetTickCount() - t;
//    printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    IplImage* tempfinal = NULL;
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        IplImage temp2 = IplImage(img);
        IplImage* temp = cutImage(&temp2, cvRect(r->x, r->y, r->width, r->height));
        tempfinal = temp;
    }
    return tempfinal;
    
    return NULL;
}
//画直方图用
int HistogramBins = 256;
float HistogramRange1[2]={0,255};
float *HistogramRange[1]={&HistogramRange1[0]};
int CompareHist(IplImage* image1, IplImage* image2)
{
    IplImage* srcImage;
    IplImage* targetImage;
    if (image1->nChannels != 1) {
        srcImage = cvCreateImage(cvSize(image1->width, image1->height), image1->depth, 1);
        cvCvtColor(image1, srcImage, CV_BGR2GRAY);
    } else {
        srcImage = image1;
    }
    
    if (image2->nChannels != 1) {
        targetImage = cvCreateImage(cvSize(image2->width, image2->height), srcImage->depth, 1);
        cvCvtColor(image2, targetImage, CV_BGR2GRAY);
    } else {
        targetImage = image2;
    }
    
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    
    cvCalcHist(&srcImage, Histogram1);
    cvCalcHist(&targetImage, Histogram2);
    
    cvNormalizeHist(Histogram1, 1);
    cvNormalizeHist(Histogram2, 1);
    
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似
    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));
    
    
    // CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似
    printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));
    printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
    
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);
    if (image1->nChannels != 1) {
        cvReleaseImage(&srcImage);
    }
    if (image2->nChannels != 1) {
        cvReleaseImage(&targetImage);
    }
    return 0;
}


double CompareHist_CV_COMP_CHISQR(IplImage* image1, IplImage* image2)
{
    IplImage* srcImage;
    IplImage* targetImage;
    if (image1->nChannels != 1) {
        srcImage = cvCreateImage(cvSize(image1->width, image1->height), image1->depth, 1);
        cvCvtColor(image1, srcImage, CV_BGR2GRAY);
    } else {
        srcImage = image1;
    }
    
    if (image2->nChannels != 1) {
        targetImage = cvCreateImage(cvSize(image2->width, image2->height), srcImage->depth, 1);
        cvCvtColor(image2, targetImage, CV_BGR2GRAY);
    } else {
        targetImage = image2;
    }
    
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    
    cvCalcHist(&srcImage, Histogram1);
    cvCalcHist(&targetImage, Histogram2);
    
    cvNormalizeHist(Histogram1, 1);
    cvNormalizeHist(Histogram2, 1);
    
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似
//    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    
//    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));
    
    
    // CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似
//    printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));
//    printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
    double result = cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR);
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);
    if (image1->nChannels != 1) {
        cvReleaseImage(&srcImage);
    }
    if (image2->nChannels != 1) {
        cvReleaseImage(&targetImage);
    }
    return result;
}

double CompareHist_CV_COMP_BHATTACHARYYA(IplImage* image1, IplImage* image2)
{
    IplImage* srcImage;
    IplImage* targetImage;
    if (image1->nChannels != 1) {
        srcImage = cvCreateImage(cvSize(image1->width, image1->height), image1->depth, 1);
        cvCvtColor(image1, srcImage, CV_BGR2GRAY);
    } else {
        srcImage = image1;
    }
    
    if (image2->nChannels != 1) {
        targetImage = cvCreateImage(cvSize(image2->width, image2->height), srcImage->depth, 1);
        cvCvtColor(image2, targetImage, CV_BGR2GRAY);
    } else {
        targetImage = image2;
    }
    
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    
    cvCalcHist(&srcImage, Histogram1);
    cvCalcHist(&targetImage, Histogram2);
    
    cvNormalizeHist(Histogram1, 1);
    cvNormalizeHist(Histogram2, 1);
    
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似
    //    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    
    //    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));
    
    
    // CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似
    //    printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));
    //    printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
    double result =cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA);
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);
    if (image1->nChannels != 1) {
        cvReleaseImage(&srcImage);
    }
    if (image2->nChannels != 1) {
        cvReleaseImage(&targetImage);
    }
    return result;
}

double CompareHist_CV_COMP_CORREL(IplImage* image1, IplImage* image2)
{
    IplImage* srcImage;
    IplImage* targetImage;
    if (image1->nChannels != 1) {
        srcImage = cvCreateImage(cvSize(image1->width, image1->height), image1->depth, 1);
        cvCvtColor(image1, srcImage, CV_BGR2GRAY);
    } else {
        srcImage = image1;
    }
    
    if (image2->nChannels != 1) {
        targetImage = cvCreateImage(cvSize(image2->width, image2->height), srcImage->depth, 1);
        cvCvtColor(image2, targetImage, CV_BGR2GRAY);
    } else {
        targetImage = image2;
    }
    
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    
    cvCalcHist(&srcImage, Histogram1);
    cvCalcHist(&targetImage, Histogram2);
    
    cvNormalizeHist(Histogram1, 1);
    cvNormalizeHist(Histogram2, 1);
    
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似
    //    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    
    //    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));
    
    
    // CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似
    //    printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));
    //    printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
    double result = cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL);
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);
    if (image1->nChannels != 1) {
        cvReleaseImage(&srcImage);
    }
    if (image2->nChannels != 1) {
        cvReleaseImage(&targetImage);
    }
    return result;
}


double CompareHist_CV_COMP_INTERSECT(IplImage* image1, IplImage* image2)
{
    IplImage* srcImage;
    IplImage* targetImage;
    if (image1->nChannels != 1) {
        srcImage = cvCreateImage(cvSize(image1->width, image1->height), image1->depth, 1);
        cvCvtColor(image1, srcImage, CV_BGR2GRAY);
    } else {
        srcImage = image1;
    }
    
    if (image2->nChannels != 1) {
        targetImage = cvCreateImage(cvSize(image2->width, image2->height), srcImage->depth, 1);
        cvCvtColor(image2, targetImage, CV_BGR2GRAY);
    } else {
        targetImage = image2;
    }
    
    CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);
    
    cvCalcHist(&srcImage, Histogram1);
    cvCalcHist(&targetImage, Histogram2);
    
    cvNormalizeHist(Histogram1, 1);
    cvNormalizeHist(Histogram2, 1);
    
    // CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似
    //    printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
    
    //    printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));
    
    
    // CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似
    //    printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));
    //    printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
    double result = cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT);
    cvReleaseHist(&Histogram1);
    cvReleaseHist(&Histogram2);
    if (image1->nChannels != 1) {
        cvReleaseImage(&srcImage);
    }
    if (image2->nChannels != 1) {
        cvReleaseImage(&targetImage);
    }
    return result;
}

int comparetest(int argc, char* argv[])
{
    
    CascadeClassifier cascade;
    namedWindow("image1");
    namedWindow("image2");
    if( !cascade.load( cascadeName ) )
    {
        return -1;
    }
    
    Mat srcImg, targetImg;
    IplImage* faceImage1;
    IplImage* faceImage2;
    srcImg = imread(srcImage);
    targetImg = imread(targetImage);
    faceImage1 = detect(srcImg, cascade, 1);
    if (faceImage1 == NULL) {
        return -1;
    }
    //    cvSaveImage("d:\\face.jpg", faceImage1, 0);
    faceImage2 = detect(targetImg, cascade, 1);
    if (faceImage2 == NULL) {
        return -1;
    }
    //    cvSaveImage("d:\\face1.jpg", faceImage2, 0);
//    imshow("image1", Mat(faceImage1));
//    imshow("image2", Mat(faceImage2));
    
    CompareHist(faceImage1, faceImage2);
    cvWaitKey(0);  
    cvReleaseImage(&faceImage1);  
    cvReleaseImage(&faceImage2);  
    return 0;  
}



double CompareGet(int choose, char *srcImagePath, char *targetImagePath)
{
    
    srcImage = srcImagePath;
    targetImage = targetImagePath;
    CascadeClassifier cascade;
    namedWindow("image1");
    namedWindow("image2");
    if( !cascade.load( cascadeName ) )
    {
        return -1;
    }
    
    Mat srcImg, targetImg;
    IplImage* faceImage1;
    IplImage* faceImage2;
    srcImg = imread(srcImage);
    targetImg = imread(targetImage);
    faceImage1 = detect(srcImg, cascade, 1);
    if (faceImage1 == NULL) {
        return -1;
    }
    //    cvSaveImage("d:\\face.jpg", faceImage1, 0);
    faceImage2 = detect(targetImg, cascade, 1);
    if (faceImage2 == NULL) {
        return -1;
    }
    //    cvSaveImage("d:\\face1.jpg", faceImage2, 0);
    imshow("image1", Mat(faceImage1));
    imshow("image2", Mat(faceImage2));
    double result = 0;
    switch (choose) {
        case CV_COMP_CHISQR_T:
            result = CompareHist_CV_COMP_CHISQR(faceImage1, faceImage2);
            break;
        case CV_COMP_CORREL_T:
            result = CompareHist_CV_COMP_CORREL(faceImage1, faceImage2);
            break;
        case CV_COMP_INTERSECT_T:
            result = CompareHist_CV_COMP_INTERSECT(faceImage1, faceImage2);
            break;
        case CV_COMP_BHATTACHARYYA_T:
            result = CompareHist_CV_COMP_BHATTACHARYYA(faceImage1, faceImage2);
            break;
        default:
            break;
    }
//    CompareHist(faceImage1, faceImage2);
    cvWaitKey(0);
    cvReleaseImage(&faceImage1);
    cvReleaseImage(&faceImage2);
    return result;
}