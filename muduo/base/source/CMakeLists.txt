cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -rdynamic -g -lrt")
message(STATUS,"CXXFLAGS: ${CMAKE_CXX_FLAGS}")

set(base_SRC 
    Timestamp.cpp 
    Exception.cpp 
    CurrentThread.cpp 
    Thread.cpp 
    Condition.cpp 
    CountDownLatch.cpp
    ThreadPool.cpp
    #LogStream.cpp
    #Logging.cpp
    Date.cpp
    TimeZone.cpp
    )

add_library(muduo_base ${base_SRC})
target_link_libraries(muduo_base pthread rt)

install(TARGETS muduo_base DESTINATION lib)
#file(GLOB HEADERS "*.h")
set(HEADERS
    Timestamp.h
    Atomic.h
    Condition.h
    copyable.h
    CountDownLatch.h
    CurrentThread.h
    Date.h
    Exception.h
    Mutex.h
    noncopyable.h
    Thread.h
    ThreadPool.h
    TimeZone.h
    Types.h)
install(FILES ${HEADERS} DESTINATION include/muduo/base)
