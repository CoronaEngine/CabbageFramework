file(GLOB_RECURSE EXAMPLES_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EXAMPLES_SOURCE_FILES})
add_executable(CabbageFrameworkExamples ${EXAMPLES_SOURCE_FILES})

# 设置VS启动项目
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CabbageFrameworkExamples)

set_target_properties(CabbageFrameworkExamples PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG> # 可执行文件输出路径
    PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG> # PDB 文件输出路径
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:CabbageFrameworkExamples> # VS 调试工作目录
)

target_include_directories(CabbageFrameworkExamples PRIVATE
    "${PROJECT_SOURCE_DIR}/Env/glfw/include")

target_link_libraries(CabbageFrameworkExamples PRIVATE
    glfw
    CabbageFramework
)
