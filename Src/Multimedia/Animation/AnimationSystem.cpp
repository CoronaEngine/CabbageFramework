#include "AnimationSystem.h"
#include <iostream>
#include <sstream>
#include <thread>

AnimationSystem &AnimationSystem::get()
{
    static AnimationSystem instance;
    return instance;
}

void AnimationSystem::start()
{
    std::cout << "AnimationSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&AnimationSystem::mainloop, this);
    // mainloopThread->detach();
}

void AnimationSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> AnimationSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}