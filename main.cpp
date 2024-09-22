#include <iostream>
#include <string>
#define MAX_ITEM 107
using namespace std;
class number {
public:
    int up=0;
    int down=1;

    int gcd(int a,int b) {
        if(b==0)return a;
        return gcd(b,a%b);
    }
    void cancelliing() {
        int thegcd=gcd(up,down);
        up/=thegcd;
        down/=thegcd;
        if(down<0 and up<0) {
            down*=0-1;
            up*=0-1;
        }
        if(down<0 and up>0) {
            down*=0-1;
            up*=0-1;
        }
    }
    void print(bool isdegreeover0) {
        if((up==-1 or up==1 ) and down==1 and isdegreeover0)return;
        if(up>0) {
            if(down!=1)cout<<up<<"/"<<down;
            else cout<<up;
        }
        else {
            if(down!=1)cout<<0-up<<"/"<<down;
            else cout<<0-up;
        }
    }

};
number newNumber(int a,int b) {
    number c;
    c.up=a;
    c.down=b;
    c.cancelliing();
    return c;
}
number addNumber(number a,number b) {
    number c;
    c.up=a.up*b.down+b.up*a.down;
    c.down=a.down*b.down;
    c.cancelliing();
    return c;
}
number mulNumber(number a,number b) {
    number c;
    c.up=a.up*b.up;
    c.down=a.down*b.down;
    c.cancelliing();
    return c;
}
class item :number{
public:
    number coefficient;
};
class polynomial {
public:
    int highest_degree;
    item theItem[MAX_ITEM];
    void ini() {
        for(int i=0;i<MAX_ITEM;i++) {
            theItem[i].coefficient=newNumber(0,1);
        }
    }

    void PrintPolynomial(bool needEndl) {
        bool isAllIsZero=true;
        for(int i=highest_degree;i>=0;i--) {
            if(theItem[i].coefficient.up!=0) {
                isAllIsZero=false;
                if(i!=highest_degree) {
                    if(theItem[i].coefficient.up>0)cout<<" + ";
                    else cout<<" - ";
                }
                else if(highest_degree==0 and theItem[i].coefficient.up<0)cout<<" -";
                if(i!=0)theItem[i].coefficient.print(true);
                else theItem[i].coefficient.print(false);
                if(i>1)cout<<"x^"<<i;
                if(i==1)cout<<"x";
                if(i==0)continue;
                /*
                if(theItem[i-1].coefficient.up>0)cout<<" + ";
                else cout<<" - ";
                */
            }
        }
        if(isAllIsZero)cout<<"0";
        if(needEndl) cout<<endl;
    }
    void getPolyNomial(string a) {
        int i=0;
        int max_degree=0;
        while(true) {
            bool isPositive_degree;
            if(a[i]=='-') {
                isPositive_degree=false;
                i++;
            }
            else if(a[i]=='+') {
                isPositive_degree=true;
                i++;
            }
            else isPositive_degree=true;
            int coe_up=0;
            int coe_down=0;
            int degree=0;
            if(a[i]=='x' or a[i]=='X') {
                coe_up=1;
                coe_down=1;
            }
            else {
                for(;a[i]>='0'&&a[i]<='9';i++) {
                    coe_up=coe_up*10+int(a[i]-'0');
                }
                if(a[i]=='/') {
                    for(i++;a[i]>='0'&&a[i]<='9';i++) {
                        coe_down=coe_down*10+int(a[i]-'0');
                    }
                }
                else coe_down=1;
            }
            if(a[i]=='x' or a[i]=='X') {
                if(a[++i]=='^') {
                    for(i++;a[i]>='0'&&a[i]<='9';i++) {
                        degree=degree*10+int(a[i]-'0');
                    }
                }
                else {
                    degree=1;
                    //i++;
                }
            }
            else {
                degree=0;
                i++;
            }
            if(!isPositive_degree)coe_up*=-1;
            if(degree>max_degree)max_degree=degree;
            theItem[degree].coefficient=newNumber(coe_up,coe_down);
            if(a[i]==0)break;
        }
        highest_degree=max_degree;
    }
};
class divideResult {
public:
    polynomial q;
    polynomial r;
};
polynomial AddPolynomial(polynomial a,polynomial b) {
    polynomial c;
    c.ini();
    c.highest_degree=0;
    for(int i=0;i<MAX_ITEM;i++) {
        c.theItem[i].coefficient=addNumber(a.theItem[i].coefficient,b.theItem[i].coefficient);
        if(c.theItem[i].coefficient.up!=0)c.highest_degree=i;
    }
    //c.highest_degree=a.highest_degree>=b.highest_degree?a.highest_degree:b.highest_degree;

    return c;
}
polynomial MultiplyPolynomial(polynomial a,polynomial b) {
    polynomial c;
    c.ini();
    for(int i=0;i<=a.highest_degree;i++) {
        for(int j=0;j<=b.highest_degree;j++) {
            if(i+j>=MAX_ITEM)break;
            c.theItem[i+j].coefficient=addNumber(c.theItem[i+j].coefficient,mulNumber(a.theItem[i].coefficient,b.theItem[j].coefficient));
        }
    }
    c.highest_degree=a.highest_degree+b.highest_degree;
    return  c;
}
polynomial SubtractPolynomial(polynomial a,polynomial b) {
    polynomial d;
    d.ini();
    d.theItem[0].coefficient.up=0-1;
    d.theItem[0].coefficient.down=1;
    d.highest_degree=0;
    return AddPolynomial(a,MultiplyPolynomial(b,d));
}
divideResult DividePolynomial(polynomial a,polynomial b) {
    polynomial result_q;
    polynomial result_r;
    result_q.ini();
    result_r.ini();
    result_r=a;
    while(true) {
        //result_q.PrintPolynomial(true);
        //result_r.PrintPolynomial(true);
        polynomial s;
        s.highest_degree=result_r.highest_degree-b.highest_degree;
        s.theItem[s.highest_degree].coefficient.up=b.theItem[b.highest_degree].coefficient.down*result_r.theItem[result_r.highest_degree].coefficient.up;
        s.theItem[s.highest_degree].coefficient.down=b.theItem[b.highest_degree].coefficient.up*result_r.theItem[result_r.highest_degree].coefficient.down;
        s.theItem[s.highest_degree].coefficient.cancelliing();
        result_q=AddPolynomial(result_q,s);
        result_r=SubtractPolynomial(result_r,MultiplyPolynomial(s,b));
        if(result_r.highest_degree<b.highest_degree or result_r.highest_degree==0)break;
    }
    divideResult re;
    re.q=result_q;
    re.r=result_r;
    return re;
}
polynomial q_polynomial[MAX_ITEM];
int number_q_polynomial=0;
polynomial r_polynomial[MAX_ITEM];
int number_r_polynomial=0;
bool isLastrIs0=false;
polynomial GCD(polynomial a,polynomial b) {
    if(b.highest_degree==0) {
        if(b.theItem[0].coefficient.up==0) {
            isLastrIs0=true;
            return a;
        }
        return b;
    }
    divideResult re=DividePolynomial(a,b);
    cout<<"(";a.PrintPolynomial(false);cout<<") = (";b.PrintPolynomial(false);cout<<") * (";re.q.PrintPolynomial(false);cout<<") + (";re.r.PrintPolynomial(false);cout<<")"<<endl;
    q_polynomial[++number_q_polynomial]=re.q;
    r_polynomial[++number_r_polynomial]=re.r;
    return GCD(b,re.r);
}

