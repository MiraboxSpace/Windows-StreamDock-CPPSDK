#include "streamDock.h"


streamDock::streamDock(tranSport *transport,struct hid_device_info  *devInfo){

    this->transport=transport;

    this->vendor_id=devInfo->vendor_id;
    this->product_id=devInfo->product_id;
    this->product_string=devInfo->product_string;
    this->path=devInfo->path;
    this->serial_number=devInfo->serial_number;
    this->manufacturer_string=devInfo->manufacturer_string;
    this->release_number=devInfo->release_number;

}

std::string streamDock::getFileExtension(const std::string& fileName) 
{
    size_t pos = fileName.find_last_of('.');
    if (pos == std::string::npos) {
        return ""; // 没有找到文件扩展名
    }
    return fileName.substr(pos + 1);
}

unsigned char *streamDock::getFirmVersion(int lenth)
{
    return NULL;
}

int streamDock::open()
{
    if(this->transport->open(this->path)==-1)
    {
        return -1;
    }
    return 1;
}

int streamDock::disconnected()
{
    return this->transport->disconnected();
}

int streamDock::setBrightness(int percent)
{
    return 0;
}

 int streamDock::setBackgroundImg(std::string path)
 {
     return 0;
 }



unsigned char * streamDock::read()
{
    return 0;
}

int streamDock::setKeyImg(std::string path,int key)
{
    return 0;
}

int streamDock::cleaerIcon(int index)
{
    return this->transport->keyClear(index);
}

int streamDock::clearAllIcon()
{
    int res = this->transport->keyAllClear();
    this->refresh();
    return res;
}

int streamDock::wakeScreen()
{
    return this->transport->wakeScreen();
}


int streamDock::refresh()
{
    return this->transport->refresh();
}


