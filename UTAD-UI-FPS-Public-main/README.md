# UTAD-UI-FPS-Public
 
Documentación Práctica UI Carlos Rodríguez Calzada

Pido disculpas por las interfaces que he creado yo mismo y el daño que puedan causar a cualquiera que las vea.

Implementaciones:

- Barra de vida:
	Con un delegado bindeo el recibir daño del jugador con la progress bar para actualizarla.
	Cuando actualiza la vida si está por debajo del umbral activa el cambio de color.
	El cambio de color se hace durante el tick del widget para que haga un ciclo entre rojo y verde.
	Los valores del umbral y del tiempo del ciclo están definidas al principio del PlayerHealthBar.cpp

- Crosshair:
	Para las animaciones del crosshair tengo dos funciones, una para cuando el personaje se mueve y otra para cuando dispara. 
	El personaje es quien llama a las funciones cuando realiza las acciones.
	Simularían la pérdida de precisión por el movimiento o por el retroceso del arma. Como solo hay un png me he limitado a hacerlo más grande y ya.
	Del mismo modo, hay otra función que la cambia el color si tiene un enemigo delante. También llamada desde el jugador cuando lo detecta con un raycast.

- HitMarker:
	Hay un widget que es simplemente un fondo rojo con algo de trasparencia. Cuando el jugador recibe daño se muestra y automáticamente se esconde tras el valor fijado en PlayerHitMarker.cpp

- PantallaSplash (me gusta el naranja):
	Este es muy similar al anterior. Un widget que se muestra, esta vez, desde el begin play y dura lo que esté definido en el SplashScreen.h o en el Blueprint. Por alguna razón esta es la única UPROPERTY que uso. Lo hice hace mucho pero me daba pereza hacer la documentación, no tenía tanto manejo por entonces.

- Árbol de Habilidades:
	En el enum tengo puesto todas las posibles ramas de mejoras del personaje. En este caso solo velocidad, salud y daño. Para añadir una nueva rama, solo hay que añadir un nuevo elemento al Enum. (Y todo lo relativo al widget claro, colocar los botones y eso)
	Cada nodo del árbol tiene dos variables a modificar. El tipo de habilidad y lo que cuesta. Y cuando lo pulsas te muestra el menú de confirmación si tienes puntos suficientes, o si no, uno de que no tienes suficientes puntos.
	El árbol, como tal, gestiona todo. Tiene la cuenta de cuántos puntos tienes, cuántos puntos tienes en cada habilidad y en función de ello qué botones muestra o no. Por defecto, solo muestra los de 1 punto. Y una vez desbloqueada, muestra el siguiente.
	Todos los botones están en un mismo array ordenado y se hace un pequeño cálculo para saber qué botón es el siguiente dentro de la lista.

