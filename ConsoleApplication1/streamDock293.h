#ifndef _STREAMDOCK293_
#define _STREAMDOCK293_

#include "streamDock.h"
#include "tranSport.h"
#include <iostream>
#include "hidapi.h"
#include <string>
#include <vector>
#include <cstdio>
#include <string>
#include <stdio.h>
// #include <jpeglib.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include <filesystem>

//using namespace cv;

// #include "png.h"
class streamDock293 :public streamDock
{
private:

public:

    streamDock293(tranSport* transport, struct hid_device_info* devInfo);
    ~streamDock293();



    /*
        @note:获取设备的固件版本
        @param lenth ：固件版本的长度 
        @return 返回固件版本的版本号存放数组的首地址，如果出错返回空
    */
    unsigned char* getFirmVersion(int lenth);

    /*
        @note:设置设备屏幕的亮度,如果传入的值小于0，值会被拉回0，如果大于100会被回100
        @param percent ：亮度的数值1-100
        @return 成功返回0，如果出错返回-1
    */
    int setBrightness(int percent);

    /*
        @note:设置设备屏幕的背景图片
        @param path ：图片的路径
        @return 成功返回1，如果出错返回-1
    */
    int setBackgroundImg(std::string path);

    /*
	@note:设置设备屏幕的背景图片
	@param buffer ：存有RGB数据的vector容器
	@param width ：图片的宽
	@param height ：图片的高
	@return 成功返回1，如果出错返回-1
	*/
    int setBackgroundImgData(std::vector<unsigned char>buffer, int width, int height);

    /*
       @note:接受设备发送的信息 数据传送成功时会返回ack ok ,当设备连接激活时，按下按键会返回一个unsigned char数组，下标为9的字节为按键编号，下标为10的字节存放按键状态0x00抬起，0x01按下
       @return 成功返回获得的数组首地址，如果出错返回NULL
   */
    unsigned char* read();
    /*
       @note:设置设备按键的图标
       @param path ：图片的路径
       @return 成功返回1，如果出错返回-1
   */
    int setKeyImg(std::string path, int key);
    /*
        @note:设置设备屏幕的按键图片
        @param path ：存放图片数据的数组
        @return 成功返回1，如果出错返回-1
    */
    int setKeyImgData(unsigned char* imagedata, int width, int height, int key);
};





#endif
