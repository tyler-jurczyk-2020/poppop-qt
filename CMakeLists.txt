cmake_minimum_required(VERSION 3.28.1)
project(poppop CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets)

qt_standard_project_setup()

qt_add_executable(poppop 
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

target_link_libraries(poppop PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)
