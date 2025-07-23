#pragma once

#include <concurrencpp/concurrencpp.h>

class GeometrySystem
{
  public:
    static GeometrySystem &get(); // Singleton

      void start(std::shared_ptr<concurrencpp::thread_executor> executor);
    void mainloop();

  private:
    std::shared_ptr<concurrencpp::thread_executor> mainloopThread;
};