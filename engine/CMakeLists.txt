#project config
set(ProjectName "engine")
set(ProjectVersion "0.1.0")
#cmake config
cmake_minimum_required(VERSION 3.7)
project(${ProjectName} VERSION ${ProjectVersion})
##format the vs project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectName})

#set source
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/../glm/)
link_directories(${PROJECT_SOURCE_DIR}/libs/)
#linking
add_executable(${ProjectName} src/main.cpp)
target_link_libraries(${ProjectName} glew32)
target_link_libraries(${ProjectName} glfw3dll)
target_link_libraries(${ProjectName} opengl32)
#ctest
enable_testing()
include(CTest)
include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#post


set_property(TARGET ${ProjectName} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${ProjectName}>)
add_custom_command(
    TARGET ${ProjectName} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/libs/ $<TARGET_FILE_DIR:${ProjectName}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${ProjectName}>
    COMMENT "Copying libs and res" VERBATIM)
