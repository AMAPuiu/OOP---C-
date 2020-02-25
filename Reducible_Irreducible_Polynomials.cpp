#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Monom
{
    int grad,coef;
public:
    Monom(){grad=coef=0;}
    Monom(const int g, const int c){grad=g;coef=c;}
    Monom(const Monom &m){grad=m.grad;coef=m.coef;}
    ~Monom(){grad=coef=0;}
    Monom& operator=(const Monom& m);
    friend istream& operator>>(istream &in, Monom &m);
    friend ostream& operator<<(ostream &out, Monom &m);
    int get_coef();
};
class Polinom_ireductibil;
class Polinom
{
    int nr;
    Monom *m;
public:
    Polinom();
    Polinom(int n,const Monom *mi);
    Polinom(const Polinom &p);
    ~Polinom();
    Polinom& operator=(const Polinom& p);
    friend istream& operator>>(istream &in, Polinom &p);
    friend ostream& operator<<(ostream &out, Polinom &p);
    virtual bool eisenstein();
    Polinom_ireductibil* ired();
};
class Polinom_ireductibil:public Polinom
{
public:
    Polinom_ireductibil():Polinom(){};
    Polinom_ireductibil(int n,const Monom *mi):Polinom(n,mi){};
    bool eisenstein(){return true;};
    Polinom_ireductibil& operator=(const Polinom_ireductibil&p);

};
int Monom::get_coef()
{
    return coef;
}
Monom& Monom::operator=(const Monom& m)
{
    if(this!=&m)
    {
        grad=m.grad;
        coef=m.coef;
    }
    return *this;
}
Polinom::Polinom():m()
{
    nr=1;
    m=new Monom[1];

}
Polinom::Polinom(int n,const Monom *mi)
{
    nr=n;
    m=new Monom[n+1];
    for(int i=0;i<nr;i++)
        m[i]=mi[i];
}
Polinom::Polinom(const Polinom &p)
{
    if(this!=&p)
    {
        nr=p.nr;
        //delete []m;
        m=new Monom [nr+1];
        for(int i=0;i<nr;i++)
            m[i]=p.m[i];
    }

}
Polinom::~Polinom()
{
    nr=0;
    delete[]m;
}
Polinom& Polinom::operator=(const Polinom& p)
{
    if(this!=&p)
    {nr=p.nr;
    for(int i=0;i<nr;i++)
        m[i]=p.m[i];
    }
    return *this;
}
istream& operator>>(istream &in, Monom &m)
{
    in>>m.grad>>m.coef;

    return in;
}
ostream& operator<<(ostream &out,Monom &m)
{
    out<<m.grad<<" "<<m.coef;
    return out;
}
istream& operator>>(istream &in, Polinom &p)
{
    in>>p.nr;
    delete[]p.m;
    p.m=new Monom[p.nr];
    for(int i=0;i<p.nr;i++)
        in>>p.m[i];

    return in;
}
ostream& operator<<(ostream &out,Polinom &p)
{
    out<<p.nr<<" ";
    for(int i=0;i<p.nr;i++)
        out<<p.m[i]<<" ";
    out<<"\n";

    if(p.eisenstein()==false)
    {
        int j,ok=0;
        for(j=-p.m[0].get_coef();j<=p.m[0].get_coef();j++)
        {
            if(j==0) continue;
            if(p.m[0].get_coef()%j==0)
            {
                double val_poz=0,x=1;
                for(int i=0;i<=p.nr-1;i++)
                {
                    val_poz+=p.m[i].get_coef()*x;
                    x=x*j;
                }
                if(val_poz==0)
                    {ok=1;break;}
            }
        }

        if(ok==1)
        {out<<2<<" "<<0<<" "<<-j<<" "<<1<<" "<<1<<" ";
        out<<p.nr-1<<" ";
        int x=p.m[p.nr-1].get_coef();
        int *v=new int[p.nr-1];
        for(int i=p.nr-1;i>0;i--)
        {
            v[i-1]=x;
            x=j*x+p.m[i-1].get_coef();
        }
        for(int i=0;i<p.nr-1;i++)
            out<<i<<" "<<v[i]<<" ";
        delete []v;}
    }

    return out;
}
bool Polinom::eisenstein()
{

    if(m[0].get_coef()==0)return false;
    int *viz,minim,p=0;

    minim=abs(m[0].get_coef());
    for(int i=1;i<nr-1;i++)
        if(abs(m[i].get_coef())<minim)
            minim=abs(m[i].get_coef());
    viz=new int[minim+1];
    for(int i=0;i<=minim;i++)
        viz[i]=1;
    for(int i=2;i<=minim;i++)
    {
        if(viz[i]==1)
        {
            for(int j=i+i;j<=minim;j=j+i)
                viz[j]=0;
        }
    }

    for(int i=1;i<=minim;i++)
    {
        if(viz[i]==1)
        {
            if(m[0].get_coef()%(i*i)!=0&&m[nr-1].get_coef()%i!=0)
            {
                int ok=1;
                for(int j=0;j<nr-1;j++)
                    if(m[j].get_coef()%i!=0)
                        ok=0;
                if(ok==1)
                {
                    p=i;
                    break;
                }
            }
        }
    }
    delete []viz;
    if(p==0)
        return false;
    return true;
}
Polinom_ireductibil* Polinom::ired()
{
    Polinom_ireductibil *p=new Polinom_ireductibil;
    if(eisenstein()==true)
    {
        p=(Polinom_ireductibil*)this;
        return p;
    }
    else return NULL;
}
Polinom_ireductibil& Polinom_ireductibil::operator=(const Polinom_ireductibil&p)
{
    if(this!=&p)
    {
        /*nr=p.nr;
    for(int i=0;i<nr;i++)
        m[i]=p.m[i];*/
        this->Polinom::operator=(p);
    }
    return *this;
}
int main()
{
    ifstream f("input.txt");
    ofstream g("output.txt");
    Polinom p;
    f>>p;
    g<<p;
    Polinom_ireductibil *q,r;
    q=p.ired();
    if(q!=NULL)
    cout<<(*q);
    else cout<<"NULL";


    return 0;
}
