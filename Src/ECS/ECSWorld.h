#pragma once

#include <concurrencpp/concurrencpp.h>
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
    entt::registry registry; // ECS Registry: Operate entities & component
    concurrencpp::runtime runtime; // Concurrencpp: Multi-threading

  public:
    entt::registry &getRegistry();
    concurrencpp::runtime &getRuntime();
};