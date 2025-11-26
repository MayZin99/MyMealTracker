#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "food.h"

// ------------------------------------------
// ADD MEAL / DRINK ENTRY
// ------------------------------------------
void addMeal(Meal **list, int *count) {
    Meal m;

    printf("\nType (MEAL/DRINK): ");
    scanf(" %[^\n]", m.type);

    printf("Meal or Drink Name: ");
    scanf(" %[^\n]", m.foodName);

    printf("Meal Time (Breakfast/Lunch/Dinner/Snack/Coffee/Juice etc.): ");
    scanf(" %[^\n]", m.mealTime);

    printf("Location (Home/Restaurant): ");
    scanf(" %[^\n]", m.location);

    printf("Portion (Small/Medium/Large): ");
    scanf(" %[^\n]", m.portion);

    printf("Date (YYYY-MM-DD): ");
    scanf("%s", m.date);

    printf("Notes (optional): ");
    scanf(" %[^\n]", m.notes);

    Meal *temp = realloc(*list, (*count + 1) * sizeof(Meal));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }

    *list = temp;
    (*list)[*count] = m;
    (*count)++;

    printf("✔ Entry Added Successfully!\n");
}

// ------------------------------------------
// VIEW ALL MEALS
// ------------------------------------------
void viewMeals(Meal *list, int count) {
    if (count == 0) {
        printf("\nNo records to display.\n");
        return;
    }

    printf("\n%-4s %-10s %-12s %-22s %-12s %-10s %-30s\n",
           "No", "Type", "Date", "Meal/Drink Name", "Time", "Portion", "Notes");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-4d %-10s %-12s %-22s %-12s %-10s %-30s\n",
               i+1, list[i].type, list[i].date, list[i].foodName,
               list[i].mealTime, list[i].portion, list[i].notes);
    }
}

// ------------------------------------------
// SEARCH MEALS
// ------------------------------------------
void searchMeal(Meal *list, int count) {
    if (count == 0) {
        printf("\nNo entries to search.\n");
        return;
    }

    char keyword[50];
    printf("\nSearch by food name/date/location/type: ");
    scanf(" %[^\n]", keyword);

    int found = 0;
    printf("\n%-12s %-10s %-22s %-12s %-10s %-20s\n",
           "Date","Type","Meal/Drink","Time","Portion","Location");
    printf("---------------------------------------------------------------------\n");

    for (int i=0; i<count; i++) {
        if(strstr(list[i].foodName,keyword) || strstr(list[i].date,keyword) ||
           strstr(list[i].location,keyword) || strstr(list[i].type,keyword)) {

            printf("%-12s %-10s %-22s %-12s %-10s %-20s\n",
                   list[i].date,list[i].type,list[i].foodName,
                   list[i].mealTime,list[i].portion,list[i].location);
            found=1;
        }
    }

    if(!found) printf(" Nothing Found.\n");
}

// ------------------------------------------
// DELETE ENTRY
// ------------------------------------------
void deleteMeal(Meal **list, int *count) {
    if(*count == 0) {
        printf("\nNo meals to delete.\n");
        return;
    }

    int index;
    printf("\nEnter entry number to delete: ");
    scanf("%d",&index);

    if(index < 1 || index > *count) {
        printf("Invalid index.\n");
        return;
    }

    for(int i=index-1;i<*count-1;i++)
        (*list)[i] = (*list)[i+1];

    (*count)--;
    *list = realloc(*list, (*count)*sizeof(Meal));
    printf("✔ Entry Deleted.\n");
}

// ------------------------------------------
// SAVE TO FILE
// ------------------------------------------
void saveToFile(Meal *list, int count, const char *filename) {
    FILE *f = fopen(filename,"w");
    if(!f){ printf("File open failed.\n"); return; }

    for(int i=0;i<count;i++)
        fprintf(f,"%s,%s,%s,%s,%s,%s,%s\n",
                list[i].type,list[i].date,list[i].foodName,list[i].mealTime,
                list[i].portion,list[i].location,list[i].notes);

    fclose(f);
    printf("\n Data Saved.\n");
}

// ------------------------------------------
// LOAD FROM FILE
// ------------------------------------------
int loadFromFile(Meal **list, const char *filename) {
    FILE *f=fopen(filename,"r");
    if(!f){ printf("No previous data. Starting new.\n"); return 0; }

    Meal m; int count=0;
    *list=NULL;

    while(fscanf(f,"%9[^,],%10[^,],%49[^,],%19[^,],%9[^,],%49[^,],%99[^\n]\n",
                 m.type,m.date,m.foodName,m.mealTime,m.portion,m.location,m.notes) == 7)
    {
        *list=realloc(*list,(count+1)*sizeof(Meal));
        (*list)[count++] = m;
    }
    fclose(f);

    printf("📂 Loaded %d meal records.\n",count);
    return count;
}

// ------------------------------------------
// WEEKLY/MONTHLY/YEARLY SUMMARY
// ------------------------------------------
void showSummary(Meal *list, int count, int mode) {
    if (count == 0) {
        printf("\nNo data recorded yet.\n");
        return;
    }

    char target[11];
    printf("\nEnter date to summarize from (YYYY-MM-DD): ");
    scanf("%s", target);

    // Variables for summary
    int meals = 0, drinks = 0;
    char menus[200][50];         // store unique names
    int frequency[200] = {0};    // count occurrences
    int menuCount = 0;           // how many unique menus

    // ---- FILTER ENTRIES BY MODE ----
    for (int i = 0; i < count; i++) {
        int match = 0;

        if (mode == 1 && strncmp(list[i].date, target, 8) == 0) match = 1;  // weekly
        if (mode == 2 && strncmp(list[i].date, target, 7) == 0) match = 1;  // monthly
        if (mode == 3 && strncmp(list[i].date, target, 4) == 0) match = 1;  // yearly

        if (!match) continue;

        // Count meals & drinks
        if (strcasecmp(list[i].type, "DRINK") == 0) drinks++;
        else meals++;

        // Track frequency of menu items
        int found = 0;
        for (int j = 0; j < menuCount; j++) {
            if (strcasecmp(menus[j], list[i].foodName) == 0) {
                frequency[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(menus[menuCount], list[i].foodName);
            frequency[menuCount] = 1;
            menuCount++;
        }
    }

    // ---- DISPLAY RESULT ----

    printf("\n=============== SUMMARY ===============\n");
    if (mode == 1) printf(" WEEK SUMMARY\n");
    if (mode == 2) printf("MONTH SUMMARY\n");
    if (mode == 3) printf(" YEAR SUMMARY\n");

    printf("---------------------------------------\n");
    printf("Total Meals : %d\n", meals);
    printf("Total Drinks: %d\n", drinks);
    printf("Unique Menu Items: %d\n\n", menuCount);

    printf(" MENU FREQUENCY\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%-20s × %d times\n", menus[i], frequency[i]);
    }
    printf("=======================================\n\n");
}
