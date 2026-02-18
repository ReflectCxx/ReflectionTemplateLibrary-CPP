# ========================
# RTL Integration Helpers
# ========================

# --------------------------------------------------
# Attach generated registration sources to a target
# --------------------------------------------------
function(rtl_attach_registration TARGET REG_DIR)

    # Validate registration directory exists
    if(NOT EXISTS "${REG_DIR}")
        message(FATAL_ERROR
            "\nRTL ERROR: Registration directory not found:\n"
            "  ${REG_DIR}\n"
            "Make sure clang-mirror generated files exist.\n"
        )
    endif()

    # Validate reg_src exists
	# clang-mirror generates the files in the same folder.
	# TODO: remove hard-coding.
    if(NOT EXISTS "${REG_DIR}/reg_src")
        message(FATAL_ERROR
            "\nRTL ERROR: Registration source folder not found in:\n"
            "  ${REG_DIR}\n"
            "Make sure clang-mirror generated registration sources.\n"
        )
    endif()

    # Collect generated sources
    file(GLOB RTL_REG_SRCS
        "${REG_DIR}/reg_src/*.cpp"
    )

    if(NOT RTL_REG_SRCS)
        message(FATAL_ERROR
            "\nRTL ERROR: No registration source files found in:\n"
            "  ${REG_DIR}\n"
        )
    endif()

    # Collect headers
    file(GLOB RTL_REG_HDRS
        "${REG_DIR}/*.h"
    )

    # Attach to target
    target_sources(${TARGET} PRIVATE
        ${RTL_REG_SRCS}
        ${RTL_REG_HDRS}
    )

    target_include_directories(${TARGET} PRIVATE
        "${REG_DIR}"
    )

    set_source_files_properties(${RTL_REG_SRCS}
        PROPERTIES GENERATED TRUE
    )

    source_group("RTLRegistration" FILES
        ${RTL_REG_SRCS}
        ${RTL_REG_HDRS}
    )

    message(STATUS
        "RTL: Registration attached from ${REG_DIR}"
    )

endfunction()

# -------------------
# Public entry point
# -------------------
function(rtl_enable TARGET)

    if(NOT TARGET ${TARGET})
        message(FATAL_ERROR
            "RTL ERROR: Target '${TARGET}' does not exist"
        )
    endif()

    target_link_libraries(${TARGET}
        PRIVATE RTL::ReflectionTemplateLib
    )

    get_target_property(TARGET_SOURCE_DIR ${TARGET} SOURCE_DIR)

    if(NOT TARGET_SOURCE_DIR)
        message(FATAL_ERROR
            "RTL ERROR: Could not determine source directory for '${TARGET}'"
        )
    endif()

    # Define folder name locally, hard-coded for now.
	# clang-mirror generates the files in the same folder.
	# TODO: remove hard-coding.
    set(RTL_REGISTRATION_FOLDER "RTLRegistration")

    set(REG_DIR
        "${TARGET_SOURCE_DIR}/${RTL_REGISTRATION_FOLDER}"
    )

    rtl_attach_registration(${TARGET} "${REG_DIR}")

endfunction()