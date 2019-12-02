#include <iostream>
using namespace std;
struct sarasas
{
int *elementas;
sarasas *desinys;
sarasas *kairys;
};
class dvikryptis
{
 private:
 sarasas *pradzia;
 sarasas *pabaiga;
 public:
     dvikryptis(){pradzia=NULL; pabaiga=NULL;};
     ~dvikryptis();
     sarasas *GetPradzia(){return pradzia;};
     sarasas *GetPabaiga(){return pabaiga;};
     void Ikelti(FILE*);
     void Spausdinti();
     void Tikrinti();
     void Prideti(sarasas *, int *);
     int Salinti(int);
     int Ieskoti(int);
};
dvikryptis::~dvikryptis()
{
    sarasas *kint=pradzia;
    while(pradzia!=NULL)
    {
      kint=pradzia;
      pradzia=pradzia->kairys;
      delete(kint->elementas);
      delete(kint);
    }

};
int main(){
FILE *d;
dvikryptis objektas;
d=fopen("skaiciai.txt", "r");
if(d==NULL)
{
    cout<<"Failas Nerastas"<<endl;
    exit(1);
}
objektas.Ikelti(d);
objektas.Spausdinti();
int a=3;
objektas.Spausdinti();
objektas.Salinti(a);

objektas.Spausdinti();
objektas.Ieskoti(45);
}
void dvikryptis::Ikelti(FILE *failas)
{
    sarasas *kint;
    if(!feof(failas))
        {
        pabaiga=new sarasas;
        pradzia=pabaiga;
        pradzia->elementas=new int;
        fscanf(failas, "%i",pradzia->elementas);
        pradzia->kairys=NULL;
        pradzia->desinys=NULL;
        }
    while(!feof(failas))
    {
        kint=new sarasas;
        kint->elementas=new int;
        fscanf(failas,"%i",kint->elementas);
        kint->kairys=NULL;
        kint->desinys=pradzia;
        pradzia->kairys=kint;
        pradzia=kint;
    }
}
void dvikryptis::Prideti(sarasas *kint, int *sk)
{
    sarasas *kint2;
    kint2=new sarasas;
    kint2->elementas=sk;
    if(kint==pradzia)
    {
        kint2->desinys=pradzia;
        kint2->kairys=NULL;
        pradzia->kairys=kint2;
        pradzia=kint2;
    }
    else
    {
        kint2->desinys=kint;
        kint2->kairys=kint->kairys;
        (kint->kairys)->desinys=kint2;
        kint->kairys=kint2;

    }
}
int dvikryptis::Salinti(int sk)
{
int pos(0);
        sarasas *kint=pabaiga;
    while(kint!=NULL)
    {
    if(*kint->elementas==sk)
    {
       if(kint==pradzia){pradzia=pradzia->desinys;if(pradzia!=NULL){pradzia->kairys=NULL;}}
       else if(kint==pabaiga){pabaiga=pabaiga->kairys;if(pabaiga!=NULL){pabaiga->desinys=NULL;}}
       else{kint->desinys->kairys=kint->kairys;kint->kairys->desinys=kint->desinys;}
    }
    kint=kint->kairys;
}
}
int dvikryptis::Ieskoti(int sk)
{
    sarasas *kint=pabaiga;
    int pos=0,flag=0,value;
    while(kint!=NULL)
    {
        pos++;
        if(*kint->elementas==sk)
        {
        flag=1;
        pos--;

        break;

    }
    kint=kint->kairys;
      }
    if(flag==1)
    {
        cout<<endl;
        cout<<"Elementas rastas pozicijoje:"<<pos<<endl;
    }
    else
        {
        cout<<"Elementas nerastas."<<endl;
        }
}
void dvikryptis::Spausdinti()
{
    sarasas *kint=pabaiga;
    while(kint!=NULL)
    {
        cout<<*kint->elementas<<" ";
        kint=kint->kairys;
    }
    cout<<endl;
}


