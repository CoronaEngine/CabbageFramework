#pragma once

#include <thread>

class AnimationSystem
{
  public:
    static AnimationSystem &get();

    void start();
    void mainloop();

  private:
    std::shared_ptr<std::thread> mainloopThread;
};