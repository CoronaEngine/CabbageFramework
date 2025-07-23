#include "PhysicsSystem.h"
#include <iostream>
#include <thread>

PhysicsSystem &PhysicsSystem::get()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "PhysicsSystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
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