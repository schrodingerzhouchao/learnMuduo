cmake_minimum_required(VERSION 3.10)

set(net_SRC 
    EventLoop.cpp
    Channel.cpp
    Poller.cpp
    poller/DefaultPoller.cpp
    poller/EPollPoller.cpp
    )

add_library(muduo_net ${net_SRC})
target_link_libraries(muduo_net muduo_base)
install(TARGETS muduo_net DESTINATION lib)

set(HEADERS
    Channel.h
    EventLoop.h
    Poller.h
    )
install(FILES ${HEADERS} DESTINATION include/muduo/net)
