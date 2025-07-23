#pragma once

#include <memory>
#include <thread>

class GeometrySystem
{
  private:
    GeometrySystem() = default;

  public:
    ~GeometrySystem();

  public:
    static GeometrySystem &get(); // Singleton

    void start();
    void stop();
    void mainloop();

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};