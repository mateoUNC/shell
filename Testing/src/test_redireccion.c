// test_redireccion.c
//
// Este archivo contiene los tests de redirección de entrada y salida para la
// shell, incluyendo pruebas para archivos de entrada con una sola línea,
// múltiples líneas y archivos vacíos.

#include "test_redireccion.h"
#include "commands.h"
#include "test_mocks.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Test de redirección de entrada con el comando "cat".
 *
 * Este test verifica que el comando "cat" pueda leer desde un archivo de
 * entrada y redirigir la salida a un archivo de salida, comprobando que el
 * contenido se mantenga igual.
 */
void test_cat_redireccion_entrada(void) {
  // Crear archivo de entrada con contenido de prueba
  FILE *entrada = fopen("entrada.txt", "w");
  TEST_ASSERT_NOT_NULL_MESSAGE(entrada,
                               "No se pudo crear el archivo de entrada.");

  fprintf(entrada, "Este es un test de redirección de entrada.\n");
  fclose(entrada);

  // Redirigir la salida de `cat` a un archivo de salida
  char *args[] = {"cat", "<", "entrada.txt", ">", "salida.txt", NULL};
  int running = 1;

  // Ejecutar el comando "cat" con redirección
  execute_command(args, &running);

  // Verificar el contenido del archivo de salida
  FILE *salida = fopen("salida.txt", "r");
  TEST_ASSERT_NOT_NULL_MESSAGE(salida,
                               "No se pudo abrir el archivo de salida.");

  char buffer[256];
  fgets(buffer, sizeof(buffer), salida);
  fclose(salida);

  TEST_ASSERT_EQUAL_STRING("Este es un test de redirección de entrada.\n",
                           buffer);

  // Eliminar archivos temporales
  remove("entrada.txt");
  remove("salida.txt");
}

/**
 * @brief Test de redirección de entrada desde un archivo con múltiples líneas.
 *
 * Verifica que el comando "cat" pueda procesar correctamente un archivo con
 * varias líneas, asegurando que cada línea se conserve en el archivo de salida
 * en el mismo orden.
 */
void test_cat_redireccion_entrada_multilinea(void) {
  // Crear archivo de entrada con varias líneas
  FILE *entrada = fopen("entrada_multilinea.txt", "w");
  TEST_ASSERT_NOT_NULL_MESSAGE(entrada,
                               "No se pudo crear el archivo de entrada.");

  fprintf(entrada, "Línea 1\nLínea 2\nLínea 3\n");
  fclose(entrada);

  // Redirigir la salida de `cat` a un archivo de salida
  char *args[] = {
      "cat", "<", "entrada_multilinea.txt", ">", "salida_multilinea.txt", NULL};
  int running = 1;

  execute_command(args, &running);

  // Verificar el contenido del archivo de salida
  FILE *salida = fopen("salida_multilinea.txt", "r");
  TEST_ASSERT_NOT_NULL_MESSAGE(salida,
                               "No se pudo abrir el archivo de salida.");

  char buffer[256];
  fgets(buffer, sizeof(buffer), salida);
  TEST_ASSERT_EQUAL_STRING("Línea 1\n", buffer);

  fgets(buffer, sizeof(buffer), salida);
  TEST_ASSERT_EQUAL_STRING("Línea 2\n", buffer);

  fgets(buffer, sizeof(buffer), salida);
  TEST_ASSERT_EQUAL_STRING("Línea 3\n", buffer);

  fclose(salida);
  remove("entrada_multilinea.txt");
  remove("salida_multilinea.txt");
}

/**
 * @brief Test de redirección de entrada desde un archivo vacío.
 *
 * Verifica que el comando "cat" maneje correctamente un archivo de entrada
 * vacío, de modo que no genere contenido en el archivo de salida.
 */
void test_cat_redireccion_entrada_vacia(void) {
  // Crear un archivo de entrada vacío
  FILE *entrada = fopen("entrada_vacia.txt", "w");
  fclose(entrada);

  // Redirigir la salida de `cat` a un archivo de salida vacío
  char *args[] = {"cat", "<", "entrada_vacia.txt", ">", "salida_vacia.txt",
                  NULL};
  int running = 1;

  execute_command(args, &running);

  // Verificar que el archivo de salida esté vacío
  FILE *salida = fopen("salida_vacia.txt", "r");
  TEST_ASSERT_NOT_NULL_MESSAGE(salida,
                               "No se pudo abrir el archivo de salida.");

  char buffer[256];
  TEST_ASSERT_NULL(fgets(buffer, sizeof(buffer), salida));

  fclose(salida);
  remove("entrada_vacia.txt");
  remove("salida_vacia.txt");
}
