add_library(async SHARED SPSCBoundedQueue.cpp)
target_link_libraries(async PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
