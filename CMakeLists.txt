cmake_minimum_required(VERSION 3.0)
project(trts)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(SDL sdl)

file(GLOB COMMON_SOURCES "src/common/*.cpp")
file(GLOB LOBBY_SOURCES "src/lobby/*.cpp")
file(GLOB GAME_SOURCES "src/game/*.cpp")
file(GLOB UI_SOURCES "src/ui/*.cpp")
file(GLOB IO_SOURCES "src/io/*.cpp")

add_executable(trts ${IO_SOURCES} ${LOBBY_SOURCES})
target_include_directories(trts PRIVATE
        ${PROJECT_SOURCE_DIR}/include/lobby
        ${PROJECT_SOURCE_DIR}/include/io
        ${GTKMM_INCLUDE_DIRS})

add_executable(ui ${COMMON_SOURCES} ${IO_SOURCES} ${UI_SOURCES})
target_include_directories(ui PRIVATE
        ${PROJECT_SOURCE_DIR}/include/ui
        ${PROJECT_SOURCE_DIR}/include/io
        ${PROJECT_SOURCE_DIR}/include/common
        ${SDL_INCLUDE_DIRS})


add_executable(game ${COMMON_SOURCES} ${IO_SOURCES} ${GAME_SOURCES})
target_include_directories(game PRIVATE
        ${PROJECT_SOURCE_DIR}/include/game
        ${PROJECT_SOURCE_DIR}/include/io
        ${PROJECT_SOURCE_DIR}/include/common)


link_directories(${GTKMM_LIBRARY_DIRS})
target_link_libraries(trts ${GTKMM_LIBRARIES})
target_link_libraries(ui ${SDL_LIBRARIES})
