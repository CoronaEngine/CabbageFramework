#pragma once

#include <memory>
#include <thread>

class RenderingSystem
{
  private:
    RenderingSystem() = default;

  public:
    ~RenderingSystem();

  public:
    static RenderingSystem &get();

    void start();
    void stop();
    void mainloop();

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};