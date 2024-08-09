project(Chess2)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Glob all header, source, UI, and image files
file(GLOB_RECURSE CHESS_HEADERS "include/*.h")
file(GLOB_RECURSE CHESS_SOURCE "src/*.cpp")
file(GLOB_RECURSE PIECE_HEADERS "include/pieces_inc/*.h")
file(GLOB_RECURSE PIECE_SOURCE "src/pieces_src/*.cpp")
file(GLOB_RECURSE CHESS_RESOURCES "resources/ui/*.ui")
file(GLOB_RECURSE CHESS_IMAGES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "resources/art/*.png" "resources/art/*.ico")

# Add the executable
add_executable(Chess2 WIN32 ${CHESS_HEADERS} ${CHESS_SOURCE} ${CHESS_RESOURCES} ${PIECE_HEADERS} ${PIECE_SOURCE} src/main.cpp
    include/pieces_inc/knight.h
    src/pieces_src/knight.cpp
    include/pieces_inc/queen.h
    src/pieces_src/queen.cpp
    include/pieces_inc/rook.h
    src/pieces_src/rook.cpp
    include/pieces_inc/bishop.h
    src/pieces_src/bishop.cpp
    include/pieces_inc/king.h
    src/pieces_src/king.cpp
    include/move.h
    include/clock.h
    src/clock.cpp)

# Include directories
target_include_directories(Chess2 PRIVATE include include/pieces_inc)

# Link the Qt6 widgets library
target_link_libraries(Chess2 Qt6::Widgets)

# Set target properties
set_target_properties(Chess2 PROPERTIES
                      AUTOMOC ON
                      AUTOUIC ON
                      AUTORCC ON
                      AUTOUIC_SEARCH_PATHS "resources/ui")

# Add resources
qt_add_resources(Chess2 "art" PREFIX "/" FILES ${CHESS_IMAGES})

# Deploy Qt dependencies on Windows
if(WIN32)
  add_custom_command(TARGET Chess2 POST_BUILD
                     COMMAND $<TARGET_FILE:Qt6::windeployqt> $<TARGET_FILE:Chess2>)
endif(WIN32)
