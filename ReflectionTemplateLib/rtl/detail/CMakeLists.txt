# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/detail/CMakeLists.txt

# Make the 'inc' folder visible as a public include dir
target_include_directories(ReflectionTemplateLib
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

add_subdirectory(inc)
add_subdirectory(src)