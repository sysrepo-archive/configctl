# LIBGIT2_INCLUDE_DIRS - include directories
# LIBGIT2_LIBRARIES - library directories

find_package(PkgConfig)
pkg_check_modules(PC_LIBGIT2 QUIET libgit2)

find_path(LIBGIT2_INCLUDE_DIR git2.h
	HINTS ${PC_LIBGIT2_INCLUDEDIR} ${PC_LIBGIT2_INCLUDE_DIRS} PATH_SUFFIXES git2)

find_library(LIBGIT2_LIBRARY NAMES git2
	HINTS ${PC_LIBGIT2_LIBDIR} ${PC_LIBGIT2_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LIBGIT2 DEFAULT_MSG LIBGIT2_LIBRARY LIBGIT2_INCLUDE_DIR)

mark_as_advanced(LIBGIT2_INCLUDE_DIR LIBGIT2_LIBRARY)
