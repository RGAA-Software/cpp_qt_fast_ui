cmake_minimum_required(VERSION 3.5)

project(qt_cpp_advanced_ui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
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
)

target_link_libraries(qt_cpp_advanced_ui PRIVATE Qt5::Widgets)
