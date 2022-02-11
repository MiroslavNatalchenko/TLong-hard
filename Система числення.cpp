#include <bits/stdc++.h>

using namespace std;

class Tlong
{
    const static int Nmax=1000;
    public:
        void input_long();
        void output_long();
        Tlong operator+(Tlong b);
        Tlong operator-(Tlong b);
        Tlong operator*(Tlong&b);
        Tlong operator/(Tlong&b);
        Tlong operator%(Tlong&b);
        void inp_mas(Tlong mas[],int&N,Tlong&Num,Tlong&system);
        void out_mas(Tlong mas[],int N);
    private:
        int len=1;
        char sign='+';
        int digit[Nmax]={0};
        int Lenlong();
        Tlong add_abs(Tlong&a,Tlong&b);
        Tlong sub_abs(Tlong&a,Tlong&b);
        int comp_abs(Tlong&a,Tlong&b);
        int comp(Tlong&a,Tlong&b);
};
void Tlong::input_long()
{
    string S;
    cin >> S;
    if (S[0]=='+' || S[0]=='-')
    {
        sign=S[0];
        S.erase(0,1);
    }
    len=S.size();
    for (int i=0; i<Nmax; i++)
        digit[i]=0;
    for (int i=0; i<S.size(); i++)
        digit[Nmax-len+i]=S[i]-48;
}
void Tlong::output_long()
{
    if (len==1 && digit[Nmax-1]==0)
        sign='+';
    if (sign=='-')
        cout << '-';
    for (int i=Nmax-len; i<Nmax; ++i)
        cout << digit[i];
}
int Tlong::comp_abs(Tlong&a,Tlong&b)
{
    if (a.len > b.len) return 1;
    if (a.len < b.len) return -1;
    for (int i=Nmax-a.len; i<Nmax; ++i)
    {
        if (a.digit[i] > b.digit[i]) return 1;
        if (a.digit[i] < b.digit[i]) return -1;
    }
    return 0;
}
int Tlong::comp(Tlong&a,Tlong&b)
{
    if (a.sign!=b.sign)
    {
        if (a.sign=='-')
            return -1;
        return 1;
    }
    if (a.sign=='+')
        return comp_abs(a,b);
    return -comp_abs(a,b);
}
int Tlong::Lenlong()
{
    int i=0;
    while (i<Nmax-1 && digit[i]==0) ++i;
    return Nmax-i;
}
Tlong Tlong::add_abs(Tlong&a,Tlong&b)
{
    Tlong res;
    int S=0,p=0;
    for (int i=Nmax-1;i>=0;--i)
    {
        S=a.digit[i]+b.digit[i] + p;
        res.digit[i]=S%10;
        p=S/10;
    }
    res.len=res.Lenlong();
    return res;
}
Tlong Tlong::sub_abs(Tlong&a,Tlong&b)
{
    Tlong res;
    int S=0,p=0;
    for (int i=Nmax-1;i>=0;--i)
    {
        S=a.digit[i] - b.digit[i] - p;
        if (S<0)
        {
            res.digit[i]=S+10;
            p=1;
        }
        else
        {
            res.digit[i]=S;
            p=0;

        }
    }
    res.len=res.Lenlong();
    res.sign='+';
    return res;
}
Tlong Tlong::operator-(Tlong b)
{
    Tlong res;
    if (sign!=b.sign)
    {
        res=add_abs(*this,b);
        if (sign == '+')
            res.sign='+';
        else res.sign='-';
    }
    else
    {
        if (comp_abs(*this,b)==1)
           res=sub_abs(*this,b);
        else res=sub_abs(b,*this);

        if (comp(*this,b)!=-1)
            res.sign='+';
        else res.sign='-';

    }
    return res;
}
Tlong Tlong::operator+(Tlong b)
{
    Tlong res;
    if (sign == b.sign)
    {
        res=add_abs(*this,b);
        if (sign == '+')
            res.sign='+';
        else res.sign='-';
    }
    else
    {
        b.sign=sign;
        res=*this - b;
    }
    return res;
}
Tlong Tlong::operator*(Tlong&b)
{
    Tlong res;
    int S=0,p=0;
    if (b.sign == sign)
        res.sign='+';
    else res.sign='-';
    for (int i=Nmax-1; i>=Nmax-b.len-1; --i)
        for (int j=Nmax-1; j>=Nmax-len-1; --j)
        {
            S=digit[j]*b.digit[i]+p+res.digit[i+j-Nmax+1];
            p=S/10;
            res.digit[i+j-Nmax+1]=S%10;
        }
    res.len=res.Lenlong();
    return res;
}
Tlong Tlong::operator/(Tlong&b)
{
   Tlong res,divident;
   int cnt;
   for(int i=Nmax-len;i<Nmax;++i)
   {
        for (int j=Nmax-divident.len;j<Nmax;j++)
            divident.digit[j-1]=divident.digit[j];
        divident.digit[Nmax-1]=digit[i];
        divident.len=divident.Lenlong();
        cnt=0;
        while(cnt<9 && comp_abs(divident,b)>=0)
        {
            ++cnt;
            divident=sub_abs(divident,b);
        }
        res.digit[i]=cnt;
    }
    if(sign==b.sign)
        res.sign='+';
    else
        res.sign='-';
    res.len=res.Lenlong();
    return res;
}
Tlong Tlong::operator%(Tlong&b)
{
   Tlong res,divident;
   int cnt;
   for(int i=Nmax-len; i<Nmax; ++i)
   {
        for (int j=Nmax-divident.len;j<Nmax;j++)
            divident.digit[j-1]=divident.digit[j];
        divident.digit[Nmax-1]=digit[i];
        divident.len=divident.Lenlong();
        cnt=0;
        while(cnt<9 && comp_abs(divident,b)>=0)
        {
            ++cnt;
            divident=sub_abs(divident,b);

        }
        res.digit[i]=cnt;
    }
    if(sign==b.sign)
        res.sign='+';
    else
        res.sign='-';
    res.len=res.Lenlong();
    return divident;
}
void Tlong::inp_mas(Tlong mas[],int&N,Tlong&Num,Tlong&system)
{
   Tlong zero;
   while(comp_abs(Num,zero)!=0)
   {
       ++N;
       mas[1000-N]=Num%system;
       Num=Num/system;
   }
}
void Tlong::out_mas(Tlong mas[],int N)
{
    Tlong ten;
    ten.len=2;
    ten.digit[Nmax-2]=1;
    for (int i=1000-N;i<1000;i++)
    {
        if (comp_abs(mas[i],ten)==-1)
            mas[i].output_long();
        else
        {
            cout << '[';
            mas[i].output_long();
            cout << ']';
        }
    }
}


Tlong mas[1000];
int main()
{
    Tlong Num,system,res;
    int N=0;
    Num.input_long();
    system.input_long();
    Num.inp_mas(mas,N,Num,system);
    Num.out_mas(mas,N);
}
