#include <iostream>
#include <fstream>
using namespace std;

class Polinom
{
    int n;
    double *v;
public:
    Polinom();
    Polinom(const int m, const double *w);
    Polinom(const Polinom &p);
    ~Polinom();
    Polinom operator=(const Polinom& q);
    friend istream& operator>>(istream& in, Polinom& p);
    friend ostream& operator<<(ostream& out, const Polinom& p);
    double value(const double a);
    Polinom operator+(Polinom q);
    Polinom operator-(Polinom q);
    Polinom operator*(Polinom q);
};
class Pereche
{
    double a;
    Polinom p;
    friend class Polinom;
public:
    int verif();
    friend istream& operator>>(istream& in, Pereche& q);
    friend ostream& operator<<(ostream& out, const Pereche& q);
};
Polinom::Polinom()
{
    v=new double[1];
    v[0]=0;
    n=0;
}
Polinom::Polinom(const int m, const double *w)
{
    //delete[]v;
    v=new double[m+1];

    for(int i=0;i<=m;i++)
        v[i]=w[i];
    n=m;
}
Polinom::Polinom(const Polinom &p)
{
    //delete[]v;
    n=p.n;
    v=new double[p.n+1];
    for(int i=0;i<=n;i++)
        v[i]=p.v[i];
}
Polinom::~Polinom()
{
    n=0;
    delete[]v;
}
Polinom Polinom::operator=(const Polinom &q)
{
    int same=1;
    if(n!=q.n)
        same=0;
    else for(int i=0;i<=n;i++)
            if(v[i]!=q.v[i])
                same=0;
    if(same==0)
    {
        delete[]v;
        v=new double[q.n+1];
        n=q.n;
        for(int i=0;i<=n;i++)
            v[i]=q.v[i];
    }

    return *this;
}
istream& operator>>(istream& in, Polinom& p)
{   double t;
    in>>p.n;
    delete[]p.v;
    p.v=new double[p.n+1];
    for(int i=0;i<=p.n;i++)
        {
            in>>t;
            p.v[i]=t;
        }
    return in;
}
ostream& operator<<(ostream& out,const Polinom& p)
{
    out<<p.n<<" ";
    for(int i=0;i<=p.n;i++)
        out<<p.v[i]<<" ";

    return out;
}
double Polinom::value(const double a)
{
    double val=0,x=1;
    for(int i=0;i<=n;i++)
    {
        val+=v[i]*x;
        x=x*a;
    }
    return val;
}
Polinom Polinom::operator+(Polinom q)
{
    double temp[max(n,q.n)+1];
    for(int i=0;i<=max(n,q.n);i++)
        temp[i]=0;
    for(int i=0;i<=min(n,q.n);i++)
        temp[i]=v[i]+q.v[i];
    for(int i=min(n,q.n)+1;i<=n;i++)
        temp[i]=v[i];
    for(int i=min(n,q.n)+1;i<=q.n;i++)
        temp[i]=q.v[i];
    int i=max(n,q.n);
    while(temp[i]==0)
        i--;
    int m=i;
    if(m==-1)
        m=0;
    Polinom s(m,temp);
    return s;
}
Polinom Polinom::operator-(Polinom q)
{

    double temp[max(n,q.n)+1];
    for(int i=0;i<=max(n,q.n);i++)
        temp[i]=0;
    for(int i=0;i<=min(n,q.n);i++)
        temp[i]=v[i]-q.v[i];
    for(int i=min(n,q.n)+1;i<=n;i++)
        temp[i]=v[i];
    for(int i=min(n,q.n)+1;i<=q.n;i++)
        temp[i]=q.v[i];
    int i=max(n,q.n);
    while(temp[i]==0)
        i--;
    int m=i;
    if(m==-1)
        m=0;
    Polinom d(m,temp);
    return d;
}
Polinom Polinom::operator*(Polinom q)
{
    double temp[n+q.n+1];
    int i;
    for(i=0;i<=n+q.n;i++)
        temp[i]=0;
    for(i=0;i<=q.n;i++)
        temp[i]=v[0]*q.v[i];
    for(i=1;i<=n;i++)
    {
        for(int j=0;j<=q.n;j++)
        {
            temp[i+j]+=v[i]*q.v[j];
        }
    }
    Polinom p(n+q.n,temp);

    return p;
}
int Pereche::verif()
{
    if(p.value(a)==0)
        return 1;
    else return 0;
}
istream& operator>>(istream& in, Pereche& q)
{
    in>>q.a;
    in>>q.p;
    return in;
}
ostream& operator<<(ostream& out, const Pereche& q)
{
    out<<q.a<<" ";
    out<<q.p;
    return out;
}
int main()
{
  ifstream f("in.txt");
  ofstream g("out.txt");
  int op;
  cout<<"MENIU:\n";
  cout<<"1.Valoare in punct\n";
  cout<<"2.Suma polinoame\n";
  cout<<"3.Diferenta polinoame\n";
  cout<<"4.Produs polinoame\n";
  cout<<"5. Verificare radacina\n";
  cout<<"6.EXIT\n";
  Polinom p,q,r,d,s;
  Pereche x;
  double a;
  int fisier=0;
  cout<<"Citire din fisier? 0-nu, 1-da\n";
  cin>>fisier;
  if(fisier==0)
  {cout<<"\nop=";
  cin>>op;
  cout<<"\n";
  while(op!=6)
  {
      switch(op)
      {
      case 1:
        //Polinom p;
        //double a;
        cout<<"Polinom:\n";
        cin>>p;
        cout<<"Valoare:\n";
        cin>>a;
        cout<<"Valoare in punct:\n";
        cout<<p.value(a)<<"\n";
        break;
      case 2:
        //Polinom p,q,s;
        cout<<"Polinom:\n";
        cin>>p;
        cout<<"Polinom:\n";
        cin>>q;
        s=p+q;
        cout<<"Suma:\n";
        cout<<s;
        cout<<"\n";
        break;
      case 3:
        //Polinom p,q,d;
        cout<<"Polinom:\n";
        cin>>p;
        cout<<"Polinom:\n";
        cin>>q;
        d=p-q;
        cout<<"Suma:\n";
        cout<<d;
        cout<<"\n";
        break;
      case 4:
        //Polinom p,q,d;
        cout<<"Polinom:\n";
        cin>>p;
        cout<<"Polinom:\n";
        cin>>q;
        d=p*q;
        cout<<"Produs:\n";
        cout<<d;
        cout<<"\n";
        break;
      case 5:
        //Pereche p;
        cout<<"Pereche:\n";
        cin>>x;
        if(x.verif()==0)
            cout<<"Nu e radacina\n";
        else cout<<"E radacina\n";
        break;
      default:
        cout<<"Nu exista optiunea\n";
      }
      cout<<"op=";
      cin>>op;
      cout<<"\n";
  }
  }
  else
  {
     f>>op;
     while(op!=6)
     {switch(op)
      {
      case 1:
        f>>p;
        f>>a;
        g<<p.value(a)<<"\n";
        break;
      case 2:
        f>>p;
        f>>q;
        s=p+q;
        g<<s<<"\n";
        break;
      case 3:
        f>>p;
        f>>q;
        d=p-q;
        g<<d<<"\n";
        break;
      case 4:
        f>>p;
        f>>q;
        d=p*q;
        g<<d<<"\n";
        break;
      case 5:
        f>>x;
        if(x.verif()==0)
            g<<"NU"<<"\n";
        else g<<"DA"<<"\n";
        break;
      }
      f>>op;
     }

  }


    return 0;
}
