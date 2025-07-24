#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化渲染系统
}

void RenderingSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 注册渲染系统相关的事件处理器
}

void RenderingSystem::onStart()
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

void RenderingSystem::onQuit()
{
    // 关闭渲染系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
}

const char *RenderingSystem::getName() const
{
    return "RenderingSystem";
}
