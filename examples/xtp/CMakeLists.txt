cmake_minimum_required(VERSION 3.19.2)

project(xtp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH}) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})

if (UNIX)
    set(LIB_PATH ${CMAKE_SOURCE_DIR}/deps/xtp/linux_glibc_2.12)
    set(QUOTE_LIB_NAME libxtpquoteapi.so)
    set(TRADER_LIB_NAME libxtptraderapi.so)
endif()

if (WIN32)
    set(LIB_PATH ${CMAKE_SOURCE_DIR}/deps/xtp/win32/dll)
    set(QUOTE_LIB_NAME xtpquoteapi.lib)
    set(TRADER_LIB_NAME xtptraderapi.lib)
endif()
    
if (APPLE)
endif()
    
if (MINGW)
endif()

#-----------------------------------------------------------

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/deps/xtp/include)

link_directories(${LIB_PATH})

add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# example: cp /home/he/src/github/hanjingo/broker/deps/xtp/linux_glibc_2.12/libxtpquoteapi.so /home/he/src/github/hanjingo/broker/bin/
# example: copy D:\\src\\broker\\deps\\xtp\\win32\\dll\xtpquoteapi.dll D:\\src\\broker\\bin
file(COPY ${LIB_PATH}/${QUOTE_LIB_NAME} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY ${LIB_PATH}/${TRADER_LIB_NAME} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

target_link_libraries(${PROJECT_NAME}
    ${QUOTE_LIB_NAME}
    ${TRADER_LIB_NAME})