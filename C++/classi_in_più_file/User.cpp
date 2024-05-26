/*In questo file vanno tutte le istruzioni delle funzioni*/
#include <cstring>
#include "User.h"

User::User(int costructor_age,const char *costructor_name,const char *costructor_surname, const char *costructor_roleuser)
{
    age = costructor_age;
    int len = strlen(costructor_name)+1;
    name = new char[len];
    strncpy(name,costructor_name,len);
    name[len-1] = '\0' ;        
    len = strlen(costructor_surname)+1;
    surname = new char[len];
    strncpy(surname,costructor_surname,len);
    surname[len-1] = '\0' ;
    len = strlen(costructor_roleuser)+1;
    roleuser = new char[len];
    strncpy(roleuser,costructor_roleuser,len);
    roleuser[len-1] = '\0' ;
}
User::~User(){
    delete[] name;
    delete[] surname;
    delete[] roleuser;
    name = 0;
    surname = 0;
    roleuser = 0;
}

char* User::getname(){ return name;}
int User::getage(){return age;}
char* User::getsurname(){ return surname;}
char* User::getroleuser(){ return roleuser;}