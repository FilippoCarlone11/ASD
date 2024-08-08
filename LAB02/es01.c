#include <stdio.h>
int isEven(int a);

int gcd(int a, int b);
int main(){
    int a[150] = {
            48, 56, 98, 64, 81, 120, 56, 60, 84, 36, 40, 100, 144, 90, 45, 72, 18, 30,
            55, 88, 77, 91, 99, 24, 66, 80, 32, 121, 51, 33, 27, 96, 54, 63, 75, 85,
            105, 123, 147, 42, 132, 48, 52, 100, 63, 108, 117, 120, 75, 90, 135, 25,
            49, 64, 78, 84, 96, 110, 42, 126, 140, 55, 60, 65, 132, 144, 150, 169, 176,
            183, 99, 102, 108, 114, 128, 130, 144, 150, 168, 175, 77, 84, 91, 121, 128,
            136, 147, 169, 182, 196, 210, 225, 90, 100, 105, 108, 112, 120, 125, 135,
            140, 145, 150, 156, 162, 169, 180, 189, 198, 210, 220, 225, 240, 250, 256,
            260, 270, 280, 289, 300, 315, 330, 340, 350, 360, 375, 390, 405, 420, 441,
            450, 462, 480, 500, 520, 525, 540, 550, 560, 576, 600, 625, 640, 650, 675
    };

    int b[150] = {
            18, 42, 49, 16, 27, 45, 84, 30, 42, 48, 80, 50, 96, 15, 54, 18, 54, 42,
            110, 44, 35, 13, 33, 12, 11, 20, 16, 11, 68, 99, 18, 64, 27, 21, 25, 65,
            70, 41, 49, 21, 33, 72, 13, 25, 54, 36, 65, 60, 70, 18, 30, 45, 25, 35,
            32, 26, 42, 48, 44, 30, 21, 20, 35, 40, 72, 18, 27, 60, 65, 85, 77, 39,
            56, 34, 24, 16, 72, 30, 42, 32, 35, 25, 36, 63, 77, 45, 55, 49, 22, 42,
            11, 63, 56, 18, 35, 40, 25, 35, 45, 55, 63, 77, 91, 11, 42, 77, 13, 12,
            25, 36, 49, 72, 54, 90, 15, 80, 65, 44, 75, 32, 48, 30, 45, 60, 80, 99,
            22, 28, 18, 24, 64, 30, 72, 99, 105, 16, 36, 45, 75, 84, 54, 65, 77, 90
    };

    int c[150] = {
            6, 14, 49, 16, 27, 15, 28, 30, 42, 12, 40, 50, 48, 15, 9, 18, 18, 6, 55,
            44, 7, 13, 33, 12, 11, 20, 16, 11, 17, 33, 9, 32, 27, 21, 25, 5, 35, 41,
            49, 21, 33, 24, 13, 25, 9, 36, 13, 60, 5, 18, 45, 25, 7, 32, 26, 42, 48,
            22, 30, 21, 20, 7, 20, 12, 6, 9, 60, 13, 85, 7, 39, 56, 34, 24, 16, 18,
            15, 21, 16, 35, 5, 12, 21, 7, 45, 5, 11, 11, 42, 7, 63, 7, 35, 25, 35, 5,
            7, 45, 55, 63, 7, 91, 11, 42, 7, 13, 12, 25, 36, 49, 24, 18, 15, 80, 44,
            65, 75, 16, 48, 30, 15, 30, 40, 9, 22, 7, 14, 16, 18, 24, 16, 72, 9, 15,
            21, 12, 36, 45, 15, 75, 84, 9, 65, 77, 15, 7, 18, 11, 30
    };
    int errore = 0;
    for(int i = 0; i <100; i++){
        if(gcd(a[i], b[i]) != c[i]){
            printf( "%d " ,i );
            errore++;
        }
            //
    }
    printf("%d", errore);

}

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

