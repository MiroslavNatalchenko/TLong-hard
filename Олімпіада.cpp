#include <iostream>

using namespace std;

const long long Nmax=50000;
struct TLong
{
    char sign='+';
    int len=1;
    int digit[Nmax]={0};
};

void input_long(TLong & a)
{
    string S;
    cin >> S;
    if (S[0]=='+' || S[0]=='-')
    {
        a.sign=S[0];
        S.erase(0,1);
    }
    a.len=S.size();
    for (int i=0; i<Nmax; i++)
        a.digit[i]=0;
    for (int i=0; i<S.size(); i++)
        a.digit[Nmax-a.len+i]=S[i]-48;
}

void output_long(TLong & a)
{
    if (a.len==1 && a.digit[Nmax-1]==0)
        a.sign='+';
    if (a.sign=='-') cout<<'-';
    for (int i=Nmax-a.len; i<Nmax; ++i)
        cout << a.digit[i];
}

int comp_abs(TLong & a, TLong & b)
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

int comp(TLong & a, TLong & b)
{
    if (a.sign!=b.sign)
    {
        if (a.sign=='-') return -1;
        return 1;
    }
    if (a.sign=='+') return comp_abs(a,b);
    return -comp_abs(a,b);
}

int Lenlong(TLong & a)
{
    int i=0;
    while (i<Nmax-1 && a.digit[i]==0) ++i;
    return Nmax-i;
}

TLong sub_abs(TLong&a, TLong&b)
{
    TLong res;
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
    res.len=Lenlong(res);
    res.sign='+';
    return res;
}

TLong add_abs(TLong&a,TLong&b)
{
    TLong res;
    int S=0,p=0;
    for (int i=Nmax-1;i>=0;--i)
    {
        S=a.digit[i]+b.digit[i] + p;
        res.digit[i]=S%10;
        p=S/10;
    }
    res.len=Lenlong(res);
    return res;
}

TLong sub(TLong&a,TLong b)
{
    TLong res;
    if (a.sign!=b.sign)
    {
        res=add_abs(a,b);
        if (a.sign == '+')
            res.sign='+';
        else res.sign='-';
    }
    else
    {
        if (comp_abs(a,b)==1)
           res=sub_abs(a,b);
        else res=sub_abs(b,a);

        if (comp(a,b)!=-1)
            res.sign='+';
        else res.sign='-';

    }
    return res;
}

TLong add(TLong&a,TLong b)
{
    TLong res;
    if (a.sign == b.sign)
    {
        res=add_abs(a,b);
        if (a.sign == '+')
            res.sign='+';
        else res.sign='-';
    }
    else
    {
        b.sign=a.sign;
        res=sub(a,b);
    }
    return res;
}

TLong multy(TLong&a,TLong&b)
{
    TLong res;
    int S=0,p=0;
    if (b.sign == a.sign)
        res.sign='+';
    else res.sign='-';
    for (int i=Nmax-1; i>=Nmax-b.len-1; --i)
        for (int j=Nmax-1; j>=Nmax-a.len-1; --j)
        {
            S=a.digit[j]*b.digit[i] + p + res.digit[i+j-Nmax+1];
            p=S/10;
            res.digit[i+j-Nmax+1]=S%10;
        }

    res.len=Lenlong(res);
    return res;
}

TLong divmod(TLong&a,TLong&b,TLong&divident)
{
   TLong res;
   int digit;
   for(int i=Nmax-a.len; i<Nmax; ++i)
   {
        for (int j=Nmax-divident.len;j<Nmax;j++)
            divident.digit[j-1]=divident.digit[j];
        divident.digit[Nmax-1]=a.digit[i];
        divident.len=Lenlong(divident);
        digit=0;
        while(digit<9 && comp_abs(divident,b)>=0)
        {
            ++digit;
            divident=sub_abs(divident,b);
        }
        res.digit[i]=digit;
    }
    if(a.sign==b.sign)
        res.sign='+';
    else
        res.sign='-';
    if(a.sign=='-')
        divident.sign='-';
    res.len=Lenlong(res);
    return res;
}

TLong factorial(TLong&c)
{
    TLong mnozhetel,res,one;
    one.digit[Nmax-1]=1;
    res.digit[Nmax-1]=1;
    mnozhetel.digit[Nmax-1]=2;
    while (comp_abs(mnozhetel,c)<1)
    {
        res=multy(res,mnozhetel);
        mnozhetel=add_abs(mnozhetel,one);
    }
    return res;
}

int main()
{
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   TLong a,b,c,res,divident;
   input_long(a);
   input_long(b);
   input_long(c);
   if (b.sign=='-')
   {
       output_long(a);
       cout << "+(";
       output_long(b);
       cout << ")=";
       res=add(a,b);
       output_long(res);
       cout << '\n';

       output_long(a);
       cout << "-(";
       output_long(b);
       cout << ")=";
       res=sub(a,b);
       output_long(res);
       cout << '\n';

       output_long(a);
       cout << "*(";
       output_long(b);
       cout << ")=";
       res=multy(a,b);
       output_long(res);
       cout << '\n';

       output_long(a);
       cout << "/(";
       output_long(b);
       cout << ")=";
       res=divmod(a,b,divident);
       output_long(res);
       cout << " (";
       output_long(divident);
       cout << ")" << '\n';



       output_long(c);
       cout << "!=";
       res=factorial(c);
       output_long(res);
   }
   else
   {
       output_long(a);
       cout << "+";
       output_long(b);
       cout << "=";
       res=add(a,b);
       output_long(res);
       cout << '\n';

       output_long(a);
       cout << "-";
       output_long(b);
       cout << "=";
       res=sub(a,b);
       output_long(res);
       cout << '\n';

       output_long(a);
       cout << "*";
       output_long(b);
       cout << "=";
       res=multy(a,b);
       output_long(res);
       cout << '\n';

       if (b.digit[Nmax-1]==0 && b.len==1)
           cout << "Division by zero." << '\n';
       else
       {
          output_long(a);
          cout << "/";
          output_long(b);
          cout << "=";
          res=divmod(a,b,divident);
          output_long(res);
          cout << " (";
          output_long(divident);
          cout << ")" << '\n';
       }

       output_long(c);
       cout << "!=";
       res=factorial(c);
       output_long(res);
   }
}
