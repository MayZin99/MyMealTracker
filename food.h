#ifndef FOOD_H
#define FOOD_H

typedef struct {
    char type[10];        // MEAL or DRINK
    char mealTime[20];    // Breakfast/Lunch/Dinner/Snack/Coffee/Juice etc.
    char foodName[50];
    char location[50];
    char portion[10];     // Small/Medium/Large
    char date[11];        // YYYY-MM-DD
    char notes[100];
} Meal;

// Core features
void addMeal(Meal **list, int *count);
void viewMeals(Meal *list, int count);
void searchMeal(Meal *list, int count);
void deleteMeal(Meal **list, int *count);

// Save / Load
void saveToFile(Meal *list, int count, const char *filename);
int  loadFromFile(Meal **list, const char *filename);

// Summary
void showSummary(Meal *list, int count, int mode);
// mode = 1 → Weekly
// mode = 2 → Monthly
// mode = 3 → Yearly

#endif
