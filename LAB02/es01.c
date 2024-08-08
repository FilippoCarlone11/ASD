int isEven(int a);
int gcd(int a, int b);

int gcd(int a, int b){
    int swapVar;
    if (b == 1)
        return 1;
    if (a == b)
        return b;
    if (b > a){
        swapVar = b;
        b = a;
        a = swapVar;
    }
    if(isEven(a) && isEven(b))
        return 2*gcd(a/2, b/2);
    if(isEven(a) && !isEven(b)){
        return gcd(b, a/2);
    }

    if(!isEven(a) && isEven(b))
        return gcd(a, b/2);
    if(!isEven(a) && !isEven(b))
        return gcd((a-b)/2, b);
}

int isEven(int a){
    if(a % 2 == 0)
        return 1;
    return 0;
}

