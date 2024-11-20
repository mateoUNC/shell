cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto
project(
    "ShellProject"
    VERSION 1.0.0
    DESCRIPTION "A nice shell project!"
    LANGUAGES C
)

# Configurar el prefijo para que CMake encuentre las configuraciones generadas por Conan
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_BINARY_DIR}/Release/generators")

# Incluir el archivo con la configuración de Conan
include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

# Incluir directorios de encabezados
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Establecer el estándar de C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Especificar el directorio de salida para los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Incluir el módulo ExternalProject
include(ExternalProject)

# Habilitar testing
include(CTest)

# Recopilar todos los archivos fuente en la carpeta src
file(GLOB SOURCES "src/*.c")

# Buscar dependencias usando Conan y PkgConfig
find_package(cJSON REQUIRED)
find_package(unity REQUIRED)

# Crear el ejecutable
add_executable(shell ${SOURCES})

# Enlazar las librerías
target_link_libraries(shell PRIVATE
    cjson::cjson
    unity::unity
)

# Copiar config.json al directorio de salida del ejecutable
add_custom_command(
    TARGET shell POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/config.json
            $<TARGET_FILE_DIR:shell>/config.json
)

# Añadir subdirectorios
add_subdirectory(monitor)
add_subdirectory(Testing)