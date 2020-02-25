#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Farmacie
{
public:
    virtual void citire(istream &in)=0;
    virtual void afisare(ostream &out)=0;
};
class Farmacie_offline:public Farmacie
{
    static int nr_farmacii;
    string denumire;
    int nr_angajati;
    int *profit;
    int nr_luni;
public:
    Farmacie_offline();
    Farmacie_offline(string nume,int nr, int *p, int s);
    Farmacie_offline(const Farmacie_offline& p);
    ~Farmacie_offline();
    Farmacie_offline& operator=(const Farmacie_offline & p);
    friend istream& operator>>(istream &in, Farmacie_offline &p);
    friend ostream& operator<<(ostream &out, Farmacie_offline &p);
    void citire(istream &in);
    void afisare(ostream &out);
    int get_nr_luni()const {return nr_luni;};
    static int get_nr_farmacii(){return nr_farmacii;};
};
int Farmacie_offline::nr_farmacii=0;
class Farmacie_online:public Farmacie
{
    static int nr_farmacii;
    string adresa;
    int vizitatori;
    double discount;
public:
    Farmacie_online();
    Farmacie_online(string adresa,int nr, double d);
    Farmacie_online(const Farmacie_online& p);
    ~Farmacie_online();
    Farmacie_online& operator=(const Farmacie_online & p);
    friend istream& operator>>(istream &in, Farmacie_online &p);
    friend ostream& operator<<(ostream &out, Farmacie_online &p);
    void citire(istream &in);
    void afisare(ostream &out);
    int get_vizitatori()const {return vizitatori;};
    static int get_nr_farmacii(){return nr_farmacii;};
};
int Farmacie_online::nr_farmacii=0;
template <class T> class GestionareFarmacii
{
   int index;
   static const int ID;
   T *f;
public:
    GestionareFarmacii();
    GestionareFarmacii(int id, T* farm, int nr);
    GestionareFarmacii(const GestionareFarmacii <T> &p);
    ~GestionareFarmacii();
    GestionareFarmacii& operator=(const GestionareFarmacii <T> &p);
    template<class T1>friend istream& operator>>(istream &in, GestionareFarmacii <T1> &p);
    template<class T1>friend ostream& operator<<(ostream &out, GestionareFarmacii <T1> &p);
    GestionareFarmacii& operator+=(const T &farm);
};
template<typename T> const int GestionareFarmacii<T>::ID = 0;
template<>class GestionareFarmacii<unsigned>
{
    unsigned int vizitatori;
public:
    void afisare(ostream &out,Farmacie_online *p)
    { int x=p[0].get_nr_farmacii();
        for(int i=0;i<x;i++)
            vizitatori+=p[i].get_vizitatori();
        out<<vizitatori;
    }
    GestionareFarmacii(){vizitatori=0;};

};

