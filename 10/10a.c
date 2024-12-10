#include <stdio.h>

#define BOUNDS 60
#define inBounds(n) n >= 0 && n < BOUNDS

typedef struct coordinates{
    int x, y;
}coords;

void printMap(int map[BOUNDS][BOUNDS], coords head){
    printf("\n");
    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            if(i != head.x || j != head.y)printf("%d", map[i][j]);
            else printf("X");
        }
        printf("\n");
    }
    printf("\n");
}

void clear(int map[BOUNDS][BOUNDS]){
    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            if(map[i][j] == -1) map[i][j] = 9;
        }
    }
}

int bloom(int map[BOUNDS][BOUNDS], coords head, int i){
    if(map[head.x][head.y] != i) return 0;
    //printf("%d: %d, %d\n", i, head.x, head.y);
    //printMap(map, head);
    if(i == 9){
        map[head.x][head.y] = -1;
        return 1;
    } 
    
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
    //printf("path: %d\n", path);
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
            if(!map[i][j]) {
                headPos[headPosCount].x = i;
                headPos[headPosCount].y = j;
                headPosCount++;
            }
        }
    }
    for(int i = 0; i < headPosCount; i++){
        //printf("----%d, %d\n", headPos[i].x, headPos[i].y);
        scoreTotal += bloom(map, headPos[i], 0);
        clear(map);
    }
    printf("%d\n", scoreTotal);
    return 0;
}
/* I accidentally solved part2 before part1
 * Normally I would clean up the code slightly
 * or try to optimisse itbut I think leaving
 * it like this might provide some comedic value
 *
 * The difference between here and partB is that
 * here any visited 9s get marked so we dont
 * count them again (there are most likely smarter
 * ways to do this).
 */
