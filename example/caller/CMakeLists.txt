# set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friend.pb.cc)
add_executable(consumer ${SRC_LIST})
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -I/usr/local/include")
# link_directories(/usr/local/lib)
# target_link_libraries(provider protobuf)
target_link_libraries(consumer mprpc protobuf)