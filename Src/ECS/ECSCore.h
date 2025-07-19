#pragma once

#include "ISystem.h"
#include "TaskScheduler.h"

class ECSCore
{
  private:
    concurrencpp::runtime runtime;
    entt::registry registry;
    std::unique_ptr<TaskScheduler> scheduler;
    std::vector<std::shared_ptr<ISystem>> systems;
    bool m_running = true;

  public:
    ECSCore()
    {
        // 使用所有硬件线程
        auto executor = runtime.thread_pool_executor();
        scheduler = std::make_unique<TaskScheduler>(executor);
    }

    // 向引擎注册系统
    template <typename T, typename... Args>
    void addSystem(Args &&...args)
    {
        systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    // 获取 registry 的引用，用于初始化实体
    entt::registry &getRegistry()
    {
        return registry;
    }

    // 主循环
    void run()
    {
        while (m_running)
        {
            // 每帧执行调度
            scheduler->run(registry, systems);
        }
    }

    void stop()
    {
        m_running = false;
    }

    void start()
    {
        m_running = true;
    }
};