#include "AnimationSystem.h"

AnimationSystem::AnimationSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化动画系统
}

void AnimationSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 在此注册事件处理
}

void AnimationSystem::onStart()
{
    mainloopThread = std::make_shared<std::thread>([this]() {
        static int i = 0;
        do
        {
            std::printf("%s system tick %d \n", getName(), i++);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } while (running);
    });
}

void AnimationSystem::onQuit()
{
    // 关闭动画系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
}

const char *AnimationSystem::getName() const
{
    return "AnimationSystem";
}