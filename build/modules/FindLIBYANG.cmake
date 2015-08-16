# LIBYANG_INCLUDE_DIR - include directories
# LIBYANG_LIBRARY - library directories

find_package(PkgConfig)
pkg_check_modules(PC_LIBYANG QUIET yang)

find_path(LIBYANG_INCLUDE_DIR libyang/tree_data.h
	HINTS ${PC_LIBYANG_INCLUDEDIR} ${PC_LIBYANG_INCLUDE_DIRS} PATH_SUFFIXES yang)

find_library(LIBYANG_LIBRARY NAMES yang tree_data
	HINTS ${PC_LIBYANG_LIBDIR} ${PC_LIBYANG_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LIBYANG DEFAULT_MSG LIBYANG_LIBRARY LIBYANG_INCLUDE_DIR)

mark_as_advanced(LIBYANG_INCLUDE_DIR LIBYANG_LIBRARY)
