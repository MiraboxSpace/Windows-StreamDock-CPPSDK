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
    //���豸��ʹ���豸·����
    int open(char *path);
    //��ȡ�豸�Ĺ̼�id
    unsigned char *getInputReport(int lenth);
    //��ȡ�豸�ķ�����Ϣ
    int read(unsigned char *data,unsigned long lenth);
    //���豸�·���Ϣ
    int write(unsigned char *data,unsigned long lenth);
    //��enumerate���ص��豸��Ϣ�б�����
    void freeEnumerate(hid_device_info *devs);
    //��ȡ�豸��Ϣ�б�
    hid_device_info *enumerate(int vid, int pid);
    //�����豸��Ļ���� 1-100
    int setBrightness(int percent);
    //�����豸��Ļ�ı���ͼ
    int setBackgroundImg(unsigned char *buffer);
    //�����豸ĳ��������ͼ��
    int setKeyImg(std::string path,int key);
    //���ĳ��������ͼ�� 1-15
    int keyClear(int i);
    //������а�����ͼ��
    int keyAllClear();
    //������Ļ
    int wakeScreen();
    //�����ݴ�����ɺ���������ˢ����ʾ
    int refresh();
    //�Ͽ�����
    int disconnected();
    //�ر��豸
    void close();
};
#endif