# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.



# -------- Options ----------

set(OCPN_TEST_REPO
    "mike-rossiter/aisrx-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "mike-rossiter/aisrx-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "mike-rossiter/aisrx-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)
option(aisRX_USE_SVG "Use SVG graphics" ON)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME aisRX_pi)
set(PKG_VERSION  0.6.0)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME aisRX)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME aisRX) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Read AIS binary messages")
set(PKG_DESCRIPTION [=[
Read AIS binary messages
]=])

set(PKG_AUTHOR "Mike Rossiter")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://github.com/Rasbats/aisRX_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/aisRX.html)

set(SRC
    src/ais.h
    src/ais8_200.cpp
    src/ais8.cpp
    src/ais_bitset.cpp
    src/AIS_Bitstring.cpp
    src/AIS_Bitstring.h
    src/ais.cpp
    src/aisRXgui.cpp
    src/aisRXgui.h
    src/aisRXgui_impl.cpp
    src/aisRXgui_impl.h
    src/aisRX_pi.cpp
    src/aisRX_pi.h
    src/icons.cpp
    src/icons.h
    src/signal.cpp
    src/signal.h
    src/widget.cpp
    src/widget.h
    src/bbox.cpp
    src/bbox.h
    src/AISdisplay.cpp
    src/AISdisplay.h
    src/ASMmessages.cpp
    src/ASMmessages.h
)

set(PKG_API_LIB api-16)  #  A directory in libs/ e. g., api-17 or api-16

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/tinyxml")
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/plugin_dc")
  target_link_libraries(${PACKAGE_NAME} ocpn::plugin-dc)

  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/sqlite")
  target_link_libraries(${PACKAGE_NAME} ocpn::sqlite)

  # The wxsvg library enables SVG overall in the plugin
  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/wxsvg")
  target_link_libraries(${PACKAGE_NAME} ocpn::wxsvg)
endmacro ()
