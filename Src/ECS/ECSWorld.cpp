#include <algorithm>

#include "Components.h"
#include "ECSWorld.h"

#include <Hardware/HardwareSystem.h>
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
    AnimationSystem::get().start();
    AudioSystem::get().start();
    HardwareSystem::get().start();
    RenderingSystem::get().start();
    ResourceSystem::get().start();
}

ECSWorld::~ECSWorld()
{
    dispatcher.trigger<EngineStopEvent>();
}

ECSWorld &ECSWorld::get()
{
    return instance;
}

entt::registry &ECSWorld::getRegistry()
{
    return registry;
}

entt::dispatcher &ECSWorld::getDispatcher()
{
    return dispatcher;
}