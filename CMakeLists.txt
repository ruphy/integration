project(integration)

cmake_minimum_required(VERSION 2.6)

set(modules/gauss.c modules/ranlxd.c modules/ranlxs.c  modules/start.c  modules/utils.c OTHER_FILES)

add_executable(integration ${OTHER_FILES}
main.cpp serie.cpp integraledeterministico.cpp
integralemc.cpp)

install(TARGETS integration RUNTIME DESTINATION bin)
