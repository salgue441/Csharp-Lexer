# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.22.1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(googletest-populate NONE)



include(ExternalProject)
ExternalProject_Add(googletest-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip"
                    SOURCE_DIR          "/mnt/c/users/carlo/documents/Tec de Monterrey/semestres/2023/Febrero - Junio/TC2037.601 - Implementacion de Metodos Computacionales/evidencias/threadlexer/build/_deps/googletest-src"
                    BINARY_DIR          "/mnt/c/users/carlo/documents/Tec de Monterrey/semestres/2023/Febrero - Junio/TC2037.601 - Implementacion de Metodos Computacionales/evidencias/threadlexer/build/_deps/googletest-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


