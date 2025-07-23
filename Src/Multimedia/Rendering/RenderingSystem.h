#pragma once

#include <concurrencpp/concurrencpp.h>

class RenderingSystem
{
  public:
    static RenderingSystem &get();

    void start(std::shared_ptr<concurrencpp::thread_executor> executor);
    void mainloop();

  private:
    std::shared_ptr<concurrencpp::thread_executor> mainloopThread;
};