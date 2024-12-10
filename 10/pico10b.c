#include <stdio.h>

#define BOUNDS 60
#define inBounds(n) n >= 0 && n < BOUNDS

#define bloomWr(map, head, i, pos, incr) \
if(inBounds(head.pos+incr)){ \
    head.pos += incr; \
    path += bloom(map, head, i+1); \
    head.pos -= incr; \
}

typedef struct coordinates{
    int x, y;
}coords;

int bloom(int map[BOUNDS][BOUNDS], coords head, int i){
    if(map[head.x][head.y] != i) return 0;
    if(i == 9) return 1;
    
    int path = 0;
    bloomWr(map, head, i, x, 1);
    bloomWr(map, head, i, y, 1);
    bloomWr(map, head, i, x, -1);
    bloomWr(map, head, i, y, -1);
    return path;
}

int main(){
    int map[BOUNDS][BOUNDS] = {0};
    coords headPos[BOUNDS*BOUNDS] = {0};
    int headPosCount = 0;
    int scoreTotal = 0;

    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            scanf("%1d", &map[i][j]);
            if(!map[i][j]) {
                headPos[headPosCount].x = i;
                headPos[headPosCount].y = j;
                headPosCount++;
            }
        }
    }
    for(int i = 0; i < headPosCount; i++){
        scoreTotal += bloom(map, headPos[i], 0);
    }
    printf("%d\n", scoreTotal);
    return 0;
}
/* Adds a macro 
 */
