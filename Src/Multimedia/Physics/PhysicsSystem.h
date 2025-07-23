#pragma once

#include <memory>
#include <thread>

class PhysicsSystem
{
  private:
    PhysicsSystem() = default;

  public:
    ~PhysicsSystem();

  public:
    static PhysicsSystem &get();

    void start();
    void stop();
    void mainloop();

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};