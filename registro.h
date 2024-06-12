#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct {
	int dia;
	int mes;
	int anio;
 } Fecha;

typedef struct   // CREACION DE OTRA ESTRUCTURA PARA REGISTRARSE Y PODER LOGEARSE EN EL SISTEMA
{
    char nombre_Apellido [40];
    char dni [9];
    char email [30];
    Fecha nacimiento;
    char contra [20];
    char user [15];
} usuario;

int comprobar_Nombre (FILE*, char []);
int comprobar_Contra (FILE *, char []);
int verificar_Contrasena (char[]);
int verificar_Caracteres (char [], int);
int verificar_Existencia (FILE*, char []);
int verificar_Space (char[]);
int verificar_Contrasena (char[]);
int comprobar_Mayusculas (char[]);
int verificar_minusculas (char []);
int comprobar_Numeros (char []);
int verificar_Dni (char []);
int verificar_Existencia_Persona (FILE *, char []);
int verificar_Mail (char mail []);
#endif // REGISTRO_H_INCLUDED
