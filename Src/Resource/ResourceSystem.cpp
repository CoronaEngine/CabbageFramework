#include "ResourceSystem.h"
#include <ECS/ECSWorld.h>
#include <ECS/Events.hpp>

ResourceSystem::ResourceSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化资源系统
    ECSWorld::get().getDispatcher().sink<EngineStartEvent>().connect<&ISystem::onStart>(this);
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&ISystem::onQuit>(this);
    std::printf("Scene %-5s %-16s %-10s\n", "null", getName(), "created");
}

void ResourceSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 注册资源系统相关的事件处理器
}

void ResourceSystem::onStart()
{
    running = true;
    std::printf("Scene %-5s %-16s %-10s\n", "null", getName(), "started");
    mainloopThread = std::make_shared<std::thread>([this]() {
        int i = 0;
        do
        {
            std::printf("Scene %-5s %-16s %-10s %-5d\n", "null", getName(), "ticked", i++);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } while (running);
    });
}

void ResourceSystem::onQuit()
{
    running = false;
    // 关闭资源系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
    std::printf("Scene %-5s %-16s %-10s]\n", "null", getName(), "quited");
}

const char *ResourceSystem::getName() const
{
    return "ResourceSystem";
}
