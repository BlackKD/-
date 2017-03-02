//
//  Header.h
//  opencv_2
//
//  Created by XiaoPeng on 17/2/21.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#define CV_COMP_CHISQR_T 0
#define CV_COMP_BHATTACHARYYA_T 1
#define CV_COMP_CORREL_T 2
#define CV_COMP_INTERSECT_T 3
double Compare_New_Get(int choose, char *srcImagePath, char *targetImagePath);
double CompareGet(int choose, char *srcImagePath, char *targetImagePath);
int comparetest(int argc, char* argv[]);
int newcomparetest(int argc, char* argv[]);


#endif /* Header_h */
