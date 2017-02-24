//
//  CreatNewPicture.hpp
//  opencv_2
//
//  Created by XiaoPeng on 17/2/24.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#ifndef CreatNewPicture_hpp
#define CreatNewPicture_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include "Header.h"
using namespace cv;
using namespace std;
int test1();
int test2();
void detectAndCut( string path ,string dir, string filename);
int test3();
#endif /* CreatNewPicture_hpp */
