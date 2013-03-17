project(integration)

cmake_minimum_required(VERSION 2.8)

find_package(Boost)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" ${CMAKE_SOURCE_DIR})

add_executable(integration main.cpp serie.cpp integrali/integralebase.cpp
integrali/integraledeterministico.cpp integrali/integralemc.cpp)

target_link_libraries(integration  ${Boost_LIBRARIES})

install(TARGETS integration RUNTIME DESTINATION bin)
