Instrucciones de uso: 1. Ubicar archivo en la terminal 2. Ejecutar con make

Supuestos: Esta tarea significo un complicado uso de pipes, ya que estas no podian ser reutilizadas para la concurrencia del juego,
por esta razon me sujete al hecho de que solo se puden jugar 2 turnos (ya que el programa se queda atrapado en el jugador 2, osea el hijo), y solo escribi el codigo del movimiento del ajedrez en el jugador 1 para hacer menos tediosa la revision de la tarea.
En el caso del jugador 2 solo cambiaba el movimiento del peon y el numero al cual identificaban las piezas. En Tarea2.c existe el uso
de memoria compartida y de una pipe "bidereccional".
