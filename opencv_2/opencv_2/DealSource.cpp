//
//  DealSource.cpp
//  opencv_2
//
//  Created by XiaoPeng on 17/2/24.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#include "DealSource.hpp"
#include "CreatNewPicture.hpp"
#include "Header.h"
#include <dirent.h>

char  TestPath[] = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/14-220/";
vector<TestLine> TestPool;
bool InitializationPool(const char * FilePath)
{
    vector<string> files;
    
    ////获取该路径下的所有文件
    struct dirent *mydir;
    DIR * dp = opendir(FilePath);
    while((mydir = readdir(dp) )!= NULL)
    {
        if(mydir->d_type==8)
        {
            TestLine temp;
            temp.Name = mydir->d_name;
            temp.Path = string(TestPath) + string(mydir->d_name);
        }
    }
    return true;
}

bool get_10_top_path()
{
    return true;
    
}