#include "RenderingSystem.h"
#include <iostream>
#include <thread>

RenderingSystem &RenderingSystem::get()
{
    static RenderingSystem instance;
    return instance;
}

void RenderingSystem::mainloop()
{
    static int i = 1;
    std::cout << "RenderingSystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}