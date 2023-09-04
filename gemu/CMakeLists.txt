set(MAIN_SOURCES
  main.c
)

add_executable(gemu ${MAIN_SOURCES})
target_link_libraries(gemu emu)
target_include_directories(gemu PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/SDL2)  # Include both project-specific headers and SDL headers

message(STATUS "SDL Libraries: ${SDL2_LIBRARIES} - ${SDL2_LIBRARY}")
message(STATUS "SDL TTF Libraries: ${SDL2_TTF_LIBRARIES} - ${SDL2_TTF_LIBRARY}")

install(TARGETS gemu
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

add_custom_command(
    TARGET gemu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/NotoSansMono-Medium.ttf
    $<TARGET_FILE_DIR:gemu>
    VERBATIM)

if (WIN32)
    add_custom_command(
        TARGET gemu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/gemu/SDL2.dll  # Update the path to the correct SDL2.dll location
        $<TARGET_FILE_DIR:gemu>
        VERBATIM)
    
    add_custom_command(
        TARGET gemu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/gemu/SDL2_ttf.dll  # Update the path to the correct SDL2_ttf.dll location
        $<TARGET_FILE_DIR:gemu>
        VERBATIM)

    add_custom_command(
        TARGET gemu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/gemu/zlib1.dll  # Update the path to the correct zlib1.dll location
        $<TARGET_FILE_DIR:gemu>
        VERBATIM)
    
    add_custom_command(
        TARGET gemu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/gemu/libfreetype-6.dll  # Update the path to the correct libfreetype-6.dll location
        $<TARGET_FILE_DIR:gemu>
        VERBATIM)
endif ()