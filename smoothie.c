//Veronica Martucci
//COP3502 Fall 2021
//P1: Making Smoothies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define  MAX 21

//This struct stores one component of a smoothie recipe
typedef struct item{
  int itemID; //represents ingredient number
  int numParts; //represents number of ingredient parts
}item;

//This struct stores one smoothie recipe
typedef struct recipe{
  int numItems; //stores the number of different ingredients
  item *itemList; //array where each line stores one ingredient from the recipe
  int totalParts; //equals the sum of numParts of each ingredient in the smoothie
}recipe;

//This function dynamically allocates an array of strings to store
//the input, and sizes each individual string dynamically to be the
//proper size (string length plus 1), and returns a pointer to the array.
char** readIngredients(int numIngredients){

  char **ingredients = calloc(numIngredients, sizeof(char*));

  for(int i = 0; i < numIngredients; i++){

    char temp[MAX];
    scanf("%s", temp);

    int length = (strlen(temp)+1);

    ingredients[i] = calloc(length, sizeof(char));
    strcpy(ingredients[i], temp);
  }

  return ingredients;
}

//This function dynamically allocates space for a single recipe,
//dynamically allocates an array of item of the proper size, updates the
//numItems field of the struct, fills the array of items appropriately
//based on the input and returns a pointer to the struct dynamically allocated.
recipe* readRecipe(int numItems){

  recipe *singleRecipe = malloc(sizeof(recipe));

  singleRecipe -> itemList = calloc(numItems, sizeof(item));

  singleRecipe -> numItems = numItems;

  for(int i = 0; i < numItems; i++){
     scanf("%d", &singleRecipe -> itemList[i].itemID);
     scanf("%d", &singleRecipe -> itemList[i].numParts);
  }

  singleRecipe -> itemList = singleRecipe -> itemList;
  singleRecipe -> totalParts = 0;

  for(int i = 0; i < numItems; i++){
    singleRecipe -> totalParts = singleRecipe -> itemList[i].numParts + singleRecipe -> totalParts;
  }

  return singleRecipe;
}

//This function dynamically allocates an array of pointers to recipes of size numRecipes,
//reads numRecipes number of recipes from standard input, creates structs to store each
//recipe and has the pointers point to each struct, in the order the information was read in.
//(Should call readRecipe in a loop.)
recipe** readAllRecipes(int numRecipes){

  recipe** smoothieList = malloc(numRecipes * sizeof(recipe*));

  for(int i = 0; i < numRecipes; i++){

    int numItems;
    scanf("%d", &numItems);

    //call readRecipe function
    if(numItems > 0 && numItems <= 100){
      smoothieList[i] = readRecipe(numItems);
    }
  }

  return smoothieList;
}

//This function dynamically allocates an array of doubles of size numIngredients
//such that index i stores the # of pounds of ingredient i needed to fulfill all
//smoothie orders and returns a pointer to the array
double* calculateOrder(int numSmoothies, recipe** smoothieList, int numIngredients){

  int smoothieIndex;
  double smoothieAmount;

  //freqency array to store the amount of each ingredient
  double* amtOfEachItem = calloc(numIngredients, sizeof(double));

  for(int i = 0; i < numSmoothies; i++){

    scanf("%d", &smoothieIndex);
    scanf("%lf", &smoothieAmount);

    recipe *smoothieNumber = smoothieList[smoothieIndex];

    int ingredLength = smoothieNumber -> numItems;
    int totalParts = smoothieNumber -> totalParts;

    for(int j = 0; j < ingredLength; j++){
      int id = smoothieNumber -> itemList[j].itemID;
      int part = smoothieNumber -> itemList[j].numParts;

      double partsNeeded[ingredLength];

      //amountNeeded = (smoothieAmount / totalParts) * numParts
      partsNeeded[j] = (double)((smoothieAmount / totalParts) * part);

      amtOfEachItem[id] += partsNeeded[j];
    }
  }

return amtOfEachItem;
}

//This function prints out a list, in ingredient order, of each ingredient, a space
//and the amount of that ingredient to order rounded to 6 decimal places.
//One ingredient per line
void printOrder(char** ingredientList, double* amtOfEachItem, int numIngredients){

  for(int i = 0; i < numIngredients; i++){

    if(amtOfEachItem[i] > 0){
      printf("%s %.6f\n", ingredientList[i], amtOfEachItem[i]);
    }
  }
}

//This function frees all the memory pointed to by ingredientList
void freeIngredients(char** ingredientList, int numIngredients){

  for(int i = 0; i < numIngredients; i++){
    free(ingredientList[i]);
  }
  free(ingredientList);
}

//This function frees all the memory pointed to by allRecipe
void freeRecipes(recipe** smoothieList, int numRecipes){

  for(int i = 0; i < numRecipes; i++){
    free(smoothieList[i]);
  }
  free(smoothieList);
}

int main(){

  int numIngredients;
  scanf("%d", &numIngredients);

  char** ingredientList;
  if(numIngredients > 0 && numIngredients <= 100000){
    ingredientList = readIngredients(numIngredients);
  }

  int numRecipes;
  scanf("%d", &numRecipes);

  recipe** smoothieList;
  if(numRecipes > 0 && numRecipes <= 100){
    smoothieList = readAllRecipes(numRecipes);
  }

  int numStores;
  scanf("%d", &numStores);

  for(int i = 0; i < numStores; i++){

    double* amtOfEachItem;
    int numSmoothies;
    scanf("%d", &numSmoothies);

    if(numSmoothies > 0 && numSmoothies <= 100000){
      amtOfEachItem = calculateOrder(numSmoothies, smoothieList, numIngredients);
    }

    printf("Store #%d:\n", i+1);
    printOrder(ingredientList, amtOfEachItem, numIngredients);

    free(amtOfEachItem);
  }

  freeIngredients(ingredientList, numIngredients);

  freeRecipes(smoothieList, numRecipes);

  return 0;
}
