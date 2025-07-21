 #pragma once

 #include <algorithm>
 #include <set>
 #include <string>
 #include <unordered_map>
 #include <vector>

 #include <cstdint>
 #include <filesystem>
 #include <fstream>
 #include <iostream>
 #include <regex>
 #include <sstream>

 #include <ktm/ktm.h>


 struct CabbageFramework
 {
     CabbageFramework() = delete;
     ~CabbageFramework() = delete;

     struct Actor;
     struct Scene;

     struct Actor
     {
       public:
         Actor(Scene &scene, std::string path = "");
         ~Actor();

         void move(float pos[3]);
         void rotate(float euler[3]);
         void scale(float size[3]);

         void setWorldMatrix(const float pose[16]);
         float getWorldMatrix() const;

         void setMeshShape(std::string path);
         void setSkeletalAnimation(std::string path);

         bool detectCollision(const Actor& other);

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
       public:
         Scene(void *surface = nullptr, bool lightField = false);
         ~Scene();

         void setCamera(float camera[4]);
         void setSunDirection(float direction);
         void setDisplaySurface(void *surface);

         Actor &detectActorByRay(float origin[3], float dir[3]);

         friend Actor; 
         const uint64_t sceneID;
     };
 };