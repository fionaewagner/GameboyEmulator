file(GLOB sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.c")
file(GLOB headers CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(emu STATIC ${sources} ${headers})
target_include_directories(emu PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
    target_include_directories(emu PUBLIC ${PROJECT_SOURCE_DIR}/include/SDL2)  # SDL headers in GameboyEmulator/include/SDL2

    # Specify the path to the SDL2.dll for linking on Windows
    target_link_libraries(emu PUBLIC ${PROJECT_SOURCE_DIR}/gemu/SDL2.dll)  # Path to SDL2.dll

    # Specify the path to the SDL2_ttf.dll for linking on Windows
    target_link_libraries(emu PUBLIC ${PROJECT_SOURCE_DIR}/gemu/SDL2_ttf.dll)  # Path to SDL2_ttf.dll
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(emu PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(emu PUBLIC ${SDL2_LIBRARIES})
endif()

include_directories("/usr/local/include")