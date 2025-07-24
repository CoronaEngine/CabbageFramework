#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>
#include <marl/defer.h>
#include <marl/scheduler.h>

#include <Multimedia/Animation/AnimationSystem.h>
#include <Multimedia/Audio/AudioSystem.h>
#include <Multimedia/Rendering/RenderingSystem.h>
#include <Resource/ResourceSystem.h>

class ECSWorld
{
    struct SceneSystem
    {
        std::shared_ptr<AnimationSystem> animationSystem;
        std::shared_ptr<AudioSystem> audioSystem;
        std::shared_ptr<RenderingSystem> renderingSystem;
    };

  public:
    static ECSWorld &get(); // Singleton

    ECSWorld(const marl::Scheduler::Config &config);

    ~ECSWorld();

  private:
    entt::dispatcher globalDispatcher;                                           // Global Event Dispatcher
    std::shared_ptr<ResourceSystem> resourceSystem;                              // Resource System
    std::unordered_map<entt::entity, entt::dispatcher> sceneDispatchers;         // SceneEntity -> Dispatcher
    std::unordered_map<entt::entity, std::shared_ptr<SceneSystem>> sceneSystems; // SceneEntity -> Systems

  private:
    entt::registry registry;   // ECS Registry: Operate entities & component
    marl::Scheduler scheduler; // Scheduler: Run ECS Systems Tasks

  public:
    marl::Scheduler &getScheduler();
    entt::registry &getRegistry();
    entt::dispatcher &getDispatcher();
    entt::dispatcher &getDispatcher(const entt::entity &scene); // 获取对应场景的事件分发器

    entt::entity createScene();
};