# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/rtl/src/CMakeLists.txt

# Collect local sources (absolute paths)
set(LOCAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxMirror.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxMirrorToJson.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Function.cpp"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_SOURCES})
source_group("Source Files\\RTL" FILES ${LOCAL_SOURCES})