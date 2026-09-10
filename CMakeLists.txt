cmake_minimum_required(VERSION 3.16)

project(MeetingGrid VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# MSVC 下强制源码按 UTF-8 解释，保证中文字符串正确
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ---------------------------------------------------------------------------
# Qt 6 定位（解决 CMakeSettings x64-Release 漏配 CMAKE_PREFIX_PATH 导致的
# "find_package(Qt6 ...) 失败"；三种来源均可）
#   优先级：-DCMAKE_PREFIX_PATH / -DQt6_DIR 参数 > 环境变量 QTDIR > 常见默认路径
# ---------------------------------------------------------------------------
if(NOT CMAKE_PREFIX_PATH AND NOT Qt6_DIR)
    if(DEFINED ENV{QTDIR} AND EXISTS "$ENV{QTDIR}/lib/cmake/Qt6")
        set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")
    elseif(EXISTS "C:/Qt/6.11.1/msvc2022_64/lib/cmake/Qt6")
        set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/msvc2022_64")
    elseif(EXISTS "D:/Qt/6.10.3/msvc2022_64/lib/cmake/Qt6")
        set(CMAKE_PREFIX_PATH "D:/Qt/6.10.3/msvc2022_64")
    else()
        message(FATAL_ERROR
            "未找到 Qt6 CMake 配置（find_package 前自动探测失败）。\n"
            "请指定 Qt 安装目录后重试，例如：\n"
            "  cmake -S . -B build -DCMAKE_PREFIX_PATH=C:/Qt/6.11.1/msvc2022_64\n"
            "或设置环境变量 QTDIR=C:/Qt/6.11.1/msvc2022_64 后重新配置。")
    endif()
endif()
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Multimedia WebSockets)

# ---------------------------------------------------------------------------
# 客户端（GUI）
# ---------------------------------------------------------------------------
qt_add_executable(MeetingGrid WIN32
    src/main.cpp
    src/GridManager.h    src/GridManager.cpp
    src/IconFactory.h    src/IconFactory.cpp
    src/VideoTile.h      src/VideoTile.cpp
    src/VideoSource.h    src/VideoSource.cpp
    src/AudioSource.h    src/AudioSource.cpp
    src/ControlButton.h  src/ControlButton.cpp
    src/GridContainer.h  src/GridContainer.cpp
    src/MainWindow.h     src/MainWindow.cpp
    src/SignalingClient.h src/SignalingClient.cpp
)

target_include_directories(MeetingGrid PRIVATE server)
target_link_libraries(MeetingGrid PRIVATE Qt6::Widgets Qt6::Multimedia Qt6::WebSockets)

# ---------------------------------------------------------------------------
# 单元测试
# ---------------------------------------------------------------------------
enable_testing()
find_package(Qt6 QUIET COMPONENTS Test)
if(Qt6Test_FOUND)
    qt_add_executable(gridtest
        tests/tst_gridmanager.cpp
        src/GridManager.h
        src/GridManager.cpp
    )
    target_include_directories(gridtest PRIVATE src)
    target_link_libraries(gridtest PRIVATE Qt6::Test Qt6::Core)
    add_test(NAME gridtest COMMAND gridtest)

    # 信令集成测试：进程内直连 SignalingServer + SignalingClient
    qt_add_executable(signalingtest
        tests/tst_signalingclient.cpp
        src/SignalingClient.h    src/SignalingClient.cpp
        server/SignalingServer.h server/SignalingServer.cpp
        server/protocol.h
    )
    target_include_directories(signalingtest PRIVATE src server)
    target_link_libraries(signalingtest PRIVATE Qt6::Test Qt6::Core Qt6::Network Qt6::WebSockets)
    add_test(NAME signalingtest COMMAND signalingtest)
endif()

# ---------------------------------------------------------------------------
# 信令服务端（联网会议地基）
# ---------------------------------------------------------------------------
option(BUILD_SERVER "Build the WebSocket signaling server" ON)
if(BUILD_SERVER)
    add_subdirectory(server)
endif()

# ---------------------------------------------------------------------------
# 统一运行产物目录：build/bin/<CONFIG>（便于测试、部署与多配置共存）
# ---------------------------------------------------------------------------
foreach(tgt MeetingGrid gridtest signalingtest)
    if(TARGET ${tgt})
        set_target_properties(${tgt} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
    endif()
endforeach()
if(TARGET MeetingGridServer)
    set_target_properties(MeetingGridServer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
endif()

# ---------------------------------------------------------------------------
# 安装与部署说明
#   1) install(TARGETS ...) 只安装可执行文件；
#   2) Qt 运行库/插件由 deploy.bat 在安装后用 windeployqt 部署到同目录
#      （Qt 官方 qt_generate_deploy_app_script 在该工程路径中文目录下不可靠，
#       改用 windeployqt，兼容 Qt5/Qt6）。
# 产物目录：out/deploy/<CONFIG>/bin（见 deploy.bat）
# ---------------------------------------------------------------------------
include(GNUInstallDirs)
install(TARGETS MeetingGrid RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(TARGET MeetingGridServer)
    install(TARGETS MeetingGridServer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
