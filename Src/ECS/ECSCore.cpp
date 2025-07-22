#include "ECSCore.h"
#include "Components.h"

ECSCore &ECSCore::get()
{
    static ECSCore instance;
    return instance;
}

const entt::entity ECSCore::createTexture(const std::string &texturePath)
{
    entt::entity texture = registry.create();
    registry.emplace<ImageDeviceComponent>(texture, ImageDeviceComponent{});
    registry.emplace<ImageHostComponent>(texture, ImageHostComponent{.path = texturePath});
    return texture;
}

const entt::entity ECSCore::createMaterial(const entt::entity &baseColorTexture)
{
    entt::entity material = registry.create();
    registry.emplace<MaterialParamsComponent>(material, MaterialParamsComponent{});
    registry.emplace<BaseColorTextureComponent>(material, BaseColorTextureComponent{.texture = baseColorTexture});
    return material;
}

const entt::entity ECSCore::createMesh(const entt::entity &material,
                                       const entt::entity &normalTexture,
                                       const entt::entity &OpacityTexture)
{
    entt::entity mesh = registry.create();
    registry.emplace<MeshHostComponent>(mesh, MeshHostComponent{});
    registry.emplace<MeshDeviceComponent>(mesh, MeshDeviceComponent{});
    registry.emplace<MaterialComponent>(mesh, MaterialComponent{.material = material});
    registry.emplace<NormalTextureComponent>(mesh, NormalTextureComponent{.texture = normalTexture});
    registry.emplace<OpacityTextureComponent>(mesh, OpacityTextureComponent{.texture = OpacityTexture});
    return mesh;
}

const entt::entity ECSCore::createActor(const ktm::fvec3 &transform,
                                        const ktm::fvec3 &rotate,
                                        const ktm::fvec3 &scale,
                                        const std::string &modelPath)
{
    entt::entity actor = registry.create();
    registry.emplace<ActorPoseComponent>(actor, ActorPoseComponent{
                                                    .transform = transform,
                                                    .rotate = rotate,
                                                    .scale = scale});
    registry.emplace<BoneMatrixHostComponent>(actor, BoneMatrixHostComponent{});
    registry.emplace<BoneMatrixDeviceComponent>(actor, BoneMatrixDeviceComponent{});
    registry.emplace<MeshesComponent>(actor, MeshesComponent{.path = modelPath});
    return actor;
}

const entt::entity ECSCore::createScene(const float &cameraFOV,
                                        const ktm::fvec3 &cameraPos,
                                        const ktm::fvec3 &cameraForward,
                                        const ktm::fvec3 &cameraWorldUp,
                                        const ktm::fvec3 &sunLightDirection)
{
    entt::entity scene = registry.create();
    registry.emplace<CameraComponent>(scene, CameraComponent{
                                                 .fov = cameraFOV,
                                                 .pos = cameraPos,
                                                 .forward = cameraForward,
                                                 .worldUp = cameraWorldUp});
    registry.emplace<SunLightComponent>(scene, SunLightComponent{.direction = sunLightDirection});
    registry.emplace<ActorsComponent>(scene, ActorsComponent{});
    return scene;
}