#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"
#include "menus.h"
#include "pila.h"
// =================================================================================================
// =================================================================================================
void registro_En_El_sistema(char archivo[])
{
    // Esta funci�n registra un nuevo usuario en un archivo binario.
    // Abre el archivo en modo a�adir y leer binario.
    // Llama a la funci�n crear_Cuenta para obtener los datos del usuario.
    // Escribe los datos del usuario al final del archivo y luego cierra el archivo.

    printf("------------------------------------------------------------------\n");
    printf("CREACION DE USUARIO\n");
    printf("------------------------------------------------------------------\n");

    FILE *arch = fopen(archivo, "a+b");
    usuario persona;

    if (arch != NULL)
    {
        persona = crear_Cuenta(arch);
        fseek(arch, 0, SEEK_END);
        fwrite(&persona, sizeof(usuario), 1, arch);
    }

    fclose(arch);
}
// =================================================================================================
// =================================================================================================
usuario crear_Cuenta(FILE *arch)
{
    // Esta funci�n crea una cuenta de usuario.
    // Utiliza otras funciones para solicitar y registrar datos espec�ficos del usuario,
    // como nombre de usuario y contrase�a, utilizando el archivo proporcionado.

    usuario personaAux;
    personaAux = pedir_Datos_Registro(arch, personaAux);
    nombre_Usuario(arch, &personaAux);
    contrasena(arch, &personaAux);

    return personaAux;
}
// =================================================================================================
// =================================================================================================
void nombre_Usuario(FILE* arch, usuario *persona)
{
    // Esta funci�n permite al usuario crear y validar un nombre de usuario.
    // Proporciona instrucciones sobre los requisitos del nombre de usuario,
    // y verifica la disponibilidad del nombre ingresado utilizando comprobar_Usuario.

    int variableUser = 1;
    while (variableUser != 0)
    {
        printf("------------------------------------------------------------------\n");
        printf("CREE SU NOMBRE DE USUARIO\n");
        printf("------------------------------------------------------------------\n");
        printf("Requisitos:\n");
        printf("Debe tener m�nimo 8 caracteres\n");
        printf("NO debe contener may�sculas\n");
        printf("NO debe contener espacios\n");
        printf("------------------------------------------------------------------\n");
        printf("INGRESE AQUI: ");
        fflush(stdin);
        gets((*persona).user);
        printf("------------------------------------------------------------------\n");

        // Verifica la disponibilidad del nombre de usuario utilizando comprobar_Usuario
        variableUser = comprobar_Usuario(arch, (*persona).user);

        if (variableUser != 0)
        {
            printf("------------------------------------------------------------------\n");
            printf("REINGRESAR NOMBRE DE USUARIO\n");
            printf("------------------------------------------------------------------\n");
        }
    }
}
// =================================================================================================
// =================================================================================================
void contrasena(FILE* arch, usuario *persona)
{
    // Esta funci�n permite al usuario crear y validar una contrase�a.
    // Proporciona instrucciones sobre los requisitos de la contrase�a,
    // y verifica la validez de la contrase�a ingresada utilizando comprobar_Contra y verificar_Contrasena.

    int variableContra = 1;

    while (variableContra != 0)
    {
        printf("------------------------------------------------------------------\n");
        printf("CREE UNA CONTRASE�A\n");
        printf("------------------------------------------------------------------\n");
        printf("Requisitos:\n");
        printf("Debe contener al menos una may�scula\n");
        printf("Debe tener m�nimo 8 caracteres\n");
        printf("Debe contener al menos un n�mero\n");
        printf("NO debe contener espacios\n");
        printf("------------------------------------------------------------------\n");
        printf("INGRESE AQUI: ");
        fflush(stdin);
        gets((*persona).contra);
        printf("------------------------------------------------------------------\n");

        // Verifica la validez de la contrase�a utilizando comprobar_Contra
        variableContra = comprobar_Contra(arch, (*persona).contra);

        // Si la contrase�a pasa la primera validaci�n, verifica requisitos adicionales usando verificar_Contrasena
        if (variableContra == 0)
        {
            variableContra = verificar_Contrasena((*persona).contra);
        }

        if (variableContra != 0)
        {
            printf("------------------------------------------------------------------\n");
            printf("REESCRIBA LA CONTRASE�A\n");
            printf("------------------------------------------------------------------\n");
        }
    }
}
// =================================================================================================
// =================================================================================================
int comprobar_Usuario(FILE *arch, char palabra[])
{
    // Esta funci�n verifica la validez de un nombre de usuario.
    // Realiza m�ltiples comprobaciones utilizando funciones auxiliares para asegurar que el nombre de usuario cumple con los requisitos establecidos.

    int minUser = 8;
    int flag = 0;   // Flag para verificar caracteres y longitud m�nima
    int flag2 = 0;  // Flag para verificar presencia de may�sculas
    int flag3 = 0;  // Flag para verificar espacios en blanco
    int flag4 = 0;  // Flag para verificar presencia de min�sculas
    int flag6 = 0;  // Flag adicional, parece no estar siendo utilizado
    int flag7 = 0;  // Flag para verificar existencia del usuario en el archivo

    // Realiza las verificaciones necesarias utilizando funciones auxiliares
    flag = verificar_Caracteres(palabra, minUser);
    flag7 = verificar_Existencia(arch, palabra);
    flag3 = verificar_Space(palabra);
    flag2 = comprobar_Mayusculas_User(palabra);
    flag4 = verificar_minusculas(palabra);

    // Si alguna de las comprobaciones devuelve un resultado no v�lido, establece flag a 1 (indicando fallo)
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag7 != 0 || flag6)
    {
        flag = 1;
    }

    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Contra(FILE *arch, char palabra[])
{
    // Define la longitud m�nima requerida para la contrase�a
    int minContra = 8;

    // Variables para almacenar los resultados de las verificaciones
    int flag = 0;    // Indicador general de validez de la contrase�a
    int flag2 = 0;   // Verifica la presencia de al menos una may�scula
    int flag3 = 0;   // Verifica que no haya espacios en blanco
    int flag4 = 0;   // Verifica la presencia de al menos una min�scula
    int flag5 = 0;   // Verifica la presencia de al menos un n�mero

    // Verifica la longitud m�nima y otros caracteres de la contrase�a
    flag = verificar_Caracteres(palabra, minContra);

    // Verifica si hay espacios en blanco en la contrase�a
    flag3 = verificar_Space(palabra);

    // Verifica si hay al menos una may�scula en la contrase�a
    flag2 = comprobar_Mayusculas(palabra);

    // Verifica si hay al menos una min�scula en la contrase�a
    flag4 = verificar_minusculas(palabra);

    // Verifica si hay al menos un n�mero en la contrase�a
    flag5 = comprobar_Numeros(palabra);

    // Si alguna de las verificaciones falla, establece flag a 1
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag5 != 0)
    {
        flag = 1;
    }

    // Retorna flag, que indica si la contrase�a es v�lida (0) o inv�lida (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Mayusculas(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay may�sculas)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual est� en el rango de letras may�sculas ASCII (65-90)
        if (palabra[i] >= 65 && palabra[i] <= 90)
        {
            // Si encuentra al menos una may�scula, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron may�sculas
    if (flag == 1)
    {
        printf("-NO CONTIENE MAYUSCULA-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos una may�scula (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int verificar_minusculas(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay min�sculas)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual est� en el rango de letras min�sculas ASCII (97-122)
        if (palabra[i] >= 97 && palabra[i] <= 122)
        {
            // Si encuentra al menos una min�scula, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron min�sculas
    if (flag == 1)
    {
        printf("-NO CONTIENE MINUSCULA-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos una min�scula (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay n�meros)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual est� en el rango de d�gitos ASCII (48-57)
        if (palabra[i] >= 48 && palabra[i] <= 57)
        {
            // Si encuentra al menos un n�mero, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron n�meros
    if (flag == 1)
    {
        printf("-NO CONTIENE NUMEROS-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos un n�mero (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros_Dni(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 0 (asume inicialmente que todos los caracteres son v�lidos)
    int flag = 0;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual no est� en el rango v�lido de d�gitos (48-57 en ASCII)
        if (palabra[i] < 48 || palabra[i] > 57)
        {
            // Si encuentra alg�n caracter fuera del rango, cambia flag a 1 y sale del bucle
            flag = 1;
            break;
        }
    }

    // Si flag es 1, significa que se encontraron caracteres inv�lidos
    if (flag == 1)
    {
        printf("-CARACTERES INVALIDOS-\n");
    }

    // Retorna flag, que indica si la cadena contiene caracteres inv�lidos (1) o no (0)
    return flag;
}
// =================================================================================================
// =================================================================================================
int verificar_Caracteres(char palabra[], int min)
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que la cantidad es insuficiente)
    int flag = 1;

    // Verifica si la cantidad de caracteres es mayor o igual al m�nimo requerido
    if (caracteres >= min)
    {
        // Si cumple con el requisito, cambia flag a 0
        flag = 0;
    }

    // Si flag es 1, significa que la cadena tiene menos caracteres de los requeridos
    if (flag == 1)
    {
        printf("-CANTIDAD INSUFICIENTE DE CARACTERES-\n");
    }

    // Retorna flag, que indica si la cadena cumple con el m�nimo de caracteres (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int verificar_Existencia(FILE *arch, char palabra[])
{
    int flag = 0;          // Inicializa flag en 0 (no existe el usuario)
    usuario aux;           // Variable auxiliar para almacenar cada usuario le�do

    fseek(arch, 0, SEEK_SET);  // Posiciona el puntero al inicio del archivo

    // Itera sobre cada registro de usuario en el archivo
    while (fread(&aux, sizeof(usuario), 1, arch) > 0)
    {
        // Compara el nombre de usuario del registro actual con 'palabra'
        if (strcmp(aux.user, palabra) == 0)
        {
            flag = 2;  // Si encuentra una coincidencia, cambia flag a 2 (usuario ya existe)
            break;     // Termina el bucle, ya que no es necesario seguir buscando
        }
    }

    // Si flag es 2, significa que el usuario ya existe en el archivo
    if (flag == 2)
    {
        printf("-EL NOMBRE INGRESADO YA EXISTE-\n");
    }

    return flag;  // Retorna flag, indicando si el usuario existe (2) o no (0)
}
// =================================================================================================
// =================================================================================================
int verificar_Space(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la longitud de la cadena
    int flag = 0;  // Inicializa flag en 0 (no contiene espacios)

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Comprueba si el caracter actual es un espacio (c�digo ASCII 32)
        if (palabra[i] == ' ')
        {
            flag = 1;  // Si encuentra un espacio, cambia flag a 1
            break;     // Termina el bucle, ya que no es necesario seguir buscando
        }
    }

    // Si flag es 1, significa que la cadena contiene al menos un espacio
    if (flag == 1)
    {
        printf("-CONTIENE ESPACIOS-\n");  // Imprime un mensaje indicando que la cadena contiene espacios
    }

    return flag;  // Retorna flag, indicando si la cadena contiene espacios (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int comprobar_Mayusculas_User(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la longitud de la cadena
    int flag = 0;  // Inicializa flag en 0 (no contiene may�sculas)

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Comprueba si el caracter actual es una letra may�scula (c�digos ASCII entre 65 y 90)
        if (palabra[i] >= 'A' && palabra[i] <= 'Z')
        {
            flag = 1;  // Si encuentra una may�scula, cambia flag a 1
            break;     // Termina el bucle, ya que no es necesario seguir buscando
        }
    }

    // Si flag es 1, significa que la cadena contiene al menos una may�scula
    if (flag == 1)
    {
        printf("-CONTIENE MAYUSCULA-\n");  // Imprime un mensaje indicando que la cadena contiene may�sculas
    }

    return flag;  // Retorna flag, indicando si la cadena contiene may�sculas (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int verificar_Contrasena(char palabra[])
{
    char aux[20];  // Variable auxiliar para almacenar la confirmaci�n de la contrase�a
    int flag = 1;  // Inicializa flag en 1 (contrase�as no coinciden)

    printf("------------------------------------------------------------------\n");
    printf("VERIFICAR CONTRASENA\n");
    printf("------------------------------------------------------------------\n");

    printf("Repetir contrasena: ");
    gets(aux);  // Lee la confirmaci�n de la contrase�a desde el usuario

    // Compara la contrase�a original con la confirmaci�n (case insensitive)
    if (stricmp(palabra, aux) == 0)
    {
        flag = 0;  // Si coinciden, cambia flag a 0 (contrase�as coinciden)
    }

    // Si flag sigue siendo 1, indica que las contrase�as no coinciden
    if (flag == 1)
    {
        printf("------------------------------------------------------------------\n");
        printf("LA CONTRASENA NO COINSIDE\n");
        printf("------------------------------------------------------------------\n");
    }
    else
    {
        printf("------------------------------------------------------------------\n");
        printf("VERIFICADO\n");
        printf("------------------------------------------------------------------\n");
    }

    return flag;  // Retorna flag, indicando si las contrase�as coinciden (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Dni(char dni[])
{
    int flag = 1;  // Inicializa flag en 1 (DNI inv�lido por defecto)
    int cantidad = strlen(dni);  // Obtiene la cantidad de caracteres del DNI ingresado

    // Verifica si la cantidad de caracteres del DNI es igual a 8
    if (cantidad == 8)
    {
        flag = 0;  // Cambia flag a 0 si la cantidad es correcta (DNI v�lido)
    }

    // Si flag sigue siendo 1, indica que el DNI no tiene la cantidad correcta de caracteres
    if (flag == 1)
    {
        printf("-DNI INEXISTENTE-\n");  // Muestra un mensaje de error indicando que el DNI es inv�lido
    }

    return flag;  // Retorna flag, indicando si el DNI es v�lido (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Telefono(char tele[])
{
    int flag = 1;  // Inicializa flag en 1 (Tel�fono inv�lido por defecto)
    int cantidad = strlen(tele);  // Obtiene la cantidad de caracteres del n�mero de tel�fono ingresado

    // Verifica si la cantidad de caracteres del tel�fono es mayor a 8
    if (cantidad > 8)
    {
        flag = 0;  // Cambia flag a 0 si la cantidad es mayor a 8 (Tel�fono v�lido)
    }

    // Si flag sigue siendo 1, indica que el tel�fono no cumple con la longitud m�nima
    if (flag == 1)
    {
        printf("-TELEFONO INEXISTENTE-\n");  // Muestra un mensaje de error indicando que el tel�fono es inv�lido
    }

    return flag;  // Retorna flag, indicando si el tel�fono es v�lido (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Mail(char mail[])
{
    int flag = 1;  // Inicializa flag en 1 (indicando que el mail no es v�lido por defecto)
    int caracteres = strlen(mail);  // Obtiene la cantidad de caracteres en la cadena mail[]

    // Itera sobre cada caracter de la cadena mail[]
    for (int i = 0; i < caracteres; i++)
    {
        if (mail[i] == 64)  // Verifica si el caracter actual es el '@' (c�digo ASCII)
        {
            flag = 0;  // Cambia flag a 0 (indicando que el mail es v�lido)
        }
    }

    // Si flag sigue siendo 1, significa que no se encontr� el caracter '@' en la cadena
    if (flag == 1)
    {
        printf("-EL MAIL NO ES VALIDO-\n");  // Muestra un mensaje de error
    }

    return flag;  // Retorna flag, indicando si el mail es v�lido (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Existencia_Persona(FILE *arch, char palabra[])
{
    int flag = 0;  // Inicializa flag en 0 (indicando que la persona no existe por defecto)
    usuario aux;   // Crea una variable auxiliar de tipo usuario para almacenar registros del archivo

    fseek(arch, 0, SEEK_SET);  // Posiciona el puntero al inicio del archivo

    // Itera sobre cada registro del archivo arch
    while (fread(&aux, sizeof(usuario), 1, arch) > 0)
    {
        // Compara el DNI del registro actual con la palabra ingresada
        if (strcmp(aux.dni, palabra) == 0)
        {
            flag = 1;  // Cambia flag a 1 si encuentra una coincidencia (indicando que la persona existe)
        }
    }

    // Si flag es 1, muestra un mensaje indicando que la persona ya tiene cuenta
    if (flag == 1)
    {
        printf("-LA PERSONA INGRESADA YA POSEE UNA CUENTA-\n");
    }

    return flag;  // Retorna flag, indicando si la persona existe (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int comprobar_Caracteres_Usuario(char palabra[])
{
    int flag = 1;  // Inicializa flag en 1 (indicando caracteres no v�lidos por defecto)
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter es una letra may�scula, min�scula o espacio
        if ((palabra[i] >= 65 && palabra[i] <= 90) || (palabra[i] >= 97 && palabra[i] <= 122) || palabra[i] == 32)
        {
            flag = 0;  // Cambia flag a 0 si encuentra un caracter v�lido
        }
        else
        {
            flag = 1;  // Si encuentra un caracter no v�lido, cambia flag a 1
            printf("-CARACTERES NO VALIDOS EN EL NOMBRE Y APELLIDO-\n");
            break;  // Sale del bucle for
        }
    }
    return flag;  // Retorna flag, indicando si hay caracteres no v�lidos (1) o todos son v�lidos (0)
}
// =================================================================================================
// =================================================================================================
int verificar_dos_o_mas_palabras(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena
    int minimo = 3;  // M�nimo n�mero de caracteres para considerar que hay dos palabras
    int flag = 1;  // Inicializa flag en 1 (indicando que no se han encontrado dos palabras por defecto)

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si hay un espacio (' ') y si se ha alcanzado el m�nimo de caracteres
        if (i >= minimo && palabra[i] == ' ')
        {
            // Itera sobre los caracteres despu�s del espacio para verificar si hay al menos 3 caracteres adicionales
            for (int u = i + 1; u < caracteres; u++)
            {
                if (u == i + minimo)
                {
                    flag = 0;  // Cambia flag a 0 si encuentra al menos dos palabras separadas por un espacio
                    break;  // Sale del bucle for
                }
            }
        }
    }

    // Si no se encontraron dos palabras, imprime un mensaje y cambia flag a 1
    if (flag == 1)
    {
        printf("-NO SE COMPLETO EL NOMBRE Y APELLIDO-\n");
    }

    return flag;  // Retorna flag, indicando si se encontraron dos palabras (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Anio(int anio)
{
    int flag = 0;      // Variable para indicar la validez del a�o (0: v�lido, 1: inv�lido)
    int limite = 2006; // L�mite m�nimo de a�o considerado v�lido
    int i = 0;         // Contador para contar el n�mero de d�gitos en el a�o
    int aux = anio;    // Variable auxiliar para almacenar el valor original de 'anio'

    // Calcula el n�mero de d�gitos en el a�o
    while (anio > 0)
    {
        anio = anio / 10;
        i++;
    }

    // Verifica si el a�o es mayor que el l�mite o si no tiene exactamente 4 d�gitos
    if (aux > limite || i != 4)
    {
        flag = 1;  // Cambia 'flag' a 1 si el a�o no cumple con los criterios de validez
    }

    return flag;  // Retorna 'flag' (0: v�lido, 1: inv�lido)
}
// =================================================================================================
// =================================================================================================
int verificar_Mes(int mes)
{
    int flag = 0;  // Variable para indicar la validez del mes (0: v�lido, 1: inv�lido)

    // Verifica si el mes est� fuera del rango v�lido (de 1 a 12)
    if (mes < 1 || mes > 12)
    {
        flag = 1;  // Cambia 'flag' a 1 si el mes est� fuera del rango v�lido
    }

    return flag;  // Retorna 'flag' (0: v�lido, 1: inv�lido)
}
// =================================================================================================
// =================================================================================================
int verificar_Dia(int dia, int mes)
{
    int flag = 0;  // Variable para indicar si el d�a es inv�lido (0: v�lido, 1: inv�lido)

    // Arreglos que contienen los meses con 30 y 31 d�as respectivamente
    int meses_31_dias[] = {1, 3, 5, 7, 8, 10, 12};
    int meses_30_dias[] = {4, 6, 9, 11};
    int febrero = 2;

    // Verifica si el mes tiene 30 d�as
    for (int i = 0; i < 4; i++)
    {
        if (mes == meses_30_dias[i])
        {
            if (dia > 30)
            {
                flag = 1;  // Cambia 'flag' a 1 si el d�a es mayor a 30 en un mes con 30 d�as
                break;
            }
        }
    }

    // Verifica si el mes tiene 31 d�as
    for (int i = 0; i < 7; i++)
    {
        if (mes == meses_31_dias[i])
        {
            if (dia > 31)
            {
                flag = 1;  // Cambia 'flag' a 1 si el d�a es mayor a 31 en un mes con 31 d�as
                break;
            }
        }
    }

    // Verifica febrero (mes 2) espec�ficamente para a�os bisiestos y no bisiestos
    if (mes == febrero)
    {
        if (dia > 29)
        {
            flag = 1;  // Cambia 'flag' a 1 si el d�a es mayor a 29 en febrero (posible a�o bisiesto)
        }
    }

    return flag;  // Retorna 'flag' (0: v�lido, 1: inv�lido)
}
// =================================================================================================
// =================================================================================================
int comprobar_Edad(int dia, int mes, int anio)
{
    int flag = 0;    // Variable para indicar si la fecha es inv�lida (0: v�lida, 1: inv�lida)
    int flag1 = 0;   // Variables para almacenar los resultados de las funciones de verificaci�n
    int flag2 = 0;
    int flag3 = 0;

    // Llama a las funciones de verificaci�n para el a�o, mes y d�a
    flag1 = verificar_Anio(anio);
    flag2 = verificar_Mes(mes);
    flag3 = verificar_Dia(dia, mes);

    // Si alguna de las verificaciones indica que la fecha es inv�lida, establece 'flag' en 1
    if (flag1 != 0 || flag2 != 0 || flag3 != 0)
    {
        flag = 1;
        printf ("-FECHA DE NACIMIENTO INVALIDA-\n");
    }

    return flag;  // Retorna 'flag' (0: fecha v�lida, 1: fecha inv�lida)
}
// =================================================================================================
// =================================================================================================
int verificar_Rol(char aux)
{
    int flag = 0;  // Variable para indicar si el rol es inv�lido (0: v�lido, 1: inv�lido)

    // Verifica si el car�cter 'aux' no es '0' ni '1'
    if (aux != '0' && aux != '1')
    {
        flag = 1;
        printf ("-ROL INVALIDO-\n");
    }

    return flag;  // Retorna 'flag' (0: rol v�lido, 1: rol inv�lido)
}
// =================================================================================================
// =================================================================================================
int verificar_Caracteres_Edad(char dia[], char mes[], char anio[])
{
    int flag = 0;    // Variable para indicar si hay caracteres inv�lidos (0: no hay, 1: hay)
    int flag1 = 1;   // Variables para almacenar el resultado de la verificaci�n de cada cadena
    int flag2 = 1;
    int flag3 = 1;

    flag1 = comprobar_Numeros_Edad(dia);   // Verifica si 'dia' contiene solo n�meros
    flag2 = comprobar_Numeros_Edad(mes);   // Verifica si 'mes' contiene solo n�meros
    flag3 = comprobar_Numeros_Edad(anio);  // Verifica si 'anio' contiene solo n�meros

    // Si alguno de los flag es 1, indica que hay caracteres inv�lidos
    if (flag1 == 1 || flag2 == 1 || flag3 == 1)
    {
        printf ("CARACTERES INVALIDOS\n");
        flag = 1;
    }

    return flag;  // Retorna 'flag' (0: caracteres v�lidos, 1: caracteres inv�lidos)
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros_Edad(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena
    int flag = 0;                      // Variable para indicar si hay caracteres no num�ricos (0: no hay, 1: hay)

    // Itera a trav�s de cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter no es un n�mero (fuera del rango 48 a 57 en ASCII)
        if (palabra[i] < 48 || palabra[i] > 57)
        {
            flag = 1;  // Si encuentra un caracter no num�rico, establece flag en 1
            break;     // Termina la iteraci�n, ya que no es necesario seguir verificando
        }
    }

    return flag;  // Retorna flag (0: caracteres num�ricos, 1: caracteres no num�ricos encontrados)
}
// =================================================================================================
// =================================================================================================
usuario pedir_Datos_Registro(FILE *arch, usuario persona) {
    int flag = 1;
    int flag2 = 1;
    int flag3 = 1;
    int flag4 = 1;

    // Bucle principal para validar todos los datos ingresados
    while (flag == 1) {
        flag2 = 1;
        flag3 = 1;
        flag4 = 1;

        // Validaci�n del nombre y apellido
        while (flag4 == 1 || flag3 == 1) {
            printf("------------------------------------------------------------------\n");
            printf("NOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(persona.nombre_Apellido);
            flag4 = comprobar_Caracteres_Usuario(persona.nombre_Apellido);
            flag3 = verificar_dos_o_mas_palabras(persona.nombre_Apellido);
        }

        flag3 = 1;

        // Validaci�n del DNI
        while (flag2 == 1 || flag3 == 1 || flag4 == 1) {
            printf("------------------------------------------------------------------\n");
            printf("DNI: ");
            fflush(stdin);
            gets(persona.dni);
            flag3 = verificar_Dni(persona.dni);
            flag4 = comprobar_Numeros_Dni(persona.dni);
            flag2 = verificar_Space(persona.dni);
        }

        // Verificar existencia del DNI en el archivo
        flag = verificar_Existencia_Persona(arch, persona.dni);
    }

    fseek(arch, 0, SEEK_END);
    flag2 = 1;
    flag4 = 1;
    flag3 = 1;

    // Validaci�n del tel�fono
    while (flag2 == 1 || flag4 == 1 || flag3 == 1) {
        printf("------------------------------------------------------------------\n");
        printf("TELEFONO: ");
        fflush(stdin);
        gets(persona.tele);
        flag3 = verificar_Telefono(persona.tele);
        flag4 = comprobar_Numeros_Dni(persona.tele);
        flag2 = verificar_Space(persona.tele);
    }

    flag = 1;
    flag2 = 1;

    // Validaci�n del correo electr�nico
    while (flag == 1 || flag2 == 1) {
        printf("------------------------------------------------------------------\n");
        printf("DIRECCION DE CORREO: ");
        fflush(stdin);
        gets(persona.email);
        flag = verificar_Mail(persona.email);
        flag2 = verificar_Space(persona.email);
    }

    flag = 1;

    // Validaci�n de la fecha de nacimiento
    while (flag == 1) {
        flag2 = 1;
        printf("------------------------------------------------------------------\n");
        printf("FECHA DE NACIMIENTO\n");
        printf ("XX/XX/XXXX\n");
        printf("------------------------------------------------------------------\n");
        while (flag2 == 1) {
            printf("Ingrese el dia de nacimiento: ");
            fflush(stdin);
            gets(persona.nacimiento.dia);
            printf("Ingrese el mes de nacimiento: ");
            fflush(stdin);
            gets(persona.nacimiento.mes);
            printf("Ingrese el a�o de nacimiento: ");
            fflush(stdin);
            gets(persona.nacimiento.anio);
            flag2 = verificar_Caracteres_Edad(persona.nacimiento.dia, persona.nacimiento.mes, persona.nacimiento.anio);
        }
        int diaE = atoi(persona.nacimiento.dia);
        int mesE = atoi(persona.nacimiento.mes);
        int anioE = atoi(persona.nacimiento.anio);
        flag = comprobar_Edad(diaE, mesE, anioE);
    }

    flag = 1;
    flag2 = 1;

    // Validaci�n del rol
    while (flag == 1) {
        char aux = '0';
        printf("------------------------------------------------------------------\n");
        printf("ROL (1 = vendedor ; 0 = Comprador)\n");
        printf("INGRESE AQUI: ");
        fflush(stdin);
        scanf(" %c", &aux);
        flag = verificar_Rol(aux);
        if (flag == 0) {
            if (aux == '0') {
                strcpy(persona.rol, "COMPRADOR");
            } else {
                strcpy(persona.rol, "VENDEDOR");
            }
        }
    }

    return persona;
}
// =================================================================================================
// =================================================================================================
