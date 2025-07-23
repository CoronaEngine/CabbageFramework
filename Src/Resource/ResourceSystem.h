#pragma once

#include <assimp/Importer.hpp>
#include <concurrencpp/concurrencpp.h>
#include <stb_image.h>

class ResourceSystem
{
  public:
    static ResourceSystem &get();

  private:
    ResourceSystem();

    Assimp::Importer importer;
    concurrencpp::thread_pool_executor executor;

  public:
    const aiScene *loadScene(const std::string &path);
    const stbi_uc *loadTexture(const std::string &path);
    const aiScene *loadModel(const std::string &path);
    const aiScene *loadAnimation(const std::string &path);

    void mainloop();
};