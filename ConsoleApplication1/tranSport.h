#ifndef _TRANSPOT_
#define _TRANSPOT_
#undef UNICODE
#undef _UNICODE
#include <iostream>
#include "hidapi.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>

class tranSport
{
private:
    hid_device *handle;
public:
    tranSport();
    //打开设备，使用设备路径打开
    int open(char *path);
    //获取设备的固件id
    unsigned char *getInputReport(int lenth);
    //读取设备的反馈信息
    int read(unsigned char *data,unsigned long lenth);
    //向设备下发信息
    int write(unsigned char *data,unsigned long lenth);
    //将enumerate返回的设备信息列表销毁
    void freeEnumerate(hid_device_info *devs);
    //获取设备信息列表
    hid_device_info *enumerate(int vid, int pid);
    //设置设备屏幕亮度 1-100
    int setBrightness(int percent);
    //设置设备屏幕的背景图
    int setBackgroundImg(unsigned char *buffer);
    //设置设备某个按键的图标
    int setKeyImg(std::string path,int key);
    //清空某个按键的图标 1-15
    int keyClear(int i);
    //清空所有按键的图标
    int keyAllClear();
    //唤醒屏幕
    int wakeScreen();
    //在数据传输完成后可以用这个刷新显示
    int refresh();
    //断开连接
    int disconnected();
    //关闭设备
    void close();
};
#endif