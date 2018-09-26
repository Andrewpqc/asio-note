
#设置项目名称
PROJECT(AsioLearn)

#要求CMake的最低版本为2.8
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#添加头文件搜索路径
INCLUDE_DIRECTORIES(/usr/local/include)

#添加库文件搜索路径
LINK_DIRECTORIES(/usr/local/lib)

#用于将当前目录下的所有源文件的名字保存在变量 DIR_SRCS 中
#AUX_SOURCE_DIRECTORY(client.cpp CLIENT_SRCS)
#AUX_SOURCE_DIRECTORY(server.cpp SERVER_SRCS)

#用于指定从一组源文件 source1 source2 … sourceN(在变量DIR_SRCS中定义)
#编译出一个可执行文件且命名为CMake_Tutorial1
ADD_EXECUTABLE(client client.cpp)
ADD_EXECUTABLE(server server.cpp)
ADD_EXECUTABLE(async_client async_client.cpp)
ADD_EXECUTABLE(async_server async_server.cpp)
ADD_EXECUTABLE(asio_sig asio_signal.cpp)
ADD_EXECUTABLE(asio_timer asio_timer.cpp)
ADD_EXECUTABLE(resolve_query resolve_query.cpp)
ADD_EXECUTABLE(async_read async_read.cpp)
ADD_EXECUTABLE(shared_from enable_shared_from_this.cpp)
ADD_EXECUTABLE(sync_echo_client echo/echo_sync_client.cpp)
ADD_EXECUTABLE(sync_echo_server echo/echo_sync_server.cpp)
ADD_EXECUTABLE(async_echo_client echo/echo_async_client.cpp)
ADD_EXECUTABLE(async_echo_server echo/echo_async_server.cpp)


#添加编译可执行程序所需要的链接库、如果有多个中间用空格隔开
#第一个参数是可执行程序名称，第二个开始是依赖库
#在这里根据名字boost_thread去寻找libboost_thread.a文件
TARGET_LINK_LIBRARIES(client pthread boost_system)
TARGET_LINK_LIBRARIES(server pthread boost_system)
TARGET_LINK_LIBRARIES(async_client pthread boost_system)
TARGET_LINK_LIBRARIES(async_server pthread boost_system)
TARGET_LINK_LIBRARIES(asio_sig pthread boost_system)
TARGET_LINK_LIBRARIES(asio_timer pthread boost_system)
TARGET_LINK_LIBRARIES(resolve_query pthread boost_system)
TARGET_LINK_LIBRARIES(async_read pthread boost_system)
TARGET_LINK_LIBRARIES(sync_echo_client pthread boost_system)
TARGET_LINK_LIBRARIES(sync_echo_server pthread boost_system)
TARGET_LINK_LIBRARIES(async_echo_client pthread boost_system)
TARGET_LINK_LIBRARIES(async_echo_server pthread boost_system)