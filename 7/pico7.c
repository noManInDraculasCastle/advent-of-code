#include <stdio.h>
#include <math.h>
#define MAX 100

long long concatenate(long long a, long long b){ //a || b
    return pow(10, (int)log10(b)+1) *a + b;
}

long long recCalc(long long table[MAX], int i, long long num, long long target){
    if(i == MAX || table[i] == 0 || num > target){
        return num == target;
    }
    if(recCalc(table, i+1, num + table[i], target)
    || recCalc(table, i+1, num * table[i], target)
    || recCalc(table, i+1, concatenate(num, table[i]), target)){
        return 1;
    } 
    return 0;
}
int main(){
    long long target;
    long long table[MAX] = {0};
    long long calibrationResult = 0;

    while(scanf("%lld:", &target) != EOF){
        for(int i = 0; table[i] != 0; table[i] = 0, i++);

        for(int i = 0; getchar() != '\n'; i++){
            scanf("%lld", &table[i]);
        }
        calibrationResult += recCalc(table, 1, table[0], target) ? target : 0; 
    }
    printf("%lld\n", calibrationResult);
    return 0;
}