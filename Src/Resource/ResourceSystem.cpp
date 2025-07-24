#include "ResourceSystem.h"

ResourceSystem::ResourceSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化资源系统
}

void ResourceSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 注册资源系统相关的事件处理器
}

void ResourceSystem::onStart()
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

void ResourceSystem::onQuit()
{
    // 关闭资源系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
}

const char *ResourceSystem::getName() const
{
    return "ResourceSystem";
}
