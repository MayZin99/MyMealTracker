#include <stdio.h>
#include <stdlib.h>
#include "food.h"

int main(){
    Meal *list=NULL;
    int count = loadFromFile(&list,"meals.txt");
    int choice,mode;

    do{
        printf("\n========= MYMEAL TRACKER =========\n");
        printf("1. Add Meal/Drink\n");
        printf("2. View All Records\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. View Summary (Weekly/Monthly/Yearly)\n");
        printf("6. Save & Exit\n");
        printf("==================================\nChoose: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: addMeal(&list,&count); break;
            case 2: viewMeals(list,count); break;
            case 3: searchMeal(list,count); break;
            case 4: deleteMeal(&list,&count); break;
            case 5:
                printf("\nSummary Type:\n1. Weekly\n2. Monthly\n3. Yearly\nChoose: ");
                scanf("%d",&mode);
                showSummary(list,count,mode);
                break;
            case 6:
                saveToFile(list,count,"meals.txt");
                printf("\nExiting... Bye!\n");
                break;
            default:
                printf("Invalid.\n");
        }
    }while(choice!=6);

    free(list);
    return 0;
}
