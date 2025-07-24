#include "RenderingSystem.h"
#include <ECS/ECSWorld.h>
#include <ECS/Events.hpp>

RenderingSystem::RenderingSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化渲染系统
    ECSWorld::get().getDispatcher(ownerScene).sink<SceneCreateEvent>().connect<&ISystem::onStart>(this);
    ECSWorld::get().getDispatcher(ownerScene).sink<SceneDestroyEvent>().connect<&ISystem::onQuit>(this);
    std::printf("Scene %-5lld %-16s %-10s\n", static_cast<uint64_t>(ownerScene), getName(), "created");
}

void RenderingSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 注册渲染系统相关的事件处理器
}

void RenderingSystem::onStart()
{
    running = true;
    std::printf("Scene %-5lld %-16s %-10s\n", static_cast<uint64_t>(ownerScene), getName(), "started");
    mainloopThread = std::make_shared<std::thread>([this]() {
        int i = 0;
        do
        {
            std::printf("Scene %-5lld %-16s %-10s %-5d\n", static_cast<uint64_t>(ownerScene), getName(), "ticked", i++);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } while (running);
    });
}

void RenderingSystem::onQuit()
{
    running = false;
    // 关闭渲染系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
    std::printf("Scene %-5lld %-16s %-10s\n", static_cast<uint64_t>(ownerScene), getName(), "quited");
}

const char *RenderingSystem::getName() const
{
    return "RenderingSystem";
}
