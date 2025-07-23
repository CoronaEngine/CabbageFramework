#pragma once

#include <iostream>
#include <memory>
#include <thread>


class AnimationSystem
{
  private:
    AnimationSystem() = default;

  public:
    ~AnimationSystem();

  public:
    static AnimationSystem &get();

    void start();
    void stop();
    void mainloop();

    void testTask()
    {
        std::cout << "Anim Test\n";
    }

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};