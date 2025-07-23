#include "ECSWorld.h"
#include "Components.h"

#include <Hardware/HardwareSystem.h>
#include <Multimedia/Animation/AnimationSystem.h>
#include <Multimedia/Audio/AudioSystem.h>
#include <Multimedia/Rendering/RenderingSystem.h>
#include <Resource/ResourceSystem.h>

ECSWorld::ECSWorld(marl::Scheduler::Config &config) : scheduler(config)
{
}

ECSWorld &ECSWorld::get()
{
    static marl::Scheduler::Config config;
    config.setWorkerThreadCount(std::thread::hardware_concurrency() - 7);
    static ECSWorld instance(config);
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

void ECSWorld::start()
{
    AnimationSystem::get().start();
    AudioSystem::get().start();
    HardwareSystem::get().start();
    RenderingSystem::get().start();
    ResourceSystem::get().start();
}