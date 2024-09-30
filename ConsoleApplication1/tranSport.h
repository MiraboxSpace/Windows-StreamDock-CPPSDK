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
    //读取设备的反馈信息 需要传入一个unsigned char 数组，若成功写入数据数组会被赋值ack ok，若设备被启动，按下按键，下标为9的字节中存放按键标号，下标为10的字节中存放按键状态，0x00按键抬起，0x01按键按下
    int read(unsigned char *data,unsigned long lenth);
    //向设备下发信息，data:装有数据的unsigned char数组，lenth：数组长度
    int write(unsigned char *data,unsigned long lenth);
    //将enumerate返回的设备信息列表销毁
    void freeEnumerate(hid_device_info *devs);
    //获取设备信息列表，vid：设备vid  pid：设备vid
    hid_device_info *enumerate(int vid, int pid);
    //设置设备屏幕亮度 1-100
    int setBrightness(int percent);
    //设置设备屏幕的背景图，buffer：放有BGR数据的unsigned char数组地址，size：数组大小
    int setBackgroundImg(unsigned char *buffer,int size);
    //设置设备某个按键的图标，path：图片路径，key：按键标号
    int setKeyImg(std::string path,int key);
    //设置设备某个按键的图标,buffer，装有图片信息的unsigned char 数组，key：按键标号 width： 图片长度 height：图片高度
    int setKeyImgdata(unsigned char* buffer, int key, int width, int height);
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
