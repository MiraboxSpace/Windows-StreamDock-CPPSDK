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
    std::cout << image.rows << " " << image.cols << "\n";
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
    this->transport->setBackgroundImg(buffer);
    return 0;


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
    std::filesystem::remove("347274857239.jpg");
    return res;
}

