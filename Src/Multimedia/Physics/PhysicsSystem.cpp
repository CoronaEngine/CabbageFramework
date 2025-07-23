#include "PhysicsSystem.h"
#include <iostream>
#include <sstream>

PhysicsSystem &PhysicsSystem::get()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::start()
{
    std::cout << "PhysicsSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&PhysicsSystem::mainloop, this);
}

void PhysicsSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> PhysicsSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}