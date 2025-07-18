#pragma once

#include <algorithm>
#include <ktm/ktm.h>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "Geometry/Model.h"

#include "Animation/CabbageAnimator.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include <CabbageFramework.h>
#include <PipelineManager/ComputePipeline.h>
#include <PipelineManager/RasterizerPipeline.h>


struct CabbageEngine
{
    CabbageEngine() = delete;
    ~CabbageEngine() = delete;

    struct Actor;
    struct Scene;

    struct Actor
    {
      public:
        Actor(Scene &scene, std::string path = "");
        ~Actor();

        struct Pose
        {
            ktm::fvec3 transform = ktm::fvec3(0.0f, 0.0f, 0.0f); 
            ktm::fvec3 rotate = ktm::fvec3(0.0f, 0.0f, 0.0f); 
            ktm::fvec3 scale = ktm::fvec3(1.0f, 1.0f, 1.0f); 
        };


        struct MeshDeviceData
        {
            HardwareBuffer pointsBuffer;     
            HardwareBuffer normalsBuffer;    
            HardwareBuffer texCoordsBuffer;  
            HardwareBuffer indexBuffer;    
            HardwareBuffer boneIndexesBuffer; 
            HardwareBuffer boneWeightsBuffer;

            uint32_t materialIndex;
            uint32_t textureIndex;

            Mesh *meshData;
        };


        void move(ktm::fvec3 pos);
        void rotate(ktm::fvec3 euler);
        void scale(ktm::fvec3 size);

        void setPose(const Pose &pose);
        Pose getPose() const;

        void setMeshShape(std::string path);
        void setAnimation(std::string path);
        void updateAnimation(float deltaTime);

        void setActorMatrix(ktm::fmat4x4);
        ktm::fmat4x4 getActorMatrix() const;

        HardwareBuffer getBonesMatrixBuffer() const;
        std::vector<MeshDeviceData> getDeviceMeshes() const;

        void detectCollision();

        struct OpticsParams
        {
            bool enable;
        };
        void setOpticsParams(const OpticsParams &params);

        struct AcousticsParams
        {
            bool enable;
        };
        void setAcousticsParams(const AcousticsParams &params);

        struct MechanicsParams
        {
            bool enable;
        };
        void setMechanicsParams(const MechanicsParams &params);

      private:
        friend class PhysicalSimulator;
        friend Scene;

        ktm::fmat4x4 actorMatrix = ktm::fmat4x4::from_diag(ktm::fvec4(0.0, 0.0, 0.0, 0.0));
        std::vector<MeshDeviceData> deviceMeshes; 

        HardwareBuffer bonesMatrixBuffer;
        CabbageAnimator animator;     
        Model *model;               
        Scene &scene;                
        Pose pose;           
    };

    struct Scene
    {
      public:
        Scene(void *surface = nullptr, bool lightField = false);
        ~Scene();

        struct Camera
        {
            float fov = 45.0f;                                 
            ktm::fvec3 pos = ktm::fvec3(1.0f, 1.0f, 1.0f);       
            ktm::fvec3 forward = ktm::fvec3(-1.0f, -1.0f, -1.0f);
            ktm::fvec3 worldUp = ktm::fvec3(0.0f, 1.0f, 0.0f); 
        };

        void setCamera(const Camera &camera);
        Camera& getCamera() const;

        void setSunDirection(ktm::fvec3 direction);
        ktm::fvec3 getSunDirection() const;

        void setDisplaySurface(void *surface);
        void *getDisplaySurface() const;

        Actor *detectActorByRay(ktm::fvec3 origin, ktm::fvec3 dir);
        Actor *detectActorByScreen(ktm::uvec2 pixel);

        void setCollisionActors(const std::set<Actor *> &actors);

        void update(float deltaTime);

        std::set<Actor *> getActors() const;

      private:
        std::set<Actor *> collisionActors;
        Camera camera;    
        void *displaySurface = nullptr;   
        ktm::fvec3 sunDirection = ktm::fvec3(0.0, 1.0, 0.0); 

        friend Actor; 
        std::set<Actor *> actors; 
    };

    static std::set<Scene *> getScenes();

    static void update();

  private:
    static std::set<Scene *> scenes; 
    static std::unordered_map<std::string, HardwareImage> textureImageHash;
    static std::unordered_map<std::string, Model> modelPathHash; 
};