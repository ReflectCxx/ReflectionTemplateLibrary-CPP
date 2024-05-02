# Source files
set(CLREFLECT_SRCS
    "${CMAKE_CURRENT_LIST_DIR}/ASTParser.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ClangDriver.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ClangReflectActionFactory.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ClangReflectDiagnosticConsumer.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/clang-reflect-main.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/CommandLineParser.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FileManager.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FindRecordDeclsVisitor.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/cxxIncludeScanner.lex.c"
	"${CMAKE_CURRENT_LIST_DIR}/IncludesManager.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Logger.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ReflectableInterface.cpp"
    # Add more source files as needed
)

set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/cxxIncludeScanner.lex.c" PROPERTIES LANGUAGE CXX COMPILE_FLAGS "-std=c++17")

target_sources(${CXX_EXE_NAME} PRIVATE ${CLREFLECT_SRCS})