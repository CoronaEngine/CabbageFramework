#include "GeometrySystem.h"
#include <iostream>
#include <sstream>

GeometrySystem &GeometrySystem::get()
{
    static GeometrySystem instance;
    return instance;
}

void GeometrySystem::start()
{
    std::cout << "GeometrySystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&GeometrySystem::mainloop, this);
}

void GeometrySystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> GeometrySystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}