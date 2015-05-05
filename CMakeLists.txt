project(integration)

cmake_minimum_required(VERSION 2.8)

# if(BUILD_STATIC_EXECUTABLES)
    set(CMAKE_EXE_LINKER_FLAGS -static)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
    set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)       # remove -Wl,-Bdynamic
    set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS)
    set(CMAKE_SHARED_LIBRARY_C_FLAGS)         # remove -fPIC
    set(CMAKE_SHARED_LIBRARY_CXX_FLAGS)
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)    # remove -rdynamic
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
# else(BUILD_STATIC_EXECUTABLES)
# # Set RPATH to use for installed targets; append linker search path
#     set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LOFAR_LIBDIR}")
#     set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# endif(BUILD_STATIC_EXECUTABLES)

find_package(Boost)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" ${CMAKE_SOURCE_DIR})

add_executable(integration
main.cpp
src/serie.cpp
src/integrali/integralebase.cpp
src/integrali/integraledeterministico.cpp
src/integrali/integralemc.cpp
src/agobuffon.cpp
src/esbase.cpp
src/picalc.cpp
)

target_link_libraries(integration ${Boost_LIBRARIES} gmp)

install(TARGETS integration RUNTIME DESTINATION bin)

