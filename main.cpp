#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "HisiStartVideo.h"
#include "HisiHdmi.h"

std::atomic<bool> running(true);
std::mutex mutex;

bool flag = true;
void displayVideo(HisiHdmi& hdmi) {
    while (flag) {
    }
    hdmi.init();
    while(1){
        hdmi.show_video();
    }
}

void controlCamera() {
    int input;
    while (running) {
        std::cin >> input;
        if (input == 1) {
            std::lock_guard<std::mutex> guard(mutex);
            HisiStartVideo video1(1);
            video1.start_video();
            flag = false;
            std::cout << "Camera 1 started." << std::endl;
        } else if (input == 2) {
            std::lock_guard<std::mutex> guard(mutex);
            HisiStartVideo video2(2);
            video2.start_video();
            flag = false;
            std::cout << "Camera 2 started." << std::endl;
        } 
        else if (input == 3) {
            std::lock_guard<std::mutex> guard(mutex);
            HisiStartVideo video3(3);
            video3.start_video();
            flag = false;
            std::cout << "Camera 3 started." << std::endl;
        } else if (input == 4) {
            std::lock_guard<std::mutex> guard(mutex);
            HisiStartVideo video4(4);
            video4.start_video();
            flag = false;
            std::cout << "Camera 4 started." << std::endl;
        }else if (input == 0) { // 添加一个输入0的选项来安全退出程序
            running = false;
            std::cout << "Exiting program." << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    HisiSysvbmipi sys(2, 1920, 1080);
    sys.init();
    HisiHdmi hdmi;
    // hdmi.init();

    std::thread videoThread(displayVideo, std::ref(hdmi));
    std::thread controlThread(controlCamera);

    // 等待线程完成
    videoThread.join();
    controlThread.join();

    return 0;
}

