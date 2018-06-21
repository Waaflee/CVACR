## Proyecto Final de la cátedra Microcontroladores y Electrónica de Potencia de la Facultad de Ingeniería de la Universidad Nacional de Cuyo

### ATMEGA328p como IoT

Consiste Atmega328p programado como un interprete de comandos via serial, diseñado para controlar un eje accionado por un motor PaP con driver tipo pololu (a4988).
Además un servidor basado en nodejs servirá una página web la cual se utilizará como interfaz para controlar el eje (localhost:8080 como servidor estático para front end).

Este Proyecto es Fuertemente dependiente de la librería de abstracción de hardware [AVRDuino](https://github.com/Waaflee/AVRDuino) para el manejo de un ATMEGA328p, que controlará los motores.

Dado que este proyecto contiene submódulos, la metodología corriente de trabajo (git clone) no funcionará. En vez de eso se debe proceder de la siguiente manera:
 - clonar el repositorio de forma recursiva `git clone --recursive $REPOSITORIO`(reemplazar $REPOSITORIO por la dirección correcta) esto descargara también los submódulos, que de otra forma aparecerían como carpetas vacías. Debe notarse que los submódulos
Estarán en estado DETACHED HEAD (apuntando a commit en particular) y no al master o rama de producción de ese repositorio.

- Cuando algún integrante del equipo actualize la version del submódulo empleada por este repositorio los demás deberán sincronizarse con este cambio con `git submodule update --init --recursive`, para evitar incompatibilidades y otros fenómenos no deseados.
