project(integration)

set(MODULES_FILES modules/*.c)

add_executable(integration MODULES_FILES
main.cpp serie.cpp integraledeterministico.cpp)

install(TARGETS integration RUNTIME DESTINATION bin)
