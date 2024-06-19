#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
#include "menus.h"
#include "pila.h"
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
    printf("Contraseña: %s\n", u.contra);
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
                        printf("Ingrese el año de nacimiento: ");
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
        printf ("SECCION PARA MOSTRAR DATOS DE UN USUARIO\n");
        printf ("Ingrese el Nro del usuario a modificar\n");
        printf ("------------------------------------------------------------\n");
        printf ("INGRESE AQUI = ");
        scanf ("%d", &pos);
        printf ("------------------------------------------------------------\n");
        pos = pos - 1;
        fseek (arch, sizeof (usuario)* pos, SEEK_SET);
        fread (&persona, sizeof (usuario), 1, arch);
        mostrarUsuario (persona);
        printf ("------------------------------------------------------------\n");
    }
    fclose (arch);

}
void registro_auto_Sistema (char archivo [])
{
    FILE *arch = fopen (archivo, "a+b");
    autoS aux;
    if (arch != NULL)
    {
        aux = cargar_Auto (arch, aux);
        fseek (arch, 0, SEEK_END);
        fwrite (&aux, sizeof (autoS), 1, arch);
    }
    fclose (arch);
}
// funcion para añadir un auto =============================================
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
            flag2 = verificar_Anio_Auto (aux);
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
    strcpy (autoAux.titular.user, "consecionaria");
    printf ("------------------------------------------------------------\n");
    printf ("PRECIO DE ADQUISICION\n");
    gets (autoAux.precioDeAdquisicion);
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
    if (num > 200000)
    {
        flag = 1;
        printf ("-DEMASIADOS KMS-\n");
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
        if ((strcmp (letras, aux.patente.letras) == 0) && (strcmp (numeros, aux.patente.numeros) == 0))
        {
            flag = 1;
            printf ("-EL AUTO YA EXISTE-\n");
            break;
        }
    }
    return flag;
}
void recorrer_Array_Autos (char archivo [])
{
    FILE* arch = fopen (archivo, "rb");
    autoS aux;
    int i = 0;
    while (fread (&aux, sizeof (autoS), 1, arch) > 0)
    {
        printf ("------------------------------------------------------------\n");
        printf ("AUTO Nro %d\n", i + 1);
        printf ("------------------------------------------------------------\n");
        mostrarAuto (aux);
        i++;
    }
    fclose  (arch);
}
void mostrarAuto(autoS automovil)
{
    printf("Patente: %s-%s\n", automovil.patente.letras, automovil.patente.numeros);
    printf("Marca: %s\n", automovil.marca);
    printf("Modelo: %s\n", automovil.modelo);
    printf("Año: %s\n", automovil.anio);
    printf("Kilómetros: %s\n", automovil.kms);
    printf ("Titular %s\n", automovil.titular.user);
    printf("Precio de Adquisición: %s\n", automovil.precioDeAdquisicion);
}

