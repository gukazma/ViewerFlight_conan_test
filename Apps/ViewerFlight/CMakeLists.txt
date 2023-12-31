# 查找 Qt 包信息备用
set(TARGET_NAME ViewerFlight)

if (MSVC)
  find_package(Qt5 COMPONENTS Core Widgets Gui CONFIG REQUIRED)
else ()
  find_package(Qt6 COMPONENTS Core Widgets Gui CONFIG REQUIRED)
endif ()
# 开启 MOC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(OpenSceneGraph 2.0.0 REQUIRED osg osgViewer osgDB osgUtil osgGA)
find_package(osgearth)

# 扫描当前源代码文件列表

file(GLOB_RECURSE CPP_HEAD_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE CPP_SOUCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE UI_SOUCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
set(OSGQT_HEAD 
${CMAKE_CURRENT_SOURCE_DIR}/Vendors/osgQt/osgQOpenGL/osgQOpenGLWidget
${CMAKE_CURRENT_SOURCE_DIR}/Vendors/osgQt/osgQOpenGL/osgQOpenGLWindow
${CMAKE_CURRENT_SOURCE_DIR}/Vendors/osgQt/osgQOpenGL/OSGRenderer
)
QT5_WRAP_CPP(MOC_SOURCES ${OSGQT_HEAD})


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CPP_HEAD_FILES} ${CPP_SOUCE_FILES} ${OSGQT_HEAD})

add_executable(${TARGET_NAME} ${CPP_HEAD_FILES} ${CPP_SOUCE_FILES} ${UI_SOUCE_FILES} ${MOC_SOURCES} ${OSGQT_HEAD})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Apps)
# 链接 Conan 指向的 Qt 库文件
message("${OSGEARTH_LIBRARIES} ****************************8")
target_link_libraries(${TARGET_NAME} PRIVATE
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::OpenGL
${OPENSCENEGRAPH_LIBRARIES}
CONAN_PKG::osgearth
)
target_include_directories(${TARGET_NAME} PRIVATE
${CMAKE_CURRENT_LIST_DIR}/Vendors/osgQt
${OPENSCENEGRAPH_INCLUDE_DIRS}
)


find_program(DEPLOYQT_EXECUTABLE windeployqt)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${DEPLOYQT_EXECUTABLE} ${CMAKE_BINARY_DIR}/bin/${TARGET_NAME}.exe
  COMMENT "Deploying qt dependencies after build..."
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
