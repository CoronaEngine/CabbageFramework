#include "ECSWorld.h"
#include "Events.hpp"

ECSWorld instance([] {
    marl::Scheduler::Config config;
    config.setWorkerThreadCount(std::max(4u, std::thread::hardware_concurrency() - 8));
    return config;
}());

ECSWorld::ECSWorld(const marl::Scheduler::Config &config) : scheduler(config)
{
    this->resourceSystem = std::make_shared<ResourceSystem>();

    globalDispatcher.trigger<EngineStartEvent>();

#ifdef CABBAGE_ENGINE_DEBUG
    createScene();
    createScene();
    createScene();
#endif
}

ECSWorld::~ECSWorld()
{
    // 立即触发事件 非线程安全
    for (auto &[scene, dispatcher] : sceneDispatchers)
    {
        dispatcher.trigger<SceneDestroyEvent>();
        dispatcher.clear();
    }

    globalDispatcher.trigger<EngineStopEvent>();

    sceneDispatchers.clear();
    sceneSystems.clear();
    globalDispatcher.clear();
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
    return globalDispatcher;
}

entt::dispatcher &ECSWorld::getDispatcher(const entt::entity &scene)
{
    if (!sceneDispatchers.contains(scene))
    {
        sceneDispatchers[scene] = std::move(entt::dispatcher{});
    }
    return sceneDispatchers[scene];
}

entt::entity ECSWorld::createScene()
{
    entt::entity scene = registry.create();
    sceneSystems[scene] = std::make_shared<ECSWorld::SceneSystem>();
    sceneSystems[scene]->animationSystem = std::make_shared<AnimationSystem>(scene);
    sceneSystems[scene]->audioSystem = std::make_shared<AudioSystem>(scene);
    sceneSystems[scene]->renderingSystem = std::make_shared<RenderingSystem>(scene);

    sceneDispatchers[scene].trigger<SceneCreateEvent>();
    return scene;
}