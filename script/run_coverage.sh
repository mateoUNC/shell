#!/bin/bash
echo "Collecting code coverage with gcov and gcovr..."

# Cambiar al directorio raíz del proyecto
PROJECT_ROOT=$(dirname "$(dirname "$(realpath "$0")")")
cd "$PROJECT_ROOT"

# Directorio de salida para los informes de cobertura
COVERAGE_DIR="./coverage_report"
mkdir -p "$COVERAGE_DIR"

# Archivo para errores de cobertura
ERROR_FILE_FLAG="$PROJECT_ROOT/tests_errors.txt"

# Asegurarse de que la variable esté definida
if [ -z "$ERROR_FILE_FLAG" ]; then
  echo "ERROR_FILE_FLAG no está definido. Abortando."
  exit 1
fi

# Ejecutar gcovr para generar reportes en HTML, XML, y TXT
gcovr -r . --exclude 'Testing' --exclude 'prometheus-client-c' --html --html-details -o "$COVERAGE_DIR/coverage.html"
gcovr -r . --exclude 'Testing' --exclude 'prometheus-client-c' --xml -o "$COVERAGE_DIR/coverage.xml"
gcovr -r . --exclude 'Testing' --exclude 'prometheus-client-c' --txt > "$ERROR_FILE_FLAG"

echo "Coverage report generated in $COVERAGE_DIR"
cat "$ERROR_FILE_FLAG"
