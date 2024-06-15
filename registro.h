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
    char rol [10];
} usuario;
int comprobar_Usuario (FILE *arch, char []);
int comprobar_Contra (FILE *, char []);
int verificar_Contrasena (char[]);
int verificar_Caracteres (char [], int);
int verificar_Existencia (FILE*, char []);
int verificar_Space (char[]);
int comprobar_Numeros_Dni (char []);
int verificar_Contrasena (char[]);
int comprobar_Mayusculas (char[]);
int verificar_minusculas (char []);
int comprobar_Numeros (char []);
int verificar_Dni (char []);
int verificar_Existencia_Persona (FILE *, char []);
int verificar_Mail (char []);
int comprobar_Mayusculas_User (char []);
int comprobar_Caracteres_Usuario (char []);
int verificar_dos_o_mas_palabras (char []);
int comprobar_Edad (int, int, int);
int verificar_Dia (int, int);
int verificar_Mes (int);
int verificar_Anio (int);
int verificar_Rol (char);
#endif // REGISTRO_H_INCLUDED
