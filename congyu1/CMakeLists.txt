cmake_minimum_required(VERSION 3.16)

project(congyu VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Multimedia
    MultimediaWidgets
)

qt_standard_project_setup()

set(SOURCES
    main.cpp

    mainwindow.h
    mainwindow.cpp

    animatedbutton.h
    animatedbutton.cpp

    cardwidget.h
    cardwidget.cpp

    gamewindow.h
    gamewindow.cpp

    settingsdialog.h
    settingsdialog.cpp
)

qt_add_executable(congyu
    ${SOURCES}
)

target_link_libraries(congyu PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

# 自动复制资源目录到 exe 同级目录
add_custom_command(TARGET congyu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:congyu>/res
)
