message("inside FindHELICS.cmake")
include(FindPkgConfig)
PKG_CHECK_MODULES(PC_HELICS "helicsSharedLib")# "helicsSharedLibd" "helics-shared" "helics-apps-shared")
message("PKG_CONFIG_FOUND=${PKG_CONFIG_FOUND}")
message("PKG_CONFIG_EXECUTABLE=${PKG_CONFIG_EXECUTABLE}")
message("PKG_CONFIG_VERSION_STRING=${PKG_CONFIG_VERSION_STRING}")
message("PC_HELICS_FOUND=${PC_HELICS_FOUND}")
message("PC_HELICS_LIBRARIES=${PC_HELICS_LIBRARIES}")
message("CMAKE_FRAMEWORK_PATH=${CMAKE_FRAMEWORK_PATH}")
message("PATH_SUFFIXES=${PATH_SUFFIXES}")
message("PC_HELICS_INCLUDEDIR=${PC_HELICS_INCLUDEDIR}")
message("PC_HELICS_INCLUDE_DIRS=${PC_HELICS_INCLUDE_DIRS}")
message("HELICS_INCLUDE_DIR=${HELICS_INCLUDE_DIR}")
message("PC_HELICS_LIBDIR=${PC_HELICS_LIBDIR}")
message("PC_HELICS_LIBRARY_DIRS=${PC_HELICS_LIBRARY_DIRS}")
find_path(
    HELICS_INCLUDE_DIR
    NAMES helics#/ValueFederate.hpp #Inputs.hpp Publications.hpp
    HINTS ${PC_HELICS_INCLUDEDIR} ${PC_HELICS_INCLUDE_DIRS}
)
message("HELICS_INCLUDE_DIR=${HELICS_INCLUDE_DIR}")
message("PC_HELICS_LIBDIR=${PC_HELICS_LIBDIR}")
message("PC_HELICS_LIBRARY_DIRS=${PC_HELICS_LIBRARY_DIRS}")
message("HELICS_LIBRARY=${HELICS_LIBRARY}")

find_library(
    HELICS_LIBRARY
    NAMES helicsSharedLib # helics-shared helics-apps-shared
    HINTS ${PC_HELICS_LIBDIR} ${PC_HELICS_LIBRARY_DIRS}
)
message("PC_HELICS_LIBDIR=${PC_HELICS_LIBDIR}")
message("PC_HELICS_LIBRARY_DIRS=${PC_HELICS_LIBRARY_DIRS}")
message("HELICS_LIBRARY=${HELICS_LIBRARY}")

find_package(CZMQ)
if (CZMQ_FOUND)
    message("CZMQ found")
endif ()

set(HELICS_LIBRARIES ${HELICS_LIBRARY} ${CZMQ_LIBRARIES})
set(HELICS_INCLUDE_DIRS ${HELICS_INCLUDE_DIR} ${CZMQ_INCLUDE_DIRS})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HELICS DEFAULT_MSG HELICS_LIBRARY HELICS_INCLUDE_DIR)
mark_as_advanced(HELICS_LIBRARY HELICS_INCLUDE_DIR)
message("end of FindHELICS.cmake")