#include "AudioSystem.h"
#include <iostream>
#include <thread>

AudioSystem &AudioSystem::get()
{
    static AudioSystem instance;
    return instance;
}

void AudioSystem::mainloop()
{
    static int i = 1;
    std::cout << "AudioSystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}