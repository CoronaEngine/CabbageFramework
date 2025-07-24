#include "AudioSystem.h"

AudioSystem::AudioSystem(const entt::entity &ownerScene)
    : ISystem(ownerScene)
{
    // 初始化音频系统
}

void AudioSystem::registerEvents(entt::dispatcher &dispatcher)
{
    // 注册音频相关的事件处理
}

void AudioSystem::onStart()
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

void AudioSystem::onQuit()
{
    // 关闭音频系统
    if (mainloopThread && mainloopThread->joinable())
    {
        mainloopThread->join();
    }
}

const char *AudioSystem::getName() const
{
    return "AudioSystem";
}
