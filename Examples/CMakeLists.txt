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

target_compile_options(CabbageFrameworkExamples PRIVATE
    $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fno-omit-frame-pointer -g>
    $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-ffunction-sections -fdata-sections>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:Clang>>:-Oz>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/GL>
    $<$<CXX_COMPILER_ID:MSVC>:/W1 /source-charset:utf-8 /execution-charset:utf-8>
)

target_compile_definitions(CabbageFrameworkExamples PRIVATE
    $<$<CONFIG:RelWithDebInfo>:ENABLE_DETAILED_LOGGING=1>
    $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
    $<$<CONFIG:MinSizeRel>:DISABLE_EXTRA_FEATURES=1>
    $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    NOMINMAX
)

target_link_options(CabbageFrameworkExamples PRIVATE
    $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Linux>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:LINKER:--gc-sections>
    $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Darwin>>:-dead_strip>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/LTCG;/OPT:REF;/OPT:ICF>
)

target_include_directories(CabbageFrameworkExamples PRIVATE
    "${PROJECT_SOURCE_DIR}/Env/glfw/include")

target_link_libraries(CabbageFrameworkExamples PRIVATE
    glfw
    CabbageFramework
)
