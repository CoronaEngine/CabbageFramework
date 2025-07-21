#pragma once

#include <string>
#include <cstdint>

struct CabbageFramework
{
    CabbageFramework() = delete;
    ~CabbageFramework() = delete;

    struct Actor;
    struct Scene;

    struct Actor
    {
        Actor(Scene &scene, std::string path = "");
        ~Actor();

        void move(float pos[3]);
        void rotate(float euler[3]);
        void scale(float size[3]);

        void setWorldMatrix(const float pose[4][4]);
        float* getWorldMatrix() const;

        void setMeshShape(std::string path);
        void setSkeletalAnimation(std::string path);

        bool detectCollision(const Actor &other);

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

        friend Scene;
        const uint64_t actorID;
    };

    struct Scene
    {
        Scene(void *surface = nullptr, bool lightField = false);
        ~Scene();

        void setCamera(const float pos[3], const float forward[3], const float worldup[3], const float fov);
        void setSunDirection(float direction[3]);
        void setDisplaySurface(void *surface);

        Actor &detectActorByRay(float origin[3], float dir[3]);

        friend Actor;
        const uint64_t sceneID;
    };
};