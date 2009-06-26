# -*- cmake -*-

function (build_version _target)
  # Read version components from the header file.
  file(STRINGS ${LIBS_OPEN_DIR}/llcommon/llversion${_target}.h lines
       REGEX " LL_VERSION_")
  foreach(line ${lines})
    string(REGEX REPLACE ".*LL_VERSION_([A-Z]+).*" "\\1" comp "${line}")
    string(REGEX REPLACE ".* = ([0-9]+);.*" "\\1" value "${line}")
    set(v${comp} "${value}")
  endforeach(line)

  # Compose the version.
  set(${_target}_VERSION "${vMAJOR}.${vMINOR}.${vPATCH}.${vBUILD}")
  if (${_target}_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(STATUS "Version of ${_target} is ${${_target}_VERSION}")
  else (${_target}_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(FATAL_ERROR "Could not determine ${_target} version (${${_target}_VERSION})")
  endif (${_target}_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")

  # Report version to caller.
  set(${_target}_VERSION "${${_target}_VERSION}" PARENT_SCOPE)
endfunction (build_version)
