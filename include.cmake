set(MY_LIBS_DIR ~/Programs/c/my_libs)
set(MY_LIBS_SOURCES
  ${MY_LIBS_DIR}/libs/string.c
  ${MY_LIBS_DIR}/libs/string.h
  ${MY_LIBS_DIR}/libs/array.c
  ${MY_LIBS_DIR}/libs/array.h
  ${MY_LIBS_DIR}/libs/geometry.c
  ${MY_LIBS_DIR}/libs/geometry.h
  ${MY_LIBS_DIR}/libs/complex.c
  ${MY_LIBS_DIR}/libs/complex.h
  ${MY_LIBS_DIR}/libs/color.c
  ${MY_LIBS_DIR}/libs/color.h
  ${MY_LIBS_DIR}/libs/time.c
  ${MY_LIBS_DIR}/libs/time.h
)

if(DEFINED MY_LIBS_USE_EASYSDL AND MY_LIBS_USE_EASYSDL)
  if(DEFINED EASYSDL_LOADED AND EASYSDL_LOADED)
    set(MY_LIBS_SOURCES ${MY_LIBS_SOURCES}
      ${MY_LIBS_DIR}/libs/easysdl.c
      ${MY_LIBS_DIR}/libs/easysdl.h
    )
  else()
    message(FATAL_ERROR "EasySDL has to be loaded first; exiting")
  endif()
endif()

add_library(my_libs ${MY_LIBS_SOURCES})

if(DEFINED MY_LIBS_USE_EASYSDL AND MY_LIBS_USE_EASYSDL)
  target_link_libraries(my_libs PRIVATE easysdl)
endif()

include_directories(${MY_LIBS_DIR})
