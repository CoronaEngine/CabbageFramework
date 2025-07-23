#include "AnimationSystem.h"
#include <iostream>
#include <thread>

AnimationSystem &AnimationSystem::get()
{
    static AnimationSystem instance;
    return instance;
}

void AnimationSystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "AnimationSystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
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