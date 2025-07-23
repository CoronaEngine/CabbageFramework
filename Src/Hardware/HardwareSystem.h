#pragma once

#include <memory>
#include <thread>

class HardwareSystem
{
  private:
    HardwareSystem() = default;

  public:
    ~HardwareSystem();

  public:
    static HardwareSystem &get();

    void start();
    void stop();
    void mainloop();

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};