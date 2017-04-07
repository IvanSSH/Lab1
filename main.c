#include <stdio.h>
#include <stdlib.h>

void *Arr, *Brr ,* Res;                 // pointers for Matrix
int flg, op, ent;                       // flg - type of operation, op - type of operation, ent - type of input
int N1 ,M1;                             // M1 - number of rows, N1 - number of columns
int Val;
const float Epsilon = 0.00001;                                //Val - volume of one cell


void multiplyInt(void* a, void* b,void* f) {                                    // Int.

    *((int*)f) = *((int*)f) + *((int*)a) * *((int*)b);
}

void multiplyFloat(void* a, void* b,void* f) {                                  //Float.
    *((float*)f) = *((float*)f) + *((float*)a) * *((float*)b);
}

void multiplyComplex(void* a, void* b, void* f) {                               // Complex.
    *((int*)f) += *((int*)a) * *((int*)b) - *((int*)a+1) * *((int*)b+1);
    *((int*)f+1) += *((int*)a) * *((int*)b+1) + *((int*)a+1) * *((int*)b);
}

void* multiply(void* a, void* b, void (*func)(void* a, void* b, void* f)) {     //Common Multiply.
    void *f = calloc(M1*N1, Val);
    int i,j,k;
    for (i = 0; i < M1; i++) {
        for (j = 1; j < M1; j++) {
            for (k = 0; k < N1; k++) {
                func(a+(i*M1+k)*Val, b+(k*M1+j)*Val, f+(i*M1+j)*Val);
            }
        }
    }
    return f;
}

void addInt(void* a, void* b) {                                        //Int.
    *((int*)a) += *((int*)b);
}

void addFloat(void* a, void* b) {                                       //Float.
    *((float*)a) += *((float*)b);
}


void addComplex(void* a, void* b) {                                     //Complex.
    *((int*)a) += *((int*)b);
    *((int*)a+1) += *((int*)b+1);
}

void add(void* a, void* b, void (*func)(void* a, void* b)) {            //Common Sum.
    int i;
    for (i = 0; i < M1*N1; i++) {
        func(a+i*Val, b+i*Val);
    }
}


void* initialization (int M, int N, int flg, int ent) {                 //Function of initialization of Matrix
    int i;
    void* A = malloc(M*N*Val);
    if (ent == 1)
            for (i=0;i<M*N;i++) {
                if (flg==1) *((int*)A+i) = ((int)(i+1));
                if (flg==2) *((float*)A+i) = ((float)(i+1))/10;
                if (flg==3) {
                        *((int*)A+i*2) = ((int)i);
                        *((int*)A+i*2+1) = ((int)(1+i));
                        printf("re = %d im = %d \n",*((int*)A+i*2),*((int*)A+i*2+1));
                        }
                }
    if (ent == 0)
                for (i=0;i<M*N;i++) {
                    if (flg==1) scanf("%d", (int*)A+i);
                    if (flg==2) scanf("%f", ((float*)A+i));
                    if (flg==3) {
                            printf("Re = ");
                            scanf("%d", (int*)A+2*i);
                            printf("Im = ");
                            scanf("%d", (int*)A+2*i+1);
                            }
                    }
    return A;
}

