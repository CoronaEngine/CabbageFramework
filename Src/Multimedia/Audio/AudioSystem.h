#pragma once

#include <ECS/ISystem.h>

#include <memory>
#include <thread>

class AudioSystem final : public ISystem
{
  public:
    AudioSystem(const entt::entity &ownerScene = entt::null);

    void registerEvents(entt::dispatcher &dispatcher) override;
    void onStart() override;
    void onQuit() override;
    const char *getName() const override;

  private:
    std::shared_ptr<std::thread> mainloopThread;
};