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


