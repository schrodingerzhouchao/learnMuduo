# Install script for directory: /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/build/libmuduo_base.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Timestamp.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Atomic.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Condition.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/copyable.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/CountDownLatch.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/CurrentThread.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Date.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Exception.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Mutex.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/noncopyable.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Thread.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/ThreadPool.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/TimeZone.h"
    "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/source/Types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
