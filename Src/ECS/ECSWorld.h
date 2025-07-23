#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>
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
};