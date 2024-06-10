aux_source_directory(. SRC_LIST)
# set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcheader.pb.cc rpcprovider.cc mprpcchannel.cc)
# add_library(mprpc SHARED ${SRC_LIST}) # 生成动态库
add_library(mprpc ${SRC_LIST}) # 生成静态库
target_link_libraries(mprpc mymuduo pthread zookeeper_mt) # muduo生成的是静态库，