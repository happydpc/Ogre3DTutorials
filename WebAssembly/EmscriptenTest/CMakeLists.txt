set(resourceToCopy "")
add_custom_command(
  OUTPUT "CopyIndexHtml"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/index.html" "${CMAKE_CURRENT_BINARY_DIR}/index.html"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/index.html"
  COMMENT "Copying resource-file 'index.html'"
)

add_executable(client Application.cpp Application.h "CopyIndexHtml")
set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s WASM=1 --bind")
