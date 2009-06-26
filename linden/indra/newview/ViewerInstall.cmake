install(TARGETS ${VIEWER_BINARY_NAME}
        DESTINATION ${APP_BIN_DIR}
        )

# Install artwork lying inside the source tree.
install(DIRECTORY res skins app_settings
        DESTINATION ${APP_SHARE_DIR}
        PATTERN ".svn" EXCLUDE
        )

if(ARTWORK_EXISTS)
  # Install files exclusive to the artwork directory.
  install(DIRECTORY ${ARTWORK_DIR}/character
          DESTINATION ${APP_SHARE_DIR}
          PATTERN ".svn" EXCLUDE
          )

  if(NOT ARTWORK_IN_SOURCE)
    # Install artwork lying outside the source tree.
    install(DIRECTORY ${ARTWORK_DIR}/res
                      ${ARTWORK_DIR}/skins
                      ${ARTWORK_DIR}/app_settings
            DESTINATION ${APP_SHARE_DIR}
            PATTERN ".svn" EXCLUDE
            )
  endif(NOT ARTWORK_IN_SOURCE)
else(ARTWORK_EXISTS)
  message(STATUS "WARNING: Artwork is not present, and will not be installed")
endif(ARTWORK_EXISTS)

install(DIRECTORY linux_tools fonts
        DESTINATION ${APP_SHARE_DIR}
        PATTERN ".svn" EXCLUDE
        )

install(FILES featuretable_linux.txt featuretable_solaris.txt gpu_table.txt
        DESTINATION ${APP_SHARE_DIR}
        )

install(FILES ${SCRIPTS_DIR}/messages/message_template.msg
        DESTINATION ${APP_SHARE_DIR}/app_settings
        )
