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
    char precioVenta [9];
    char ganancia [10];
    char dniComprador [9];
    char dniVendedor [9];

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
void registrar_Venta_Arch (char [], char [], char []);
ventaS registrar_Venta (char [], char []);
int buscar_Coincidencia_Patente (char [], char [], char []);
int comprobar_Fecha_Venta (int, int, int);
void calcular_Ganancia_Venta (char [], ventaS*);
void mostrar_Ventas (char []);
void mostrar_Ventas_Arch_Completo (FILE*, ventaS, int);
void mostrar_Venta (ventaS);
int verificar_Existencia_Persona_Venta (char [], char [], char [], char [], char []);
void mostrar_VentaS_Completo (ventaS);
int calcular_Recaudacion (FILE *, char [], char []);
void mostrar_Recaudacion (char []);
void calcular_Venta_Mayor_Ganancia(char[]);
void mostrar_Autos_menos_10 (char []);
void recorrer_Array_Autos_Comprador (char []);
void mostrar_Auto_Comprador(autoS);
void abrir_Archivo_Ventas (char []);
int buscar_Vendedor (char [], char []);
#endif // MENUS_H_INCLUDED
