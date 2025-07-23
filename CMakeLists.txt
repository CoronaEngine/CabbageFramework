
cmake_minimum_required(VERSION 4.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(
    CabbageFramework
    VERSION 0.5.0
    HOMEPAGE_URL "https://github.com/Cabbage-Engine/CabbageEngine"
    LANGUAGES C CXX
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    option(CABBAGE_FRAMEWORK_BUILD_EXAMPLES "Build examples" ON)
else()
    option(CABBAGE_FRAMEWORK_BUILD_EXAMPLES "Build examples" OFF)
endif()

add_compile_definitions(
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    NOMINMAX
    ENTT_ID_TYPE=uint64_t # 定义 ENTT 的 ID 类型为 uint64_t
    ENTT_USE_ATOMIC # 使用 ENTT 原子操作

    $<$<CONFIG:Debug>:CABBAGE_ENGINE_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(Src)
add_subdirectory(Env/assimp EXCLUDE_FROM_ALL)
add_subdirectory(Env/CabbageDisplay EXCLUDE_FROM_ALL)
add_subdirectory(Env/entt EXCLUDE_FROM_ALL)

if(CABBAGE_FRAMEWORK_BUILD_EXAMPLES)
    add_subdirectory(Env/glfw EXCLUDE_FROM_ALL)
    add_subdirectory(Examples)
endif()