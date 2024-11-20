#!/bin/bash

set -e  # Salir si algún comando falla

echo "Actualizando el sistema e instalando dependencias..."
sudo apt update
sudo apt install -y cmake gcc g++ python3-pip build-essential libmicrohttpd-dev doxygen graphviz valgrind
sudo apt install -y pkg-config
sudo apt install -y libcurl4-openssl-dev
sudo apt install -y python3.11-venv

echo "Inicializando y actualizando submódulos..."
git submodule init
git submodule update --recursive

echo "Creando y activando el entorno virtual..."
python3 -m venv venv
source venv/bin/activate

echo "Instalando Conan..."
pip install conan
conan --version

echo "Clonando prometheus-client-c..."
git clone https://github.com/digitalocean/prometheus-client-c.git

echo "Corrigiendo incompatibilidad en promhttp.c..."
sed -i 's/&promhttp_handler/(MHD_AccessHandlerCallback)promhttp_handler/' prometheus-client-c/promhttp/src/promhttp.c

echo "Compilando y configurando la biblioteca prom..."
mkdir -p prometheus-client-c/buildprom
cd prometheus-client-c/buildprom
cmake ../prom
make
sudo make install

echo "Compilando y configurando la biblioteca promhttp..."
cd ../..
mkdir -p prometheus-client-c/buildpromhttp
cd prometheus-client-c/buildpromhttp
cmake ../promhttp
make
sudo make install

echo "Actualizando el cargador dinámico..."
echo "/usr/local/lib" | sudo tee -a /etc/ld.so.conf.d/local-libs.conf
sudo ldconfig

echo "Instalando dependencias con Conan..."
mkdir build && cd build
conan install .. --build=missing

echo "Configuración completada exitosamente."

