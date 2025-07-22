#pragma once

#include <CabbageDisplayer.h>
#include <entt/entt.hpp>
#include <ktm/ktm.h>

struct ActorPoseComponent
{
    ktm::fvec3 transform = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 rotate = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 scale = ktm::fvec3(1.0f, 1.0f, 1.0f);

    ktm::fvec3 aabbMinXYZ = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 aabbMaxXYZ = ktm::fvec3(0.0f, 0.0f, 0.0f);
};

struct BoneMatrixHostComponent
{
    std::vector<ktm::fmat4x4> matrices;
};

struct BoneMatrixDeviceComponent
{
    HardwareBuffer matrices;
};

struct ImageHostComponent
{
    std::string path;            ///< 纹理文件路径
    unsigned char *data;         ///< 纹理数据指针
    int width, height, channels; ///< 纹理宽、高、通道数
};

struct ImageDeviceComponent
{
    HardwareImage image;
};

struct MaterialParamsComponent
{
    ktm::fvec3 baseColor;
    float roughness;
    float metallic;
    float specular;
    float transmission;
};

struct MeshHostComponent
{
    std::vector<uint32_t> indices;
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<uint32_t> boneIndices;
    std::vector<float> boneWeights;
};

struct MaterialComponent
{
    entt::entity material;
};

struct MeshDeviceComponent
{
    HardwareBuffer indicesBuffer;
    HardwareBuffer positionsBuffer;
    HardwareBuffer normalsBuffer;
    HardwareBuffer texCoordsBuffer;
    HardwareBuffer boneIndicesBuffer;
    HardwareBuffer boneWeightsBuffer;
};

struct BaseColorTextureComponent
{
    entt::entity texture;
};

struct NormalTextureComponent
{
    entt::entity texture;
};

struct OpacityTextureComponent
{
    entt::entity texture;
};

struct MeshesComponent
{
    std::vector<entt::entity> meshes;
    std::string path;
};

struct CameraComponent
{
    float fov = 45.0f;
    ktm::fvec3 pos = ktm::fvec3(1.0f, 1.0f, 1.0f);
    ktm::fvec3 forward = ktm::fvec3(-1.0f, -1.0f, -1.0f);
    ktm::fvec3 worldUp = ktm::fvec3(0.0f, 1.0f, 0.0f);
};

struct SunLightComponent
{
    ktm::fvec3 direction;
};

struct ActorsComponent
{
    std::vector<entt::entity> actors;
};

struct ModelComponent
{
    entt::entity model;
};