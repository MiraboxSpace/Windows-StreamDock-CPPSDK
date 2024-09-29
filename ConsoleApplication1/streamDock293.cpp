#include "streamDock293.h"

streamDock293::streamDock293(tranSport* transport, struct hid_device_info* devInfo) :streamDock(transport, devInfo) {

}

unsigned char* streamDock293::getFirmVersion(int lenth) {
    return transport->getInputReport(lenth);
}


int streamDock293::setBrightness(int percent) {

    return this->transport->setBrightness(percent);
}

int streamDock293::setBackgroundImg(std::string path)
{

    // 读取图像文件
    cv::Mat image = cv::imread(path);

    int  size = image.rows * image.cols * 3;
    unsigned char* buffer = new unsigned char[size];
    // 遍历图像的每个像素

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            // 获取像素点的BGR值

            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            // 提取BGR分量
            buffer[size - y * image.cols * 3 - x * 3 - 2] = pixel[1];
            buffer[size - y * image.cols * 3 - x * 3 - 1] = pixel[2];
            buffer[size - y * image.cols * 3 - x * 3] = pixel[0];


        }
    }
    return this->transport->setBackgroundImg(buffer, size);


}




unsigned char* streamDock293::read()
{


    unsigned char* command = new unsigned char(13);
    if (this->transport->read(command, 13) != -1)
        return command;
    else
        return NULL;


}

int streamDock293::setKeyImg(std::string path, int key)
{

    cv::Mat image = cv::imread(path), Image2;
    if (image.empty()) {
        std::cerr << "无法加载图像： " << path << std::endl;
        return -1;
    }


    // 创建一个新的图像矩阵用于存储旋转后的图像


    //// 使用flip函数实现180°旋转
    cv::flip(image, Image2, -1); // -1表示沿x和y轴翻转
    //// 保存旋转后的图像
    imwrite("347274857239.jpg", Image2);
    int res = this->transport->setKeyImg("347274857239.jpg", key);
    std::remove("347274857239.jpg");
    return res;
}

int streamDock293::setKeyImgData(unsigned char* imagedata, int width, int height, int key)
{
    cv::Mat img(height, width, CV_MAKETYPE(CV_8U, 3), imagedata, static_cast<size_t>(width * 3));
    std::vector<unsigned char>* buffer = new std::vector<unsigned char>(); // 存储JPG数据的缓冲区
    std::vector<int> compressionParams = { cv::IMWRITE_JPEG_QUALITY, 95 }; // 压缩参数，默认设置为高质量
    // 将RGB图像编码为JPG格式
    bool result = cv::imencode(".jpg", img, *buffer, compressionParams);
    if (!result) {
        std::cerr << "Failed to encode the image to JPG." << std::endl;
    }

    return this->transport->setKeyImgdata(buffer->data(), key, width, height);

}