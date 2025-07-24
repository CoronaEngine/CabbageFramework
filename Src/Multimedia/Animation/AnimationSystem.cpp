#include "AnimationSystem.h"
#include <ECS/ECSWorld.h>
#include <ECS/Events.hpp>

AnimationSystem::AnimationSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化动画系统
    ECSWorld::get().getDispatcher(ownerScene).sink<SceneCreateEvent>().connect<&ISystem::onStart>(this);
    ECSWorld::get().getDispatcher(ownerScene).sink<SceneDestroyEvent>().connect<&ISystem::onQuit>(this);
    std::printf("Scene %-5lld %-16s %-10s\n", static_cast<uint64_t>(ownerScene), getName(), "created");
}

void AnimationSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 在此注册事件处理
}

void AnimationSystem::onStart()
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

void AnimationSystem::onQuit()
{
    running = false;
    // 关闭动画系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
    std::printf("Scene %-5lld %-16s %-10s\n", static_cast<uint64_t>(ownerScene), getName(), "quited");
}

const char *AnimationSystem::getName() const
{
    return "AnimationSystem";
}