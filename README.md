A simple and practical Meal & Drink Tracking System written entirely in C.
This project was developed for the Advanced C Programming course to demonstrate mastery of:
- Dynamic memory allocation
- File handling
- Pointers & pointer-to-pointer
- Structures
- Modular programming
- User-interactive menu systems
This program helps users record their daily meals and drinks, view all records, search through entries, delete entries, and generate weekly, monthly, and yearly summaries.
>> Features
1. Add Meal / Drink Entry
Type: MEAL or DRINK
Meal time: Breakfast/Lunch/Dinner/Snack/Coffee/etc.
Food or drink name
Portion size (Small / Medium / Large)
Location (Home / Restaurant)
Date (YYYY-MM-DD)
Notes (optional)
2. View All Records
Displays all stored meals in a clean, tabular format.
3. Search Function
Search by:
food/drink name
date
location
type (MEAL / DRINK)
4. Delete an Entry
Remove any record by its index number.
5. Summary Reports
Generate summaries based on:
Weekly
Monthly
Yearly
Summary includes:
Total meals
Total drinks
Unique menu items
Frequency of each menu item
6. Save & Load Data (Persistent Storage)
Automatically loads past records from meals.txt on startup.
Saves all data to file on exit.
>> Technical Concepts Used (Advanced C)
This project demonstrates:
- Dynamic memory allocation:
- realloc(), free()
>> Pointer-to-pointer usage:
For dynamically resizing the meal list Structures:
- Custom Meal struct for storing related data
>> File handling:
- fopen(), fprintf(), fscanf(), fclose()
>> Modular programming:
main.c
food.c
food.h
>> Menu-driven user interface String processing:
- strstr(), strcmp(), strncmp(), strcasecmp(), strcpy()
