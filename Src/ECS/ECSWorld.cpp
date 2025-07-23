#include "ECSWorld.h"
#include "Components.h"

#include <Multimedia/Animation/AnimationSystem.h>
#include <Multimedia/Audio/AudioSystem.h>
#include <Multimedia/Geometry/GeometrySystem.h>
#include <Multimedia/Physics/PhysicsSystem.h>
#include <Multimedia/Rendering/RenderingSystem.h>
#include <Resource/ResourceSystem.h>

ECSWorld &ECSWorld::get()
{
    static ECSWorld instance;
    return instance;
}

entt::registry &ECSWorld::getRegistry()
{
    return registry;
}

void ECSWorld::start()
{
    AnimationSystem::get().start(runtime.thread_executor());
    AudioSystem::get().start(runtime.thread_executor());
    GeometrySystem::get().start(runtime.thread_executor());
    PhysicsSystem::get().start(runtime.thread_executor());
    RenderingSystem::get().start(runtime.thread_executor());
    ResourceSystem::get().start(runtime.thread_executor());
}