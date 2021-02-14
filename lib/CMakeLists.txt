file(GLOB SOURCES "*.cc")
include_directories(inc)
add_library(chip8lib SHARED ${SOURCES})
target_link_libraries(chip8lib ${CURSES_LIBRARIES})

