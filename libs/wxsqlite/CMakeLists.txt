cmake_minimum_required(VERSION 3.1.0)

if (TARGET wxsqlite::wxsqlite)
    return ()
endif ()

set (SRC 
  src/wxsqlite3.cpp
  include/wx/wxsqlite3def.h
  include/wx/wxsqlite3dyn.h
  include/wx/wxsqlite3.h
  include/wx/wxsqlite3opt.h
  include/wx/wxsqlite3_version.h
)
add_library(_WXSQLITE STATIC ${SRC})
target_include_directories(
  _WXSQLITE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_library(wxsqlite::wxsqlite ALIAS _WXSQLITE)
