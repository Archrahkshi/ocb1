find_path(BOTAN_INCLUDE_DIRS NAMES botan/botan.h
        PATH_SUFFIXES botan-2
        DOC "The botan include directory")

find_library(BOTAN_LIBRARIES NAMES botan botan-2
        DOC "The botan library")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BOTAN REQUIRED_VARS BOTAN_LIBRARIES BOTAN_INCLUDE_DIRS)

if(BOTAN_FOUND)
    set(BOTAN_LIBRARY ${BOTAN_LIBRARIES})
    set(BOTAN_INCLUDE_DIR ${BOTAN_INCLUDE_DIRS})
endif()

mark_as_advanced(BOTAN_INCLUDE_DIRS BOTAN_LIBRARIES)