cmake_minimum_required(VERSION 3.5)

project(qt_cpp_advanced_ui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/libvlcpp)

set(VLC_ROOT D:/software/vlc-3.0.20)
include_directories(${VLC_ROOT}/sdk/include)

add_executable(qt_cpp_advanced_ui
  main.cpp
  mainwindow.cpp
  mainwindow.h
  title_bar.cpp
  title_bar.h
  settings.cpp
  settings.h
  side_bar.cpp
  side_bar.h
  content_page.cpp
  content_page.h
  layout_helper.h
  avatar.cpp
  avatar.h
  audio_item.cpp
  audio_item.h
  play_controller.cpp
  play_controller.h
  rotate_cover.cpp
  rotate_cover.h
  slider.cpp
  slider.h
  circle_button.cpp
  circle_button.h
  volume_controller.cpp
  volume_controller.h
  mediaplayer.cpp
  mediaplayer.h

  res.qrc
)

target_link_directories(qt_cpp_advanced_ui PRIVATE ${VLC_ROOT}/sdk/lib)

target_link_libraries(qt_cpp_advanced_ui PRIVATE Qt5::Widgets libvlc libvlccore)

add_custom_command(TARGET qt_cpp_advanced_ui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/resources/music/A_Little_Story.mp3" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "${VLC_ROOT}/libvlc.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "${VLC_ROOT}/libvlccore.dll" "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${VLC_ROOT}/plugins" "${CMAKE_BINARY_DIR}/plugins"
    )
