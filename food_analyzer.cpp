#include <iostream>
#include <fstream> // File Stream
#include <ctime>   // Time function
#include <vector>
#include <sstream> // String Stream

using namespace std;

// Find current date formatted as int YYYYMMDD
int getCurrentDate()
{
    time_t t;
    // Year, month, day in human readable form
    struct tm *tm_info;

    // Store number of seconds since 1970 Jan 01 value in variable
    time(&t);
    // Convert the current time (in UTC) to the local time zone
    tm_info = localtime(&t);

    int currentYear = tm_info->tm_year + 1900; // tm_year: years since 1900
    int currentMonth = tm_info->tm_mon + 1;    // tm_mon: months [0, 11]
    int currentDay = tm_info->tm_mday;         // tm_mday: day of the month

    // Return current date YYYYMMDD as int
    return currentYear * 10'000 + currentMonth * 100 + currentDay;
}

// Constants
const string FOOD_FILE_NAME = "food_data.txt";
const int CURRENT_DATE = getCurrentDate();

// Define food item
struct FoodItem
{
    string productName;
    string expirationDate; // YYYY-MM-DD
    float temperature;     // Celsius
    float humidity;        // %

    // Convert expirationDate from string ("YYYY-MM-DD") to an int (YYYYMMDD)
    int getExpirationDateAsInt() const
    {
        int year, month, day;
        sscanf(expirationDate.c_str(), "%d-%d-%d", &year, &month, &day);

        return year * 10'000 + month * 100 + day;
    }

    // Print method for the struct
    void print() const
    {
        cout << productName << " { " << expirationDate << ", " << temperature << ", " << humidity << " }\n";
    }
};

// Init food items vec from text file data
void populateFoodItemsVec(const string &fromFileName, vector<FoodItem> &toFoodItemsVec)
{
    // Input File Stream
    ifstream file(fromFileName);

    if (file.is_open())
    {
        string line;

        // Iterate rows to get food data
        while (getline(file, line))
        {
            FoodItem foodItem;

            // Parse the line to extract attributes with string stream
            stringstream ss(line);
            // (Use getline for string spaces, >> for numerical attributes)
            getline(ss, foodItem.productName, ',');
            getline(ss, foodItem.expirationDate, ',');
            ss >> foodItem.temperature;
            // Ignore the comma separator
            ss.ignore();
            ss >> foodItem.humidity;

            // Add the food item to the vector
            toFoodItemsVec.push_back(foodItem);
        }

        file.close();
        cout << "Food items successfully loaded from '" << fromFileName << "'.\n";
    }
    else
    {
        cout << "Error opening file '" << fromFileName << "'.\n";
    }
}

// Print vector of food items
void printFoodItemsVec(const vector<FoodItem> &foodItemsVec)
{
    for (const auto &foodItem : foodItemsVec)
    {
        foodItem.print();
    }
}

// Check if the food is expired
bool isFoodExpired(const FoodItem &foodItem)
{
    // Get the expiration date as an integer in the format YYYYMMDD
    int expirationDateInt = foodItem.getExpirationDateAsInt();
    // Compare with the current date
    return expirationDateInt < CURRENT_DATE;
}

int main()
{
    // Populate vector
    vector<FoodItem> foodItemsVec;
    populateFoodItemsVec(FOOD_FILE_NAME, foodItemsVec);
    cout << "\n";

    // Print all food items
    cout << "- FOOD ITEMS:\n";
    printFoodItemsVec(foodItemsVec);
    cout << "\n";

    // Print expiration status of all food items
    cout << "- EXPIRATION STATUS:\n";
    for (const auto &foodItem : foodItemsVec)
    {
        cout << foodItem.productName << ", " << foodItem.expirationDate << "  ->  ";

        if (isFoodExpired(foodItem))
        {
            cout << "Expired\n";
        }
        else
        {
            cout << "Good\n";
        }
    }

    return 0;
}