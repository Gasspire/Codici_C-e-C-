/*In questo file vanno solo le dichiarazioni delle funzioni e della classe!*/
class User
{
private:
    int age;
    char *name;
    char *surname;
    char *roleuser;
public:
    User(int costructor_age,const char *costructor_name,const char *costructor_surname, const char *costructor_roleuser);
    char* getname();
    int getage();
    char* getsurname();
    char* getroleuser();
    ~User();
};