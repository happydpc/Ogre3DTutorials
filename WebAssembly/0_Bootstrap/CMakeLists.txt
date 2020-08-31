add_executable(client Application.cpp Application.h)
set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s WASM=1 --bind")
