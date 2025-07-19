#include "DemoSystem.h"
#include "Components.hpp"

#include <iostream>

std::vector<std::type_index> DemoSystem::getReadComponents() const
{
    return {std::type_index(typeid(DemoReadComponent))};
}

std::vector<std::type_index> DemoSystem::getWriteComponents() const
{
    return {std::type_index(typeid(DemoWriteComponent))};
}

void DemoSystem::update(entt::registry &registry)
{
    // Some logic
    std::cout << "DemoSystem update" << std::endl;
}

const char *DemoSystem::getName() const
{
    return "DemoSystem";
}