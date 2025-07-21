#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>

class ECSCore
{
  private:
    entt::registry registry;

  public:
    const entt::entity createTexture(const std::string &texturePath = "");
    const entt::entity createMaterial(const entt::entity &baseColorTexture = entt::null);
    const entt::entity createMesh(const entt::entity &material = entt::null,
                                  const entt::entity &normalTexture = entt::null,
                                  const entt::entity &OpacityTexture = entt::null);
    const entt::entity createActor(const ktm::fvec3 &transform = {0.0f, 0.0f, 0.0f},
                                   const ktm::fvec3 &rotate = {0.0f, 0.0f, 0.0f},
                                   const ktm::fvec3 &scale = {0.0f, 0.0f, 0.0f},
                                   const std::string &modelPath = "");
    const entt::entity createScene(const float &cameraFOV = 45.0f,
                                   const ktm::fvec3 &cameraPos = {0.0f, 0.0f, 0.0f},
                                   const ktm::fvec3 &cameraForward = {0.0f, 0.0f, 0.0f},
                                   const ktm::fvec3 &cameraWorldUp = {0.0f, 0.0f, 0.0f},
                                   const ktm::fvec3 &sunLightDirection = {0.0f, 0.0f, 0.0f});
};