void display(void *A,int flg) {                                         // display of matrix
    int i, j;
    for (i = 0; i < M1; i++) {
        for (j = 0; j < N1; j++) {
                if (flg==1) printf("%d  \t ", *((int*)A+i*N1+j));
                if (flg==2) printf("%5.2f \t", *((float*)A+i*N1+j));
                if (flg==3) {
                printf("Re = %d ; ",*((int*)A+i*N1*2+j*2));
                printf("Im = %d     ",*((int*)A+i*N1*2+j*2+1));
                }
            }
        printf("\n");
    }
    printf("\n");
}

 void Programtest(){                                                    // Test
    int i,j;
    M1 = 2;
    N1 = 2;
    printf("1 for int, 2 for float, 3 for complex \n");
    scanf("%d",&flg);
    printf("Operation ? add(1) multiply(2)\n");
    scanf("%d",&op);
    if (flg == 1) Val = sizeof(int);
        else if (flg == 2) Val = sizeof(float);
            else if (flg == 3) Val = 2*sizeof(int);
    ent = 1;
    Arr = initialization(M1, N1 , flg, ent);
    Brr = initialization(M1, N1, flg ,ent);
    if ( op == 2 ){
            switch (flg)
        {
            case 1:		// int.
                Res = multiply(Arr, Brr,multiplyInt);
                break;
            case 2:		// float.
                Res = multiply(Arr, Brr,multiplyFloat);
                break;
            case 3:		// char.
                Res = multiply(Arr, Brr,multiplyComplex);
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
            printf("\nAnswer is: \n");
            display(Res, flg) ;
    }
    if ( op == 1) {
            switch (flg)
        {
            case 1:		// int.
                add(Arr,Brr,addInt);
                break;
            case 2:		// float.
                add(Arr,Brr,addFloat);
                break;
            case 3:		// char.
                add(Arr,Brr,addComplex);
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
            printf("\nAnswer is: \n");
            display(Arr,flg);
    }

    if ( op == 2 ){                                                     //ѕроверка правильности данных
            switch (flg)
        {
            case 1:		// int.
                if ( (*((int*)Res)!= 7)||(*((int*)Res+1)!=10)||(*((int*)Res+2)!= 15)||(*((int*)Res+2+1)!= 22) ) printf("\nError in Multiply of Int \n");
                break;
            case 2:		// float.
                if  ( abs( *((float*)Arr) - 0.07) > Epsilon ) printf(" \nError in Add of Int \n");
            case 3:		// char.
                if  ((*((int*)Res)!= -5)||(*((int*)Res+1)!=7) || (*((int*)Res+6)!= -11)||(*((int*)Res+7)!=31)) printf("\nError in Multiply of Complex \n");
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
    }

    if ( op == 1) {
            switch (flg)
        {
            case 1:		// int.
            if ( (*((int*)Arr)!= 2)||(*((int*)Arr+1)!=4)||(*((int*)Arr+2)!= 6)||(*((int*)Arr+2+1)!= 8) ) printf("\nError in Add of Int \n");
                break;
            case 2:		// float.
                if  ( abs( *((float*)Arr) - 0.2) > Epsilon ) printf(" \nError in Add of Int \n");
                break;
            case 3:		// char.
                if ((*((int*)Arr) != 0) || (*((int*)Arr+1) != 2) || (*((int*)Arr+6) != 6) || (*((int*)Arr+7) != 8)) printf("\n!ERROR in add of Complex \n");
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
    }

}

int main()
{
    int i,j;

    printf("Test?  Yes(1)  ,  No(0) \n");
    scanf("%d", &ent);
    if (ent == 1){
            Programtest();
            goto Label1;
    }

    printf("The number of rows: \n");
    scanf("%d",&M1);
    printf("The number of columns: \n");
    scanf("%d",&N1);
    printf("1 for int, 2 for float, 3 for complex \n");
    scanf("%d",&flg);
    printf("Operation ? add(1) multiply(2)\n");
    scanf("%d",&op);
    if ((op!=1) && (M1!=N1)) {
        printf("Matrix are not suitable, sorry! \n");
        goto Label1;
    }

    if (flg == 1) Val = sizeof(int);
        else if (flg == 2) Val = sizeof(float);
            else if (flg == 3) Val = 2*sizeof(int);

    printf("Automatically? yes(1) , no(0)");                    //»нициализаци€ массивов
    scanf("%d",&ent);
    printf("entering the First Matrix:  \n");
    Arr = initialization(M1, N1 , flg, ent);
    printf("entering the Second Matrix: \n");
    Brr = initialization(M1, N1, flg ,ent);

    printf("First Matrix is: \n");
    display(Arr,flg);
    printf("Second Matrix is: \n");
    display(Brr,flg);
    printf("We start !\n");

    if ( op == 2 ){                                             // вполнение операции и вывод
            switch (flg)
        {
            case 1:		// int.
                Res = multiply(Arr, Brr,multiplyInt);
                break;
            case 2:		// float.
                Res = multiply(Arr, Brr,multiplyFloat);
                break;
            case 3:		// char.
                Res = multiply(Arr, Brr,multiplyComplex);
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
            printf("\nAnswer is: \n");
            display(Res, flg) ;
    }
    if ( op == 1) {
            switch (flg)
        {
            case 1:		// int.
                add(Arr,Brr,addInt);
                break;
            case 2:		// float.
                add(Arr,Brr,addFloat);
                break;
            case 3:		// char.
                add(Arr,Brr,addComplex);
                break;
            default:
                printf("\n ERROR: Wrong value");
        }
            printf("\nAnswer is: \n");
            display(Arr,flg);
    }

    free (Arr);
    free (Brr);
    free (Res);

   /*     for (i = 0; i < M1; i++) {
        for (j = 0; j < N1; j++) {
                if (flg==1) printf("%d          ", *((int*)Res+i*N1+j));
                if (flg==2) printf("%10.5f", *((float*)Res+i*N1+j));
                if (flg==3) {
                printf("Re = %d ; ",*((int*)Res+i*N1*2+j*2));
                printf("Im = %d     ",*((int*)Res+i*N1*2+j*2+1));
                }
            }
        printf("\n");
    }
    */
    Label1:
    printf("Fanks for watching!\n");

    return 0;
}
