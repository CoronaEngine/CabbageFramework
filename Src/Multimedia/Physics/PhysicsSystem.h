#pragma once

#include <memory>
#include <thread>

class PhysicsSystem
{
  public:
    static PhysicsSystem &get();

    void start();
    void mainloop();

  private:
    std::shared_ptr<std::thread> mainloopThread;
};