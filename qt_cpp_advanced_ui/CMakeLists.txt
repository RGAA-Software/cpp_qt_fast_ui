cmake_minimum_required(VERSION 3.5)

project(qt_cpp_advanced_ui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

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

  res.qrc
)

target_link_libraries(qt_cpp_advanced_ui PRIVATE Qt5::Widgets)
