# CMakeLists.txt for src/core-utils

ADD_DEFINITIONS (-DG_LOG_DOMAIN=\"gnc.core-utils\")

INCLUDE_DIRECTORIES (${GLIB2_INCLUDE_DIRS})
INCLUDE_DIRECTORIES (${GCONF2_INCLUDE_DIRS})
INCLUDE_DIRECTORIES (${LIBINTL_INCLUDE_PATH})
INCLUDE_DIRECTORIES (${REGEX_INCLUDE_PATH})
INCLUDE_DIRECTORIES (${GUILE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/src ) # for config.h
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/..) # for gnc-ui.h
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/../libqof/qof) # for gnc-ui.h
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}) # when building swig-core-utils.c
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}) # for gncla-dir.h, gnc-version.h

# Command to generate the swig-engine.c wrapper file
SET (SWIG_CORE_UTILS_C ${CMAKE_CURRENT_BINARY_DIR}/swig-core-utils.c)
GNC_ADD_SWIG_COMMAND (${SWIG_CORE_UTILS_C} ${CMAKE_CURRENT_SOURCE_DIR}/core-utils.i)

SET (libgnc_core_utils_SOURCES
  binreloc.c
  gnc-prefs.c
  gnc-filepath-utils.c
  gnc-features.c
  gnc-gdate-utils.c
  gnc-gkeyfile-utils.c
  gnc-glib-utils.c
  gnc-guile-utils.c
  gnc-jalali.c
  gnc-locale-utils.c
  gnc-path.c
  gnc-uri-utils.c
  ${SWIG_CORE_UTILS_C}
)

# Add dependency on config.h
SET_SOURCE_FILES_PROPERTIES (${libgnc_core_utils_SOURCES} PROPERTIES OBJECT_DEPENDS ${CONFIG_H})

# Command to generate the swig-runtime.h header
ADD_CUSTOM_COMMAND (
  OUTPUT ${SWIG_RUNTIME_H}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
  COMMAND ${SWIG_EXECUTABLE} -guile -external-runtime ${SWIG_RUNTIME_H}
)

# Add dependency on swig-runtime.h
SET_SOURCE_FILES_PROPERTIES (gnc-guile-utils.c PROPERTIES OBJECT_DEPENDS ${SWIG_RUNTIME_H})

# Workaround to create a very simple gncla-dir.h file
FILE (WRITE ${CMAKE_CURRENT_BINARY_DIR}/gncla-dir.h "
#define PREFIX \"${CMAKE_INSTALL_PREFIX}\"
#define DATADIR \"${CMAKE_INSTALL_PREFIX}/share\"
#define SYSCONFDIR \"${CMAKE_INSTALL_PREFIX}/etc\"
#define LIBDIR \"${CMAKE_INSTALL_PREFIX}/lib\"
#define BINDIR \"${CMAKE_INSTALL_PREFIX}/bin\"
#define LOCALE_DATADIRNAME \"share\"
")

# Workaround to create a simple gnc-version.h file
FILE (WRITE ${CMAKE_CURRENT_BINARY_DIR}/gnc-version.h "
/* Autogenerated. Do not change. */
#ifndef GNC_VERSION_H
#define GNC_VERSION_H

#define GNUCASH_SVN 1
#define GNUCASH_BUILD_DATE \"2010-XX-XX\"
#define GNUCASH_SVN_REV \"xxxxxxx\"
#endif
")

SET (libgnc_core_utils_HEADERS
  binreloc.h
  gnc-prefs.h
  gnc-prefs-p.h
  gnc-features.h
  gnc-filepath-utils.h
  gnc-gdate-utils.h
  gnc-gkeyfile-utils.h
  gnc-glib-utils.h
  gnc-guile-utils.h
  gnc-jalali.h
  gnc-locale-utils.h
  gnc-path.h
  gnc-uri-utils.h
)

ADD_LIBRARY	(core-utils
  ${libgnc_core_utils_SOURCES}
  ${libgnc_core_utils_HEADERS}
  )
