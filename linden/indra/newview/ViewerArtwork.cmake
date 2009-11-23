set(ARTWORK_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH
    "Path to artwork files.")

# Hide the ARTWORK_REQUIRED cache option by default.
set(doc "Require artwork?")
if(DEFINED ARTWORK_REQUIRED)
  set(ARTWORK_REQUIRED "${ARTWORK_REQUIRED}" CACHE INTERNAL "${doc}")
endif(DEFINED ARTWORK_REQUIRED)

# Check if artwork is available.
if(EXISTS "${ARTWORK_DIR}/res/arrow.cur")
  set(ARTWORK_EXISTS 1)
else(EXISTS "${ARTWORK_DIR}/res/arrow.cur")
  set(ARTWORK_EXISTS 0)
  if(PACKAGE)
    set(ARTWORK_REQUIRED 1)
    set(_ARTWORK_MESSAGE "Artwork is required to build a PACKAGE.")
  elseif(WINDOWS)
    set(ARTWORK_REQUIRED 1)
    set(_ARTWORK_MESSAGE "Artwork is required to build on Windows.")
  else()
    option(ARTWORK_REQUIRED "${doc}" ON)
    set(_ARTWORK_MESSAGE "Alternatively, disable ARTWORK_REQUIRED.")
    # Show the option.
    set(ARTWORK_REQUIRED "${ARTWORK_REQUIRED}" CACHE BOOL "${doc}" FORCE)
  endif()
endif(EXISTS "${ARTWORK_DIR}/res/arrow.cur")

# Verify artwork setting.
if(NOT ARTWORK_EXISTS AND ARTWORK_REQUIRED)
  # Try to report the artwork asset URL.
  set(asset_urls_file "${CMAKE_SOURCE_DIR}/../doc/asset_urls.txt")
  if(EXISTS "${asset_urls_file}")
    file(STRINGS "${asset_urls_file}" art_line REGEX "SLASSET_ART=")
    string(REPLACE "SLASSET_ART=" "" SLASSET_ART "${art_line}")
  endif(EXISTS "${asset_urls_file}")
  if(NOT SLASSET_ART)
    set(SLASSET_ART "http://wiki.secondlife.com/wiki/Source_downloads")
  endif(NOT SLASSET_ART)

  # Report missing artwork.
  message(FATAL_ERROR
    "The artwork directory\n"
    "  ARTWORK_DIR = ${ARTWORK_DIR}\n"
    "does not appear to contain the viewer artwork.  "
    "Download artwork files from\n"
    "  ${SLASSET_ART}\n"
    "and extract the zip file.  "
    "Then set the ARTWORK_DIR cache entry to point at "
    "linden/indra/newview within the extracted directory.  "
    "See the wiki for further help:\n"
    "  http://wiki.secondlife.com/wiki/Get_source_and_compile\n"
    "${_ARTWORK_MESSAGE}"
    )
endif(NOT ARTWORK_EXISTS AND ARTWORK_REQUIRED)

# Check if the artwork is in the source tree.
if(EXISTS "${ARTWORK_DIR}/app_settings/CA.pem")
  set(ARTWORK_IN_SOURCE 1)
else(EXISTS "${ARTWORK_DIR}/app_settings/CA.pem")
  set(ARTWORK_IN_SOURCE 0)
endif(EXISTS "${ARTWORK_DIR}/app_settings/CA.pem")
