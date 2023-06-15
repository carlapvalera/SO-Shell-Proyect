INTEGRANTES:
Francisco Vicente Suarez Bellon
Carla Sunami Perez Valera
Jan Carlos Perez Gonzalez
 GRUPO C-312

NOTA IMPORTANTE:
Para acceder a la explicación de alguna funcionalidad en específico se debe escribir help <keyword>
EJEMPLO: help basic
COMANDOS BASICOS:

Se crea en el shell un nodo*, cuya estructura posee: un int identificación, un char** instrucción, un nodo* izquierdo y un nodo* derecho.
Por supuesta también hayun enum, con todas las operaciones que contiene el shell.Cuando escribimos una linea en la consola esta se lee y 
se parsea, lo cual resulta en la creación de un nodo* con la instrucción. el orden de dichas instrucciones se ve reflejadomen un árbol de
prioridad:
1) ;
2) if-then-else-end
3) && y ||
4) |
5) >> y >
6) <

$:
Aparece siempre este signo al final del prompt.
ERDOS-Shell $

cd:
Cambia el directorio en que nos encontramos posicionados hacia uno nuevo indicado por el usuario.En este comando se compara el char** 
instrucción[0] con la palabra cd, luego se realiza el cambio de directorio con instrucción[1], para hacer el cambio simplemente se pasa
 el nuevo directorio y se usa la función chdir(cambio de directorio), la cual si devuelve mayor que cero el cambio es efectivo, en caso 
contrario se lanza una línea de error "Error changing directory to <path>" y se devuelve 1.
EJEMPLO:
ERDOS-Shell $ pwd 
/some/directory 
ERDOS-Shell $ cd /new/path 
ERDOS-Shell $ pwd 
/new/path 
ERDOS-Shell $

>, <, >>:
Redirige la entrada y salida estándar de comandos hacia/desde ficheros.

>) 
En este comando primero se realiza una copia a la salida estandar para tenerla guardada, para copiar el archivo que vamos a recibir
 como salida una vez abierto. Despues hacemos freopen con la instruccion[0] (nombre del archivo a abrir) y la salida estandar en modo 
de escritura. Luego se realiza el comando descrito en el nodo* izquierdo, una vez ejecutado el comando se reestablece la salida estandary
 se cierra la copia de la salida para no tener archivos innecesarios abiertos, se retorna si el resultado el comando fue exit status 0 o
 fail status 1.

EJEMPLO:
ERDOS-Shell $ command > file

<) 
En este comando primero se realiza una copia a la salida estandar para tenerla guardada, para copiar el archivo que vamos a recibir
 como salida una vez abierto. Despues hacemos freopen con la instruccion[0] (nombre del archivo a abrir) y la salida estandar en modo 
de escritura. Luego se realiza el comando descrito en el nodo* izquierdo, una vez ejecutado el comando se reestablece la etrada
 estandar, se cierra la copia de la entrada para no tener archivos innecesarios abiertos y se retorna si el resultado el comando fue 
exit status 0 o fail status 1.

EJEMPLO:
ERDOS-Shell $ command < file

>>) 
En este comando primero se realiza una copia a la salida estandar para tenerla guardada, para copiar el archivo que vamos a recibir
 como salida una vez abierto. Despues hacemos freopen con la instruccion[0] (nombre del archivo a abrir) y la salida estandar en modo
 de concatenar. Luego se realiza el comando descrito en el nodo* izquierdo, una vez ejecutado el comando se reestablece la salida estandar,
 autoseguido se cierra la copia de la salida para no tener archivos innecesarios abiertos y se retorna si el resultado el comando fue
 exit status 0 o fail status 1.

EJEMPLO:
ERDOS-Shell $ command >> file 

|:
Redirige la salida de un comando hacia la entrada de otro.
En este comando se crea en principio un int* de largo 2 que será el file descript de la tubería. Luego se crea la tubería 
(en caso insatisfactorio se lanza un error "Error creating pipe" y se devuelve fail status 1), luego se hace una copia de la salida 
estandar. Se abre la parte de escritura de la tubería en la salida estandar y luego se ejecuta el nodo* izquierdo de la tubería, o sea
 el comando que está antes del pipe; en caso de que haya errores de ejecución, se reestablece la salida estandar y se devuelve el fail 
status 1. Luego en caso que el comando anterior haya terminado con exit status 0 se realiza una copia a la entrada estandar, luego se
 procede de forma análoga con la misma y la parte de lectura de la tubería, se ejecuta el comando que esta posterior al pipe dando su
 resultado en una variable entera que indica si cerró con exit status 0, o fail status 1, variable que se devuelve luego de reestablecer 
la entrada.

EJEMPLO:
ERDOS-Shell $ command1 | command 2 

#:
Luego de este caracter se ignora todo lo que esta a continuacion de la línea
Al encontrarse dicho caracter se cambia por un 0, ya que este es el terminal de los punteros de char,  así truncamos la entrada del
 usuario antes de construir el árbol parseando la línea.

exit:
Cierra el shell. Se compara el comando con la palabra "exit" y se cierra el shell. Luego de dicho comando todo lo que se escriba 
será ignorado.

EJEMPLO:
ERDOS-Shell $ exit es lo mismo que ERDOS-Shell § exit qwerty


ENCADENAR COMANDOS:

Se crea en el shell un nodo*, cuya estructura posee: un int identificación, un char** instrucción, un nodo* izquierdo y un nodo* derecho.
Por supuesta también hayun enum, con todas las operaciones que contiene el shell.Cuando escribimos una linea en la consola esta se lee y 
se parsea, lo cual resulta en la creación de un nodo* con la instrucción. el orden de dichas instrucciones se ve reflejadomen un árbol de
prioridad:
1) ;
2) if-then-else-end
3) && y ||
4) |
5) >> y >
6) <


