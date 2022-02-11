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
        Tlong operator*(const Tlong&b);
        Tlong operator/(Tlong&b);
        Tlong operator/(int b);
        void inc();
        Tlong N_different(Tlong&a,Tlong&b);
    private:
        int digit[Nmax]={0};
        int len=1;
        char sign='+';
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
Tlong Tlong::operator*(const Tlong&b)
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
Tlong Tlong::operator/(int b)
{
   Tlong res;
   int ost=0;
   for (int i=Nmax-len; i<Nmax; i++)
   {
        ost=ost*10+digit[i];
        res.digit[i]=ost/b;
        ost=ost%b;
   }
   res.len=res.Lenlong();
   return res;
}
void Tlong::inc()
{
   int i=Nmax-1;
   while(digit[i]==9)
   {
      digit[i]=0;
      --i;
   }
   if(i<=Nmax-len-1)
   {
      i=Nmax-len-1;
      len++;
      digit[i]=1;
   }
   else
      ++digit[i];
}
Tlong Tlong::N_different(Tlong&a,Tlong&b)
{
    Tlong res;
    res=a*b;
    a.inc();
    b.inc();
    res=res*a*b/4;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Tlong a,b,res;
    a.input_long();
    b.input_long();
    res=a.N_different(a,b);
    res.output_long();
}
