#include "RenderingSystem.h"
#include <iostream>
#include <thread>

RenderingSystem &RenderingSystem::get()
{
    static RenderingSystem instance;
    return instance;
}

void RenderingSystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "RenderingSystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
}

void RenderingSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> RenderSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}