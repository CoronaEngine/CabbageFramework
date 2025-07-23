#include "ECSWorld.h"
#include "Components.h"

ECSWorld &ECSWorld::get()
{
    static ECSWorld instance;
    return instance;
}

entt::registry &ECSWorld::getRegistry()
{
    return registry;
}

concurrencpp::runtime &ECSWorld::getRuntime()
{
    return runtime;
}