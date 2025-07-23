#pragma once

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

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};