# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/detail/src/CMakeLists.txt

# All .cpp files in this folder (absolute paths)
set(LOCAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxReflection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectCast.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectConverters_string.cpp"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_SOURCES})
source_group("Source Files\\Detail" FILES ${LOCAL_SOURCES})