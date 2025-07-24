#include <algorithm>

#include "Components.h"
#include "ECSWorld.h"
#include "Events.hpp"

#include <Multimedia/Animation/AnimationSystem.h>
#include <Multimedia/Audio/AudioSystem.h>
#include <Multimedia/Rendering/RenderingSystem.h>
#include <Resource/ResourceSystem.h>

ECSWorld instance([] {
    marl::Scheduler::Config config;
    config.setWorkerThreadCount(std::max(4u, std::thread::hardware_concurrency() - 8));
    return config;
}());

ECSWorld::ECSWorld(const marl::Scheduler::Config &config) : scheduler(config)
{
    // 立即触发事件 非线程安全
    for (auto &[scene, dispatcher] : sceneDispatchers)
    {
        dispatcher.trigger<EngineStartEvent>();
    }
}

ECSWorld::~ECSWorld()
{
    // 立即触发事件 非线程安全
    for (auto &[scene, dispatcher] : sceneDispatchers)
    {
        dispatcher.trigger<EngineStopEvent>();
    }
}

ECSWorld &ECSWorld::get()
{
    return instance;
}

entt::registry &ECSWorld::getRegistry()
{
    return registry;
}

entt::dispatcher &ECSWorld::getDispatcher(const entt::entity &scene)
{
#ifdef CABBAGE_ENGINE_DEBUG
    if (!sceneDispatchers.contains(scene))
    {
        throw std::runtime_error("Scene does not create the dispatcher: Scene ID = " + std::to_string(static_cast<uint64_t>(scene)));
    }
#endif
    return sceneDispatchers[scene];
}