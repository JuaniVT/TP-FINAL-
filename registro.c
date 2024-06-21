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
    // Esta función registra un nuevo usuario en un archivo binario.
    // Abre el archivo en modo añadir y leer binario.
    // Llama a la función crear_Cuenta para obtener los datos del usuario.
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
    // Esta función crea una cuenta de usuario.
    // Utiliza otras funciones para solicitar y registrar datos específicos del usuario,
    // como nombre de usuario y contraseña, utilizando el archivo proporcionado.

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
    // Esta función permite al usuario crear y validar un nombre de usuario.
    // Proporciona instrucciones sobre los requisitos del nombre de usuario,
    // y verifica la disponibilidad del nombre ingresado utilizando comprobar_Usuario.

    int variableUser = 1;
    while (variableUser != 0)
    {
        printf("------------------------------------------------------------------\n");
        printf("CREE SU NOMBRE DE USUARIO\n");
        printf("------------------------------------------------------------------\n");
        printf("Requisitos:\n");
        printf("Debe tener mínimo 8 caracteres\n");
        printf("NO debe contener mayúsculas\n");
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
    // Esta función permite al usuario crear y validar una contraseña.
    // Proporciona instrucciones sobre los requisitos de la contraseña,
    // y verifica la validez de la contraseña ingresada utilizando comprobar_Contra y verificar_Contrasena.

    int variableContra = 1;

    while (variableContra != 0)
    {
        printf("------------------------------------------------------------------\n");
        printf("CREE UNA CONTRASEÑA\n");
        printf("------------------------------------------------------------------\n");
        printf("Requisitos:\n");
        printf("Debe contener al menos una mayúscula\n");
        printf("Debe tener mínimo 8 caracteres\n");
        printf("Debe contener al menos un número\n");
        printf("NO debe contener espacios\n");
        printf("------------------------------------------------------------------\n");
        printf("INGRESE AQUI: ");
        fflush(stdin);
        gets((*persona).contra);
        printf("------------------------------------------------------------------\n");

        // Verifica la validez de la contraseña utilizando comprobar_Contra
        variableContra = comprobar_Contra(arch, (*persona).contra);

        // Si la contraseña pasa la primera validación, verifica requisitos adicionales usando verificar_Contrasena
        if (variableContra == 0)
        {
            variableContra = verificar_Contrasena((*persona).contra);
        }

        if (variableContra != 0)
        {
            printf("------------------------------------------------------------------\n");
            printf("REESCRIBA LA CONTRASEÑA\n");
            printf("------------------------------------------------------------------\n");
        }
    }
}
// =================================================================================================
// =================================================================================================
int comprobar_Usuario(FILE *arch, char palabra[])
{
    // Esta función verifica la validez de un nombre de usuario.
    // Realiza múltiples comprobaciones utilizando funciones auxiliares para asegurar que el nombre de usuario cumple con los requisitos establecidos.

    int minUser = 8;
    int flag = 0;   // Flag para verificar caracteres y longitud mínima
    int flag2 = 0;  // Flag para verificar presencia de mayúsculas
    int flag3 = 0;  // Flag para verificar espacios en blanco
    int flag4 = 0;  // Flag para verificar presencia de minúsculas
    int flag6 = 0;  // Flag adicional, parece no estar siendo utilizado
    int flag7 = 0;  // Flag para verificar existencia del usuario en el archivo

    // Realiza las verificaciones necesarias utilizando funciones auxiliares
    flag = verificar_Caracteres(palabra, minUser);
    flag7 = verificar_Existencia(arch, palabra);
    flag3 = verificar_Space(palabra);
    flag2 = comprobar_Mayusculas_User(palabra);
    flag4 = verificar_minusculas(palabra);

    // Si alguna de las comprobaciones devuelve un resultado no válido, establece flag a 1 (indicando fallo)
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
    // Define la longitud mínima requerida para la contraseña
    int minContra = 8;

    // Variables para almacenar los resultados de las verificaciones
    int flag = 0;    // Indicador general de validez de la contraseña
    int flag2 = 0;   // Verifica la presencia de al menos una mayúscula
    int flag3 = 0;   // Verifica que no haya espacios en blanco
    int flag4 = 0;   // Verifica la presencia de al menos una minúscula
    int flag5 = 0;   // Verifica la presencia de al menos un número

    // Verifica la longitud mínima y otros caracteres de la contraseña
    flag = verificar_Caracteres(palabra, minContra);

    // Verifica si hay espacios en blanco en la contraseña
    flag3 = verificar_Space(palabra);

    // Verifica si hay al menos una mayúscula en la contraseña
    flag2 = comprobar_Mayusculas(palabra);

    // Verifica si hay al menos una minúscula en la contraseña
    flag4 = verificar_minusculas(palabra);

    // Verifica si hay al menos un número en la contraseña
    flag5 = comprobar_Numeros(palabra);

    // Si alguna de las verificaciones falla, establece flag a 1
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag5 != 0)
    {
        flag = 1;
    }

    // Retorna flag, que indica si la contraseña es válida (0) o inválida (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Mayusculas(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay mayúsculas)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual está en el rango de letras mayúsculas ASCII (65-90)
        if (palabra[i] >= 65 && palabra[i] <= 90)
        {
            // Si encuentra al menos una mayúscula, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron mayúsculas
    if (flag == 1)
    {
        printf("-NO CONTIENE MAYUSCULA-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos una mayúscula (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int verificar_minusculas(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay minúsculas)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual está en el rango de letras minúsculas ASCII (97-122)
        if (palabra[i] >= 97 && palabra[i] <= 122)
        {
            // Si encuentra al menos una minúscula, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron minúsculas
    if (flag == 1)
    {
        printf("-NO CONTIENE MINUSCULA-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos una minúscula (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 1 (asume inicialmente que no hay números)
    int flag = 1;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual está en el rango de dígitos ASCII (48-57)
        if (palabra[i] >= 48 && palabra[i] <= 57)
        {
            // Si encuentra al menos un número, cambia flag a 0 y sale del bucle
            flag = 0;
            break;
        }
    }

    // Si flag sigue siendo 1 al final del recorrido, significa que no se encontraron números
    if (flag == 1)
    {
        printf("-NO CONTIENE NUMEROS-\n");
    }

    // Retorna flag, que indica si la cadena contiene al menos un número (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros_Dni(char palabra[])
{
    // Obtiene la cantidad de caracteres en la cadena
    int caracteres = strlen(palabra);

    // Inicializa flag en 0 (asume inicialmente que todos los caracteres son válidos)
    int flag = 0;

    // Recorre la cadena caracter por caracter
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter actual no está en el rango válido de dígitos (48-57 en ASCII)
        if (palabra[i] < 48 || palabra[i] > 57)
        {
            // Si encuentra algún caracter fuera del rango, cambia flag a 1 y sale del bucle
            flag = 1;
            break;
        }
    }

    // Si flag es 1, significa que se encontraron caracteres inválidos
    if (flag == 1)
    {
        printf("-CARACTERES INVALIDOS-\n");
    }

    // Retorna flag, que indica si la cadena contiene caracteres inválidos (1) o no (0)
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

    // Verifica si la cantidad de caracteres es mayor o igual al mínimo requerido
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

    // Retorna flag, que indica si la cadena cumple con el mínimo de caracteres (0) o no (1)
    return flag;
}
// =================================================================================================
// =================================================================================================
int verificar_Existencia(FILE *arch, char palabra[])
{
    int flag = 0;          // Inicializa flag en 0 (no existe el usuario)
    usuario aux;           // Variable auxiliar para almacenar cada usuario leído

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
        // Comprueba si el caracter actual es un espacio (código ASCII 32)
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
    int flag = 0;  // Inicializa flag en 0 (no contiene mayúsculas)

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Comprueba si el caracter actual es una letra mayúscula (códigos ASCII entre 65 y 90)
        if (palabra[i] >= 'A' && palabra[i] <= 'Z')
        {
            flag = 1;  // Si encuentra una mayúscula, cambia flag a 1
            break;     // Termina el bucle, ya que no es necesario seguir buscando
        }
    }

    // Si flag es 1, significa que la cadena contiene al menos una mayúscula
    if (flag == 1)
    {
        printf("-CONTIENE MAYUSCULA-\n");  // Imprime un mensaje indicando que la cadena contiene mayúsculas
    }

    return flag;  // Retorna flag, indicando si la cadena contiene mayúsculas (1) o no (0)
}
// =================================================================================================
// =================================================================================================
int verificar_Contrasena(char palabra[])
{
    char aux[20];  // Variable auxiliar para almacenar la confirmación de la contraseña
    int flag = 1;  // Inicializa flag en 1 (contraseñas no coinciden)

    printf("------------------------------------------------------------------\n");
    printf("VERIFICAR CONTRASENA\n");
    printf("------------------------------------------------------------------\n");

    printf("Repetir contrasena: ");
    gets(aux);  // Lee la confirmación de la contraseña desde el usuario

    // Compara la contraseña original con la confirmación (case insensitive)
    if (stricmp(palabra, aux) == 0)
    {
        flag = 0;  // Si coinciden, cambia flag a 0 (contraseñas coinciden)
    }

    // Si flag sigue siendo 1, indica que las contraseñas no coinciden
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

    return flag;  // Retorna flag, indicando si las contraseñas coinciden (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Dni(char dni[])
{
    int flag = 1;  // Inicializa flag en 1 (DNI inválido por defecto)
    int cantidad = strlen(dni);  // Obtiene la cantidad de caracteres del DNI ingresado

    // Verifica si la cantidad de caracteres del DNI es igual a 8
    if (cantidad == 8)
    {
        flag = 0;  // Cambia flag a 0 si la cantidad es correcta (DNI válido)
    }

    // Si flag sigue siendo 1, indica que el DNI no tiene la cantidad correcta de caracteres
    if (flag == 1)
    {
        printf("-DNI INEXISTENTE-\n");  // Muestra un mensaje de error indicando que el DNI es inválido
    }

    return flag;  // Retorna flag, indicando si el DNI es válido (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Telefono(char tele[])
{
    int flag = 1;  // Inicializa flag en 1 (Teléfono inválido por defecto)
    int cantidad = strlen(tele);  // Obtiene la cantidad de caracteres del número de teléfono ingresado

    // Verifica si la cantidad de caracteres del teléfono es mayor a 8
    if (cantidad > 8)
    {
        flag = 0;  // Cambia flag a 0 si la cantidad es mayor a 8 (Teléfono válido)
    }

    // Si flag sigue siendo 1, indica que el teléfono no cumple con la longitud mínima
    if (flag == 1)
    {
        printf("-TELEFONO INEXISTENTE-\n");  // Muestra un mensaje de error indicando que el teléfono es inválido
    }

    return flag;  // Retorna flag, indicando si el teléfono es válido (0) o no (1)
}
// =================================================================================================
// =================================================================================================
int verificar_Mail(char mail[])
{
    int flag = 1;  // Inicializa flag en 1 (indicando que el mail no es válido por defecto)
    int caracteres = strlen(mail);  // Obtiene la cantidad de caracteres en la cadena mail[]

    // Itera sobre cada caracter de la cadena mail[]
    for (int i = 0; i < caracteres; i++)
    {
        if (mail[i] == 64)  // Verifica si el caracter actual es el '@' (código ASCII)
        {
            flag = 0;  // Cambia flag a 0 (indicando que el mail es válido)
        }
    }

    // Si flag sigue siendo 1, significa que no se encontró el caracter '@' en la cadena
    if (flag == 1)
    {
        printf("-EL MAIL NO ES VALIDO-\n");  // Muestra un mensaje de error
    }

    return flag;  // Retorna flag, indicando si el mail es válido (0) o no (1)
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
    int flag = 1;  // Inicializa flag en 1 (indicando caracteres no válidos por defecto)
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter es una letra mayúscula, minúscula o espacio
        if ((palabra[i] >= 65 && palabra[i] <= 90) || (palabra[i] >= 97 && palabra[i] <= 122) || palabra[i] == 32)
        {
            flag = 0;  // Cambia flag a 0 si encuentra un caracter válido
        }
        else
        {
            flag = 1;  // Si encuentra un caracter no válido, cambia flag a 1
            printf("-CARACTERES NO VALIDOS EN EL NOMBRE Y APELLIDO-\n");
            break;  // Sale del bucle for
        }
    }
    return flag;  // Retorna flag, indicando si hay caracteres no válidos (1) o todos son válidos (0)
}
// =================================================================================================
// =================================================================================================
int verificar_dos_o_mas_palabras(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena
    int minimo = 3;  // Mínimo número de caracteres para considerar que hay dos palabras
    int flag = 1;  // Inicializa flag en 1 (indicando que no se han encontrado dos palabras por defecto)

    // Itera sobre cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si hay un espacio (' ') y si se ha alcanzado el mínimo de caracteres
        if (i >= minimo && palabra[i] == ' ')
        {
            // Itera sobre los caracteres después del espacio para verificar si hay al menos 3 caracteres adicionales
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
    int flag = 0;      // Variable para indicar la validez del año (0: válido, 1: inválido)
    int limite = 2006; // Límite mínimo de año considerado válido
    int i = 0;         // Contador para contar el número de dígitos en el año
    int aux = anio;    // Variable auxiliar para almacenar el valor original de 'anio'

    // Calcula el número de dígitos en el año
    while (anio > 0)
    {
        anio = anio / 10;
        i++;
    }

    // Verifica si el año es mayor que el límite o si no tiene exactamente 4 dígitos
    if (aux > limite || i != 4)
    {
        flag = 1;  // Cambia 'flag' a 1 si el año no cumple con los criterios de validez
    }

    return flag;  // Retorna 'flag' (0: válido, 1: inválido)
}
// =================================================================================================
// =================================================================================================
int verificar_Mes(int mes)
{
    int flag = 0;  // Variable para indicar la validez del mes (0: válido, 1: inválido)

    // Verifica si el mes está fuera del rango válido (de 1 a 12)
    if (mes < 1 || mes > 12)
    {
        flag = 1;  // Cambia 'flag' a 1 si el mes está fuera del rango válido
    }

    return flag;  // Retorna 'flag' (0: válido, 1: inválido)
}
// =================================================================================================
// =================================================================================================
int verificar_Dia(int dia, int mes)
{
    int flag = 0;  // Variable para indicar si el día es inválido (0: válido, 1: inválido)

    // Arreglos que contienen los meses con 30 y 31 días respectivamente
    int meses_31_dias[] = {1, 3, 5, 7, 8, 10, 12};
    int meses_30_dias[] = {4, 6, 9, 11};
    int febrero = 2;

    // Verifica si el mes tiene 30 días
    for (int i = 0; i < 4; i++)
    {
        if (mes == meses_30_dias[i])
        {
            if (dia > 30)
            {
                flag = 1;  // Cambia 'flag' a 1 si el día es mayor a 30 en un mes con 30 días
                break;
            }
        }
    }

    // Verifica si el mes tiene 31 días
    for (int i = 0; i < 7; i++)
    {
        if (mes == meses_31_dias[i])
        {
            if (dia > 31)
            {
                flag = 1;  // Cambia 'flag' a 1 si el día es mayor a 31 en un mes con 31 días
                break;
            }
        }
    }

    // Verifica febrero (mes 2) específicamente para años bisiestos y no bisiestos
    if (mes == febrero)
    {
        if (dia > 29)
        {
            flag = 1;  // Cambia 'flag' a 1 si el día es mayor a 29 en febrero (posible año bisiesto)
        }
    }

    return flag;  // Retorna 'flag' (0: válido, 1: inválido)
}
// =================================================================================================
// =================================================================================================
int comprobar_Edad(int dia, int mes, int anio)
{
    int flag = 0;    // Variable para indicar si la fecha es inválida (0: válida, 1: inválida)
    int flag1 = 0;   // Variables para almacenar los resultados de las funciones de verificación
    int flag2 = 0;
    int flag3 = 0;

    // Llama a las funciones de verificación para el año, mes y día
    flag1 = verificar_Anio(anio);
    flag2 = verificar_Mes(mes);
    flag3 = verificar_Dia(dia, mes);

    // Si alguna de las verificaciones indica que la fecha es inválida, establece 'flag' en 1
    if (flag1 != 0 || flag2 != 0 || flag3 != 0)
    {
        flag = 1;
        printf ("-FECHA DE NACIMIENTO INVALIDA-\n");
    }

    return flag;  // Retorna 'flag' (0: fecha válida, 1: fecha inválida)
}
// =================================================================================================
// =================================================================================================
int verificar_Rol(char aux)
{
    int flag = 0;  // Variable para indicar si el rol es inválido (0: válido, 1: inválido)

    // Verifica si el carácter 'aux' no es '0' ni '1'
    if (aux != '0' && aux != '1')
    {
        flag = 1;
        printf ("-ROL INVALIDO-\n");
    }

    return flag;  // Retorna 'flag' (0: rol válido, 1: rol inválido)
}
// =================================================================================================
// =================================================================================================
int verificar_Caracteres_Edad(char dia[], char mes[], char anio[])
{
    int flag = 0;    // Variable para indicar si hay caracteres inválidos (0: no hay, 1: hay)
    int flag1 = 1;   // Variables para almacenar el resultado de la verificación de cada cadena
    int flag2 = 1;
    int flag3 = 1;

    flag1 = comprobar_Numeros_Edad(dia);   // Verifica si 'dia' contiene solo números
    flag2 = comprobar_Numeros_Edad(mes);   // Verifica si 'mes' contiene solo números
    flag3 = comprobar_Numeros_Edad(anio);  // Verifica si 'anio' contiene solo números

    // Si alguno de los flag es 1, indica que hay caracteres inválidos
    if (flag1 == 1 || flag2 == 1 || flag3 == 1)
    {
        printf ("CARACTERES INVALIDOS\n");
        flag = 1;
    }

    return flag;  // Retorna 'flag' (0: caracteres válidos, 1: caracteres inválidos)
}
// =================================================================================================
// =================================================================================================
int comprobar_Numeros_Edad(char palabra[])
{
    int caracteres = strlen(palabra);  // Obtiene la cantidad de caracteres en la cadena
    int flag = 0;                      // Variable para indicar si hay caracteres no numéricos (0: no hay, 1: hay)

    // Itera a través de cada caracter de la cadena
    for (int i = 0; i < caracteres; i++)
    {
        // Verifica si el caracter no es un número (fuera del rango 48 a 57 en ASCII)
        if (palabra[i] < 48 || palabra[i] > 57)
        {
            flag = 1;  // Si encuentra un caracter no numérico, establece flag en 1
            break;     // Termina la iteración, ya que no es necesario seguir verificando
        }
    }

    return flag;  // Retorna flag (0: caracteres numéricos, 1: caracteres no numéricos encontrados)
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

        // Validación del nombre y apellido
        while (flag4 == 1 || flag3 == 1) {
            printf("------------------------------------------------------------------\n");
            printf("NOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(persona.nombre_Apellido);
            flag4 = comprobar_Caracteres_Usuario(persona.nombre_Apellido);
            flag3 = verificar_dos_o_mas_palabras(persona.nombre_Apellido);
        }

        flag3 = 1;

        // Validación del DNI
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

    // Validación del teléfono
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

    // Validación del correo electrónico
    while (flag == 1 || flag2 == 1) {
        printf("------------------------------------------------------------------\n");
        printf("DIRECCION DE CORREO: ");
        fflush(stdin);
        gets(persona.email);
        flag = verificar_Mail(persona.email);
        flag2 = verificar_Space(persona.email);
    }

    flag = 1;

    // Validación de la fecha de nacimiento
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
            printf("Ingrese el año de nacimiento: ");
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

    // Validación del rol
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
