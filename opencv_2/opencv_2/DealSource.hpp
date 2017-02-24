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
#define K_NUMB 10

char * TestPath = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/14-220/";

typedef struct TestLine{
    char * Name;
    char * Path;
    char * NewPath;
    char * MostLike[K_NUMB];
    char * NewLike[K_NUMB];
    int LikeCount;
}testline;

vector<TestLine> TestPool;

bool InitializationPool(char * FileName);

#endif /* DealSource_hpp */
