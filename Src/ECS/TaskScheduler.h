#pragma once

#include "ISystem.h"

#include <iostream>

#include <concurrencpp/concurrencpp.h>
#include <utility>

class TaskScheduler
{
  private:
    std::shared_ptr<concurrencpp::thread_pool_executor> m_executor;

  public:
    TaskScheduler(std::shared_ptr<concurrencpp::thread_pool_executor> executor)
        : m_executor(std::move(executor))
    {
    }

    // 执行一帧的所有系统
    void run(entt::registry &registry, const std::vector<std::shared_ptr<ISystem>> &systems)
    {
        std::vector<std::shared_ptr<ISystem>> remaining_systems = systems;
        std::vector<concurrencpp::result<void>> frame_tasks;

        while (!remaining_systems.empty())
        {
            std::vector<concurrencpp::result<void>> batch_tasks;
            std::unordered_set<std::type_index> batch_read_components;
            std::unordered_set<std::type_index> batch_write_components;

            auto it = remaining_systems.begin();
            while (it != remaining_systems.end())
            {
                auto system = *it;
                bool has_conflict = false;

                // 检查写-读和写-写冲突
                for (const auto &component_id : system->getReadComponents())
                {
                    if (batch_read_components.count(component_id) || batch_write_components.count(component_id))
                    {
                        has_conflict = true;
                        break;
                    }
                }
                if (has_conflict)
                {
                    it++;
                    continue;
                }

                // 检查读-写冲突
                for (const auto &component_id : system->getWriteComponents())
                {
                    if (batch_write_components.count(component_id))
                    {
                        has_conflict = true;
                        break;
                    }
                }
                if (has_conflict)
                {
                    it++;
                    continue;
                }

                // ---- 没有冲突，将此系统加入当前批次 ----
                std::cout << "[Scheduler] Adding " << system->getName() << " to current concurrent batch." << std::endl;

                // 注册此系统在本批次中的读写记录
                for (const auto &id : system->getReadComponents())
                {
                    batch_read_components.insert(id);
                }
                for (const auto &id : system->getWriteComponents())
                {
                    batch_write_components.insert(id);
                }

                // 创建并发任务
                auto task = m_executor->submit([&registry, system]() {
                    system->update(registry);
                });

                batch_tasks.push_back(std::move(task));
                frame_tasks.push_back(std::move(batch_tasks.back()));

                // 从剩余列表中移除
                it = remaining_systems.erase(it);
            }

            // 等待当前批次的所有并发任务完成，才能开始下一批次
            if (!batch_tasks.empty())
            {
                concurrencpp::when_all(m_executor, batch_tasks.begin(), batch_tasks.end());
            }
        }
    }
};