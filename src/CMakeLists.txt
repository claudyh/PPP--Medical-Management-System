cmake_minimum_required(VERSION 3.21)
project(ProjetoPPP C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ProjetoPPP Estrutura.h Funcoes.c Funcoes.h ProjetoPPP.c)
