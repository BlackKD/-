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
#include <string>
#include <iostream>
#include <vector>
using namespace std;


typedef struct TestLine{
    string Name;
    string Path;
    string NewPath;
    string MostLike[K_NUMB];
    string NewLike[K_NUMB];
    int LikeCount;
}testline;

extern vector<TestLine> TestPool;

bool InitializationPool(const char * FilePath);
bool get_10_top_path();

#endif /* DealSource_hpp */
