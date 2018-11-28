cmake_minimum_required(VERSION 3.10)
set(base_SRC Timestamp.cpp Exception.cpp CurrentThread.cpp Thread.cpp)

add_library(muduo_base ${base_SRC})
target_link_libraries(muduo_base pthread rt)

install(TARGETS muduo_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/muduo/base)
