# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_bicycle_control_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED bicycle_control_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(bicycle_control_FOUND FALSE)
  elseif(NOT bicycle_control_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(bicycle_control_FOUND FALSE)
  endif()
  return()
endif()
set(_bicycle_control_CONFIG_INCLUDED TRUE)

# output package information
if(NOT bicycle_control_FIND_QUIETLY)
  message(STATUS "Found bicycle_control: 0.1.0 (${bicycle_control_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'bicycle_control' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT bicycle_control_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(bicycle_control_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${bicycle_control_DIR}/${_extra}")
endforeach()
