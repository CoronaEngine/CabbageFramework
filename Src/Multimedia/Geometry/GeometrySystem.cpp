#include "GeometrySystem.h"
#include <iostream>
#include <thread>

GeometrySystem &GeometrySystem::get()
{
    static GeometrySystem instance;
    return instance;
}

void GeometrySystem::mainloop()
{
    static int i = 1;
    std::cout << "GeometrySystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}