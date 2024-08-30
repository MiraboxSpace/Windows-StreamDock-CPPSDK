You need to install it yourself on Windows [OpenCV](https://github.com/opencv/opencv/releases/tag/3.4.6) and [hidapi](https://github.com/libusb/hidapi/releases/tag/hidapi-0.14.0)

When using a dynamic library, you need to define a `DeviceManager` class object (device manager class), and then call the `enumerate ()` function to traverse the device to obtain the list of equipment objects.

```cpp
  DeviceManager *manager = new DeviceManager();
  auto streamDocks = manager->enumerate();
```

After obtaining the list of equipment objects, make the `open()` method open the device when the device needs to be called, and then other methods to operate the device

```cpp
auto it = StreamDocks->begin();
StreamDock *s = *it;
s->open();

// Set the brightness
s->setBrightness(100);
```

Please see the [document](https://creator.key123.vip/en/windows/cpp/dependency.html) for details