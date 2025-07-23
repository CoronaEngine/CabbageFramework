file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
add_library(CabbageFramework STATIC ${SOURCE_FILES})

set_target_properties(CabbageFramework PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/$<CONFIG> # 静态库输出路径
)

target_include_directories(CabbageFramework PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Env/CabbageDisplayer/Src"
    "${PROJECT_SOURCE_DIR}/Env/CabbageDisplayer/Env/Helicon/Src"

    "${PROJECT_SOURCE_DIR}/Env/ktm"
    "${PROJECT_SOURCE_DIR}/Env/stb"
    "${PROJECT_SOURCE_DIR}/Env/assimp/include"
    "${PROJECT_SOURCE_DIR}/Env/entt/single_include"
)

target_link_libraries(CabbageFramework PUBLIC
    assimp
    Helicon
    EnTT::EnTT
    CabbageDisplayer
)
