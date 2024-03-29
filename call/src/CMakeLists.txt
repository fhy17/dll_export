﻿# CMakeList.txt: dynamic_lib 项目文件

project(call VERSION 1.0.0.0)

# set output oath of library
# set(RUNTIME_DIR ${PROJECT_ROOT_DIR}/bin)

add_definitions(-DBASE_TEMPLATE)

# add include directory
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/export/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/dir_opt/include
)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

# message(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(
	${CMAKE_SOURCE_DIR}/lib
)

if(MSVC)
    set(VERSIONINFO_RC "${PROJECT_SOURCE_DIR}/version_info.rc")
    configure_file("${PROJECT_SOURCE_DIR}/version_info.rc.in" "${VERSIONINFO_RC}")
endif()

# add source to this project's library dll
# add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${VERSIONINFO_RC})
add_executable(${PROJECT_NAME} ${SRC_LIST} ${VERSIONINFO_RC})

target_link_libraries(${PROJECT_NAME} dir_opt)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})