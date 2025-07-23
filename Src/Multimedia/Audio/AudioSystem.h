#pragma once

#include <memory>
#include <thread>

class AudioSystem
{
  private:
    AudioSystem() = default;

  public:
    ~AudioSystem();

  public:
    static AudioSystem &get(); // Singleton

    void start();
    void stop();
    void mainloop();

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};