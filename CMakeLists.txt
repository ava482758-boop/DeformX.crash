cmake_minimum_required(VERSION 3.16)
project(DeformX_crash CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(DeformX.crash MACOSX_BUNDLE ${SOURCES})

target_link_libraries(DeformX.crash raylib)

set_target_properties(DeformX.crash PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "DeformX.crash"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.deformx"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)