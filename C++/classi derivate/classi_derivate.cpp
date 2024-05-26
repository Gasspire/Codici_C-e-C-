#include <iostream>
#include <cstring>
using namespace std;

class oggetto_geometrico{
    protected: //in modo che possa  essere visualizzato dalle sue sottoclassi, se fosse private risulterebbe inaccessibile e dunque non sarebbe possibile visualizzarlo
        float xC,yC;
    public:
        oggetto_geometrico(float x=0, float y=0) : xC(x),yC(y){}
        void printcentro(){cout<<"il centro e' : "<<xC<<" "<<yC<<endl;}

};
class cerchio : public oggetto_geometrico{
    private:
        float raggio;
    public: 
        cerchio(float costructor_raggio, float x_C,float y_C) : oggetto_geometrico(x_C,y_C){raggio = costructor_raggio;}
        float area(){return (raggio*raggio)*3.1415;}
};

class quadrato : public oggetto_geometrico{
    private: 
        float x1,y1;
    public: 
        quadrato(float costructor_x, float costructor_y,float x_C,float y_C) : oggetto_geometrico(x_C,y_C){
            x1 = costructor_x; //coordinata x del punto del lato;
            y1 = costructor_y; //coordinata y del punto del lato;
        }
        float area(){
            float a = x1 - xC;
            float b = y1 - yC;
            return 4*a*b;
        }
};


int main(){
    cerchio cerchiodestaceppa(1.4,0,0);
    cerchiodestaceppa.printcentro();
    cout<<"l'area del cerchio e' : "<<cerchiodestaceppa.area()<<endl;
    quadrato quadratosexy(3.10,4.2,0,0);
    quadratosexy.printcentro();
    cout<<"L'area del quadrato e' : "<<quadratosexy.area()<<endl;

}