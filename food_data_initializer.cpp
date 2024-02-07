#include <iostream>
#include <fstream> // File Stream
#include <cstdlib> // Rand function

using namespace std;

// Constants
const string FOOD_FILE_NAME = "food_data.txt";
const int NUM_FOOD_ITEMS = 100;

const int MIN_YEAR_EXP = 2023;
const int MAX_YEAR_EXP = 2025;

// Return a random date string "DD-MMM-YY", with month as literal
string getRandomDate(int minYear, int maxYear)
{
    string month_string;
    int year = rand() % (maxYear - minYear + 1) + minYear; // [minYear, maxYear]
    int month = rand() % 12 + 1;                           // [1, 12]
    int day = rand() % 28 + 1;                             // [1, 28]
    
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
    }
    
    return (day < 10 ? "0" : "") + to_string(day) + '-' + 
           month_string + '-' + 
           (year < 1000 ? "0" : "") + to_string(year);
}

// Return a random float within a range
float getRandomFloat(float min, float max)
{
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

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
            productName = "Item" + to_string(i + 1);
            expirationDate = getRandomDate(MIN_YEAR_EXP, MAX_YEAR_EXP);
            temperature = getRandomFloat(MIN_TEMPERATURE, MAX_TEMPERATURE);
            humidity = getRandomFloat(MIN_HUMIDITY, MAX_HUMIDITY);

            // Write attributes to file
            file << productName << ',' << expirationDate << ',' << temperature << ',' << humidity << '\n';
        }

        file.close();
        cout << "Food items successfully written to '" << fileName << "'.\n";
    }
    else
    {
        cout << "Error opening file '" << fileName << "'.\n";
    }
}

int main()
{
    // Init text file
    initRandomFoodItemsFile(FOOD_FILE_NAME, NUM_FOOD_ITEMS);

    return 0;
}
