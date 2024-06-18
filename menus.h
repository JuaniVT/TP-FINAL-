#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
typedef struct
{
    char letras[4];
    char numeros[4];
} patente;

typedef struct
{
    patente patente;
    char marca[15];
    char modelo[20];
    char anio [5];
    char kms [9];
    usuario titular;
    char precioDeAdquisicion [9];
} autoS;

typedef struct
{
    Fecha fecha;
    patente autoAVender;
    float precioVenta;
    float ganancia;
    int dniComprador;
    int dniVendedor;

} ventaS;
void modificar_usuario (char []);
void mostrar_Archivo (char []);
void mostrarUsuario(usuario);
void mostrar_Datos_Usuario (char []);
void registro_auto_Sistema (char []);
autoS cargar_Auto (FILE*, autoS);
int comprobar_Caracteres_Patente (char []);
int comprobar_kms_Auto (char []);
int validar_Existencia_Auto (FILE*, char [], char []);
void recorrer_Array_Autos (char []);
void mostrarAuto(autoS);
void modificar_Auto (char []);
int verificar_Anio_Auto (int);
void mostrar_Datos_Auto (char []);
void registrar_Venta (char [], char [], char []);
int buscar_Coincidencia_Patente (char [], char [], char []);
int comprobar_Edad_Venta (int, int, int);
#endif // MENUS_H_INCLUDED
