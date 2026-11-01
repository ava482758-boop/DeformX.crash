cmake_minimum_required(VERSION 3.16)
project(DeformX_crash CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(${RAYLIB_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(DeformX.crash MACOSX_BUNDLE ${SOURCES})

# 链接我们手动编译出来的静态库
target_link_libraries(DeformX.crash ${RAYLIB_LIBRARIES})

# 链接 iOS 系统必需的框架（Metal、音频等）
target_link_libraries(DeformX.crash
    "-framework Metal"
    "-framework MetalKit"
    "-framework UIKit"
    "-framework CoreGraphics"
    "-framework Foundation"
    "-framework OpenGLES"
    "-framework AVFoundation"
    "-framework CoreAudio"
    "-framework CoreVideo"
    "-framework IOKit"
    "-framework QuartzCore"
)

set_target_properties(DeformX.crash PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "DeformX.crash"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.deformx"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)
