cmake_minimum_required(VERSION 3.28)
project(YOBADesktopDemo LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# YOBADesktopDemo
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/Theme.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Resources (fonts, images, etc.)
file(GLOB_RECURSE RESOURCE_FILES "resources/*")

foreach(RESOURCE_FILE ${RESOURCE_FILES})
  file(RELATIVE_PATH RESOURCE_FILE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${RESOURCE_FILE}")

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${RESOURCE_FILE}"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/${RESOURCE_FILE_RELATIVE_PATH}"
  )
endforeach()

# SFML
include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.1.0
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable(SFML)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

# YOBA
add_subdirectory(lib/YOBA)
target_link_libraries(${PROJECT_NAME} PRIVATE YOBA)