;
Se ejecutan varios comandos en la misma linea unom a continuacion de otro en el orden escrito.
En este operador se ejecuta primero el hijo izquierdo y luego el hijo derecho.

&&:
Permite unir varios comandos y el  operador N-símo solo se ejecutará si el operador N-1 tiene un status satisfactorio( lo que seria un
AND en logica).En este operador se ejecuta el hijo izquierdo y solo si devuelve exit status 0 se ejecuta el hijo derecho.

||:
Permite poner varios comandos y retorna el primer comando que tenga un exit status 0, si esto no pasa rtealiza tods los comandos y retorna
 fail status 1( lo que seria un OR en logica).En este operador se ejecuta el hijo izquierdo en caso de que este finalice con fail status 1
 es que se ejecuta el hijo derecho.


HISTORY:
Enseña el historial de los ultimos 10 comandos ejecutados organizados por antiguedad del mas antiguo al menos. El comando history tambien 
es guardado en el historial.El comando tiene "memoria", cerrar el prompt no hace que se pierdan los comandos escritos, si el shell se 
cierra mediante el comando exit, si se cerra manual o se apaga la pc, se queda con el estado de la ultima vez que se cerro correctamente.

EJEMPLO:
ERDOS-Shell $ history
1: command 1
2: command 2 > file
3: command 5 | command 6 #comentario de ese command
4: history
ERDOS-Shell $



EJEMPLO:
ERDOS-Shell $ history
1: command 1
2: command 2 > file
3: command 5 | command 6 #comentario de ese command
4: history
ERDOS-Shell $ exit
user@machine $ ./a.out
ERDOS-Shell $ history
1: command 1
2: command 2 > file
3: command 5 | command 6 #comentario de ese command
4: history
5: history

EJEMPLO:
ERDOS-Shell $ history
1: command 1
2: command 2 > file
3: command 5 | command 6 #comentario de ese command
4: history
ERDOS-Shell $ again 1
ERDOS-Shell $ history
1: command 1
2: command 2 > file
3: command 5 | command 6 #comentario de ese command
4: history
5: command 1
6: history
ERDOS-Shell $

PD again es imprescindible que al menos haya un espacio entre again y el numero.


EXP CONDICIONALES:(IF, THEN, ELSE, END)

Se crea en el shell un nodo*, cuya estructura posee: un int identificación, un char** instrucción, un nodo* izquierdo y un nodo* derecho.
Por supuesta también hayun enum, con todas las operaciones que contiene el shell.Cuando escribimos una linea en la consola esta se lee y 
se parsea, lo cual resulta en la creación de un nodo* con la instrucción. el orden de dichas instrucciones se ve reflejadomen un árbol de
prioridad:
1) ;
2) if-then-else-end
3) && y ||
4) |
5) >> y >
6) <

if:
Evalúa comandos y dependiendo de que si finaliza satisfactoriamente o no se ejecuta una u otra expresión.
Al parsear esta expresión se pregunta si existe "then" para asegurarse de que esta escrita con la estructura correcta.

then:
Se realiza en caso del que el if haya sido satisfactorio, la cual evalua comandos.
Al parsear esta expresión se pregunta si existe "else" para asegurarse de que esta escrita con la estructura correcta.

else:
Evalúa comandos en caso de que el if no haya sido satisfactorio.
Al parsear esta expresión se pregunta si existe "end" para asegurarse de que esta escrita con la estructura correcta.

end:
Se escribe luego de haber concluido con toda la expresión condicional que se quiere evaluar.

EJEMPLO:
ERDOS Shell $ if command1 then command2 else command3 end
ERDOS Shell $
IMPORTANTE:
Al escribir esta expresión se debe dejar al menos un espacio entre expresión y comando para evitar errores como:
ERDOS Shell $ comand > rifa.txt
el archivo rifa.txt contiene en el la palabra if, de manera que si no se tuviera en cuenta los espacios el programa 
esta propenso a tener errores al tomar esta como una palabra clave.


FUNCIONALIDADES:
Ejecutar más de una tubería en una misma línea. Cuando parseamos aemas de crearse un árbol este dicho árbol es de prioridad( leyendose de 
izquierda a derecha, formandose nodos* donde su hijo izquierdo es el comando y el derecho será otra tubería hasta llegar al final de la 
línea donde tendrá en caso de ser una tubería, otro comando.
El operador | lo que hace es que mandar la salida del hijo izquierdo a la entrada del hijo derecho, por lo que tener más de una tubería
en una línea de código enlazará la salida de los nodos* izquierdos con la entrada de los nodos* derechos.

EJEMPLO:
ERDOS-Shell $ command1 | command2 | command3 


FUNCIONALIDADES:
Los comandos que se introducen en el Shell puede tener todos los espacios intermedios entre estos. Por ello, el parse funciona
separando la linea de caracteres por los caracteres especiales( |, ||, ;, &&,<, >, >>, if, then, else), conviertendolo en un árbol donde
las hojas son los comandos más simples.
Aunque en el caso de la expresión  if-then-else si nes necesario al menos dejar un espacio entrem expresiones:
ERDOS Shell $ comand > rifa.txt

EJEMPLO:
ERDOS-Shell $ command1 | command2 
ERDOS-Shell $ command1|command2 
ERDOS-Shell $ command1     |   command2 
ERDOS-Shell $
