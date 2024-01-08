#include <iostream>
#include <fstream> // File Stream
#include <cstdlib> // Rand function

using namespace std;

// Constants
const string FOOD_FILE_NAME = "food_data.txt";
const int NUM_FOOD_ITEMS = 8;

const int MIN_YEAR_EXP = 2023;
const int MAX_YEAR_EXP = 2025;
const float MIN_TEMPERATURE = -20.0;
const float MAX_TEMPERATURE = +20.0;
const int MIN_HUMIDITY = 25.0;
const int MAX_HUMIDITY = 85.0;

// Return a random date string "YYYY-MM-DD"
string getRandomDate(int minYear, int maxYear)
{
    int year = rand() % (maxYear - minYear + 1) + minYear; // [minYear, maxYear]
    int month = rand() % 12 + 1;                           // [1, 12]
    int day = rand() % 28 + 1;                             // [1, 28]

    return (year < 1000 ? "0" : "") + to_string(year) + '-' +
           (month < 10 ? "0" : "") + to_string(month) + '-' +
           (day < 10 ? "0" : "") + to_string(day);
}

// Return a random float within a range
float getRandomFloat(float min, float max)
{
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

// Fill the text file with random food data
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
        cout << "Error opening file.\n";
    }
}

int main()
{
    // Init text file
    initRandomFoodItemsFile(FOOD_FILE_NAME, NUM_FOOD_ITEMS);

    return 0;
}