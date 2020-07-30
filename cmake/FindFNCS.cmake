message("inside FindFNCS.cmake")
include(FindPkgConfig)
PKG_CHECK_MODULES(PC_FNCS "libfncs")

find_path(
    FNCS_INCLUDE_DIR
    NAMES fncs.hpp
    HINTS ${PC_FNCS_INCLUDEDIR} ${PC_FNCS_INCLUDE_DIRS}
)
message("FNCS_INCLUDE_DIR=${FNCS_INCLUDE_DIR}")
find_library(
    FNCS_LIBRARY
    NAMES fncs
    HINTS ${PC_FNCS_LIBDIR} ${PC_FNCS_LIBRARY_DIRS}
)

find_package(CZMQ)
if (CZMQ_FOUND)
    message("CZMQ found in FindFNCS.cmake")
endif ()

set(FNCS_LIBRARIES ${FNCS_LIBRARY} ${CZMQ_LIBRARIES})
set(FNCS_INCLUDE_DIRS ${FNCS_INCLUDE_DIR} ${CZMQ_INCLUDE_DIRS})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FNCS DEFAULT_MSG FNCS_LIBRARY FNCS_INCLUDE_DIR)
mark_as_advanced(FNCS_LIBRARY FNCS_INCLUDE_DIR)
message("end of FindFNCS.cmake")
