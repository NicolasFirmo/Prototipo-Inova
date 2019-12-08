add_library(
    nic
    include/Estruturas.h
    include/Lista.h
    include/Ferramentas.h
    include/Relogio.h
    lib/Relogio.cpp
    lib/Lista.cpp
    )

target_include_directories(nic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")