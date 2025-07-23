#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>

class ECSWorld
{
  public:
    static ECSWorld &get(); // Singleton

  private:
    ECSWorld() = default;
    ECSWorld(const ECSWorld &other) = delete;
    ECSWorld &operator=(const ECSWorld &other) = delete;
    ECSWorld(const ECSWorld &&other) = delete;
    ECSWorld &operator=(const ECSWorld &&other) = delete;

  private:
    entt::registry registry;       // ECS Registry: Operate entities & component

  public:
    entt::registry &getRegistry();

    void start(); // Start ECS World
};