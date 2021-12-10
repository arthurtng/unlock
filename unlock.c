#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define GRID 3
#define POSITIONS (GRID*GRID)
#define MAXNUM 1000

// first position in each row
#define FIRSTROW 1
#define SECONDROW 4
#define THIRDROW 7

struct grid{
   int square[GRID][GRID];
   int y;
   int x;   
};
typedef struct grid grid;

void test(void);
void printgrid(int grid[GRID][GRID]);
bool explore(int grid[GRID][GRID], int y, int x, int num, int* counter);
void coordtogrid(int coordinate, grid* g);
grid* grid_init(void);

int main(void)
{
   test();
   
   int coordinate;
   printf("Grid:\n1 2 3\n4 5 6\n7 8 9\n\nInput starting point: ");
   scanf("%d", &coordinate);
   if (coordinate < 1 || coordinate > 9){
      fprintf(stderr, "Please select coordinate between 1 and 9\n");
      exit(EXIT_FAILURE);
   } 
   
   grid* g = grid_init();
   coordtogrid(coordinate, g);
   
   int counter = 0;      
   explore(g->square, g->y, g->x, 1, &counter);   
   free(g);
                  
   return 0;
}

void test(void)
{
   grid new;
   coordtogrid(5, &new);
   assert(new.x == 1);
   assert(new.y == 1);
   coordtogrid(9, &new);
   assert(new.x == 2);
   assert(new.y == 2);
   coordtogrid(1, &new);
   assert(new.x == 0);
   assert(new.y == 0);
   coordtogrid(2, &new);
   assert(new.x == 1);
   assert(new.y == 0);
   
}

grid* grid_init(void)
{
   grid* new = calloc(1, sizeof(grid));
   if (new == NULL){
      fprintf(stderr, "Error initialising grid.\n");
      exit(EXIT_FAILURE);
   }
   return new;
}

void coordtogrid(int coordinate, grid* g)
{
   // first row
   if (coordinate < 4){
      g->y = 0;
      g->x = coordinate - FIRSTROW; //based on first number in the row
   }
   // third row
   else if (coordinate > 6){
      g->y = 2;
      g->x = coordinate - THIRDROW;
   }
   // second row
   else {
      g->y = 1;
      g->x = coordinate - SECONDROW;
   }      
      
}

// Input grid and starting coordinates
bool explore(int grid[GRID][GRID], int y, int x, int num, int* counter)
{
   if (grid[y][x] != 0){
      return false;
   } 
   
   grid[y][x] = num; 
      
   if (num == POSITIONS){
      (*counter)++; 
      printf("Pattern no. %d\n", *counter);
      printgrid(grid);
      printf("\n");
   }
   
   // Go left 
   if (x - 1 >= 0){
      if (explore(grid, y, x-1, num+1, counter)){
	 return true;
      }      
   }
   
   // Go up
   if (y - 1 >= 0){
      if (explore(grid, y-1, x, num+1, counter)){
	 return true;
      }          
   }
   
   // Go down
   if (y + 1 < GRID){ 
      if (explore(grid, y+1, x, num+1, counter)){
	 return true;
      }
   }
   
   // Go right
   if (x + 1 < GRID){
      if (explore(grid, y, x+1, num+1, counter)){
	 return true;
      }
   }
   
   // Go up and left
   if (x - 1 >= 0 && y - 1 >= 0){
      if(explore(grid, y-1, x-1, num+1, counter)){
         return true;
      }
   }
   
   // Go down and left   
   if (x - 1 >= 0 && y + 1 < GRID){
      if (explore(grid, y+1, x-1, num+1, counter)){
         return true;
      }
   }
   
   // Go up and right
   if (x + 1 < GRID && y - 1 >= 0){
      if (explore(grid, y-1, x+1, num+1, counter)){
         return true;
      }
   }  
   
   // Go down and right
   if (x + 1 < GRID && y + 1 < GRID){
      if (explore(grid, y+1, x+1, num+1, counter)){
         return true;
      }
   }
                        
   grid[y][x] = 0; // for backtracking through the route taken
              
   return false;        
}

void printgrid(int grid[GRID][GRID])
{
   for (int j=0; j<GRID; j++){
      for (int i=0; i<GRID; i++){
         printf("%d ", grid[j][i]);
      }
      printf("\n");
   }
      
}

