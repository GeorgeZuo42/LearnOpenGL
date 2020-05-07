cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
file(GLOB MY_DLL ${PROJECT_SOURCE_DIR}/lib/*.dll)
foreach(dll IN LISTS MY_DLL)
    message("Copy ${dll}")
endforeach()

file(COPY ${MY_DLL} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

include_directories(${PROJECT_SOURCE_DIR}/include/)
link_directories(${PROJECT_SOURCE_DIR}/lib/)
add_executable(engine main.cpp)

target_link_libraries(engine glew32)
target_link_libraries(engine glfw3dll)
target_link_libraries(engine opengl32)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