int main() {
    polynomial a,b;
    a.ini();
    b.ini();
    string sa,sb;
    cout<<"f(x):";
    cin>>sa;
    a.getPolyNomial(sa);
    cout<<"g(x):";
    cin>>sb;
    b.getPolyNomial(sb);
/*
    divideResult c=DividePolynomial(a,b);
    c.q.PrintPolynomial(true);
    c.r.PrintPolynomial(true);
*/
    polynomial gcdP=GCD(a,b);
    polynomial c;
    c.highest_degree=0;
    c.theItem[0].coefficient.up=gcdP.theItem[gcdP.highest_degree].coefficient.down;
    c.theItem[0].coefficient.down=gcdP.theItem[gcdP.highest_degree].coefficient.up;
    polynomial gcdP_monic=MultiplyPolynomial(gcdP,c);
    cout<<endl<<"gcd of f(x),g(x) = ";
    gcdP.PrintPolynomial(true);
    cout<<"(f(x),g(x))= ";
    gcdP_monic.PrintPolynomial(true);
    /*
    cout<<endl<<" q: ";
    for(int i=1;i<=number_q_polynomial;i++) {
        q_polynomial[i].PrintPolynomial(false);cout<<" ; ";
    }
    cout<<endl<<" r: ";
    for(int i=1;i<=number_r_polynomial;i++) {
        r_polynomial[i].PrintPolynomial(false);cout<<" ; ";
    }
    cout<<endl;
    */
    polynomial justOne;
    justOne.getPolyNomial("1");
    cout<<endl;
    if(number_q_polynomial==3 and !isLastrIs0) {
        cout<<"u(x):";
        MultiplyPolynomial(c,AddPolynomial(justOne,MultiplyPolynomial(q_polynomial[2],q_polynomial[3]))).PrintPolynomial(true);
        cout<<"V(x):";
        MultiplyPolynomial(c,SubtractPolynomial(MultiplyPolynomial(MultiplyPolynomial(q_polynomial[1],q_polynomial[2]),q_polynomial[3]),AddPolynomial(q_polynomial[1],q_polynomial[2]))).PrintPolynomial(true);

    }
    return 0;
}
/*
x^4-4x^3+x+2
x^3-2x+1

2x^3+5x+1
x^3-x^2+2x+6
*/
