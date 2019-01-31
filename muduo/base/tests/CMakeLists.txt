cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -rdynamic")
message(STATUS,"CXXFLAGS: ${CMAKE_CXX_FLAGS}")

add_executable(exception_test Exception_test.cpp)
target_link_libraries(exception_test muduo_base)

add_executable(atomic_unittest Atomic_unittest.cpp)
target_link_libraries(atomic_unittest muduo_base)

add_executable(thread_test Thread_test.cpp)
target_link_libraries(thread_test muduo_base pthread)

add_executable(mutex_test Mutex_test.cpp)
target_link_libraries(mutex_test muduo_base pthread)

add_executable(blockingqueue_test BlockingQueue_test.cpp)
target_link_libraries(blockingqueue_test muduo_base pthread)

add_executable(blockingqueue_bench BlockingQueue_bench.cpp)
target_link_libraries(blockingqueue_bench muduo_base pthread)

add_executable(boundedblockingqueue_test BoundedBlockingQueue_test.cpp)
target_link_libraries(boundedblockingqueue_test muduo_base pthread)

add_executable(threadpool_test ThreadPool_test.cpp)
target_link_libraries(threadpool_test muduo_base pthread)

add_executable(singleton_test Singleton_test.cpp)
target_link_libraries(singleton_test muduo_base pthread)

add_executable(pthonce_test pthonce_test.cpp)
target_link_libraries(pthonce_test pthread)


add_executable(pthkey_test pthkey_test.cpp)
target_link_libraries(pthkey_test pthread)

add_executable(threadlocal_test ThreadLocal_test.cpp)
target_link_libraries(threadlocal_test muduo_base pthread)

add_executable(threadlocalsingleton_test ThreadLocalSingleton_test.cpp)
target_link_libraries(threadlocalsingleton_test muduo_base pthread)

add_executable(log_test1 Log_test1.cpp)
target_link_libraries(log_test1 muduo_base pthread)

add_executable(PtrToBool PtrToBool.cpp)

add_executable(Date_test Date_test.cpp)
target_link_libraries(Date_test muduo_base)

add_executable(convert_order convert_order.cpp)

add_executable(TimeZone_unittest TimeZone_unittest.cpp)
target_link_libraries(TimeZone_unittest muduo_base)

add_executable(backtrace_test backtrace_test.cpp)

add_executable(currthd_stacktrace_test currthd_stacktrace_test.cpp)
target_link_libraries(currthd_stacktrace_test muduo_base)

