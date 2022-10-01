#[[
### 配置须知
- 需要设置下面的path环境变量，否则无法正常运行
- Path=
  C:\IDE\compiler\QT\5.9.6\mingw53_32\bin\;
  C:\IDE\compiler\QT\5.9.6\mingw53_32\lib\;
  C:\IDE\compiler\QT\Tools\mingw530_32\bin\;
  C:\IDE\compiler\QT\Tools\mingw530_32\lib\;
- 配置UIC和Qt Designer两个外部执行工具(非必要)，详情参考下面链接的文章
  https://www.cnblogs.com/ubuntu1987/p/12651866.html
]]
cmake_minimum_required(VERSION 3.23)
project(QtExample)

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
# 指定c++的版本
set(CMAKE_CXX_STANDARD 11)
# 自动使用下面的工具
set(CMAKE_AUTOMOC ON)
# 自动解析静态资源文件
set(CMAKE_AUTORCC ON)
# 自动解析.ui文件为C++文件
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "-mwindows")
# 指定qt的环境目录
set(CMAKE_PREFIX_PATH "C:/IDE/compiler/QT/5.9.6/mingw53_32")

# 必须要查找到了相应的模块，才能使用下面的函数
find_package(
        Qt5
        REQUIRED
        COMPONENTS
        Core
        Gui
        Widgets
)
set(QRC_SOURCE_FILES imageResource.qrc)

qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})
# 添加指定的源文件
add_executable(
        ${PROJECT_NAME}
        main.cpp
        ${QRC_FILES}
        mainwindow.cpp
        mainwindow.h
)
# 链接指定的库
target_link_libraries(
        ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
#指定qt5使用的模块
qt5_use_modules(${PROJECT_NAME} Core Widgets Gui)


if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
