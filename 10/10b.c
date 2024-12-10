#include <stdio.h>

#define BOUNDS 60
#define inBounds(n) n >= 0 && n < BOUNDS

typedef struct coordinates{
    int x, y;
}coords;

//New roads open up as you walk
//They kinda open up in the same
//way a flower might open up its leafs
//thus the name bloom. Thats what I
//thought of initially anyways.
int bloom(int map[BOUNDS][BOUNDS], coords head, int i){
    //since we always go up one step at a time,
    //the number recursive calls i should also
    //be the height of the road if the path is valid
    if(map[head.x][head.y] != i) return 0;
    
    //obv map[head.x][head.y] == i & 9 is max
    if(i == 9) return 1;
    
    int path = 0;
    if(inBounds(head.x+1)){
        head.x += 1;
        path += bloom(map, head, i+1);
        head.x -= 1;
    }
    if(inBounds(head.y+1)){
        head.y += 1;
        path += bloom(map, head, i+1);
        head.y -= 1;
    }
    if(inBounds(head.x-1)){
        head.x -= 1;
        path += bloom(map, head, i+1);
        head.x += 1;
    }
    if(inBounds(head.y-1)){
        head.y -= 1;
        path += bloom(map, head, i+1);
        head.y += 1;
    }
    return path;
}

int main(){
    coords headPos[BOUNDS*BOUNDS] = {0};
    int headPosCount = 0;
    int scoreTotal = 0;

    int map[BOUNDS][BOUNDS] = {0};

    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            scanf("%1d", &map[i][j]);
            //avoid looking at whole table again
            //by saving every head position
            if(!map[i][j]) {
                headPos[headPosCount].x = i;
                headPos[headPosCount].y = j;
                headPosCount++;
            }
        }
    }
    for(int i = 0; i < headPosCount; i++){
        //recursively investigate every possible hiking route
        scoreTotal += bloom(map, headPos[i], 0);
    }
    printf("%d\n", scoreTotal);
    return 0;
}