void modificar_Auto (char archivo [])
{
    recorrer_Array_Autos (archivo);
    FILE *arch = fopen (archivo, "rb+");
    if (arch != NULL)
    {
        printf ("=========================================================\n");
        printf (" SECCION PARA MODIFICAR UN AUTO\n");
        printf ("=========================================================\n");
        autoS autoAux;
        int flag = 0;
        int flag2 = 0;
        int pos = 0;
        int op = 1;
        printf ("Ingrese el Nro del auto a modificar\n");
        scanf ("%d", &pos);
        printf ("=========================================================\n");
        pos = pos - 1;
        fseek (arch, sizeof (autoS)* pos, SEEK_SET);
        fread (&autoAux, sizeof (autoS), 1, arch);
        mostrarAuto (autoAux);
        while (op != 0)
        {
            printf ("=========================================================\n");
            printf ("1- Modificar patente\n");
            printf ("2- Modificar Marca\n");
            printf ("3- Modificar Modelo\n");
            printf ("4- Modificar el anio de fabricacion\n");
            printf ("5- Modificar los kms\n");
            printf ("6- Modificar el precio de adquisicion\n");
            printf ("7- Modificar todos los datos\n");
            printf ("0 para finalizar la ejecucion\n");
            printf (" INGRESE AQUI = ");
            scanf ("%i", &op);
            printf ("\n");
            printf ("=========================================================\n");
            switch (op)
            {
            case 1:
                flag = 1;
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
                break;
            case 2:
                printf ("------------------------------------------------------------\n");
                printf ("INGRESE LA MARCA DEL AUTO\n");
                fflush (stdin);
                gets (autoAux.marca);
                break;
            case 3:
                printf ("------------------------------------------------------------\n");
                printf ("INGRESE EL MODELO DEL AUTO\n");
                fflush (stdin);
                gets (autoAux.modelo);
                break;
            case 4:
                flag = 1;
                flag2 = 1;
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
                        flag2 = verificar_Anio_Auto (aux);
                    }
                }
                break;
            case 5:
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
                break;
            case 6:
                printf ("------------------------------------------------------------\n");
                printf ("PRECIO DE ADQUISICION\n");
                gets (autoAux.precioDeAdquisicion);
                break;
            case 7:
                autoAux = cargar_Auto (arch, autoAux);
                break;
            case 0:

                break;
            default:
                printf ("------------------------------------------------------------\n");
                printf ("SE INGRESO UN VALOR INCORRECTO\n");
                printf ("------------------------------------------------------------\n");
                break;
            }
            fseek(arch, sizeof(usuario) *pos, SEEK_SET);
            fwrite(&autoAux, sizeof(autoS), 1, arch);
        }
    }
    fclose (arch);
}
int verificar_Anio_Auto (int anio)
{
    int flag = 0;
    int limite = 2024;
    int i = 0;
    int aux = anio;
    while (anio > 0)
    {
        anio = anio / 10;
        i++;
    }
    if (aux > limite || i != 4)
    {
        flag = 1;
    }
    return flag;
}
void mostrar_Datos_Auto (char archivo [])
{
    FILE *arch = fopen (archivo, "rb+");
    int pos = 0;
    autoS auxAuto;
    if (arch != NULL)
    {
        printf ("------------------------------------------------------------\n");
        printf ("SECCION PARA MOSTRAR DATOS DE UN AUTO\n");
        printf ("Ingrese el Nro del usuario a modificar\n");
        printf ("------------------------------------------------------------\n");
        printf ("INGRESE AQUI = ");
        scanf ("%d", &pos);
        printf ("------------------------------------------------------------\n");
        pos = pos - 1;
        fseek (arch, sizeof (autoS)* pos, SEEK_SET);
        fread (&auxAuto, sizeof (autoS), 1, arch);
        mostrarAuto(auxAuto);
        printf ("------------------------------------------------------------\n");
    }
    fclose (arch);

}
void registrar_Venta_Arch (char ventasArch [], char autosArch [], char usersArch [])
{
    FILE *arch = fopen (ventasArch, "ab");
    ventaS aux;
    if (arch != NULL)
    {
        aux = registrar_Venta (autosArch, usersArch);
        fseek (arch, 0, SEEK_END);
        fwrite (&aux, sizeof (ventaS), 1, arch);
    }
    fclose (arch);
}
ventaS registrar_Venta (char autosArch [], char usersArch [])
{
    printf ("------------------------------------------------------------\n");
    printf ("SECCION PARA REGISTRAR UNA VENTA\n");
    printf ("------------------------------------------------------------\n");
    ventaS venta;
    int flag = 1;
    int flag2 = 1;
    while (flag == 1)
    {
        flag2 = 1;
        printf ("------------------------------------------------------------------\n");
        printf ("FECHA DE OPERACION\n");
        printf ("------------------------------------------------------------------\n");
        while (flag2 == 1)
        {
            printf("Ingrese el dia de operacion: ");
            fflush (stdin);
            gets (venta.fecha.dia);
            printf("Ingrese el mes de operacion: ");
            fflush (stdin);
            gets (venta.fecha.mes);
            printf("Ingrese el año de operacion: ");
            fflush (stdin);
            gets (venta.fecha.anio);
            flag2 = verificar_Caracteres_Edad (venta.fecha.dia, venta.fecha.mes, venta.fecha.anio);
        }
        int diaE = atoi (venta.fecha.dia);
        int mesE = atoi (venta.fecha.mes);
        int anioE = atoi (venta.fecha.anio);
        flag = comprobar_Fecha_Venta (diaE, mesE, anioE);
    }
    flag = 1;
    flag2 = 1;
    int flag3 = 1;
    while (flag3 == 1)
    {
        flag = 1;
        while (flag == 1)
        {
            printf ("------------------------------------------------------------\n");
            printf ("INGRESE LAS LETRAS DE LA PATENTE\n");
            fflush (stdin);
            gets (venta.autoAVender.letras);
            flag = comprobar_Caracteres_Patente (venta.autoAVender.letras);
        }
        flag = 1;
        while (flag == 1)
        {
            printf ("------------------------------------------------------------\n");
            printf ("INGRESE LAS NUMEROS DE LA PATENTE\n");
            fflush (stdin);
            gets (venta.autoAVender.numeros);
            flag = comprobar_Numeros_Dni (venta.autoAVender.numeros);
        }
        flag3 = buscar_Coincidencia_Patente (autosArch, venta.autoAVender.letras, venta.autoAVender.numeros);
    }
    flag = 1;
    while (flag == 1)
    {
        printf ("------------------------------------------------------------\n");
        printf ("INGRESE EL PRECIO DE VENTA\n");
        fflush (stdin);
        gets (venta.precioVenta);
        flag = comprobar_Numeros_Dni (venta.precioVenta);
        if (flag == 0)
        {
            calcular_Ganancia_Venta (autosArch, &venta);
        }

    }
    flag = 1;
    flag2 = 1;
    flag3 = 1;
    while (flag == 1 || flag3 == 1 || flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("DNI DEL VENDEDOR: ");
        fflush (stdin);
        gets (venta.dniVendedor);
        flag2 = verificar_Dni (venta.dniVendedor);
        flag3 = comprobar_Numeros_Dni (venta.dniVendedor);
        flag = verificar_Space (venta.dniVendedor);
    }
    flag = 1;
    flag2 = 1;
    flag3 = 1;
    int flag4 = 1;
    while (flag == 1 || flag3 == 1 || flag2 == 1 || flag4 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("DNI DEL COMPRADOR: ");
        fflush (stdin);
        gets (venta.dniComprador);
        flag2 = verificar_Dni (venta.dniComprador);
        flag3 = comprobar_Numeros_Dni (venta.dniComprador);
        flag = verificar_Space (venta.dniComprador);
        if (flag == 0 && flag2 == 0 && flag3 == 0)
        {
            flag4 = verificar_Existencia_Persona_Venta (autosArch, usersArch, venta.dniComprador, venta.autoAVender.letras, venta.autoAVender.numeros);
        }
    }
    return venta;
}
int buscar_Coincidencia_Patente (char archivo [], char letras [], char numeros [])
{
    FILE *arch = fopen (archivo, "rb");
    autoS aux;
    int flag = 1;
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
    {
        if ((strcmp (letras, aux.patente.letras) == 0) && (strcmp (numeros, aux.patente.numeros) == 0) /*&& strcmpi (aux.titular.user, "consecionaria") == 0*/)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf ("-EL AUTO NO EXISTE O YA SE A VENDIDO-\n");
    }
    fclose (arch);
    return flag;
}
int comprobar_Fecha_Venta (int dia, int mes, int anio)
{
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    flag1 = verificar_Anio_Auto (anio);
    flag2 = verificar_Mes (mes);
    flag3 = verificar_Dia (dia, mes);
    if (flag1 != 0 || flag2 != 0 || flag3 != 0)
    {
        flag = 1;
        printf ("-FECHA INVALIDA-\n");
    }
    return flag;
}
void calcular_Ganancia_Venta (char autosArch [], ventaS *venta)
{
    FILE *arch = fopen (autosArch, "rb");
    autoS aux;
    if (arch != NULL)
    {
        while (fread(&aux, sizeof (autoS), 1, arch) > 0)
        {
            if ((strcmp ((*venta).autoAVender.letras, aux.patente.letras) == 0) && (strcmp ((*venta).autoAVender.numeros, aux.patente.numeros) == 0))
            {
                int precioAdquisicion = atoi (aux.precioDeAdquisicion);
                int precioVenta = atoi ((*venta).precioVenta);
                int ganancia = precioVenta - precioAdquisicion;
                sprintf ((*venta).ganancia, "%d", ganancia);
            }
        }
    }
    fclose (arch);
}
void mostrar_Ventas (char ventasArch [])
{
    FILE * arch = fopen (ventasArch, "rb");
    ventaS aux;
    int i = 0;
    while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("VENTA Nro %d\n", i + 1);
        mostrar_Venta (aux);
        i++;
    }
    fclose (arch);
}
void mostrar_Venta (ventaS aux)
{
    // Mostrar los datos de fecha y patente
    printf("Fecha de venta: %s/%s/%s\n", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    printf("Patente: %s-%s\n", aux.autoAVender.letras, aux.autoAVender.numeros);
}
int verificar_Existencia_Persona_Venta (char autosArch [], char usersArch [], char dni [], char letras [], char numeros [])
{
    FILE *arch = fopen (usersArch, "rb");
    int flag = 1;
    usuario aux;
    int i = 0;
    if (arch != NULL)
    {
        fseek (arch, 0, SEEK_SET);
        while (fread (&aux, sizeof (usuario), 1, arch) > 0)
        {
            if (strcmp (aux.dni, dni) == 0)
            {
                FILE * arc = fopen (autosArch, "rb+");
                autoS autoAux;
                if (arc != NULL)
                {
                    while (fread (&autoAux, sizeof (autoS), 1, arc) > 0)
                    {
                        if ((strcmp (letras, autoAux.patente.letras) == 0) && (strcmp (numeros, autoAux.patente.numeros) == 0))
                        {
                            fseek (arc, sizeof (autoS)*i, SEEK_SET);
                            autoAux.titular = aux;
                            fwrite (&autoAux, sizeof (autoS), 1, arc);
                            flag = 0;
                            break;
                        }
                        i++;

                    }
                    fclose (arc);
                }
            }
        }
        fclose (arch);
    }

    if (flag == 1)
    {
        printf ("-LA PERSONA INGRESADA NO EXITE-\n");
    }

    return flag;
}
void mostrar_Ventas_Arch_Completo (char ventasArch [])
{
    FILE * arch = fopen (ventasArch, "rb");
    ventaS aux;
    int i = 0;
    while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("VENTA Nro %d\n", i + 1);
        printf ("------------------------------------------------------------------\n");
        mostrar_VentaS_Completo (aux);
        i++;
    }
    fclose (arch);
}
void mostrar_VentaS_Completo (ventaS venta)
{
    printf("Patente: %s-%s\n", venta.autoAVender.letras, venta.autoAVender.numeros);
    printf("Fecha: %s/%s/%s\n", venta.fecha.dia, venta.fecha.mes, venta.fecha.anio);
    printf("Precio de Venta: %s\n", venta.precioVenta);
    printf("Ganancia: %s\n", venta.ganancia);
    printf("DNI del Comprador: %s\n", venta.dniComprador);
    printf("DNI del Vendedor: %s\n", venta.dniVendedor);
}
int calcular_Recaudacion (FILE *arch, char anio [], char mes [])
{
    ventaS aux;
    int flag = 1;
    int flag2 = 1;
    int i = 0;
    printf ("------------------------------------------------------------------\n");
    printf ("SECCION QUE CALCULA LAS RECAUDACIONES\n");
    printf ("------------------------------------------------------------------\n");
    while (flag == 1 || flag2 == 1)
    {
        printf ("INGRESE EL AÑO QUE DESEA CONTABILIZAR: ");
        fflush (stdin);
        gets (anio);
        flag = comprobar_Numeros_Dni (anio);
         int anioInt = atoi (anio);
        flag2 = verificar_Anio_Auto (anioInt);
    }
    flag = 1;
    flag2 = 1;
    while (flag == 1 || flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE EL MES QUE DESEA CONTABILIZAR: ");
        fflush (stdin);
        gets (mes);
        flag = comprobar_Numeros_Dni (anio);
        int mesInt = atoi (mes);
        flag2 = verificar_Mes (mesInt);
    }
    while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
    {
        if (strcmp (anio, aux.fecha.anio) == 0 && strcmp (mes, aux.fecha.mes) == 0)
        {
            i++;
        }
    }
    return i;
}
void mostrar_Recaudacion (char ventas [])
{
    ventaS aux;
    int recaudacionFinal = 0;
    char anio [5];
    char mes [3];
    FILE *arch = fopen (ventas, "rb");
    if (arch != NULL)
    {
        int cant_Ventas = calcular_Recaudacion (arch, anio, mes);
        int* array = (int*) malloc (sizeof (int)*cant_Ventas);
        int i = 0;
        fseek (arch, 0, SEEK_SET);
        printf ("------------------------------------------------------------------\n");
        printf ("SE ENCONTRO del mes %s\n", mes);
        printf ("------------------------------------------------------------------\n");
        while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
        {
            if (strcmp (anio, aux.fecha.anio) == 0 && strcmp (mes, aux.fecha.mes) == 0)
            {
                mostrar_VentaS_Completo (aux);
                printf ("------------------------------------------------------------------\n");
                int gananciaInt = atoi (aux.ganancia);
                array[i] = gananciaInt;
                i++;
            }
        }
        for (int i = 0 ; i < cant_Ventas ; i++)
            {
                recaudacionFinal = recaudacionFinal + array [i];
            }
    }
    fclose (arch);
    printf ("LA RECAUDACION DEL MES DE %s, año %s fue de %d\n", mes, anio, recaudacionFinal);
    printf ("------------------------------------------------------------------\n");

}
void calcular_Venta_Mayor_Ganancia(char ventasArch[])
{
    FILE *arch = fopen(ventasArch, "rb");
    ventaS aux, mayorVenta;
    int mayorGanancia = -1;

    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo de ventas.\n");
    }
    while (fread(&aux, sizeof(ventaS), 1, arch) > 0)
    {
        int ganancia = atoi(aux.ganancia);
        if (ganancia > mayorGanancia)
        {
            mayorGanancia = ganancia;
            mayorVenta = aux;
        }
    }
    fclose(arch);
    printf ("------------------------------------------------------------------\n");
    printf("VENTA DE MAYOR GANANCIA\n");
    printf ("------------------------------------------------------------------\n");
    mostrar_VentaS_Completo (mayorVenta);
}
void mostrar_Autos_menos_10 (char autosArch [])
{
    printf ("------------------------------------------------------------------\n");
    printf("AUTOS CON MENOS DE 10 AÑOS\n");
    printf ("------------------------------------------------------------------\n");
    FILE *arch = fopen (autosArch, "rb");
    autoS aux;
    if (arch != NULL)
    {
        while (fread (&aux, sizeof (autoS), 1, arch) > 0)
        {
            int anioInt = atoi (aux.anio);
            int auX = 2024 - anioInt;
            if (auX < 10 && strcmp (aux.titular.user, "consecionaria") == 0)
            {
                mostrarAuto (aux);
            }
        }
    }
    fclose (arch);
}
