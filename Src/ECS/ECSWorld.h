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

  private:
    ECSWorld(marl::Scheduler::Config &config);
    ECSWorld(const ECSWorld &other) = delete;
    ECSWorld &operator=(const ECSWorld &other) = delete;
    ECSWorld(const ECSWorld &&other) = delete;
    ECSWorld &operator=(const ECSWorld &&other) = delete;

  private:
    entt::registry registry;     // ECS Registry: Operate entities & component
    entt::dispatcher dispatcher; // ECS Dispatcher: Dispatch events
    marl::Scheduler scheduler;   // Scheduler: Run ECS Systems Tasks
  public:
    entt::registry &getRegistry();
    entt::dispatcher &getDispatcher();

    void start(); // Start ECS World
};