#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Constants
const string FOOD_FILE_NAME = "food_data.txt";
const int MAX_FOOD_ITEMS = 100;

const int MIN_YEAR_EXP = 2023;
const int MAX_YEAR_EXP = 2025;

// Struct to define a food item
struct FoodItem {
    string name;
    int quantity;
    string expiration_date;

    // Gets the month input "02" and returns "Feb"
    string convertMonthToString(int month) {
        string month_string;

        switch(month) {
            case 1:
                month_string = "Jan";
                break;
            case 2:
                month_string = "Feb";
                break;
            case 3:
                month_string = "Mar";
                break;
            case 4:
                month_string = "Apr";
                break;
            case 5:
                month_string = "May";
                break;
            case 6:
                month_string = "Jun";
                break;
            case 7:
                month_string = "Jul";
                break;
            case 8:
                month_string = "Aug";
                break;
            case 9:
                month_string = "Sep";
                break;
            case 10:
                month_string = "Oct";
                break;
            case 11:
                month_string = "Nov";
                break;
            case 12:
                month_string = "Dec";
                break;
            default:
                month_string = "Invalid Month";
                break;
        }

        return month_string;
    }

    string formatFoodItem() {
        string formattedName = name.substr(0, 5);

        if (formattedName.size() < 5) {
            formattedName.append(5 - formattedName.size(), ' '); // Pad with spaces if name is shorter than 5 characters
        }
        
        string formattedQuantity = (quantity < 10 ? "0" : "") + to_string(quantity);
        string formattedExpirationDate = expiration_date.substr(0, 2) + "-" +
                                            convertMonthToString(stoi(expiration_date.substr(3, 2))) + "-" +
                                            expiration_date.substr(8, 2);
        
        return formattedName + ": q" + formattedQuantity + ", " + formattedExpirationDate;
    }
};

// Return a random date string "DD-MMM-YY", with month as literal
string getRandomDate(int minYear, int maxYear)
{
    string month_string;
    int year = rand() % (maxYear - minYear + 1) + minYear; // [minYear, maxYear]
    int month = rand() % 12 + 1;                           // [1, 12]
    int day = rand() % 28 + 1;                             // [1, 28]
    
    return (day < 10 ? "0" : "") + to_string(day) + '-' + 
           (month < 10 ? "0" : "") + to_string(month) + '-' + 
           (year < 1000 ? "0" : "") + to_string(year);
}

// Return a random float within a range
float getRandomFloat(float min, float max)
{
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

/*
// Fill a text file with food attributes randomly determined, one row for each food item
void initRandomFoodItemsFile(const string &fileName, int numItems)
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Open file in writing mode
    ofstream file(fileName);

    if (file.is_open())
    {
        // Generate random food attributes and print them to the text file
        string productName, expirationDate;
        float temperature, humidity;

        for (int i = 0; i < numItems; i++)
        {
            productName = "Fd" + to_string((i + 1) < 10 ? "0" : "") + to_string(i + 1);
            expirationDate = getRandomDate(MIN_YEAR_EXP, MAX_YEAR_EXP);

            // Write attributes to file
            file << productName << ',' << expirationDate << '\n';
        }

        file.close();
        cout << "Food items successfully written to '" << fileName << "'.\n";
    }
    else
    {
        cout << "Error opening file '" << fileName << "'.\n";
    }
}
*/

// Populates the food items vector with random data
void populateFoodItemsVector(vector<FoodItem>& foodItems) {
    for (int i = 0; i < MAX_FOOD_ITEMS; i++)
    {
        FoodItem fd;
        fd.name = "Fd" + to_string((i + 1) < 10 ? '0' : 0) + to_string(i + 1);
        fd.quantity = rand() % 100 + 1;  // Random quantity between 1 and 100

        // Generate random expiration date
        fd.expiration_date = getRandomDate(MIN_YEAR_EXP, MAX_YEAR_EXP);

        // Add the FoodItem to the vector
        foodItems.push_back(fd);
    }
}

void printAllFoodItems(vector<FoodItem>& foodItems) {
    for (FoodItem& item : foodItems) {
        cout << item.formatFoodItem() << endl;
    }
}

int main()
{
    // Init text file
    //initRandomFoodItemsFile(FOOD_FILE_NAME, MAX_FOOD_ITEMS);

    // Test
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    vector<FoodItem> foodItems;
    
    populateFoodItemsVector(foodItems);
    printAllFoodItems(foodItems);

    return 0;
}
