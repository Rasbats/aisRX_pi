# Install script for directory: C:/Users/Mike/Documents/GitHub/aisRX_pi

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app/files")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins" TYPE SHARED_LIBRARY FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/Debug/aisRX_pi.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins" TYPE SHARED_LIBRARY FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/Release/aisRX_pi.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins" TYPE SHARED_LIBRARY FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/MinSizeRel/aisRX_pi.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins" TYPE SHARED_LIBRARY FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/RelWithDebInfo/aisRX_pi.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins/aisRX_pi" TYPE DIRECTORY FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/data")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
    configure_file(
      C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5-msvc-6.3.9600.xml.in
      C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app/files/metadata.xml
      @ONLY
    )
  
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ar_SA/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ar_SA.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/bg_BG/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/bg_BG.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ca_ES/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ca_ES.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/cs_CZ/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/cs_CZ.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/da_DK/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/da_DK.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/de_DE/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/de_DE.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/el_GR/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/el_GR.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/es_ES/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/es_ES.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/et_EE/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/et_EE.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/fi_FI/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/fi_FI.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/fil_PH/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/fil_PH.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/fr_FR/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/fr_FR.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/gl_ES/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/gl_ES.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/hi_IN/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/hi_IN.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/hu_HU/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/hu_HU.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/id_ID/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/id_ID.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/is_IS/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/is_IS.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/it_IT/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/it_IT.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ja_JP/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ja_JP.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ko_KR/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ko_KR.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/mr_IN/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/mr_IN.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/nb_NO/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/nb_NO.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/nl_NL/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/nl_NL.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/pl_PL/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/pl_PL.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/pt_BR/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/pt_BR.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/pt_PT/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/pt_PT.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ro_RO/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ro_RO.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ru_RU/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/ru_RU.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/sv_SE/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/sv_SE.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/th_TH/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/th_TH.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/tr_TR/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/tr_TR.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/vi_VN/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/vi_VN.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/zh_CN/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/zh_CN.mo")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/zh_TW/LC_MESSAGES" TYPE FILE RENAME "opencpn-aisRX_pi.mo" FILES "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/zh_TW.mo")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/api-16/cmake_install.cmake")
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/WindowsHeaders/cmake_install.cmake")
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/jsoncpp/cmake_install.cmake")
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/tinyxml/cmake_install.cmake")
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/wxJSON/cmake_install.cmake")
  include("C:/Users/Mike/Documents/GitHub/aisRX_pi/build/libs/sqlite/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Mike/Documents/GitHub/aisRX_pi/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
