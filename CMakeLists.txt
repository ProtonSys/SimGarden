cmake_minimum_required(VERSION 3.20)
project(SimuladorJardim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(SOURCES
        main.cpp

        core/Interface.cpp
        core/Simulator.cpp
        core/Validator.cpp

        jardim/Jardim.cpp
        jardim/Posicao.cpp

        jardineiro/Jardineiro.cpp

        plantas/Planta.cpp
        plantas/Cacto.cpp
        plantas/Roseira.cpp
        plantas/ErvaDaninha.cpp
        plantas/PlantaExotica.cpp

        ferramentas/Ferramenta.cpp
        ferramentas/Regador.cpp
        ferramentas/PacoteAdubo.cpp
        ferramentas/TesouraPoda.cpp
        ferramentas/FerramentaZ.cpp
)

set(HEADERS
        core/Interface.h
        core/Simulator.h
        core/Validator.h
        config/Settings.h

        jardim/Jardim.h
        jardim/Posicao.h

        jardineiro/Jardineiro.h

        plantas/Planta.h
        plantas/Cacto.h
        plantas/Roseira.h
        plantas/ErvaDaninha.h
        plantas/PlantaExotica.h

        ferramentas/Ferramenta.h
        ferramentas/Regador.h
        ferramentas/PacoteAdubo.h
        ferramentas/TesouraPoda.h
        ferramentas/FerramentaZ.h
)

add_executable(SimuladorJardim
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(SimuladorJardim PRIVATE
        core
        config
        jardim
        jardineiro
        plantas
        ferramentas
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()