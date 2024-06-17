#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
#include "menus.h"
// POR EL MOMENTO ESTO MUESTRA LOS USUARIOS DE CARACTER TEMPORAL
void mostrar_Archivo (char archivo [])
{
    printf ("------------------------------------------------------------------\n");
    printf ("LISTA DE USUARSIOS\n");
    FILE *arch =fopen (archivo, "rb");
    usuario aux;
    int i = 0;
    if (arch != NULL)
    {
        while (fread(&aux, sizeof (usuario), 1, arch) > 0)
        {
            if (strcmpi (aux.user, "consecionaria") != 0)
            {
                printf ("------------------------------------------------------------------\n");
                printf ("USUARIO Nro %d:\n", i + 1);
                mostrarUsuario (aux);
                printf ("\n");
            }
            i++;
        }
    }
    fclose (arch);
}
// FUNCION Q MODIFICA UN USUARIO ====================================================================
void mostrarUsuario(usuario u)
{
    printf ("------------------------------------------------------------------\n");
    printf("Nombre y Apellido: %s\n", u.nombre_Apellido);
    printf("DNI: %s\n", u.dni);
    printf ("TELEFONO: %s\n", u.tele);
    printf("Email: %s\n", u.email);
    printf("Fecha de Nacimiento: %s/%s/%s\n", u.nacimiento.dia, u.nacimiento.mes, u.nacimiento.anio);
    printf("Contrase�a: %s\n", u.contra);
    printf("Usuario: %s\n", u.user);
    printf("Rol: %s\n", u.rol);
    printf ("------------------------------------------------------------------\n");
}
void modificar_usuario (char archivo [])
{
    mostrar_Archivo (archivo);
    FILE *arch = fopen (archivo, "rb+");
    if (arch != NULL)
    {
        printf ("=========================================================\n");
        printf (" SECCION PARA MODIFICAR UN USUARIO\n");
        printf ("=========================================================\n");
        usuario persona;
        int flag = 0;
        int flag2 = 0;
        int flag3 = 0;
        int flag4 = 0;
        int pos = 0;
        int op = 1;
        printf ("Ingrese el Nro del usuario a modificar\n");
        scanf ("%d", &pos);
        pos = pos - 1;
        fseek (arch, sizeof (usuario)* pos, SEEK_SET);
        fread (&persona, sizeof (usuario), 1, arch);
        mostrarUsuario (persona);
        while (op != 0)
        {
            printf ("=========================================================\n");
            printf ("1- Modificar Nombre y Apeliido\n");
            printf ("2- Modificar dni\n");
            printf ("3- Modificar telefono\n");
            printf ("4- Modificar el rol\n");
            printf ("5- Modificar direccion de correo\n");
            printf ("6- Modificar fecha de nacimiento\n");
            printf ("7- Modificar usuario\n");
            printf ("8- Modificar contrasena\n");
            printf ("9- Modificar todos los datos\n");
            printf ("0 para finalizar la ejecucion\n");
            printf (" INGRESE AQUI = ");
            scanf ("%i", &op);
            printf ("\n");
            printf ("=========================================================\n");
            switch (op)
            {
            case 1:
                flag4 = 1;
                flag3 = 1;
                while (flag4 == 1 || flag3 == 1)
                {
                    printf ("------------------------------------------------------------------\n");
                    printf ("NOMBRE Y APELLIDO: ");
                    fflush (stdin);
                    gets (persona.nombre_Apellido);
                    flag4 = comprobar_Caracteres_Usuario (persona.nombre_Apellido);
                    flag3 = verificar_dos_o_mas_palabras (persona.nombre_Apellido);
                }
                break;
            case 2:
                flag = 1;
                flag2 = 1;
                flag3 = 1;
                flag4 = 1;
                while (flag2 == 1 || flag3 == 1 || flag4 == 1 || flag3 == 1)
                {
                    printf ("------------------------------------------------------------------\n");
                    printf ("DNI: ");
                    fflush (stdin);
                    gets (persona.dni);
                    flag3 = verificar_Dni (persona.dni);
                    flag4 = comprobar_Numeros_Dni (persona.dni);
                    flag2 = verificar_Space (persona.dni);
                    flag = verificar_Existencia_Persona (arch, persona.dni);
                }
                break;
            case 3:
                flag = 1;
                flag2 = 1;
                flag3 = 1;
                while (flag == 1 || flag2 == 1 || flag3 == 1)
                {
                    printf ("------------------------------------------------------------------\n");
                    printf ("TELEFONO: ");
                    fflush (stdin);
                    gets (persona.tele);
                    flag2 = verificar_Telefono (persona.tele);
                    flag3 = comprobar_Numeros_Dni (persona.tele);
                    flag = verificar_Space (persona.tele);
                }
                break;
            case 4:
                flag = 1;
                while (flag == 1)
                {
                    char aux = '0' ;
                    printf ("------------------------------------------------------------------\n");
                    printf ("ROL (1 = vendedor ; 0 = Comprador)");
                    printf ("INGRESE AQUI = ");
                    fflush (stdin);
                    scanf ("%c", &aux);
                    flag = verificar_Rol (aux);
                    if (flag == 0)
                    {
                        if (aux == '0')
                        {
                            strcpy (persona.rol, "COMPRADOR");
                        }
                        else
                        {
                            strcpy (persona.rol, "VENDEDOR");
                        }
                    }
                }
                break;
            case 5:
                flag = 1;
                flag2 = 1;
                while (flag == 1 || flag2 == 1)
                {
                    printf ("------------------------------------------------------------------\n");
                    printf ("DIRECCION DE CORREO: ");
                    fflush (stdin);
                    gets (persona.email);
                    flag = verificar_Mail (persona.email);
                    flag2 = verificar_Space (persona.email);
                }
                break;
            case 6:
                flag = 1;
                while (flag == 1)
                {
                    flag2 = 1;
                    printf ("------------------------------------------------------------------\n");
                    printf ("FECHA DE NACIMIENTO\n");
                    printf ("------------------------------------------------------------------\n");
                    while (flag2 == 1)
                    {
                        printf("Ingrese el dia de nacimiento: ");
                        fflush (stdin);
                        gets (persona.nacimiento.dia);
                        printf("Ingrese el mes de nacimiento: ");
                        fflush (stdin);
                        gets (persona.nacimiento.mes);
                        printf("Ingrese el a�o de nacimiento: ");
                        fflush (stdin);
                        gets (persona.nacimiento.anio);
                        flag2 = verificar_Caracteres_Edad (persona.nacimiento.dia, persona.nacimiento.mes, persona.nacimiento.anio);
                    }
                    int diaE = atoi (persona.nacimiento.dia);
                    int mesE = atoi (persona.nacimiento.mes);
                    int anioE = atoi (persona.nacimiento.anio);
                    flag = comprobar_Edad (diaE, mesE, anioE);
                }
                break;
            case 7:
                nombre_Usuario (arch, &persona);
                break;
            case 8:
                contrasena (arch, &persona);
                break;
            case 9:
                persona = crear_Cuenta (arch);
                break;
            case 0:

                break;
            default:
                printf ("------------------------------------------------------------\n");
                printf ("SE INGRESO UN VALOR INCORRECTO\n");
                printf ("------------------------------------------------------------\n");
                break;
            }
            fseek(arch, sizeof(usuario) * pos, SEEK_SET);
            fwrite(&persona, sizeof(usuario), 1, arch);
        }
    }

    fclose (arch);
}
void mostrar_Datos_Usuario (char archivo [])
{
    FILE *arch = fopen (archivo, "rb+");
    int pos = 0;
    usuario persona;
    if (arch != NULL)
    {
        printf ("------------------------------------------------------------\n");
        printf ("SECCION PARA MOSTRA DATOS DE UN USUARIO\n");
        printf ("Ingrese el Nro del usuario a modificar\n");
        printf ("------------------------------------------------------------\n");
        printf ("INGRESE AQUI = ");
        scanf ("%d", &pos);
        pos = pos - 1;
        fseek (arch, sizeof (usuario)* pos, SEEK_SET);
        fread (&persona, sizeof (usuario), 1, arch);
        mostrarUsuario (persona);
    }
    fclose (arch);

}
void registro_auto_Sistema (char archivo [])
{
    FILE *arch = fopen (archivo, "ab");
    autoS aux;
    if (arch != NULL)
    {
        aux = cargar_Auto (arch, aux);
        fseek (arch, 0, SEEK_END);
        fwrite (&aux, sizeof (autoS), 1, arch);
    }
    fclose (arch);
}
// funcion para a�adir un auto =============================================
autoS cargar_Auto (FILE *arch, autoS autoAux)
{
    printf ("------------------------------------------------------------\n");
    printf ("SECCION PARA AGREGAR UN AUTO\n");
    printf ("------------------------------------------------------------\n");
    int flag = 1;
    int flag3 = 1;
    while (flag3 == 1)
    {
       while (flag == 1)
        {
            printf ("------------------------------------------------------------\n");
            printf ("INGRESE LAS LETRAS DE LA PATENTE\n");
            fflush (stdin);
            gets (autoAux.patente.letras);
            flag = comprobar_Caracteres_Patente (autoAux.patente.letras);
        }
        flag = 1;
        while (flag == 1)
        {
            printf ("------------------------------------------------------------\n");
            printf ("INGRESE LAS NUMEROS DE LA PATENTE\n");
            fflush (stdin);
            gets (autoAux.patente.numeros);
            flag = comprobar_Numeros_Dni (autoAux.patente.numeros);
        }
        flag3 = validar_Existencia_Auto (arch, autoAux.patente.letras, autoAux.patente.numeros);
    }

    printf ("------------------------------------------------------------\n");
    printf ("INGRESE LA MARCA DEL AUTO\n");
    fflush (stdin);
    gets (autoAux.marca);
    printf ("------------------------------------------------------------\n");
    printf ("INGRESE EL MODELO DEL AUTO\n");
    fflush (stdin);
    gets (autoAux.modelo);
    flag = 1;
    int flag2 = 1;
    while (flag == 1 || flag2 == 1)
    {
    printf ("------------------------------------------------------------\n");
    printf ("INGRESE EL ANIO DEL AUTO\n");
    fflush (stdin);
    gets (autoAux.anio);
    flag = comprobar_Numeros_Dni (autoAux.anio);
    if (flag == 0)
        {
            int aux = atoi (autoAux.anio);
            flag2 = verificar_Anio (aux);
        }
    }
    flag = 1;
    flag2 = 1;
    while (flag2 == 1)
    {
    printf ("------------------------------------------------------------\n");
    printf ("INGRESE LOS KMS DEL AUTO\n");
    fflush (stdin);
    gets (autoAux.kms);
    flag2 = comprobar_kms_Auto (autoAux.kms);
    }
    return autoAux;
}
// COMPROBACIONES A LA CARGAR DE AUTOS =====================================
int comprobar_Caracteres_Patente (char palabra [])
{
    int flag = 0;
    int caracteres = strlen (palabra);
    caracteres = caracteres - 1;
    for (int i = 0 ; i < caracteres ; i++)
    {
        if (palabra [i] < 65 || palabra [i] > 90)
        {
            flag = 1;
        }
    }
    if (flag == 1)
        {
            printf ("-CARACTERES INVALIDOS-\n");
        }
    return flag;
}
int comprobar_kms_Auto (char kms [])
{
    int flag = 0;
    int num = atoi (kms);
    if (num > 300000)
        {
            flag = 1;
        }
    return flag;
}
int validar_Existencia_Auto (FILE *arch, char letras [], char numeros [])
{
    fseek (arch, 0, SEEK_SET);
    autoS aux;
    int flag = 0;
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
        {
            if (strcmp (aux.patente.letras, letras) == 0 && strcmp (aux.patente.numeros, numeros) == 0)
                {
                    flag = 1;
                    printf ("-EL AUTO YA EXISTE-\n");
                }
        }
    return flag;
}
void recorrer_Array_Autos (char archivo [])
{
    FILE* arch = fopen (archivo, "rb");
    autoS aux;
    while (fread (&aux, sizeof (autoS), 1, arch) > 0)
        {
            mostrarAuto (aux);
        }
}
void mostrarAuto(autoS automovil)
{
    printf("Patente: %s %s\n", automovil.patente.letras, (automovil).patente.numeros);
    printf("Marca: %s\n", (automovil).marca);
    printf("Modelo: %s\n", (automovil).modelo);
    printf("A�o: %s\n", (automovil).anio);
    printf("Kil�metros: %s\n", (automovil).kms);
    printf("Precio de Adquisici�n: %s\n", automovil.precioDeAdquisicion);
    printf("\n");
}
