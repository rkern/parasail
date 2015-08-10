#.rst:
# FindSSE2
# --------
#
# Finds SSE2 support
#
# This module can be used to detect SSE2 support in a C/C++ compiler.  If
# the compiler supports SSE2, the flags required to compile with
# SSE2 support are returned in variables for the different languages.
# The variables may be empty if the compiler does not need a special
# flag to support SSE2.
#
# The following variables are set:
#
# ::
#
#    SSE2_C_FLAGS - flags to add to the C compiler for SSE2 support
#    SSE2_CXX_FLAGS - flags to add to the CXX compiler for SSE2 support
#    SSE2_FOUND - true if SSE2 is detected
#
#=============================================================================

set(_SSE2_REQUIRED_VARS)
set(CMAKE_REQUIRED_QUIET_SAVE ${CMAKE_REQUIRED_QUIET})
set(CMAKE_REQUIRED_QUIET ${SSE2_FIND_QUIETLY})

function(_SSE2_FLAG_CANDIDATES LANG)
  set(SSE2_FLAG_CANDIDATES
    #Empty, if compiler automatically accepts SSE2
    " "
    #GNU, Intel
    "-march=core2"
    #clang
    "-msse2"
  )

  set(SSE2_${LANG}_FLAG_CANDIDATES "${SSE2_FLAG_CANDIDATES}" PARENT_SCOPE)
endfunction()

# sample SSE2 source code to test
set(SSE2_C_TEST_SOURCE
"
#include <emmintrin.h>
int foo() {
    __m128i vOne = _mm_set1_epi16(1);
    __m128i result = _mm_add_epi16(vOne,vOne);
    return _mm_extract_epi16(result, 0);
}
int main(void) { return foo(); }
")

# check c compiler
if(CMAKE_C_COMPILER_LOADED)
  # if these are set then do not try to find them again,
  # by avoiding any try_compiles for the flags
  if(SSE2_C_FLAGS)
    unset(SSE2_C_FLAG_CANDIDATES)
  else()
    _SSE2_FLAG_CANDIDATES("C")
    include(CheckCSourceCompiles)
  endif()

  foreach(FLAG IN LISTS SSE2_C_FLAG_CANDIDATES)
    set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${FLAG}")
    unset(SSE2_FLAG_DETECTED CACHE)
    if(NOT CMAKE_REQUIRED_QUIET)
      message(STATUS "Try SSE2 C flag = [${FLAG}]")
    endif()
    check_c_source_compiles("${SSE2_C_TEST_SOURCE}" SSE2_FLAG_DETECTED)
    set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
    if(SSE2_FLAG_DETECTED)
      set(SSE2_C_FLAGS_INTERNAL "${FLAG}")
      break()
    endif()
  endforeach()

  set(SSE2_C_FLAGS "${SSE2_C_FLAGS_INTERNAL}"
    CACHE STRING "C compiler flags for SSE2 intrinsics")

  list(APPEND _SSE2_REQUIRED_VARS SSE2_C_FLAGS)
  unset(SSE2_C_FLAG_CANDIDATES)
endif()

# check cxx compiler
if(CMAKE_CXX_COMPILER_LOADED)
  # if these are set then do not try to find them again,
  # by avoiding any try_compiles for the flags
  if(SSE2_CXX_FLAGS)
    unset(SSE2_CXX_FLAG_CANDIDATES)
  else()
    _SSE2_FLAG_CANDIDATES("CXX")
    include(CheckCXXSourceCompiles)

    # use the same source for CXX as C for now
    set(SSE2_CXX_TEST_SOURCE ${SSE2_C_TEST_SOURCE})
  endif()

  foreach(FLAG IN LISTS SSE2_CXX_FLAG_CANDIDATES)
    set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${FLAG}")
    unset(SSE2_FLAG_DETECTED CACHE)
    if(NOT CMAKE_REQUIRED_QUIET)
      message(STATUS "Try SSE2 CXX flag = [${FLAG}]")
    endif()
    check_cxx_source_compiles("${SSE2_CXX_TEST_SOURCE}" SSE2_FLAG_DETECTED)
    set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
    if(SSE2_FLAG_DETECTED)
      set(SSE2_CXX_FLAGS_INTERNAL "${FLAG}")
      break()
    endif()
  endforeach()

  set(SSE2_CXX_FLAGS "${SSE2_CXX_FLAGS_INTERNAL}"
    CACHE STRING "C++ compiler flags for SSE2 parallization")

  list(APPEND _SSE2_REQUIRED_VARS SSE2_CXX_FLAGS)
  unset(SSE2_CXX_FLAG_CANDIDATES)
  unset(SSE2_CXX_TEST_SOURCE)
endif()

set(CMAKE_REQUIRED_QUIET ${CMAKE_REQUIRED_QUIET_SAVE})

if(_SSE2_REQUIRED_VARS)
  include(FindPackageHandleStandardArgs)

  find_package_handle_standard_args(SSE2
                                    REQUIRED_VARS ${_SSE2_REQUIRED_VARS})

  mark_as_advanced(${_SSE2_REQUIRED_VARS})

  unset(_SSE2_REQUIRED_VARS)
else()
  message(SEND_ERROR "FindSSE2 requires C or CXX language to be enabled")
endif()
