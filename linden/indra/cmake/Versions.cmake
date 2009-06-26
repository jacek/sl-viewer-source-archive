include(BuildVersion)

if(VIEWER)
  build_version(viewer)
endif(VIEWER)

if(SERVER)
  build_version(server)
endif(SERVER)
