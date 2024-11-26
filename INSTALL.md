## INSTALL.md

### Instrucciones para Compilar, Ejecutar y Utilizar la Shell y el Programa de Monitoreo

Estas instrucciones detallan cómo instalar y configurar el proyecto de la shell y el programa de monitoreo en un entorno Linux. Los pasos están alineados con lo que se realiza en GitHub Actions para compilar y probar el proyecto.

#### Prerrequisitos

- **Sistema Operativo**: Linux
- **CMake**: Versión 3.15 o superior
- **Conan**: Para gestionar las dependencias
- **gcc/g++**: Para compilar el código
- **Git**: Para clonar el repositorio

##### Instalación de Herramientas Necesarias

#### Paso 1: Clonar el Repositorio

Clona el repositorio del proyecto usando Git:

```bash
git clone https://github.com/ICOMP-UNC/so-i-24-chp2-mateoUNC.git
cd so-i-24-chp2-mateoUNC
```

#### Paso 2: Configurar e Instalar Dependencias

Ejecuta el script `setup.sh` para configurar el entorno y preparar las dependencias necesarias:

```bash
chmod +x setup.sh
./setup.sh
```

#### Paso 3: Compilar el Proyecto con CMake

Una vez instaladas las dependencias, puedes compilar el proyecto usando CMake:

```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake ../
make
```

Esto compilará tanto la shell como el programa de monitoreo, y colocará los ejecutables en el directorio `bin/`.

#### Paso 4: Ejecutar la Shell y el Programa de Monitoreo

Los ejecutables están en el directorio `bin/`. Para ejecutar la shell:

```bash
./bin/shell
```

Para iniciar el monitoreo desde la shell, puedes utilizar el comando interno:

```bash
start_monitor
```

#### Uso de la Shell

- **Comandos Internos**: La shell soporta varios comandos internos, como `cd`, `echo`, `start_monitor`, `stop_monitor`, y `status_monitor`.
- **Redirecciones y Pipes**: Puedes utilizar redirecciones (`<`, `>`) y pipes (`|`) como lo harías en una shell tradicional.

#### Pruebas y Cobertura

El proyecto incluye pruebas unitarias que se pueden ejecutar para verificar la funcionalidad de la shell y el programa de monitoreo.

Para ejecutar las pruebas:

```bash
cd build
ctest
```

Para generar un reporte de cobertura usando `gcov` y `lcov`:

```bash
# Compilar con flags de cobertura
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS="--coverage" -DCMAKE_CXX_FLAGS="--coverage"
cmake --build .

# Ejecutar pruebas
ctest

# Generar reporte de cobertura
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --list coverage.info
```

El archivo `coverage.info` contendrá la información de cobertura, que se puede visualizar con herramientas compatibles.

### Notas Finales

- Asegúrate de tener todos los permisos necesarios para ejecutar los scripts y los ejecutables.
- Puedes modificar el archivo `config.json` para ajustar la configuración del programa de monitoreo, como el intervalo de muestreo y las métricas a recolectar.

Estas instrucciones te permitirán instalar, compilar, ejecutar y probar el proyecto de manera efectiva en un entorno Linux.

