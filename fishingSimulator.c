#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUCKET  10
#define MAX_POND 15

typedef struct {
  unsigned char  size; // in cm
  char          *species;
} Fish;

typedef struct {
  char         *name;
  unsigned char keepSize;
  Fish          bucket[MAX_BUCKET];
  unsigned char numFish;
} Fisher;

typedef struct {
  Fish          fish[MAX_POND];
  unsigned char numFish;
} Pond;

int addFish(Pond *p, unsigned char size, char *species){
  // if the pond is full, do not add
  if ( (p->numFish) > 15){
    return 0;
  }
  // else, place fish at the end of array
  else{
    int index = (int) p->numFish;
    Fish addedFish = {size, species};
    p->fish[index] = addedFish;
    p->numFish ++;
    return 1;
  }
}

void listFish(Fish *arrayOfFish, int n){
  // iterate through arrayOfFish and print
  for (int i=0; i < n; i++){
    printf("%2d cm %s\n", arrayOfFish->size, arrayOfFish->species);
    ++arrayOfFish;
  }
}

char likes(Fisher *fisher, Fish *f){
  // if the fish size is greater or equal to prefered keep size and NOT sunfish, they like
  if ((fisher->keepSize) <= (f->size)){
    if (strcmp(f->species, "Sunfish") != 0){
      return '1';
    }
  }
  else{
    return '0';
  }
}

int keep(Fisher *fisher, Fish *f){
  // if fisher has room in bucket, add to end of array
  if ((fisher->numFish) < 10){
    int index = (int) fisher->numFish;
    Fish temp;
    temp.size = f->size;
    temp.species = f->species;
    (fisher->bucket)[index] = temp;
    ++ fisher->numFish;
    return 1;
  }
  return 0;
}


int castLine(Fisher *fisher, Pond *p){
  // if pond has no fish, return 0
  if ((p->numFish) == 0){
    return 0;
  }
  // if fisher's bucket is full, return 0;
  if ((fisher->numFish) == 10){
    return 0;
  }
  // select random number between 0 and number of fish in pond
  int random = rand() % p->numFish;

  Fish chosenFish;
  chosenFish.species = p->fish[random].species;
  chosenFish.size = p->fish[random].size;

  // if fisher likes chosen fish,
  if (likes(fisher, &chosenFish) == '1'){
     // put in bucket
     keep(fisher, &chosenFish);
     int indexPond = (int) p->numFish;
     // place fish from end in removed fish
     p->fish[random] = p->fish[indexPond -1];
     -- p->numFish;
     return 1;
  }
  return 0;
}

void giveAwayFish(Fisher *fisher1, Fisher *fisher2, Pond *p){
  int size1 = (int) fisher1->numFish;
  int size2 = (int) fisher2->numFish;
  int pondSize = (int) p->numFish;

  // calculate how much room is in bucket
  int ableToTake = 10 - size2;

  // if fisher 2 cannot take any of the fish, put in pond
  if (ableToTake == 0){
    for (int k = 0; k < size1; k++){

      Fish temp;
      temp.species = fisher1->bucket[k].species;
      temp.size = fisher1->bucket[k].size;

      p->fish[pondSize] = temp;

      ++pondSize;
      ++p->numFish;
      --fisher1->numFish;
    }
  }
  else{
    // place as many in fisher 2's bucket
    for (int i = 0; i < ableToTake; i ++){
      if (size1 > 0){

        Fish temp2;
        temp2.species = fisher1->bucket[i].species;
        temp2.size = fisher1->bucket[i].size;

        fisher2->bucket[size2] = temp2;

        ++fisher2->numFish;
        ++size2;
        --fisher1->numFish;
        --size1;
      }
    }
    // if player 1 still has fish, put rest in pond
    if (size1 != 0){
      for (int j = 0; j < size1; j++){

        Fish temp3;
        temp3.species = fisher1->bucket[j].species;
        temp3.size = fisher1->bucket[j].size;
        p->fish[pondSize] = temp3;

        ++pondSize;
        ++p->numFish;
        --fisher1->numFish;
      }
    }
  }
}

int main(){
  srand(time(NULL));
  Fisher fred = {"Fred", 15, 0, 0};
  Fisher *fredPtr = &fred;
  Fisher suzy = {"Suzy", 10, 0, 0};
  Fisher *suzyPtr = &suzy;

  Pond mainPond = {.numFish = 0};
  Pond *mainPtr = &mainPond;
  addFish(mainPtr, 4, "Sunfish");
  addFish(mainPtr, 25, "Pike");
  addFish(mainPtr, 20, "Bass");
  addFish(mainPtr, 30, "Perch");
  addFish(mainPtr, 14, "Sunfish");
  addFish(mainPtr, 15, "Pike");
  addFish(mainPtr, 9, "Pike");
  addFish(mainPtr, 12, "Bass");
  addFish(mainPtr, 5, "Sunfish");
  addFish(mainPtr, 12, "Sunfish");
  addFish(mainPtr, 10, "Bass");
  addFish(mainPtr, 2, "Bass");
  addFish(mainPtr, 16, "Perch");
  addFish(mainPtr, 30, "Sunfish");
  addFish(mainPtr, 7, "Perch");

  printf("Here are the fish in the pond:\n");
  listFish(mainPtr->fish, mainPtr->numFish);

  printf("\n\nFirst Fred attempts to catch 10 fish in the big pond ...\nFred's Fish: \n");
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);
  castLine(fredPtr, mainPtr);

  listFish(fredPtr->bucket, fredPtr->numFish);
  printf("\n\nSuzy now attempts to catch 10 fish in the big pond ...\nSuzy's fish:\n");

  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);
  castLine(suzyPtr, mainPtr);

  listFish(suzyPtr->bucket, suzyPtr->numFish);

  printf("\nHere is what is left of the pond ...\n");
  listFish(mainPtr->fish, mainPtr->numFish);

  giveAwayFish(suzyPtr, fredPtr, mainPtr);
  printf("\nThis is what is left after Suzy gives her fish to Fred: \n");
  printf("Fred's Fish: \n");
  listFish(fredPtr->bucket, fredPtr->numFish);

  printf("\nSuzy's Fish: \n");
  listFish(suzyPtr->bucket, suzyPtr->numFish);

  printf("\nHere are the fish in the pond:\n");
  listFish(mainPtr->fish, mainPtr->numFish);

}
