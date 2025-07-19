#pragma once

#include "ISystem.h"

class DemoSystem final : public ISystem
{
  public:
    DemoSystem() = default;
    ~DemoSystem() = default;

    std::vector<std::type_index> getReadComponents() const override;
    std::vector<std::type_index> getWriteComponents() const override;
    void update(entt::registry &registry) override;
    const char *getName() const override;
};