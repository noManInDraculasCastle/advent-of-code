#include <stdio.h>
#define BOUNDS 50
#define MAX_CHAR 62

typedef struct nodetile{
    char node;
    int antinode;
}tile;

typedef struct coordinates{
    int x;
    int y;
    int filled;
}coords;

int abs(int n){
    return n < 0 ? -n : n;
}

int notOutOfBounds(int x, int y){
    return x < BOUNDS && y < BOUNDS && x >= 0 && y >= 0;
}

//note: x and y are reversed, both have the same bound so we dont care
void antinodeMap(tile nodeMap[BOUNDS][BOUNDS], char nodeType){
    coords nodeInst[BOUNDS*BOUNDS] = {0};
    int coordTablePos = 0;
    coords newAntiNode = {0,0,0};

    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            if(nodeMap[i][j].node == nodeType){
                
                nodeInst[coordTablePos].x = i;
                nodeInst[coordTablePos].y = j;
                nodeInst[coordTablePos].filled = 1;
                coordTablePos++;
            }
        }
    }
    //Obviously for each pair of nodes we will have one pair of antinodes
    //From the perspective of the second node, one of the antinode is
    //* going to be located exactly the same distance away from the first
    //* node, but in the opposite direction.  
    for(coordTablePos = 0; nodeInst[coordTablePos].filled != 0; coordTablePos++){
        for(int i = 0; nodeInst[i].filled != 0; i++){
            if(i == coordTablePos);
            else{
                //expression in abs is the distance
                //the distance is multiplied by a number to dictate direction
                newAntiNode.x = nodeInst[i].x + abs(nodeInst[coordTablePos].x - nodeInst[i].x)*(nodeInst[i].x > nodeInst[coordTablePos].x?1:-1);
                newAntiNode.y = nodeInst[i].y + abs(nodeInst[coordTablePos].y - nodeInst[i].y)*(nodeInst[i].y > nodeInst[coordTablePos].y?1:-1);

                if(notOutOfBounds(newAntiNode.x, newAntiNode.y)){
                    nodeMap[newAntiNode.x][newAntiNode.y].antinode = 1;
                }
            }
        }
    }
}

int main(){
    tile nodeMap[BOUNDS][BOUNDS] = {0};
    char charTable[MAX_CHAR] = {0};
    int antinodeNum = 0;

    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            scanf(" %c", &nodeMap[i][j].node);
            
            //all characters appearing on the map will be saved in a table,
            //and changed one by one
            if(nodeMap[i][j].node != '.'){
                for(int z = 0; z < MAX_CHAR; z++){
                    if(charTable[z] == '\0'){
                        charTable[z] = nodeMap[i][j].node;
                        break;
                    }
                    if(charTable[z] == nodeMap[i][j].node){
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < MAX_CHAR && charTable[i] != '\0'; i++){
        antinodeMap(nodeMap, charTable[i]);
    }
    for(int i = 0; i < BOUNDS; i++){
        for(int j = 0; j < BOUNDS; j++){
            antinodeNum += nodeMap[i][j].antinode;
        }
    }
    printf("%d\n", antinodeNum);
}