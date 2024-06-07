#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct {
	int dia;
	int mes;
	int anio;
 } Fecha;

typedef struct   // CREACION DE OTRA ESTRUCTURA PARA REGISTRARSE Y PODER LOGEARSE EN EL SISTEMA
{
    char nombre [30];
    char apellido [30];
    int dni;
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
#endif // REGISTRO_H_INCLUDED
