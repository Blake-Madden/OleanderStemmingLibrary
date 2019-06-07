# ------------------------------------------------------------------------------
# Clang Format
# ------------------------------------------------------------------------------
OPTION(ENABLE_FORMAT "Run clang-format on all files in src/ and include/" OFF)

if(ENABLE_FORMAT)
    # Get all project files
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.[chi]pp
        ${PROJECT_SOURCE_DIR}/src/*.[chi]xx
        ${PROJECT_SOURCE_DIR}/src/*.[chi]cc
        ${PROJECT_SOURCE_DIR}/src/*.[chi]hh
        ${PROJECT_SOURCE_DIR}/src/*.[chi]ii
        ${PROJECT_SOURCE_DIR}/src/*.[CHI]

        ${PROJECT_SOURCE_DIR}/include/*.[chi]pp
        ${PROJECT_SOURCE_DIR}/include/*.[chi]xx
        ${PROJECT_SOURCE_DIR}/include/*.[chi]cc
        ${PROJECT_SOURCE_DIR}/include/*.[chi]hh
        ${PROJECT_SOURCE_DIR}/include/*.[chi]ii
        ${PROJECT_SOURCE_DIR}/include/*.[CHI]
    )

    # Add format target if executable is found
    find_program(CLANG_FORMAT "clang-format")
    if(CLANG_FORMAT)
        add_custom_target(
            format
            COMMAND /usr/bin/clang-format
            -i
            -style=file
            ${ALL_CXX_SOURCE_FILES}
        )
    endif()
endif()
