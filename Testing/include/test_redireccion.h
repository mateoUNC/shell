// test_redireccion.h
//
// Declaración de funciones para probar la redirección de entrada y salida en la
// shell.

#ifndef TEST_REDIRECCION_H
#define TEST_REDIRECCION_H

/**
 * @brief Test de redirección de entrada con archivo de una sola línea.
 *
 * Verifica que el comando "cat" pueda leer la entrada correctamente desde un
 * archivo de una sola línea y redirigir la salida a otro archivo.
 */
void test_cat_redireccion_entrada(void);

/**
 * @brief Test de redirección de entrada con un archivo de múltiples líneas.
 *
 * Verifica que el comando "cat" pueda leer correctamente varias líneas desde un
 * archivo y redirigir la salida a otro archivo.
 */
void test_cat_redireccion_entrada_multilinea(void);

/**
 * @brief Test de redirección de entrada con un archivo vacío.
 *
 * Verifica que el comando "cat" maneje correctamente la redirección de entrada
 * desde un archivo vacío, sin generar contenido en el archivo de salida.
 */
void test_cat_redireccion_entrada_vacia(void);

#endif // TEST_REDIRECCION_H
