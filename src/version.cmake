message(STATUS "Setting tag version and commit ID")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${TO}")
