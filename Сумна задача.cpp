#include <bits/stdc++.h>

using namespace std;

class Tlong
{
    const static int Nmax=10000;
    public:
        void input_long();
        void output_long();
        Tlong operator+(Tlong b);
        Tlong operator-(Tlong b);
        Tlong operator*(Tlong&b);
        Tlong operator/(Tlong&b);
        Tlong stepin(int b);
        void inp_mas(int mas[]);
        Tlong N_var(int mas[]);
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
    cout << '\n';
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
Tlong Tlong::stepin(int b)
{
    Tlong step=*this,res;
    res.digit[Nmax-1]=1;
    int N_povtor=0,b2=b;
    while (b2)
    {
        ++N_povtor;
        b2=b2/2;
    }
    for (int i=0;i<=N_povtor-1;i++)
    {
        res=res*res;
        if (b>>(N_povtor-i-1)&1)
            res=res*step;
    }
    return res;
}
void Tlong::inp_mas(int mas[])
{
    char symbol;
    while(cin >> symbol)
        ++mas[symbol];
}
Tlong Tlong::N_var(int mas[])
{
    Tlong res,two,one,add;
    two.digit[Nmax-1]=2;
    one.digit[Nmax-1]=1;
    for (int i=0;i<128;i++)
    {
       add=two.stepin(mas[i]);
       res=res+add;
       res=res-one;
    }
    return res;
}


int mas[1000];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Tlong a,res;
    a.inp_mas(mas);
    res=a.N_var(mas);
    res.output_long();
}
