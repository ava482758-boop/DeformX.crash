cmake_minimum_required(VERSION 3.16)
project(DeformX_crash CXX)

set(CMAKE_CXX_STANDARD 17)

# 暴力搜索 raylib 的头文件路径
include_directories(src)
include_directories(${raylib_DIR}/../../src)
include_directories(${raylib_DIR}/../../../src)
include_directories(${raylib_DIR}/../../../../src)

file(GLOB SOURCES "src/*.cpp")

add_executable(DeformX.crash MACOSX_BUNDLE ${SOURCES})

# 找到生成的 .a 静态库并链接
find_library(RAYLIB_LIB raylib PATHS ${raylib_DIR} NO_DEFAULT_PATH)
if(NOT RAYLIB_LIB)
    # 如果找不到，就用常规方式
    find_package(raylib REQUIRED)
    target_link_libraries(DeformX.crash raylib)
else()
    target_link_libraries(DeformX.crash ${RAYLIB_LIB})
endif()

set_target_properties(DeformX.crash PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "DeformX.crash"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.deformx"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)
