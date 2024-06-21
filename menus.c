#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
#include "menus.h"
#include "pila.h"
// =================================================================================================
// =================================================================================================
void mostrar_Archivo(char archivo[])
{
    // Encabezado inicial para mostrar la lista de usuarios
    printf("------------------------------------------------------------------\n");
    printf("LISTA DE USUARIOS\n");

    // Abrir el archivo en modo lectura binaria
    FILE *arch = fopen(archivo, "rb");
    usuario aux;
    int i = 0;

    // Verificar si se abri� correctamente el archivo
    if (arch != NULL)
    {
        // Bucle para leer cada usuario del archivo
        while (fread(&aux, sizeof(usuario), 1, arch) > 0)
        {
            // Excluir temporalmente el usuario "consecionaria"
            if (strcmpi(aux.user, "consecionaria") != 0)
            {
                // Mostrar informaci�n del usuario
                printf("------------------------------------------------------------------\n");
                printf("USUARIO Nro %d:\n", i + 1);
                mostrarUsuario(aux); // Llama a una funci�n mostrarUsuario para mostrar los detalles del usuario
                printf("\n");
            }
            i++; // Incrementar contador de usuarios mostrados
        }
        fclose(arch); // Cerrar el archivo despu�s de leer todos los usuarios
    }
    else
    {
        // Mensaje de error si no se pudo abrir el archivo
        printf("Error al abrir el archivo %s\n", archivo);
    }
}
// =================================================================================================
// =================================================================================================
void mostrarUsuario(usuario u)
{
    printf ("------------------------------------------------------------------\n");
    printf("Nombre y Apellido: %s\n", u.nombre_Apellido);  // Imprime el nombre y apellido del usuario
    printf("Dni: %s\n", u.dni);                            // Imprime el DNI del usuario
    printf ("Telefono: %s\n", u.tele);                     // Imprime el tel�fono del usuario
    printf("Direccion de correo: %s\n", u.email);          // Imprime el correo electr�nico del usuario
    printf("Fecha de Nacimiento: %s/%s/%s\n", u.nacimiento.dia, u.nacimiento.mes, u.nacimiento.anio);  // Imprime la fecha de nacimiento del usuario
    printf("Contrase�a: %s\n", u.contra);                  // Imprime la contrase�a del usuario
    printf("Usuario: %s\n", u.user);                       // Imprime el nombre de usuario
    printf("Rol: %s\n", u.rol);                            // Imprime el rol del usuario (COMPRADOR o VENDEDOR)
    printf ("------------------------------------------------------------------\n");
}
// =================================================================================================
// =================================================================================================
void modificar_usuario (char archivo [])
{
    mostrar_Archivo (archivo);  // Muestra todos los usuarios presentes en el archivo especificado
    FILE *arch = fopen (archivo, "rb+");  // Abre el archivo en modo lectura y escritura binaria

    if (arch != NULL)
    {
        printf ("------------------------------------------------------------------\n");
        printf (" SECCION PARA MODIFICAR UN USUARIO\n");
        printf ("------------------------------------------------------------------\n");

        usuario persona;  // Declara una variable para almacenar los datos del usuario a modificar
        int flag = 0;
        int flag2 = 0;
        int flag3 = 0;
        int flag4 = 0;
        int pos = 0;
        int op = 1;

        printf ("Ingrese el Nro del usuario a modificar\n");
        scanf ("%d", &pos);  // Solicita al usuario el n�mero de usuario a modificar
        pos = pos - 1;  // Ajusta la posici�n para que coincida con el �ndice del arreglo (resta 1)

        fseek (arch, sizeof (usuario) * pos, SEEK_SET);  // Posiciona el puntero en la posici�n del usuario seleccionado
        fread (&persona, sizeof (usuario), 1, arch);  // Lee los datos del usuario desde el archivo y los guarda en la variable persona

        mostrarUsuario (persona);  // Muestra los datos actuales del usuario seleccionado

        while (op != 0)
        {
            printf ("------------------------------------------------------------------\n");
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
            scanf ("%i", &op);  // Solicita al usuario la opci�n de modificaci�n
            printf ("\n");
            printf ("------------------------------------------------------------------\n");

            switch (op)
            {
            case 1:
                // Modificar Nombre y Apellido
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
                // Modificar DNI
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
                // Modificar Tel�fono
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
                // Modificar Rol
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
                // Modificar Direcci�n de Correo
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
                // Modificar Fecha de Nacimiento
                flag = 1;
                while (flag == 1)
                {
                    flag2 = 1;
                    printf ("------------------------------------------------------------------\n");
                    printf ("FECHA DE NACIMIENTO\n");
                    printf ("Formato: XX/XX/XXXX\n");
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
                // Modificar Usuario
                nombre_Usuario (arch, &persona);
                break;

            case 8:
                // Modificar Contrase�a
                contrasena (arch, &persona);
                break;

            case 9:
                // Modificar Todos los Datos
                persona = crear_Cuenta (arch);
                break;

            case 0:
                // Finalizar la ejecuci�n
                break;

            default:
                // Opci�n incorrecta
                printf ("------------------------------------------------------------------\n");
                printf ("SE INGRESO UN VALOR INCORRECTO\n");
                printf ("------------------------------------------------------------------\n");
                break;
            }

            fseek(arch, sizeof(usuario) * pos, SEEK_SET);  // Posiciona el puntero en la posici�n del usuario a modificar
            fwrite(&persona, sizeof(usuario), 1, arch);  // Escribe los datos modificados en el archivo
        }
    }

    fclose (arch);  // Cierra el archivo
}
// =================================================================================================
// =================================================================================================
void mostrar_Datos_Usuario (char archivo [])
{
    FILE *arch = fopen (archivo, "rb+");  // Abre el archivo en modo lectura y escritura binaria

    int pos = 0;  // Variable para almacenar la posici�n del usuario a mostrar
    usuario persona;  // Variable para almacenar los datos del usuario le�dos del archivo

    if (arch != NULL)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("SECCION PARA MOSTRAR DATOS DE UN USUARIO\n");
        printf ("Ingrese el Nro del usuario a mostrar\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI = ");
        scanf ("%d", &pos);  // Solicita al usuario el n�mero de usuario a mostrar
        printf ("------------------------------------------------------------------\n");

        pos = pos - 1;  // Ajusta la posici�n para que coincida con el �ndice del arreglo (resta 1)
        fseek (arch, sizeof (usuario)* pos, SEEK_SET);  // Posiciona el puntero en la posici�n del usuario seleccionado
        fread (&persona, sizeof (usuario), 1, arch);  // Lee los datos del usuario desde el archivo y los guarda en la variable persona

        mostrarUsuario (persona);  // Muestra los datos del usuario utilizando la funci�n mostrarUsuario

        printf ("------------------------------------------------------------------\n");
    }

    fclose (arch);  // Cierra el archivo
}
// =================================================================================================
// =================================================================================================
void registro_auto_Sistema (char archivo [])
{
    FILE *arch = fopen (archivo, "a+b");  // Abre el archivo en modo agregar y leer/escribir binario

    autoS aux;  // Variable para almacenar temporalmente los datos del autom�vil

    if (arch != NULL)
    {
        aux = cargar_Auto (arch, aux);  // Llama a la funci�n cargar_Auto para cargar los datos del autom�vil desde el archivo

        fseek (arch, 0, SEEK_END);  // Coloca el puntero al final del archivo para a�adir el nuevo registro
        fwrite (&aux, sizeof (autoS), 1, arch);  // Escribe los datos del autom�vil en el archivo

        fclose (arch);  // Cierra el archivo
    }
}
// =================================================================================================
// =================================================================================================
autoS cargar_Auto (FILE *arch, autoS autoAux)
{
    printf ("------------------------------------------------------------------\n");
    printf ("SECCION PARA AGREGAR UN AUTO\n");
    printf ("------------------------------------------------------------------\n");

    int flag = 1;
    int flag3 = 1;

    // Bucle para ingresar las letras de la patente y validarlas
    while (flag3 == 1)
    {
        // Bucle para ingresar las letras de la patente
        while (flag == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE LAS LETRAS DE LA PATENTE\n");
            printf ("Formato: EN MAYUSCULA\n");
            printf ("Ejemplo: 'ABC'\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (autoAux.patente.letras);
            flag = comprobar_Caracteres_Patente (autoAux.patente.letras);
        }
        flag = 1;

        // Bucle para ingresar los n�meros de la patente y validarlos
        while (flag == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE LAS NUMEROS DE LA PATENTE\n");
            printf ("Ejemplo: '403'\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (autoAux.patente.numeros);
            flag = comprobar_Numeros_Dni (autoAux.patente.numeros);
        }

        // Validaci�n de la existencia del auto en el archivo
        flag3 = validar_Existencia_Auto (arch, autoAux.patente.letras, autoAux.patente.numeros);
    }

    // Ingreso de la marca del auto
    printf ("------------------------------------------------------------------\n");
    printf ("INGRESE LA MARCA DEL AUTO\n");
    printf ("------------------------------------------------------------------\n");
    printf ("INGRESE AQUI: ");
    fflush (stdin);
    gets (autoAux.marca);

    // Ingreso del modelo del auto
    printf ("------------------------------------------------------------------\n");
    printf ("INGRESE EL MODELO DEL AUTO\n");
    printf ("------------------------------------------------------------------\n");
    printf ("INGRESE AQUI: ");
    fflush (stdin);
    gets (autoAux.modelo);

    flag = 1;
    int flag2 = 1;

    // Bucle para ingresar el a�o del auto y validar
    while (flag == 1 || flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE EL ANIO DEL AUTO\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
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

    // Bucle para ingresar los kil�metros del auto y validar
    while (flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE LOS KMS DEL AUTO\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        gets (autoAux.kms);
        flag2 = comprobar_kms_Auto (autoAux.kms);
    }

    // Establecer el usuario titular del auto como "consecionaria"
    strcpy (autoAux.titular.user, "consecionaria");

    flag = 1;

    // bucle que comprueba que el precio de adquisicion sea correcto
    while (flag == 1)
    {
        // Ingreso del precio de adquisici�n del auto
        printf ("------------------------------------------------------------------\n");
        printf ("PRECIO DE ADQUISICION\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        gets (autoAux.precioDeAdquisicion);
        flag = comprobar_Numeros_Dni (autoAux.precioDeAdquisicion);
    }


    printf ("------------------------------------------------------------------\n");
    printf ("CARGADO CORRECTAMENTE\n");
    printf ("------------------------------------------------------------------\n");
    return autoAux;
}
// =================================================================================================
// =================================================================================================
int comprobar_Caracteres_Patente (char palabra [])
{
    int flag = 0;
    int caracteres = strlen (palabra);
    caracteres = caracteres - 1;

    // Bucle para iterar sobre cada car�cter de la cadena, excluyendo el �ltimo ('\0')
    for (int i = 0 ; i < caracteres ; i++)
    {
        // Verifica si el car�cter no est� en el rango de letras may�sculas (A-Z) seg�n el c�digo ASCII
        if (palabra[i] < 65 || palabra[i] > 90)
        {
            flag = 1;  // Establece el flag a 1 si encuentra un car�cter inv�lido
        }
    }

    // Si se encontraron caracteres inv�lidos, imprime un mensaje
    if (flag == 1)
    {
        printf ("-CARACTERES INVALIDOS-\n");
    }

    return flag;  // Retorna el flag, que indica si se encontraron caracteres inv�lidos (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int comprobar_kms_Auto (char kms [])
{
    int flag = 0;
    int num = atoi (kms);  // Convierte la cadena de caracteres a un entero usando atoi()

    // Verifica si el n�mero de kil�metros supera los 200,000
    if (num > 200000)
    {
        flag = 1;  // Establece el flag a 1 si los kil�metros son mayores a 200,000
        printf ("-DEMASIADOS KMS-\n");  // Imprime un mensaje de advertencia
    }

    return flag;  // Retorna el flag, que indica si los kil�metros exceden el l�mite (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int validar_Existencia_Auto (FILE *arch, char letras [], char numeros [])
{
    fseek (arch, 0, SEEK_SET);  // Establece el puntero de archivo al inicio del archivo
    autoS aux;  // Variable auxiliar para almacenar cada registro de auto le�do
    int flag = 0;  // Flag inicializado a 0, indica que el auto no ha sido encontrado a�n

    // Itera a trav�s del archivo leyendo cada registro de auto
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
    {
        // Compara las letras y n�meros de patente con los del auto actual
        if ((strcmp(letras, aux.patente.letras) == 0) && (strcmp(numeros, aux.patente.numeros) == 0))
        {
            flag = 1;  // Si encuentra una coincidencia, establece el flag a 1
            printf ("-EL AUTO YA EXISTE-\n");  // Imprime un mensaje de advertencia
            break;  // Sale del bucle while, ya que no es necesario continuar buscando
        }
    }

    return flag;  // Retorna el flag, indicando si el auto ya existe (1) o no (0)
}
// =================================================================================================
// =================================================================================================
void recorrer_Array_Autos (char archivo [])
{
    FILE* arch = fopen (archivo, "rb");  // Abre el archivo en modo lectura binaria ("rb")
    autoS aux;  // Declara una variable auxiliar para almacenar cada registro de auto
    int i = 0;  // Inicializa un contador para el n�mero de autos
    if (arch == NULL)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("NO HAY AUTOS DISPONIBLES\n");
        printf ("------------------------------------------------------------------\n");
    }
    // Verifica si el archivo se abri� correctamente
    else
    {
        // Bucle para leer cada registro de auto del archivo
        while (fread (&aux, sizeof (autoS), 1, arch) > 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("AUTO Nro %d\n", i + 1);  // Muestra el n�mero de auto actual
            printf ("------------------------------------------------------------------\n");
            mostrarAuto (aux);  // Llama a la funci�n mostrarAuto para mostrar los detalles del auto
            i++;  // Incrementa el contador de autos
        }

        fclose (arch);  // Cierra el archivo despu�s de leer todos los registros
    }
}
// =================================================================================================
// =================================================================================================
void mostrarAuto(autoS automovil)
{
    // Imprime la patente del autom�vil formateada como "Patente: letras-numeros"
    printf("Patente: %s-%s\n", automovil.patente.letras, automovil.patente.numeros);

    // Imprime la marca del autom�vil
    printf("Marca: %s\n", automovil.marca);

    // Imprime el modelo del autom�vil
    printf("Modelo: %s\n", automovil.modelo);

    // Imprime el a�o del autom�vil
    printf("A�o: %s\n", automovil.anio);

    // Imprime los kil�metros del autom�vil
    printf("Kil�metros: %s\n", automovil.kms);

    // Imprime el titular del autom�vil
    printf("Titular: %s\n", automovil.titular.user);

    // Imprime el precio de adquisici�n del autom�vil
    printf("Precio de Adquisici�n: %s\n", automovil.precioDeAdquisicion);
}
// =================================================================================================
// =================================================================================================
void modificar_Auto(char archivo[])
{
    recorrer_Array_Autos(archivo); // Muestra todos los autos existentes en el archivo
    FILE *arch = fopen(archivo, "rb+"); // Abre el archivo en modo lectura y escritura binaria
    if (arch != NULL)
    {
        printf ("------------------------------------------------------------------\n");
        printf(" SECCION PARA MODIFICAR UN AUTO\n");
        printf ("------------------------------------------------------------------\n");
        autoS autoAux; // Variable para almacenar temporalmente los datos del auto a modificar
        int flag = 0;
        int flag2 = 0;
        int pos = 0;
        int op = 1;

        // Solicita al usuario el n�mero del auto a modificar
        printf("Ingrese el Nro del auto a modificar\n");
        scanf("%d", &pos);
        printf ("------------------------------------------------------------------\n");
        pos = pos - 1;

        // Ubica la posici�n del auto en el archivo seg�n el n�mero ingresado
        fseek(arch, sizeof(autoS) * pos, SEEK_SET);

        // Lee los datos del auto desde el archivo y los guarda en autoAux
        fread(&autoAux, sizeof(autoS), 1, arch);

        // Muestra los datos actuales del auto seleccionado
        mostrarAuto(autoAux);

        // Bucle para permitir al usuario seleccionar qu� dato modificar
        while (op != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf("1- Modificar patente\n");
            printf("2- Modificar Marca\n");
            printf("3- Modificar Modelo\n");
            printf("4- Modificar el anio de fabricacion\n");
            printf("5- Modificar los kms\n");
            printf("6- Modificar el precio de adquisicion\n");
            printf("7- Modificar todos los datos\n");
            printf("0 para finalizar la ejecucion\n");
            printf(" INGRESE AQUI = ");
            scanf("%i", &op);
            printf("\n");
            printf ("------------------------------------------------------------------\n");

            switch (op)
            {
            case 1:
                flag = 1;
                while (flag == 1)
                {
                    // Modifica las letras y n�meros de la patente del auto
                    printf ("------------------------------------------------------------------\n");
                    printf("INGRESE LAS LETRAS DE LA PATENTE\n");
                    printf ("------------------------------------------------------------------\n");
                    printf ("INGRESE AQUI= ");
                    fflush(stdin);
                    gets(autoAux.patente.letras);
                    flag = comprobar_Caracteres_Patente(autoAux.patente.letras);
                }
                flag = 1;
                while (flag == 1)
                {
                    printf ("------------------------------------------------------------------\n");
                    printf("INGRESE LAS NUMEROS DE LA PATENTE\n");
                    fflush(stdin);
                    gets(autoAux.patente.numeros);
                    flag = comprobar_Numeros_Dni(autoAux.patente.numeros);
                }
                break;
            case 2:
                // Modifica la marca del auto
                printf ("------------------------------------------------------------------\n");
                printf("INGRESE LA MARCA DEL AUTO\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI= ");
                fflush(stdin);
                gets(autoAux.marca);
                break;
            case 3:
                // Modifica el modelo del auto
                printf ("------------------------------------------------------------------\n");
                printf("INGRESE EL MODELO DEL AUTO\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI= ");
                fflush(stdin);
                gets(autoAux.modelo);
                break;
            case 4:
                flag = 1;
                flag2 = 1;
                while (flag == 1 || flag2 == 1)
                {
                    // Modifica el a�o de fabricaci�n del auto
                    printf ("------------------------------------------------------------------\n");
                    printf("INGRESE EL ANIO DEL AUTO\n");
                    printf ("------------------------------------------------------------------\n");
                    printf ("INGRESE AQUI= ");
                    fflush(stdin);
                    gets(autoAux.anio);
                    flag = comprobar_Numeros_Dni(autoAux.anio);
                    if (flag == 0)
                    {
                        int aux = atoi(autoAux.anio);
                        flag2 = verificar_Anio_Auto(aux);
                    }
                }
                break;
            case 5:
                flag = 1;
                flag2 = 1;
                while (flag2 == 1)
                {
                    // Modifica los kil�metros del auto
                    printf ("------------------------------------------------------------------\n");
                    printf("INGRESE LOS KMS DEL AUTO\n");
                    printf ("MAX 200000 KMS\n");
                    printf ("------------------------------------------------------------------\n");
                    printf ("INGRESE AQUI= ");
                    fflush(stdin);
                    gets(autoAux.kms);
                    flag2 = comprobar_kms_Auto(autoAux.kms);
                }
                break;
            case 6:
                // Modifica el precio de adquisici�n del auto
                printf ("------------------------------------------------------------------\n");
                printf("PRECIO DE ADQUISICION\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI= ");
                fflush(stdin);
                gets(autoAux.precioDeAdquisicion);
                break;
            case 7:
                // Permite modificar todos los datos del auto
                autoAux = cargar_Auto(arch, autoAux);
                break;
            case 0:
                // Finaliza la ejecuci�n del programa
                break;
            default:
                // Opci�n inv�lida
                printf ("------------------------------------------------------------------\n");
                printf("SE INGRESO UN VALOR INCORRECTO\n");
                printf ("------------------------------------------------------------------\n");
                break;
            }

            // Escribe los cambios realizados en el archivo
            fseek(arch, sizeof(autoS) * pos, SEEK_SET);
            fwrite(&autoAux, sizeof(autoS), 1, arch);
        }
    }

    fclose(arch); // Cierra el archivo
}
// =================================================================================================
// =================================================================================================
int verificar_Anio_Auto(int anio)
{
    int flag = 0;     // Variable para indicar si el a�o es v�lido (0) o no v�lido (1)
    int limite = 2024; // A�o l�mite hasta el cual se considera v�lido el a�o de fabricaci�n
    int i = 0;         // Contador para determinar la cantidad de d�gitos del a�o
    int aux = anio;    // Variable auxiliar para mantener el valor original del a�o

    // Bucle para contar la cantidad de d�gitos del a�o
    while (anio > 0)
    {
        anio = anio / 10; // Divisi�n sucesiva por 10 para contar los d�gitos
        i++;             // Incrementa el contador de d�gitos
    }

    // Condiciones para determinar si el a�o es inv�lido
    if (aux > limite || i != 4)
    {
        flag = 1; // Establece flag a 1 si el a�o supera el l�mite o no tiene 4 d�gitos
    }

    return flag; // Devuelve flag, indicando la validez del a�o (0: v�lido, 1: no v�lido)
}
// =================================================================================================
// =================================================================================================
void mostrar_Datos_Auto(char archivo [])
{
    int flag2 = 1; // Variable que permite poder ingresar al while y comprobar la existencia de la patente
    autoS auxAuto; // Variable para almacenar temporalmente los datos del auto
        while (flag2 == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf("SECCION PARA MOSTRAR DATOS DE UN AUTO\n");
            printf("Ingrese la patente del auto a buscar\n");
            printf ("------------------------------------------------------------------\n");

            int flag = 1;

            // Bucle para verificar las letras de la patente
            while (flag == 1)
            {
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE LAS LETRAS DE LA PATENTE\n");
                printf ("Formato: EN MAYUSCULA\n");
                printf ("Ejemplo: 'DEF'\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI: ");
                fflush (stdin);
                gets (auxAuto.patente.letras);
                flag = comprobar_Caracteres_Patente (auxAuto.patente.letras);
            }

            flag = 1;

            // Bucle para verificar los n�meros de la patente
            while (flag == 1)
            {
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE LAS NUMEROS DE LA PATENTE\n");
                printf ("Formato: EN MAYUSCULA\n");
                printf ("Ejemplo: '543'\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI: ");
                fflush (stdin);
                gets (auxAuto.patente.numeros);
                flag = comprobar_Numeros_Dni (auxAuto.patente.numeros);
            }

            // Verificar si la patente ingresada coincide con alg�n auto en el archivo autosArch
            flag2 = buscar_Coincidencia_Patente (archivo, auxAuto.patente.letras, auxAuto.patente.numeros);
        }
        // Busca la poscion que ocupa en el archivo el auto a buscar y lo retorna para mostrarlo en lo que sigue
        int i = buscar_Posicion_Auto (archivo, auxAuto.patente.letras, auxAuto.patente.numeros);
        // Apertura del archivo para mostrar el auto.
        FILE * arch = fopen (archivo, "rb");
        fseek(arch, sizeof(autoS) * i, SEEK_SET); // Coloca el puntero de lectura en la posici�n del auto deseado
        fread(&auxAuto, sizeof(autoS), 1, arch); // Lee los datos del auto desde el archivo y los guarda en auxAuto

        mostrarAuto(auxAuto); // Llama a la funci�n mostrarAuto para imprimir los datos del auto
        printf ("------------------------------------------------------------------\n");

    fclose(arch); // Cierra el archivo despu�s de usarlo
}
// =================================================================================================
// =================================================================================================
void registrar_Venta_Arch (char ventasArch [], char autosArch [], char usersArch [], usuario vendedor)
{
    // Abrir el archivo de ventas
    FILE *arch = fopen (ventasArch, "ab");
    ventaS aux; // Variable auxiliar de tipo ventaS para almacenar la venta registrada

    // Verificar si se abri� correctamente el archivo
    if (arch != NULL)
    {
        // Llamar a la funci�n registrar_Venta para obtener los datos de la venta a registrar
        aux = registrar_Venta (autosArch, usersArch, vendedor);

        // Posicionarse al final del archivo para a�adir la nueva venta
        fseek (arch, 0, SEEK_END);

        // Escribir la estructura auxiliar (ventaS) en el archivo
        fwrite (&aux, sizeof (ventaS), 1, arch);
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose (arch);
}
// =================================================================================================
// =================================================================================================
ventaS registrar_Venta (char autosArch [], char usersArch [], usuario vendedor)
{
    // Imprimir encabezado para la secci�n de registro de venta
    printf ("------------------------------------------------------------------\n");
    printf ("SECCION PARA REGISTRAR UNA VENTA\n");
    printf ("------------------------------------------------------------------\n");
    ventaS venta; // Estructura para almacenar los datos de la venta
    int flag = 1; // Variable de control para ciclos while
    int flag2 = 1; // Variable de control adicional para ciclos while

    // Bucle para ingresar la fecha de operaci�n v�lida
    while (flag == 1)
    {
        flag2 = 1;
        printf ("------------------------------------------------------------------\n");
        printf ("FECHA DE OPERACION\n");
        printf ("Formato: XX/XX/XXXX\n");
        printf ("------------------------------------------------------------------\n");

        // Bucle para verificar la entrada de la fecha
        while (flag2 == 1)
        {
            printf("Ingrese el dia de operacion: ");
            fflush (stdin);
            gets (venta.fecha.dia);
            printf("Ingrese el mes de operacion: ");
            fflush (stdin);
            gets (venta.fecha.mes);
            printf("Ingrese el a�o de operacion: ");
            fflush (stdin);
            gets (venta.fecha.anio);
            flag2 = verificar_Caracteres_Edad (venta.fecha.dia, venta.fecha.mes, venta.fecha.anio);
        }

        // Convertir la fecha ingresada a enteros para validarla
        int diaE = atoi (venta.fecha.dia);
        int mesE = atoi (venta.fecha.mes);
        int anioE = atoi (venta.fecha.anio);

        // Verificar si la fecha de operaci�n es v�lida
        flag = comprobar_Fecha_Venta (diaE, mesE, anioE);
    }

    flag = 1;
    flag2 = 1;
    int flag3 = 1;

    // Bucle para ingresar la patente del autom�vil a vender
    while (flag3 == 1)
    {
        flag = 1;

        // Bucle para verificar las letras de la patente
        while (flag == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE LAS LETRAS DE LA PATENTE\n");
            printf ("Formato: EN MAYUSCULA\n");
            printf ("Ejemplo: 'DEF'\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (venta.autoAVender.letras);
            flag = comprobar_Caracteres_Patente (venta.autoAVender.letras);
        }

        flag = 1;

        // Bucle para verificar los n�meros de la patente
        while (flag == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE LAS NUMEROS DE LA PATENTE\n");
            printf ("Formato: EN MAYUSCULA\n");
            printf ("Ejemplo: '543'\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (venta.autoAVender.numeros);
            flag = comprobar_Numeros_Dni (venta.autoAVender.numeros);
        }

        // Verificar si la patente ingresada coincide con alg�n auto en el archivo autosArch
        flag3 = buscar_Coincidencia_Patente (autosArch, venta.autoAVender.letras, venta.autoAVender.numeros);
    }

    flag = 1;

    // Bucle para ingresar el precio de venta del autom�vil
    while (flag == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE EL PRECIO DE VENTA\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        gets (venta.precioVenta);
        flag = comprobar_Numeros_Dni (venta.precioVenta);

        // Si el precio es v�lido, calcular la ganancia de la venta
        if (flag == 0)
        {
            calcular_Ganancia_Venta (autosArch, &venta);
        }
    }
    // Se ingresa automaticamente el dni del vendedor logeado en la venta
    strcpy (venta.dniVendedor, vendedor.dni);

    flag = 1;
    flag2 = 1;
    flag3 = 1;
    int flag4 = 1;
    // Bucle para ingresar el DNI del comprador v�lido y verificar su existencia
    while (flag == 1 || flag3 == 1 || flag2 == 1 || flag4 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("DNI DEL COMPRADOR:\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        gets (venta.dniComprador);

        // Verificar el formato y caracteres del DNI del comprador
        flag2 = verificar_Dni (venta.dniComprador);
        flag3 = comprobar_Numeros_Dni (venta.dniComprador);
        flag = verificar_Space (venta.dniComprador);

        // Si el DNI del comprador es v�lido, verificar su existencia en el archivo de usuarios
        if (flag == 0 && flag2 == 0 && flag3 == 0)
        {
            flag4 = verificar_Existencia_Persona_Venta (autosArch, usersArch, venta.dniComprador, venta.autoAVender.letras, venta.autoAVender.numeros);
        }
    }

    // Retornar la estructura venta con todos los datos ingresados y verificados
    return venta;
}
// =================================================================================================
// =================================================================================================
int buscar_Coincidencia_Patente (char archivo [], char letras [], char numeros [])
{
    // Abrir el archivo
    FILE *arch = fopen (archivo, "rb");
    autoS aux; // Variable auxiliar de tipo autoS para leer los registros del archivo
    int flag = 1; // Variable de control para indicar si se encontr� la patente

    // Leer registros del archivo hasta el final
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
    {
        // Comparar las letras y n�meros de la patente con los del registro actual (aux)
        if ((strcmp (letras, aux.patente.letras) == 0) && (strcmp (numeros, aux.patente.numeros) == 0) && strcmpi (aux.titular.user, "consecionaria") == 0)
        {
            flag = 0; // Cambiar el valor de flag a 0 si se encuentra la patente
            break; // Salir del bucle ya que se encontr� una coincidencia
        }
    }

    // Si flag es 1, significa que no se encontr� la patente en el archivo
    if (flag == 1)
    {
        printf ("-EL AUTO NO EXISTE O YA SE HA VENDIDO-\n");
    }

    // Cerrar el archivo despu�s de la b�squeda
    fclose (arch);

    // Retornar el valor de flag, que indica si se encontr� la patente (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Fecha_Venta (int dia, int mes, int anio)
{
    int flag = 0; // Variable de control para indicar si la fecha es v�lida (0) o inv�lida (1)
    int flag1 = 0; // Variables de control adicionales para verificar a�o, mes y d�a
    int flag2 = 0;
    int flag3 = 0;

    // Verificar el a�o del auto
    flag1 = verificar_Anio_Auto (anio);

    // Verificar el mes
    flag2 = verificar_Mes (mes);

    // Verificar el d�a dentro del mes y a�o dados
    flag3 = verificar_Dia (dia, mes);

    // Si alguna de las verificaciones devuelve un resultado no v�lido, establecer flag en 1 y mostrar un mensaje
    if (flag1 != 0 || flag2 != 0 || flag3 != 0)
    {
        flag = 1;
        printf ("-FECHA INVALIDA-\n");
    }

    // Retornar el valor de flag, que indica si la fecha es v�lida (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
void calcular_Ganancia_Venta (char autosArch [], ventaS *venta)
{
    // Abrir el archivo de autos en modo lectura binaria
    FILE *arch = fopen (autosArch, "rb");
    autoS aux; // Variable auxiliar de tipo autoS para leer los registros del archivo de autos

    // Verificar si se abri� correctamente el archivo
    if (arch != NULL)
    {
        // Leer registros del archivo hasta el final
        while (fread(&aux, sizeof (autoS), 1, arch) > 0)
        {
            // Comparar las letras y n�meros de la patente con los del registro actual (aux)
            if ((strcmp ((*venta).autoAVender.letras, aux.patente.letras) == 0) && (strcmp ((*venta).autoAVender.numeros, aux.patente.numeros) == 0))
            {
                // Convertir precios de cadena a entero para calcular la ganancia
                int precioAdquisicion = atoi (aux.precioDeAdquisicion);
                int precioVenta = atoi ((*venta).precioVenta);
                int ganancia = precioVenta - precioAdquisicion;

                // Convertir la ganancia de entero a cadena y almacenarla en la estructura de venta
                sprintf ((*venta).ganancia, "%d", ganancia);
            }
        }
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose (arch);
}
// =================================================================================================
// =================================================================================================
void mostrar_Ventas (char ventasArch [])
{
    // Abrir el archivo de ventas
    FILE *arch = fopen (ventasArch, "rb");
    ventaS aux; // Variable auxiliar de tipo ventaS para leer los registros del archivo
    int i = 0; // Contador para el n�mero de venta

    // Verificar si se abri� correctamente el archivo
    if (arch != NULL)
    {
        // Leer registros del archivo hasta el final
        while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
        {
            // Imprimir encabezado y n�mero de venta
            printf ("------------------------------------------------------------------\n");
            printf ("VENTA Nro %d\n", i + 1);

            // Llamar a la funci�n mostrar_Venta para mostrar los detalles de la venta actual
            mostrar_Venta (aux);

            i++; // Incrementar el contador de ventas
        }
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose (arch);
}
// =================================================================================================
// =================================================================================================
void mostrar_Venta (ventaS aux)
{
    // Mostrar los datos de fecha y patente de la venta recibida como par�metro
    printf("Fecha de venta: %s/%s/%s\n", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    printf("Patente: %s-%s\n", aux.autoAVender.letras, aux.autoAVender.numeros);
}
// =================================================================================================
// =================================================================================================
int verificar_Existencia_Persona_Venta (char autosArch [], char usersArch [], char dni [], char letras [], char numeros [])
{
    FILE *arch = fopen (usersArch, "rb"); // Abrir el archivo de usuarios
    int flag = 1; // Variable de control para indicar si se encontr� el usuario (0) o no (1)
    usuario aux; // Variable para almacenar temporalmente los registros de usuario
    int i = 0; // Contador para el �ndice del auto encontrado (para actualizar el titular)

    // Verificar si se abri� correctamente el archivo de usuarios
    if (arch != NULL)
    {
        fseek (arch, 0, SEEK_SET); // Posicionarse al inicio del archivo

        // Leer registros del archivo de usuarios hasta el final
        while (fread (&aux, sizeof (usuario), 1, arch) > 0)
        {
            // Comparar el DNI del usuario actual con el DNI buscado
            if (strcmp (aux.dni, dni) == 0)
            {
                FILE *arc = fopen (autosArch, "rb+"); // Abrir el archivo de autos
                autoS autoAux; // Variable para almacenar temporalmente los registros de auto

                // Verificar si se abri� correctamente el archivo de autos
                if (arc != NULL)
                {
                    // Leer registros del archivo de autos hasta el final
                    while (fread (&autoAux, sizeof (autoS), 1, arc) > 0)
                    {
                        // Comparar las letras y n�meros de la patente con el auto actual
                        if ((strcmp (letras, autoAux.patente.letras) == 0) && (strcmp (numeros, autoAux.patente.numeros) == 0))
                        {
                            fseek (arc, sizeof (autoS)*i, SEEK_SET); // Posicionarse en la posici�n del auto encontrado
                            autoAux.titular = aux; // Actualizar el titular del auto con el usuario encontrado
                            fwrite (&autoAux, sizeof (autoS), 1, arc); // Escribir el auto actualizado en el archivo
                            flag = 0; // Cambiar el valor de flag a 0 indicando que se encontr� y actualiz� el titular
                            break; // Salir del bucle ya que se encontr� el auto
                        }
                        i++; // Incrementar el contador de �ndice
                    }
                    fclose (arc); // Cerrar el archivo de autos despu�s de la operaci�n
                }
            }
        }
        fclose (arch); // Cerrar el archivo de usuarios despu�s de la operaci�n
    }

    // Si flag es 1, significa que no se encontr� el usuario en el archivo de usuarios
    if (flag == 1)
    {
        printf ("-LA PERSONA INGRESADA NO EXISTE-\n");
    }

    // Retornar el valor de flag, que indica si se encontr� (0) o no (1) el usuario
    return flag;
}
// =================================================================================================
// =================================================================================================
void abrir_Archivo_Ventas (char ventasArch [])
{
    // Abrir el archivo de ventas
    FILE *arch = fopen (ventasArch, "rb");
    if (arch != NULL)
    {
        ventaS aux; // Variable auxiliar de tipo ventaS para leer los registros del archivo
        int i = 0; // Contador para el n�mero de venta
        mostrar_Ventas_Arch_Completo (arch, aux, i);
        // Cerrar el archivo despu�s de la operaci�n
    }
    fclose (arch);
}
void mostrar_Ventas_Arch_Completo (FILE* arch, ventaS aux, int i)
{
    // Leer registros del archivo de ventas hasta el final
    if (fread (&aux, sizeof (ventaS), 1, arch) > 0)
    {
        // Imprimir encabezado y n�mero de venta
        printf ("------------------------------------------------------------------\n");
        printf ("VENTA Nro %d\n", i + 1);
        printf ("------------------------------------------------------------------\n");

        // Llamar a la funci�n mostrar_VentaS_Completo para mostrar todos los detalles de la venta actual
        mostrar_VentaS_Completo (aux);
        mostrar_Ventas_Arch_Completo (arch, aux, i + 1);
    }

}
// =================================================================================================
// =================================================================================================
void mostrar_VentaS_Completo (ventaS venta)
{
    // Mostrar todos los detalles de la venta recibida como par�metro

    // Mostrar la patente del auto vendido
    printf("Patente: %s-%s\n", venta.autoAVender.letras, venta.autoAVender.numeros);

    // Mostrar la fecha de la venta
    printf("Fecha: %s/%s/%s\n", venta.fecha.dia, venta.fecha.mes, venta.fecha.anio);

    // Mostrar el precio de venta
    printf("Precio de Venta: %s\n", venta.precioVenta);

    // Mostrar la ganancia obtenida en la venta
    printf("Ganancia: %s\n", venta.ganancia);

    // Mostrar el DNI del comprador
    printf("DNI del Comprador: %s\n", venta.dniComprador);

    // Mostrar el DNI del vendedor
    printf("DNI del Vendedor: %s\n", venta.dniVendedor);
}
// =================================================================================================
// =================================================================================================
int calcular_Recaudacion (FILE *arch, char anio [], char mes [])
{
    ventaS aux; // Variable auxiliar de tipo ventaS para leer los registros del archivo
    int flag = 1; // Variable de control para el ingreso del a�o
    int flag2 = 1; // Variable de control para el ingreso del mes
    int i = 0; // Contador para el n�mero de ventas encontradas

    // Mostrar encabezado para la secci�n de c�lculo de recaudaciones
    printf ("------------------------------------------------------------------\n");
    printf ("SECCION QUE CALCULA LAS RECAUDACIONES\n");
    printf ("------------------------------------------------------------------\n");

    // Ciclo para validar y obtener el a�o correcto
    while (flag == 1 || flag2 == 1)
    {
        printf ("INGRESE EL A�O QUE DESEA CONTABILIZAR: ");
        fflush (stdin);
        gets (anio);
        flag = comprobar_Numeros_Dni (anio); // Validar que la cadena contenga solo n�meros
        int anioInt = atoi (anio); // Convertir la cadena a entero
        flag2 = verificar_Anio_Auto (anioInt); // Validar que el a�o sea v�lido seg�n la l�gica de negocio
    }

    flag = 1;
    flag2 = 1;

    // Ciclo para validar y obtener el mes correcto
    while (flag == 1 || flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE EL MES QUE DESEA CONTABILIZAR: ");
        fflush (stdin);
        gets (mes);
        flag = comprobar_Numeros_Dni (anio); // Validar que la cadena contenga solo n�meros
        int mesInt = atoi (mes); // Convertir la cadena a entero
        flag2 = verificar_Mes (mesInt); // Validar que el mes sea v�lido seg�n la l�gica de negocio
    }

    // Leer registros del archivo de ventas hasta el final
    while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
    {
        // Verificar si la venta corresponde al a�o y mes especificados
        if (strcmp (anio, aux.fecha.anio) == 0 && strcmp (mes, aux.fecha.mes) == 0)
        {
            i++; // Incrementar el contador de ventas encontradas
        }
    }

    // Retornar el n�mero total de ventas encontradas para el a�o y mes especificados
    return i;
}
// =================================================================================================
// =================================================================================================
void mostrar_Recaudacion (char ventas [])
{
    ventaS aux; // Variable auxiliar de tipo ventaS para leer los registros del archivo
    int recaudacionFinal = 0; // Variable para almacenar la recaudaci�n total del mes
    char anio [5]; // Arreglo de caracteres para almacenar el a�o seleccionado
    char mes [3]; // Arreglo de caracteres para almacenar el mes seleccionado
    FILE *arch = fopen (ventas, "rb"); // Abrir el archivo de ventas

    // Verificar si se abri� correctamente el archivo
    if (arch != NULL)
    {
        // Obtener la cantidad de ventas para el a�o y mes especificados
        int cant_Ventas = calcular_Recaudacion (arch, anio, mes);

        // Crear un arreglo din�mico para almacenar las ganancias de cada venta del mes
        int* array = (int*) malloc (sizeof (int) * cant_Ventas);
        int i = 0; // Variable para el �ndice del arreglo din�mico

        fseek (arch, 0, SEEK_SET); // Posicionarse al inicio del archivo

        // Mostrar encabezado indicando el mes encontrado
        printf ("------------------------------------------------------------------\n");
        printf ("SE ENCONTRO del mes %s\n", mes);
        printf ("------------------------------------------------------------------\n");

        // Leer registros del archivo de ventas hasta el final
        while (fread (&aux, sizeof (ventaS), 1, arch) > 0)
        {
            // Verificar si la venta corresponde al a�o y mes especificados
            if (strcmp (anio, aux.fecha.anio) == 0 && strcmp (mes, aux.fecha.mes) == 0)
            {
                // Mostrar los detalles completos de la venta
                mostrar_VentaS_Completo (aux);
                printf ("------------------------------------------------------------------\n");

                // Convertir la ganancia de la venta a entero y almacenar en el arreglo din�mico
                int gananciaInt = atoi (aux.ganancia);
                array[i] = gananciaInt;
                i++;
            }
        }

        // Calcular la recaudaci�n final sumando todas las ganancias del arreglo din�mico
        for (int j = 0; j < cant_Ventas; j++)
        {
            recaudacionFinal = recaudacionFinal + array[j];
        }

        // Liberar la memoria asignada al arreglo din�mico
        free(array);
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose (arch);

    // Mostrar la recaudaci�n total del mes seleccionado
    printf ("LA RECAUDACION DEL MES DE %s, a�o %s fue de %d\n", mes, anio, recaudacionFinal);
    printf ("------------------------------------------------------------------\n");
}
// =================================================================================================
// =================================================================================================
void calcular_Venta_Mayor_Ganancia(char ventasArch[])
{
    FILE *arch = fopen(ventasArch, "rb"); // Abrir el archivo de ventas
    ventaS aux, mayorVenta; // Variables para almacenar las ventas y la venta con mayor ganancia
    int mayorGanancia = -1; // Variable para almacenar la mayor ganancia, inicializada en -1

    // Verificar si se pudo abrir correctamente el archivo
    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo de ventas.\n");
        return; // Salir de la funci�n si no se pudo abrir el archivo
    }

    // Leer registros del archivo de ventas hasta el final
    while (fread(&aux, sizeof(ventaS), 1, arch) > 0)
    {
        int ganancia = atoi(aux.ganancia); // Convertir la ganancia de la venta actual a entero

        // Verificar si la ganancia actual es mayor que la mayor ganancia encontrada hasta ahora
        if (ganancia > mayorGanancia)
        {
            mayorGanancia = ganancia; // Actualizar la mayor ganancia
            mayorVenta = aux; // Actualizar la venta con mayor ganancia
        }
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose(arch);

    // Mostrar encabezados para indicar la venta de mayor ganancia encontrada
    printf ("------------------------------------------------------------------\n");
    printf("VENTA DE MAYOR GANANCIA\n");
    printf ("------------------------------------------------------------------\n");

    // Mostrar todos los detalles de la venta con mayor ganancia utilizando la funci�n mostrar_VentaS_Completo
    mostrar_VentaS_Completo(mayorVenta);
}
// =================================================================================================
// =================================================================================================
void mostrar_Autos_menos_10 (char autosArch [])
{
    // Mostrar encabezados indicando la secci�n de autos con menos de 10 a�os
    printf ("------------------------------------------------------------------\n");
    printf("AUTOS CON MENOS DE 10 A�OS\n");
    printf ("------------------------------------------------------------------\n");
    FILE *arch = fopen (autosArch, "rb"); // Abrir el archivo de autos
    autoS aux; // Variable para almacenar los datos de cada auto

    // Verificar si se pudo abrir correctamente el archivo
    if (arch != NULL)
    {
        // Leer registros del archivo de autos hasta el final
        while (fread (&aux, sizeof (autoS), 1, arch) > 0)
        {
            int anioInt = atoi (aux.anio); // Convertir el a�o del auto a entero
            int edadAuto = 2024 - anioInt; // Calcular la edad del auto restando el a�o actual

            // Verificar si la edad del auto es menor a 10 a�os y si el titular es "consecionaria"
            if (edadAuto < 10 && strcmp (aux.titular.user, "consecionaria") == 0)
            {
                mostrarAuto(aux); // Mostrar los detalles completos del auto utilizando la funci�n mostrarAuto
            }
        }
    }

    // Cerrar el archivo despu�s de la operaci�n
    fclose (arch);
}
void recorrer_Array_Autos_Comprador (char archivo [])
{
    FILE* arch = fopen (archivo, "rb");  // Abre el archivo en modo lectura binaria ("rb")
    autoS aux;  // Declara una variable auxiliar para almacenar cada registro de auto
    int i = 0;  // Inicializa un contador para el n�mero de autos

    // Verifica si el archivo se abri� correctamente
    if (arch != NULL)
    {
        // Bucle para leer cada registro de auto del archivo
        while (fread (&aux, sizeof (autoS), 1, arch) > 0)
        {
            if (strcmp (aux.titular.user, "consecionaria") == 0)
            {
                printf ("------------------------------------------------------------------\n");
                printf ("AUTO Nro %d\n", i + 1);  // Muestra el n�mero de auto actual
                printf ("------------------------------------------------------------------\n");
                mostrar_Auto_Comprador (aux);  // Llama a la funci�n mostrarAuto para mostrar los detalles del auto
                i++;  // Incrementa el contador de autos
            }

        }

        fclose (arch);  // Cierra el archivo despu�s de leer todos los registros
    }
}
// =================================================================================================
// =================================================================================================
void mostrar_Auto_Comprador(autoS automovil)
{
    // Imprime la patente del autom�vil formateada como "Patente: letras-numeros"
    printf("Patente: %s-%s\n", automovil.patente.letras, automovil.patente.numeros);

    // Imprime la marca del autom�vil
    printf("Marca: %s\n", automovil.marca);

    // Imprime el modelo del autom�vil
    printf("Modelo: %s\n", automovil.modelo);

    // Imprime el a�o del autom�vil
    printf("A�o: %s\n", automovil.anio);

    // Imprime los kil�metros del autom�vil
    printf("Kil�metros: %s\n", automovil.kms);
}
int buscar_Coincidencia_Patente_Para_Mostrar_Auto (char archivo [], char letras [], char numeros [])
{
    // Abrir el archivo
    FILE *arch = fopen (archivo, "rb");
    autoS aux; // Variable auxiliar de tipo autoS para leer los registros del archivo
    int flag = 1; // Variable de control para indicar si se encontr� la patente

    // Leer registros del archivo hasta el final
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
    {
        // Comparar las letras y n�meros de la patente con los del registro actual (aux)
        if ((strcmp (letras, aux.patente.letras) == 0) && (strcmp (numeros, aux.patente.numeros) == 0))
        {
            flag = 0; // Cambiar el valor de flag a 0 si se encuentra la patente
            break; // Salir del bucle ya que se encontr� una coincidencia
        }
    }

    // Si flag es 1, significa que no se encontr� la patente en el archivo
    if (flag == 1)
    {
        printf ("-EL AUTO NO EXISTE-\n");
    }

    // Cerrar el archivo despu�s de la b�squeda
    fclose (arch);

    // Retornar el valor de flag, que indica si se encontr� la patente (0) o no (1)
    return flag;
}

int buscar_Posicion_Auto (char archivo [], char letras [], char numeros [])
{
    // Abrir el archivo
    FILE *arch = fopen (archivo, "rb");
    autoS aux; // Variable auxiliar de tipo autoS para leer los registros del archivo
    int i = 0; // Variable que retornarnmos con la posicion a mostrar

    // Leer registros del archivo hasta el final
    while (fread(&aux, sizeof (autoS), 1, arch) > 0)
    {
        // Comparar las letras y n�meros de la patente con los del registro actual (aux)
        if ((strcmp (letras, aux.patente.letras) == 0) && (strcmp (numeros, aux.patente.numeros) == 0) && strcmpi (aux.titular.user, "consecionaria") == 0)
        {
            break; // Salir del bucle ya que se encontr� una coincidencia
        }
        i++;
    }
    // Cerrar el archivo despu�s de la b�squeda
    fclose (arch);

    // Retornar el valor de flag, que indica si se encontr� la patente (0) o no (1)
    return i;
}
