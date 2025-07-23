#include "PhysicsSystem.h"
#include <iostream>
#include <thread>

PhysicsSystem &PhysicsSystem::get()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::mainloop()
{
    static int i = 1;
    std::cout << "PhysicsSystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}