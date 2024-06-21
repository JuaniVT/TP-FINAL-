#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct {
	char dia [3];
	char mes [3];
	char anio [5];
 } Fecha;

typedef struct   // CREACION DE OTRA ESTRUCTURA PARA REGISTRARSE Y PODER LOGEARSE EN EL SISTEMA
{
    char nombre_Apellido [40];
    char dni [9];
    char tele [12];
    char email [40];
    Fecha nacimiento;
    char contra [20];
    char user [15];
    char rol [10];
} usuario;
void registro_En_El_sistema (char []);
usuario crear_Cuenta (FILE*);
void nombre_Usuario (FILE*, usuario*);
void contrasena (FILE*, usuario*);
usuario pedir_Datos_Registro (FILE*, usuario);
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
int verificar_Telefono (char []);
int verificar_Existencia_Persona (FILE *, char []);
int verificar_Mail (char []);
int comprobar_Mayusculas_User (char []);
int comprobar_Caracteres_Usuario (char []);
int verificar_dos_o_mas_palabras (char []);
int verificar_Caracteres_Edad (char [], char [], char []);
int comprobar_Numeros_Edad (char []);
int comprobar_Edad (int, int, int);
int verificar_Dia (int, int);
int verificar_Mes (int);
int verificar_Anio (int);
int verificar_Rol (char);
#endif // REGISTRO_H_INCLUDED
