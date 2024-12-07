#include <stdio.h>
#include <math.h>
#define MAX 100

long long concatenate(long long a, long long b){ //a || b
    int digitsb = (int)log10(b)+1;
    long long multiplier = pow(10, digitsb);
    return multiplier *a + b;
}
//recursively tries each operator combination to find if result can be calculated
long long recCalc(long long table[MAX], int i, long long num, long long target){
    if(i == MAX || table[i] == 0 || num > target){
        return num == target;
    }//if we are at the end of the table and num = target, there is a set of operands
     //that gives us the target
     //num > target condition prevents redundand work
    long long res;
    
    //addition
    res = recCalc(table, i+1, num + table[i], target);
    if(res != 0){
        return 1;
    } 

    //multiplication
    res = recCalc(table, i+1, num * table[i], target);
    if(res != 0){
        return 1;
    }

    //concatenation
    res = recCalc(table, i+1, concatenate(num, table[i]), target);
    if(res != 0){
        return 1;
    }

    return 0;
}
int main(){
    long long target;
    long long table[MAX];
    long long calibrationResult = 0;

    while(scanf("%lld:", &target) != EOF){
        //prevents junk from prevous calculation being factored in
        for(int i = 0; i < MAX && table[i] != 0; table[i] = 0, i++);

        for(int i = 0; getchar() != '\n'; i++){
            scanf("%lld", &table[i]);
        }//format: target: num1 num2 ... numN

        if(recCalc(table, 1, table[0], target) == 1){
            calibrationResult += target;
        }//adds target only if it can be calculated with given nums and operators
    }
    printf("%lld\n", calibrationResult);
    return 0;
}