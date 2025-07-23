#pragma once

#include <iostream>
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

    void testTask2()
    {
        std::cout << "Audio Test 2\n";
    }
    void testTask(int id)
    {
        std::cout << "Audio Test: " << id << "\n";
    }

  private:
    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;
};