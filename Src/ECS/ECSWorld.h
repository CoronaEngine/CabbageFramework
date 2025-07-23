#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>
#include <marl/defer.h>
#include <marl/scheduler.h>

struct EngineStopEvent
{
};

class ECSWorld
{
  public:
    static ECSWorld &get(); // Singleton

    ECSWorld(const marl::Scheduler::Config &config);

    ~ECSWorld();

  private:
  private:
    entt::registry registry;     // ECS Registry: Operate entities & component
    entt::dispatcher dispatcher; // ECS Dispatcher: Dispatch events
    marl::Scheduler scheduler;   // Scheduler: Run ECS Systems Tasks
  public:
    entt::registry &getRegistry();
    entt::dispatcher &getDispatcher();

    template <typename Func>
    void submitTask(Func &&func);

    template <typename Func, typename... Args>
    void submitTask(Func &&func, Args &&...args);
};

template <typename Func>
void ECSWorld::submitTask(Func &&func)
{
    scheduler.bind();
    defer(scheduler.unbind());
    marl::schedule(std::forward<Func>(func));
}

template <typename Func, typename... Args>
void ECSWorld::submitTask(Func &&func, Args &&...args)
{
    scheduler.bind();
    defer(scheduler.unbind());
    marl::schedule(std::forward<Func>(func), std::forward<Args>(args)...);
}