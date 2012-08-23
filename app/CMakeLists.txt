add_subdirectory(client)

if(APPLE OR WIN32)
    add_subdirectory(twiddly)
endif()