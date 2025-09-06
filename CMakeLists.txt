cmake_minimum_required(VERSION 3.10)
project(Snake2D)

set(CMAKE_CXX_STANDARD 17)

# Collect all .cpp files
file(GLOB_RECURSE SOURCES
	"${CMAKE_SOURCE_DIR}/Snake2D/src/*.cpp"
)

# Create the Snake2D executable from all source files
add_executable(Snake2D ${SOURCES})

# Tell CMAKE where to find SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/Snake2D/External/SFML/lib/cmake/SFML")

# Find required SFML packages. 'network' is not included because it's not used.
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Add SFML include directory
target_include_directories(Snake2D PRIVATE
	 "${CMAKE_SOURCE_DIR}/Snake2D/src"
	 "${CMAKE_SOURCE_DIR}/Snake2D/src/include"
	"${CMAKE_SOURCE_DIR}/Snake2D/External/SFML/include"
)

# List of SFML COMPONENTS required without config suffix
set(SFML_DLL_NAMES
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

target_link_libraries(Snake2D
    ${SFML_DLL_NAMES}
)

# -----------------------------
# Copy Assets to build output
# -----------------------------

add_custom_command(TARGET Snake2D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Snake2D/assets"
    "${CMAKE_BINARY_DIR}/assets"
)




# Copy SFML DLLs based on build type
foreach(dll ${SFML_DLL_NAMES})
    add_custom_command(TARGET Snake2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/Snake2D/External/SFML/bin/${dll}-d-2.dll>"
            "$<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/Snake2D/External/SFML/bin/${dll}-2.dll>"
            $<TARGET_FILE_DIR:Snake2D>
    )
endforeach()

# Copy OpenAL DLL (same for all configurations)
add_custom_command(TARGET Snake2D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Snake2D/External/SFML/bin/openal32.dll"
        $<TARGET_FILE_DIR:Snake2D>
)