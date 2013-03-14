project(integration)

add_executable(integration
main.cpp serie.cpp integraledeterministico.cpp)

install(TARGETS integration RUNTIME DESTINATION bin)
