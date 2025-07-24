#include "ISystem.h"
#include "ECSWorld.h"
#include "Events.hpp"

ISystem::ISystem(const entt::entity &ownerScene) : ownerScene(ownerScene), running(false)
{
    ECSWorld::get().getDispatcher(ownerScene).sink<EngineStartEvent>().connect<&ISystem::_onStart>(this);
    ECSWorld::get().getDispatcher(ownerScene).sink<EngineStopEvent>().connect<&ISystem::_onStart>(this);
}

ISystem::~ISystem()
{
    ECSWorld::get().getDispatcher(ownerScene).sink<EngineStartEvent>().disconnect<&ISystem::_onStart>(this);
    ECSWorld::get().getDispatcher(ownerScene).sink<EngineStopEvent>().disconnect<&ISystem::_onQuit>(this);
}

void ISystem::_onStart()
{
    if (!running)
    {
        std::printf("=== System [%s] Would Started ===\n", this->getName());
        running = true;
        onStart();
    }
}

void ISystem::_onQuit()
{
    if (running)
    {
        std::printf("=== System [%s] Would Stopped\n ===", this->getName());
        running = false;
        onQuit();
    }
}