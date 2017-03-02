//
//  DealSource.hpp
//  opencv_2
//
//  Created by XiaoPeng on 17/2/24.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#ifndef DealSource_hpp
#define DealSource_hpp

#include <stdio.h>
#include "CreatNewPicture.hpp"
#include "Header.h"
#define K_NUMB 25
#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef struct Line{
    double CV_COMP_CHISQR_numb;
    double CV_COMP_BHATTACHARYYA_numb;
    double CV_COMP_CORREL_numb;
    double CV_COMP_INTERSECT_numb;
    string Name;
    string Path;
}Likeline;

typedef struct TestLine{
    string Name;
    string Path;
    string NewPath;
    Likeline MostLike[K_NUMB];
    Likeline NewLike[K_NUMB];
    int LikeCount;
}testline;

extern vector<TestLine> TestPool;

bool InitializationPool(const char * FilePath);
bool get_10_top_path();
bool get_new_10_top_path();

#endif /* DealSource_hpp */
