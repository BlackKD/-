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
#include <fstream>
#include <dirent.h>
char result_dir[] = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_result/";

char result_new_dir[] = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_result_new/";
char  TestPath[] = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test/";
string test_new = "/Users/xiaopeng/Desktop/毕业设计/opencv_2/opencv_2/test_new/";
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
            if(temp.Name==".DS_Store")
                continue;
            temp.Path = string(TestPath) + string(mydir->d_name);
//            cout<<temp.Path<<endl;
            TestPool.push_back(temp);
        }
    }
    closedir(dp);
    return true;
}



bool get_10_top_path()
{
    
    for(int i= 0;i<TestPool.size();i++)
    {
        string result = result_dir + TestPool[i].Name + ".txt";
        ofstream fout(result,ios::out);
        
        Likeline *temp = new Likeline[TestPool.size()];
        for(int j=0;j<TestPool.size();j++)
        {
            int len = TestPool[i].Path.length();
            char *p1 =new char[len+1];
            for(int s = 0 ;s <= len+1;s++)
            {
                p1[s]='\0';
            }
            TestPool[i].Path.copy(p1, len);
//            cout<<TestPool[i].Path<<endl;
//            cout<<p1<<endl;
            int len2 = TestPool[j].Path.length();
            char *p2 =new char[len2+1];
            for(int s = 0 ;s <= len2+1;s++)
            {
                p2[s]='\0';
            }
            TestPool[j].Path.copy(p2, len2);
            
            try {
                temp[j].CV_COMP_CHISQR_numb = CompareGet(CV_COMP_CHISQR_T, p1, p2);
//                temp[j].CV_COMP_BHATTACHARYYA_numb = CompareGet(CV_COMP_BHATTACHARYYA_T, p1, p2);
//                temp[j].CV_COMP_CORREL_numb = CompareGet(CV_COMP_CORREL_T, p1, p2);
//                temp[j].CV_COMP_INTERSECT_numb = CompareGet(CV_COMP_INTERSECT_T, p1, p2);
                if(temp[j].CV_COMP_CHISQR_numb == -1)
                    temp[j].CV_COMP_CHISQR_numb = 9999;
                temp[j].Name = TestPool[j].Name;
                temp[j].Path = TestPool[j].Path;
            } catch (Exception e) {
                cout<<p1<<endl<<p2<<endl;
                exit(0);
            }
            
        }
        for(int k = 0; k < TestPool.size(); k++)
        {
            for(int s = k;s<TestPool.size();s++)
            {
                if(temp[s].CV_COMP_CHISQR_numb<temp[k].CV_COMP_CHISQR_numb)
                {
                    Likeline t = temp[k];
                    temp[k] = temp[s];
                    temp[s] = t;
                }
            }
        }
        cout<<"NOW NUMB"<<i+1<<endl;
        for(int k = 0; k < K_NUMB;k++)
        {
            TestPool[i].MostLike[k].Name = temp[k].Name;
            TestPool[i].MostLike[k].Path = temp[k].Path;
            TestPool[i].MostLike[k].CV_COMP_CHISQR_numb = temp[k].CV_COMP_CHISQR_numb;
            cout<<TestPool[i].MostLike[k].Name<<" "<<TestPool[i].MostLike[k].CV_COMP_CHISQR_numb<<endl;
            fout<<TestPool[i].MostLike[k].Name<<" "<<TestPool[i].MostLike[k].CV_COMP_CHISQR_numb<<" "<<TestPool[i].MostLike[k].Path<<endl;
        }
        fout.close();
    }
    return true;
    
}


bool get_new_10_top_path()
{
    
    vector<TestLine> files;
    
    ////获取该路径下的所有文件
    struct dirent *mydir;
    DIR * dp = opendir(test_new.c_str());
    while((mydir = readdir(dp) )!= NULL)
    {
        if(mydir->d_type==8)
        {
            TestLine temp;
            temp.Name = mydir->d_name;
            if(temp.Name==".DS_Store")
                continue;
            temp.Path = test_new + string(mydir->d_name);
            files.push_back(temp);
            
        }
    }
    closedir(dp);
    
    
    for(int i= 0;i<files.size();i++)
    {
        string result = result_new_dir + files[i].Name + ".txt";
        ofstream fout(result,ios::out);
        
//        Likeline *temp = new Likeline[files.size()];
        Likeline *temp[files.size()];
        for(int j=0;j<TestPool.size();j++)
        {
            int len = files[i].Path.length();
            char *p1 =new char[len+1];
            for(int s = 0 ;s <= len+1;s++)
            {
                p1[s]='\0';
            }
            files[i].Path.copy(p1, len);
            int len2 = TestPool[j].Path.length();
            char *p2 =new char[len2+1];
            for(int s = 0 ;s <= len2+1;s++)
            {
                p2[s]='\0';
            }
            TestPool[j].Path.copy(p2, len2);
//            cout<<p1<<endl<<p2<<endl;
            try {
                Likeline * mytemp = new Likeline;
                mytemp->CV_COMP_CHISQR_numb = Compare_New_Get(CV_COMP_CHISQR_T, p1, p2);
                if(mytemp->CV_COMP_CHISQR_numb < 0)
                    mytemp->CV_COMP_CHISQR_numb = 9999;
                //                temp[j].CV_COMP_BHATTACHARYYA_numb = CompareGet(CV_COMP_BHATTACHARYYA_T, p1, p2);
                //                temp[j].CV_COMP_CORREL_numb = CompareGet(CV_COMP_CORREL_T, p1, p2);
                //                temp[j].CV_COMP_INTERSECT_numb = CompareGet(CV_COMP_INTERSECT_T, p1, p2);
                
                mytemp->Name = TestPool[j].Name;
                mytemp->Path = TestPool[j].Path;
                temp[j] = mytemp;
            } catch (Exception e) {
                cout<<p1<<endl<<p2<<endl;
                exit(0);
            }
            
        }
        for(int k = 0; k < TestPool.size(); k++)
        {
            for(int s = k;s<TestPool.size();s++)
            {
                if(temp[s]->CV_COMP_CHISQR_numb<temp[k]->CV_COMP_CHISQR_numb)
                {
                    Likeline *t = temp[k];
                    temp[k] = temp[s];
                    temp[s] = t;
                }
            }
        }
        cout<<"NOW NUMB"<<i+1<<endl;
        for(int k = 0; k < K_NUMB;k++)
        {
            files[i].MostLike[k].Name = temp[k]->Name;
            files[i].MostLike[k].Path = temp[k]->Path;
            files[i].MostLike[k].CV_COMP_CHISQR_numb = temp[k]->CV_COMP_CHISQR_numb;
            cout<<files[i].MostLike[k].Name<<" "<<files[i].MostLike[k].CV_COMP_CHISQR_numb<<endl;
            fout<<files[i].MostLike[k].Name<<" "<<files[i].MostLike[k].CV_COMP_CHISQR_numb<<" "<<files[i].MostLike[k].Path<<endl;
        }
        fout.close();
    }
    return true;
    
}
