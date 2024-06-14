#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
//====================================================================================
// TRABAJO FINAL PROGRAMACION I
// Integrantes: Manuel Segovia, Juan Ignacio Valle Torres, Ignacio Agustin Villarreal
// SISTEMA PARA CONCESIONARIA DE AUTOS
//====================================================================================
void registro_En_El_sistema (char []);
usuario crear_Cuenta (FILE*);
usuario nombre_Usuario (FILE*, usuario*);
usuario contrasena (FILE*, usuario*);
usuario pedir_Datos_Registro (FILE*, usuario);
void mostrar_Archivo (char []);
void mostrarUsuario(usuario);
int main()
{
    // VARIABLES DEL MAIN =====================
    int ops = 1; // SWITCH
    char seguirMain;
    // ========================================
    // CREACION DE ARCHIVOS ===================
    char autosArch [] = "autosArch.bin";
    char usuarios [] = "usuarios.bin";
    char ventas [] = "ventas.bin";
    char personas [] = "personas.bin";
    // ========================================

    while (ops != 0)
    {
        printf ("------------------------------------------\n");
        printf ("BIENVENIDO\n");
        printf ("------------------------------------------\n");
        printf ("1- LOGIN\n");
        printf ("2- REGISTRARSE\n");
        printf ("0- PARA CERRAR EL SISTEMA\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        scanf ("%d", &ops);
        printf ("\n");
        switch (ops)
        {
        case 1:
            login_Persona (usuarios);
            break;
        case 2:
            registro_En_El_sistema (usuarios);
            break;
        case 46277918:
            mostrar_Archivo (usuarios);
            break;
        case 0:
            printf ("GRACIAS POR CONFIAR EN NOSOTROS\n");
            break;
        default:
            printf ("------------------------------------------------------------------\n");
            printf ("DISCULPE PERO EL VALOR INGRESADO NO CORRESPONDE A NINGUN EJERCICIO\n");
            printf ("Ingrese cualquier elemento p/continuar\n");
            printf ("AQUI: ");
            fflush (stdin);
            scanf ("%c", &seguirMain);
            break;
        }
    }
    return 0;
}
// registro
void registro_En_El_sistema (char archivo [])
{
    printf ("------------------------------------------------------------------\n");
    printf ("CREACION DE USUARIO\n");
    printf ("------------------------------------------------------------------\n");
    FILE *arch = fopen (archivo, "a+b");
    usuario persona;
    if (arch != NULL)
    {
        persona = crear_Cuenta (arch);
        fseek (arch, 0, SEEK_END);
        fwrite (&persona, sizeof (usuario), 1, arch);
    }
    fclose (arch);
}
// ACA SE CREA EL LA CUENTA ================================
usuario crear_Cuenta (FILE *arch)
{
    usuario personaAux;
    personaAux = pedir_Datos_Registro (arch, personaAux);
    nombre_Usuario (arch, &personaAux);
    contrasena (arch, &personaAux);

    return personaAux;
}
// ===================================================
// registro al sistema de usuario
usuario nombre_Usuario (FILE* arch, usuario *persona)
{
    int variableUser = 1;
    while (variableUser != 0)
    {
        printf ("Ingrese su nombre de usuario: ");
        fflush (stdin);
        gets ((*persona).user);
        variableUser = comprobar_Usuario (arch, (*persona).user);
        if (variableUser != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REINGRESAR NOMBRE DE USUARIO\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
    return (*persona);
}
// ======================================================
// CREA CONTRASEÑA
usuario contrasena (FILE* arch, usuario *persona)
{
    int variableContra = 1;
    //a cada funcion hay que agregarle su propia variable para recibir el valor =)
    while (variableContra != 0)
    {
        printf ("Ingrese una contrasena: ");
        fflush (stdin);
        gets ((*persona).contra);
        variableContra = comprobar_Contra (arch, (*persona).contra);
        if (variableContra == 0)
            {
             variableContra = verificar_Contrasena ((*persona).contra);
            }
        if (variableContra != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REESCRIBA LA CONTRASENA\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
    return (*persona);
}
// ===============================================================
// FUNCION QUE PIDE DATOS PERSONALES PARA EL REGISTRO ============
usuario pedir_Datos_Registro (FILE *arch, usuario persona)
{
    int flag = 1;
    int flag2 = 1;
    int flag3 = 1;
    int flag4 = 1;
    printf ("------------------------------------------------------------------\n");
    printf ("DATOS PERSONALES\n");
    printf ("------------------------------------------------------------------\n");
    while (flag == 1)
    {
        flag2 = 1;
        flag3 = 1;
        flag4 = 1;
        while (flag4 == 1 || flag3 == 1)
        {
            printf ("NOMBRE Y APELLIDO: ");
            fflush (stdin);
            gets (persona.nombre_Apellido);
            flag4 = comprobar_Caracteres_Usuario (persona.nombre_Apellido);
            flag3 = verificar_dos_o_mas_palabras (persona.nombre_Apellido);
        }
        flag3 = 1;
        while (flag2 == 1 || flag3 == 1)
        {
            printf ("DNI: ");
            fflush (stdin);
            gets (persona.dni);
            flag3 = verificar_Dni (persona.dni);
            flag2 = verificar_Space (persona.dni);
        }
        flag = verificar_Existencia_Persona (arch, persona.dni);
    }
    flag = 1;
    flag2 = 1;
    while (flag == 1 || flag2 == 1)
    {
        printf ("MAIL: ");
        gets (persona.email);
        flag = verificar_Mail (persona.email);
        flag2 = verificar_Space (persona.email);
    }
    return persona;
}

void mostrar_Archivo (char archivo [])
{
    FILE *arch =fopen (archivo, "rb");
    usuario aux;
    while (fread(&aux, sizeof (usuario), 1, arch) > 0)
        {
            mostrarUsuario (aux);
            printf ("\n");
        }
}
void mostrarUsuario(usuario u) {
    printf("Nombre y Apellido: %s\n", u.nombre_Apellido);
    printf("DNI: %s\n", u.dni);
    printf("Email: %s\n", u.email);
    printf("Fecha de Nacimiento: %02d/%02d/%d\n", u.nacimiento.dia, u.nacimiento.mes, u.nacimiento.anio);
    printf("Contraseña: %s\n", u.contra);
    printf("Usuario: %s\n", u.user);
}

