set(INSTALL OFF CACHE BOOL
    "Generate install target.")

if (INSTALL)
  set(APP_BIN_DIR "" CACHE PATH
    "Install location for binaries (a relative path goes under prefix).")
  set(APP_SHARE_DIR "" CACHE PATH
    "Install location for shared files (arelative path goes under prefix).")
  mark_as_advanced(APP_BIN_DIR APP_SHARE_DIR)
  if(NOT APP_BIN_DIR)
    set(APP_BIN_DIR bin)
  endif(NOT APP_BIN_DIR)
  if(NOT APP_SHARE_DIR)
    set(APP_SHARE_DIR share/secondlife-${viewer_VERSION})
  endif(NOT APP_SHARE_DIR)
endif (INSTALL)
