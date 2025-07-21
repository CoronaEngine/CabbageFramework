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

         void move(ktm::fvec3 pos);
         void rotate(ktm::fvec3 euler);
         void scale(ktm::fvec3 size);

         void setWorldMatrix(const ktm::fmat4x4 &pose);
         ktm::fmat4x4 getWorldMatrix() const;

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

       private:
         friend Scene;
         uint64_t actorID;
     };

     struct Scene
     {
       public:
         Scene(void *surface = nullptr, bool lightField = false);
         ~Scene();

         void setCamera(const ktm::fvec3 &pos, const ktm::fvec3 &forward, const ktm::fvec3 &worldUp, const float& fov);
         void setSunDirection(ktm::fvec3 direction);
         void setDisplaySurface(void *surface);

         Actor& detectActorByRay(ktm::fvec3 origin, ktm::fvec3 dir);

       private:
         friend Actor; 
         uint64_t sceneID;
     };
 };