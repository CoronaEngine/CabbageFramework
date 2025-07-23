#pragma once

#include <concurrencpp/concurrencpp.h>

class AudioSystem
{
  public:
    static AudioSystem &get(); // Singleton

    void start(std::shared_ptr<concurrencpp::thread_executor> executor);
    void mainloop();

  private:
    std::shared_ptr<concurrencpp::thread_executor> mainloopThread;
};