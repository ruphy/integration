project(integration)

cmake_minimum_required(VERSION 2.8)

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
src/pathint/pathint.cpp
)

target_link_libraries(integration ${Boost_LIBRARIES} gmp)

install(TARGETS integration RUNTIME DESTINATION bin)

