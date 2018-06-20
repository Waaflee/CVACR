## Proyecto Final de la cátedra Microcontroladores y Electrónica de Potencia de la Facultad de Ingeniería de la Universidad Nacional de Cuyo

### CVACR: Computer Vision Aided Cartesian Robot o Robot Cartesiano Asistido Por Visión Computacional

Consiste en un robot Cartesiano con capacidades de reconocimiento de imágenes, utilizadas para detectar objetos y sus posiciones en un sistema de referencia.

Este Proyecto es Fuertemente dependiente de la librería de abstracción de hardware [AVRDuino](https://github.com/Waaflee/AVRDuino) para el manejo de un ATMEGA328p, que controlará los motores, y de [OpenCV](https://opencv.org/) para el reconocimiento de imágenes.

Dado que este proyecto contiene submódulos, la metodología corriente de trabajo (git clone) no funcionará. En vez de eso se debe proceder de la siguiente manera:
 - clonar el repositorio de forma recursiva `git clone --recursive $REPOSITORIO`(reemplazar $REPOSITORIO por la dirección correcta) esto descargara también los submódulos, que de otra forma aparecerían como carpetas vacías. Debe notarse que los submódulos
Estarán en estado DETACHED HEAD (apuntando a commit en particular) y no al master o rama de producción de ese repositorio.

- Cuando algún integrante del equipo actualize la version del submódulo empleada por este repositorio los demás deberán sincronizarse con este cambio con `git submodule update --init --recursive`
