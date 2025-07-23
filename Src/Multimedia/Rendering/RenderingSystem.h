#pragma once

#include <concurrencpp/concurrencpp.h>

class RenderingSystem
{
  public:
    static RenderingSystem &get();

    void start();
    void mainloop();

  private:
    std::shared_ptr<std::thread> mainloopThread;
};