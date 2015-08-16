# PCRE_INCLUDE_DIRS - include directories
# PCRE_LIBRARIES - library directories

find_package(PkgConfig)
pkg_check_modules(PC_PCRE QUIET pcre)

find_path(PCRE_INCLUDE_DIR pcre.h
	HINTS ${PC_PCRE_INCLUDEDIR} ${PC_PCRE_INCLUDE_DIRS} PATH_SUFFIXES pcre)

find_library(PCRE_LIBRARY NAMES pcre
	HINTS ${PC_PCRE_LIBDIR} ${PC_PCRE_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(PCRE DEFAULT_MSG PCRE_LIBRARY PCRE_INCLUDE_DIR)

mark_as_advanced(PCRE_INCLUDE_DIR PCRE_LIBRARY)
