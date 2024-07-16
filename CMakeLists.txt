cmake_minimum_required(VERSION 2.8.12)
project(video)

set(STRIP_EXECUTABLE "aarch64-himix210-linux-strip")
set(CMAKE_CXX_COMPILER "aarch64-himix210-linux-g++")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../out/")
set(CMAKE_CXX_FLAGS_DEBUG "-rdynamic -ldl -funwind-tables -fPIC -O0 -fstack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g -rdynamic -ldl -funwind-tables -fPIC -O0")
set(CMAKE_CXX_FLAGS "-Wno-error=deprecated-declarations -Wno-deprecated-declarations ")

# 包含当前目录下的所有 .cpp 和 .c 文件
#file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_definitions(-D__USE_MCU__)

# 包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# 链接库目录
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 链接库文件
link_libraries(dl pthread)
link_libraries(aaccomm aacdec aacenc aacsbrdec dnvqe hdmi hi_cipher hi_otp hive_AEC hive_AGC hive_ANR hive_EQ hive_HPF hive_RES hive_record)
link_libraries(hive_common ive mau mpi nnie pciv securec svpruntime tde upvqe VoiceEngine gomp)


# 生成可执行文件
add_executable(video ${SRC_LIST})

# Strip the executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                  COMMAND ${STRIP_EXECUTABLE} ${PROJECT_NAME})

# If the CMake version supports it, attach header directory information
# to the targets for when we are part of a parent build (ie being pulled
# in via add_subdirectory() rather than being a standalone build).
if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.12")
	target_include_directories(video
	PRIVATE include/internal
	PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
endif()

# 安装目标文件和目录
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../dep/res/ DESTINATION res)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../dep/lib/ DESTINATION lib)
