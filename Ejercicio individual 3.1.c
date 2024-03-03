#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char**argv) {
	//Establecemos conexión con la base de datos
	MYSQL *conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "Error al inicializar la conexion: %s\n", mysql_error(conn));
		return 1;
	}
	if (mysql_real_connect(conn, "localhost", "root", "mysql", "Kahoot", 0, NULL, 0) == NULL) {
		fprintf(stderr, "Error al conectarse a la base de datos: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 1;
	}
	
	printf("Conexion exitosa a la base de datos Kahoot\n");
	
	
	//Consultamos la partida con más puntos
	
	MYSQL_RES*resultado;
	MYSQL_ROW row;
	int err;
	int puntos;
	int maxpuntos;
	
	err=mysql_query(conn,"SELECT*FROM partida");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos la tbla virtual
	resultado = mysql_store_result(conn);
	
	//obtenemos la primera fila de la tabla
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			puntos = atoi (row[3]);
			
			if (puntos > maxpuntos)
			{
			  maxpuntos = puntos;
			}
			row = mysql_fetch_row(resultado);
	}
		printf("Partida con más puntos: %d\n", maxpuntos);
		
	mysql_close(conn);
	return 0;
}


