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

entt::dispatcher &ECSWorld::getDispatcher()
{
    return dispatcher;
}

void ECSWorld::start()
{
    AnimationSystem::get().start();
    AudioSystem::get().start();
    GeometrySystem::get().start();
    PhysicsSystem::get().start();
    RenderingSystem::get().start();
    ResourceSystem::get().start();
}