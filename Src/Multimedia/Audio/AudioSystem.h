#pragma once

#include <memory>
#include <thread>

class AudioSystem
{
  public:
    static AudioSystem &get(); // Singleton

    void start();
    void mainloop();

  private:
    std::shared_ptr<std::thread> mainloopThread;
};