Farmacie_offline::Farmacie_offline()
{
    denumire="";
    nr_angajati=0;
    nr_farmacii++;
}
Farmacie_offline::Farmacie_offline(string nume,int nr, int *p,int s)
{ nr_farmacii++;
    denumire=nume;
    nr_angajati=nr;
    try
    {
        profit=new int[s];
    }
    catch(bad_alloc N)
    {
       cout << "Allocation Failure\n";
       profit=NULL;
       //return;
       exit(10);
    }
    for(int i=0;i<s;i++)
        profit[i]=p[i];
    nr_luni=s;
}
Farmacie_offline::Farmacie_offline(const Farmacie_offline& p)
{nr_farmacii++;
    denumire=p.denumire;
    nr_angajati=p.nr_angajati;
    try
    {
        profit=new int[p.nr_luni];
    }
    catch(bad_alloc N)
    {
       cout << "Allocation Failure\n";
       profit=NULL;
       return;
    }
    for(int i=0;i<p.nr_luni;i++)
        profit[i]=p.profit[i];
    nr_luni=p.nr_luni;
}
Farmacie_offline:: ~Farmacie_offline()
{
    denumire="";
    nr_angajati=0;
    nr_luni=0;
    delete []profit;
    nr_farmacii--;
}
Farmacie_offline& Farmacie_offline:: operator=(const Farmacie_offline & p)
{
    if(this!=&p)
    {
        denumire=p.denumire;
        nr_angajati=p.nr_angajati;
        nr_luni=p.nr_luni;
        delete []profit;
        try
    {
        profit=new int[p.nr_luni];
    }
    catch(bad_alloc N)
    {
       cout << "Allocation Failure\n";
       profit=NULL;
       return *this;
    }
    for(int i=0;i<p.nr_luni;i++)
        profit[i]=p.profit[i];
    }
      return *this;
}
void Farmacie_offline::citire(istream &in)
{
    in>>denumire;
    in>>nr_angajati;
    in>>nr_luni;
    delete []profit;
    try
    {
        profit=new int[nr_luni];
    }
    catch(bad_alloc N)
    {
       cout << "Allocation Failure\n";
       profit=NULL;
       return;
    }
    for(int i=0;i<nr_luni;i++)
        in>>profit[i];
}
void Farmacie_offline::afisare(ostream &out)
{
    out<<"Denumire: "<<denumire<<"\n";
    out<<"Angajati: "<<nr_angajati<<"\n";
    out<<"Luni"<<nr_luni<<"\n";
    out<<"Profit";
    for(int i=0;i<nr_luni;i++)
        out<<profit[i]<<" ";
        out<<"\n";
}
istream& operator>>(istream &in, Farmacie_offline &p)
{
    p.citire(in);
    return in;
}
ostream& operator<<(ostream &out, Farmacie_offline &p)
{
    p.afisare(out);
    return out;
}
Farmacie_online::Farmacie_online()
{ nr_farmacii++;
    adresa="";
    vizitatori=0;
    discount=0;
}
Farmacie_online::Farmacie_online(string a,int nr,double d)
{ nr_farmacii++;
    adresa=a;
    vizitatori=nr;
    discount=d;
}
Farmacie_online::Farmacie_online(const Farmacie_online& p)
{nr_farmacii++;
    adresa=p.adresa;
    vizitatori=p.vizitatori;
    discount=p.discount;
}
Farmacie_online:: ~Farmacie_online()
{nr_farmacii--;;
    adresa="";
    vizitatori=0;
    discount=0;
}
Farmacie_online& Farmacie_online:: operator=(const Farmacie_online & p)
{
    if(this!=&p)
    {
        adresa=p.adresa;
        vizitatori=p.vizitatori;
        discount=p.discount;
    }
    return *this;
}
void Farmacie_online::citire(istream &in)
{
    in>>adresa;
    in>>vizitatori;
    in>>discount;
}
void Farmacie_online::afisare(ostream &out)
{
    out<<"Adresa: "<<adresa<<"\n";
    out<<"Vizitatori: "<<vizitatori<<"\n";
    out<<"Discount: "<<discount<<"\n";
}
istream& operator>>(istream &in, Farmacie_online &p)
{
    p.citire(in);
    return in;
}
ostream& operator<<(ostream &out, Farmacie_online &p)
{
    p.afisare(out);
    return out;
}
template<class T>GestionareFarmacii<T>::GestionareFarmacii()
{
    index=0;
    //ID=0;
    f=new T[1];
}
template<class T>GestionareFarmacii<T>::GestionareFarmacii(int id, T* farm, int nr)
{
    index=nr;
    //ID=0;
    f=new T[nr];
    for(int i=0;i<nr;i++)
        f[i]=farm[i];
}
template<class T>GestionareFarmacii<T>::GestionareFarmacii(const GestionareFarmacii <T> &p)
{
    index=p.index;
    f=new T[index];
    //ID=0;
    for(int i=0;i<index;i++)
        f[i]=p.f[i];
}
template<class T>GestionareFarmacii<T>::~GestionareFarmacii()
{
    index=0;
    delete []f;
}
template<class T>GestionareFarmacii<T>& GestionareFarmacii<T>::operator=(const GestionareFarmacii <T> &p)
{
    if(this!=&p)
    {
        index=p.index;
        delete[]f;
        f=new T[index];
        for(int i=0;i<index;i++)
            f[i]=p.f[i];
    }
    return *this;
}
template<class T>istream& operator>>(istream &in, GestionareFarmacii <T> &p)
{
    in>>p.index;
    delete []p.f;
    p.f=new T[p.index];
    for(int i=0;i<p.index;i++)
        in>>p.f[i];
    return in;
}
template<class T>ostream& operator<<(ostream &out, GestionareFarmacii <T> &p)
{
    out<<"Index:"<<p.index<<"\n";
    out<<"Farmacii:";
    out<<"\n";
    for(int i=0;i<p.index;i++)
        out<<p.f[i]<<" ";
        out<<"\n";
    return out;
}
template<class T>GestionareFarmacii<T>& GestionareFarmacii<T>::operator+=(const T &farm)
{
    T *temp=new T[index];
    for(int i=0;i<index;i++)
        temp[i]=f[i];
    index++;
    delete[]f;
    f=new T[index];
    for(int i=0;i<index-1;i++)
        f[i]=temp[i];
    f[index-1]=farm;
    return *this;
}


int main()
{
    ifstream f("input.txt");
    ofstream g("output.txt");

    Farmacie_offline q3,q4;
    Farmacie_online q1,q2;
    Farmacie *p;


    GestionareFarmacii<Farmacie_online> F;
    f>>q1;

    F+=q1;
    f>>q2;
    F+=q2;
    g<<F<<"\n";
    GestionareFarmacii<Farmacie_offline> G;
    f>>q3;
    G+=q3;
    f>>q4;
    G+=q4;
    g<<G;
    //GestionareFarmacii<unsigned> H;

    return 0;
}
