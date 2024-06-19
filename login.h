#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
void login_Persona (char []);
int comprobar_Login (FILE *, char [], char [], usuario*);
int comprueba_Rol (usuario);
void menu_Vendedor (usuario);
void menu_Comprador (usuario);
#endif // LOGIN_H_INCLUDED
