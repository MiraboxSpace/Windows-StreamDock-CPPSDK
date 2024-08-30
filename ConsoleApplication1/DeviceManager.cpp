#include "DeviceManager.h"

DeviceManager * other;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Sleep(100);                                           //延时一下使设备能够被加载
    std::vector<std::tuple<int, int, int>> products = {

        {std::make_tuple((int)USBVendorIDs::USB_VID, (int)USBProductIDs::USB_PID_STREAMDOCK_936,1)}

    };
    switch (message)
    {
    case WM_DEVICECHANGE:
        if (wParam == DBT_DEVICEARRIVAL)
        {
            for (const auto& product : products) {
                struct hid_device_info* info = other->transport->enumerate(std::get<0>(product), std::get<1>(product));
                std::cout << info << std::endl;
                while (info)
                {
                    if (other->streamDockmaps->find(info->path) == other->streamDockmaps->end())
                    {
                        (*other->streamDockmaps)[info->path] =new streamDock293(other->transport,info);
                        //this->transport->freeEnumerate()
                        std::cout << "创建成功: " << std::endl;
                        break;
                    }
                    info = info->next;
                }
            }
            
        }
        else if(wParam == DBT_DEVICEREMOVECOMPLETE)
        {
            for (const auto& product : products) {
                struct hid_device_info* info = other->transport->enumerate(std::get<0>(product), std::get<1>(product));
                std::cout << info << std::endl;
                int flag = 0;
                for (auto it = other->streamDockmaps->begin(); it != other->streamDockmaps->end(); it++)
                {
                    flag = 0;
                    while (info)
                    {
                        std::cout << "path" << it->first << "   " << info->path << std::endl;
                        if (strcmp(it->first, info->path) == 0)
                        {
                            flag = 1;
                        }

                        info = info->next;
                    }
                    if (flag == 0)
                    {
                        other->streamDockmaps->erase(it);
                        std::cout << "删除成功: " << std::endl;
                        break;
                    }


                }
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
DeviceManager::DeviceManager()
{
    this->transport=new tranSport();
    this->streamDockmaps=new std::map<char *,streamDock *>;
    other = this;
}

DeviceManager::~DeviceManager()
{
    delete this->streamDockmaps;
    delete this->transport;
}

std::map<char *,streamDock *> *DeviceManager::enumerate()
{
    std::vector<std::tuple<int, int, int>> products = {
        
        {std::make_tuple((int)USBVendorIDs::USB_VID, (int)USBProductIDs::USB_PID_STREAMDOCK_936,1)}
        

     
    };

    for(const auto& product : products){
        struct hid_device_info *deviceInfo=this->transport->enumerate(std::get<0>(product),std::get<1>(product));
        struct hid_device_info* deviceInfo1 = deviceInfo;
        
        while (deviceInfo)
        {
            streamDock *node=NULL;
            if (deviceInfo->serial_number==NULL)
            {
                deviceInfo=deviceInfo->next;
                continue;
            }
            if (std::get<2>(product)==1)
            {
                node=new streamDock293(this->transport,deviceInfo);        //增加设备时在这个地方添加一个判断，生成不同的设备类
            }
            
            
            (*this->streamDockmaps)[deviceInfo->path]=node;
            deviceInfo=deviceInfo->next;
        }
        this->transport->freeEnumerate(deviceInfo1);
        
    }
    return streamDockmaps;
}


int DeviceManager::listen()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SampleClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"SampleClass",
        L"Sample Window",
        0,
        0, 0, 0, 0,
        HWND_MESSAGE, // No actual window is created
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd) {
        std::cerr << "Failed to create window." << std::endl;
        return 1;
    }
    // Register for device notifications
    DEV_BROADCAST_DEVICEINTERFACE dbdi = {};
    dbdi.dbcc_size = sizeof(dbdi);
    dbdi.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    dbdi.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
    HDEVNOTIFY hDevNotify = RegisterDeviceNotification(hwnd, &dbdi, DEVICE_NOTIFY_WINDOW_HANDLE);
    if (!hDevNotify) {
        std::cerr << "Failed to register for device notifications." << std::endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}