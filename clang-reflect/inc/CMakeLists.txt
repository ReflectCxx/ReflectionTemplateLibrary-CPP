# Header files
set(CLREFLECT_INCS
    "${CMAKE_CURRENT_LIST_DIR}/ASTParser.h"
    "${CMAKE_CURRENT_LIST_DIR}/ClangDriver.h"
	"${CMAKE_CURRENT_LIST_DIR}/ClangReflectActionFactory.h"
	"${CMAKE_CURRENT_LIST_DIR}/ClangReflectDiagnosticConsumer.h"
	"${CMAKE_CURRENT_LIST_DIR}/CommandLineParser.h"
	"${CMAKE_CURRENT_LIST_DIR}/FileManager.h"
	"${CMAKE_CURRENT_LIST_DIR}/FindRecordDeclsVisitor.h"
	"${CMAKE_CURRENT_LIST_DIR}/IncludesManager.h"
	"${CMAKE_CURRENT_LIST_DIR}/Logger.h"
	"${CMAKE_CURRENT_LIST_DIR}/Constants.h"
	"${CMAKE_CURRENT_LIST_DIR}/ReflectableInterface.h"
    # Add more header files as needed
)

# Add headers to the library target
target_sources(${CXX_EXE_NAME} PRIVATE ${CLREFLECT_INCS})
