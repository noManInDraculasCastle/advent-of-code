#include <stdio.h>
#define MAX 100

long long recCalc(long long table[MAX], int i, long long num, long long target){
    if(i == MAX || table[i] == 0 || num > target){
        return num == target ? target : 0;
    }
    long long res;
    
    //addition
    res = recCalc(table, i+1, num + table[i], target);
    if(res != 0){
        return target;
    } 

    //multiplication
    res = recCalc(table, i+1, num * table[i], target);
    if(res != 0){
        return target;
    }

    return 0;
}
int main(){
    long long target;
    long long table[MAX];
    long long calibrationResult = 0;

    while(scanf("%lld:", &target) != EOF){
        for(int i = 0; i < MAX && table[i] != 0; table[i] = 0, i++);

        for(int i = 0; getchar() != '\n'; i++){
            scanf("%lld", &table[i]);
        }
        calibrationResult += recCalc(table, 1, table[0], target);
    }

    printf("%lld\n", calibrationResult);
    return 0;
}