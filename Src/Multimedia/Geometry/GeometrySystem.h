#pragma once

#include <memory>
#include <thread>

class GeometrySystem
{
  public:
    static GeometrySystem &get(); // Singleton

    void start();
    void mainloop();

  private:
    std::shared_ptr<std::thread> mainloopThread;
};