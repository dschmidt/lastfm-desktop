
add_definitions( -D_LOGGER_DLLEXPORT -DLASTFM_COLLAPSE_NAMESPACE)

find_package(Threads REQUIRED)

add_library(logger SHARED ${LASTFM_SOURCE_DIR}/common/c++/Logger.cpp)
target_link_libraries(logger ${CMAKE_THREAD_LIBS_INIT})