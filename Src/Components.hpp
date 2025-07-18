#pragma once

#include <CabbageFramework.h>
#include <PipelineManager/ComputePipeline.h>
#include <PipelineManager/RasterizerPipeline.h>
#include <cstdint>
#include <ktm/ktm.h>
#include <vector>

struct ActorPoseComponent
{
    ktm::fvec3 transform = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 rotate = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 scale = ktm::fvec3(1.0f, 1.0f, 1.0f);
};

struct BoneMatrixHostComponent
{
    std::vector<ktm::fmat4x4> matrices;
};

struct BoneMatrixDeviceComponent
{
    HardwareBuffer matrices;
};

struct BoneMatrixComponent
{
    uint64_t hostID;
    uint64_t deviceID;
};

struct ImageHostComponent
{
    std::string path;              ///< 纹理文件路径
    unsigned char *data;           ///< 纹理数据指针
    int width, height, nrChannels; ///< 纹理宽、高、通道数
};

struct ImageDeviceComponent
{
    HardwareImage image;
};

struct ImageComponent
{
    uint64_t hostID;
    uint64_t deviceID;
};

struct MaterialHostComponent
{
    uint64_t baseColorTextureID;

    ktm::fvec3 roughness;
    ktm::fvec3 metallic;
    ktm::fvec3 specular;
    ktm::fvec3 transmission;
};

struct MaterialDeviceComponent
{
    uint64_t baseColorTextureID;

    ktm::fvec3 roughness;
    ktm::fvec3 metallic;
    ktm::fvec3 specular;
    ktm::fvec3 transmission;
};

struct MaterialComponent
{
    uint64_t hostID;
    uint64_t deviceID;
};

struct MeshHostComponent
{
    std::vector<uint32_t> indices;
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<uint32_t> boneIndices;
    std::vector<float> boneWeights;
    uint64_t normalTextureID;
    uint64_t opacityTextureID;
    uint64_t materialID;
};

struct MeshDeviceComponent
{
    HardwareBuffer indicesBuffer;
    HardwareBuffer positionsBuffer;
    HardwareBuffer normalsBuffer;
    HardwareBuffer texCoordsBuffer;
    HardwareBuffer boneIndicesBuffer;
    HardwareBuffer boneWeightsBuffer;
    uint64_t normalTextureID;
    uint64_t opacityTextureID;
    uint64_t materialID;
};

struct MeshComponent
{
    uint64_t hostID;
    uint64_t deviceID;
};

struct GeometryComponent
{
    ktm::fvec3 minXYZ = ktm::fvec3(0.0f, 0.0f, 0.0f);
    ktm::fvec3 maxXYZ = ktm::fvec3(0.0f, 0.0f, 0.0f);
    std::vector<uint64_t> meshesID;
    uint64_t boneMatrixID;
};