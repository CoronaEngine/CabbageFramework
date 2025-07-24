#pragma once

#include <ECS/ISystem.h>

#include <iostream>
#include <memory>
#include <thread>

class AnimationSystem final : ISystem
{
  public:
    AnimationSystem(const entt::entity& ownerScene);

  private:
    std::shared_ptr<std::thread> mainloopThread;
};