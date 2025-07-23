#include "AudioSystem.h"
#include <iostream>
#include <thread>

AudioSystem &AudioSystem::get()
{
    static AudioSystem instance;
    return instance;
}

void AudioSystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "AudioSystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
}

void AudioSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> AudioSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}