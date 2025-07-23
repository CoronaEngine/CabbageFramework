#include "GeometrySystem.h"
#include <iostream>
#include <thread>

GeometrySystem &GeometrySystem::get()
{
    static GeometrySystem instance;
    return instance;
}

void GeometrySystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "GeometrySystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
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