cmake_minimum_required(VERSION 3.28.1)
project(poppop CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets)
find_package(KF5WindowSystem)

add_executable(poppop 
                  popup.ui
                  video.ui
                  window_frame.h
                  video_frame.h
                  window_manager.h
                  window_frame.cc
                  video_frame.cc
                  window_manager.cc
                  main.cc
                  )

target_link_libraries(poppop PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets KF5::WindowSystem)
