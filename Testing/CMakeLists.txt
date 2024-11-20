# Testing/CMakeLists.txt

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include        # Headers de tu proyecto principal
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Headers de tus tests
)

# Coleccionar archivos fuente de test (excluyendo test_mocks.c)
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/test_mocks.c")

# Definir test_mocks.c por separado
set(TEST_MOCKS ${CMAKE_CURRENT_SOURCE_DIR}/src/test_mocks.c)

# Crear el ejecutable de test incluyendo test_mocks.c y los otros test_sources
add_executable(test_runner ${TEST_MOCKS} ${TEST_SOURCES})

# Agregar otros archivos fuente del proyecto, EXCLUYENDO prompt.c
target_sources(test_runner PRIVATE
    ${PROJECT_SOURCE_DIR}/src/commands.c
    ${PROJECT_SOURCE_DIR}/src/parser.c
    ${PROJECT_SOURCE_DIR}/src/utils.c
    # ${PROJECT_SOURCE_DIR}/src/prompt.c   # <-- Asegúrate de que esta línea está comentada o excluida
    ${PROJECT_SOURCE_DIR}/src/monitorHandle.c
    ${PROJECT_SOURCE_DIR}/src/signals.c
)

# Añadir la definición de compilación para redefinir exit
target_compile_definitions(test_runner PRIVATE exit=test_exit)

# Añadir las opciones de enlace para envolver printf
target_link_options(test_runner PRIVATE "-Wl,--wrap=printf")

# Linkear las librerías necesarias
target_link_libraries(test_runner PRIVATE cjson::cjson unity::unity)

# Añadir opciones de cobertura si se usa GCC o G++
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(test_runner PRIVATE --coverage)
    target_link_options(test_runner PRIVATE --coverage)
endif()

# Añadir el test a CTest
add_test(NAME test_runner COMMAND test_runner)
