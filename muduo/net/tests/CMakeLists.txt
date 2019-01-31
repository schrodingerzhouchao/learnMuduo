cmake_minimum_required(VERSION 3.10)

add_executable(reactor_test01 Reactor_test01.cpp)
target_link_libraries(reactor_test01 muduo_net muduo_base pthread)

add_executable(reactor_test02 Reactor_test02.cpp)
target_link_libraries(reactor_test02 muduo_net muduo_base pthread)

add_executable(reactor_test03 Reactor_test03.cpp)
target_link_libraries(reactor_test03 muduo_net muduo_base pthread)