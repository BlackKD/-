//
//  result.cpp
//  opencv_2
//
//  Created by XiaoPeng on 17/3/29.
//  Copyright © 2017年 XiaoPeng. All rights reserved.
//

#include "result.hpp"
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

//extern CascadeClassifier face_cascade;
//extern String test_PATH = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_result/";
//extern String test_New = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_new/";
using namespace std;
using namespace cv;
double K_check(string Path,int comp_numb)
{
    cout<<"K_check Starting!"<<endl;
    get_new_10_top_path();
    vector<TestLine> files;
    
    ////获取该路径下的所有文件
    struct dirent *mydir;
    DIR * dp = opendir(Path.c_str());
    while((mydir = readdir(dp) )!= NULL)
    {
        if(mydir->d_type==8)
        {
            TestLine temp;
            temp.Name = mydir->d_name;
            temp.Name.erase(temp.Name.end()-1);
            temp.Name.erase(temp.Name.end()-1);
            temp.Name.erase(temp.Name.end()-1);
            temp.Name.erase(temp.Name.end()-1);
            if(temp.Name==".DS_Store")
                continue;
            temp.Path = Path + string(mydir->d_name);
            files.push_back(temp);
            
        }
    }
    closedir(dp);
    int ess = 0;
    for(int i = 0; i < files.size();i++)
    {
        ifstream fin(files[i].Path,ios::out);
        bool find = false;
        for(int j = 0 ; j < files.size()/comp_numb; j++)
        {
            string temp;
            fin >> temp;
            if(!temp.compare(files[i].Name))
            {
                
                cout<<files[i].Name<<endl;
                find = true;
                break;
            }
            fin>>temp;
            fin>>temp;
        }
        fin.close();
        if(find)
        {
            ess++;
        }
    }
    cout<<"K_check:"<<1- double(ess)/double(files.size())<<endl;
    return ess/files.size();
}