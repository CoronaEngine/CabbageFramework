#pragma once

#include <entt/entt.hpp>

#include <typeindex>
#include <vector>

class ISystem
{
  public:
    using ComponentIdType = entt::id_type;
  public:
    virtual ~ISystem() = default;

    // 声明此系统会读取哪些组件
    virtual std::vector<std::type_index> getReadComponents() const = 0;
    // 声明此系统会写入哪些组件
    virtual std::vector<std::type_index> getWriteComponents() const = 0;

    virtual void update(entt::registry &registry) = 0;

    virtual const char *getName() const = 0;
};