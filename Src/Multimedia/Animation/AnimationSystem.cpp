#include "AnimationSystem.h"
#include <iostream>
#include <thread>

AnimationSystem &AnimationSystem::get()
{
    static AnimationSystem instance;
    return instance;
}

void AnimationSystem::mainloop()
{
    static int i = 1;
    std::cout << "AnimationSystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}