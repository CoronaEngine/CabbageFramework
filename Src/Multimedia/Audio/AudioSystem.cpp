#include "AudioSystem.h"
#include <iostream>
#include <sstream>

AudioSystem &AudioSystem::get()
{
    static AudioSystem instance;
    return instance;
}

void AudioSystem::start()
{
    std::cout << "AudioSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&AudioSystem::mainloop, this);
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