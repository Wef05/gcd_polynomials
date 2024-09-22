#include <iostream>
#include <string>
#define MAX_ITEM 107
using namespace std;
class number {
public:
    int up;
    int down;

    int gcd(int a,int b) {
        if(a%b==0)return b;
        return gcd(a/b,a%b);
    }
    void cancelliing() {
        int thegcd=gcd(up,down);
        up/=thegcd;
        down/=thegcd;
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
                if(i==highest_degree) {
                    if(theItem[i].coefficient.up<0)cout<<"-";
                }
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
polynomial AddPolynomial(polynomial a,polynomial b) {
    polynomial c;
    c.ini();
    for(int i=0;i<MAX_ITEM;i++) {
        c.theItem[i].coefficient=addNumber(a.theItem[i].coefficient,b.theItem[i].coefficient);
    }
    c.highest_degree=a.highest_degree>=b.highest_degree?a.highest_degree:b.highest_degree;
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
int main() {
    polynomial a,b;
    a.ini();
    b.ini();
    string sa,sb;
    cin>>sa;
    a.getPolyNomial(sa);
    cin>>sb;
    b.getPolyNomial(sb);

    a.PrintPolynomial(true);
    b.PrintPolynomial(true);

    polynomial c=SubtractPolynomial(a,b);
    c.PrintPolynomial(true);

    return 0;
}