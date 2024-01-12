#include <iostream>
#include <ctime>
#include <vector> // to store food items
#include <iomanip> // to format date
// include packages for temperature and humidity

/*-------------------------------------------------*/

time_t productExpirationDate; // or to initialize to current date (in seconds since epoch)

struct FoodItem {
    std::string productName;
    time_t expirationDate;
};
std::vector<FoodItem> foodItems; // vector to store food items

/*-------------------------------------------------*/

double getTemperature() {
    // TODO : get temperature from sensor
    return 0.0;
}

double getHumidity() {
    // TODO : get humidity from sensor
    return 0.0;
}

void monitorConditions() {
    std::cout << "Monitoring temperature and humidity\n";
    
    double temperature = getTemperature();
    double humidity = getHumidity();

    std::cout << "Temperature: " << temperature << " C\n";
    std::cout << "Humidity: " << humidity << " %\n";
}

/*-------------------------------------------------*/

void addFoodItem() {
    std::cout << "Adding food item\n";
    
    FoodItem foodItem;
    std::cout << "Enter product name: ";
    std::cin.ignore();
    std::getline(std::cin, foodItem.productName);

    std::cout << "Enter expiration date (YYYY-MM-DD): ";
    std::tm expirationDate = {};
    std::cin >> std::get_time(&expirationDate, "%Y-%m-%d");

    // convert expiration date to seconds since epoch for further computations
    productExpirationDate = std::mktime(&expirationDate);

    foodItems.push_back(foodItem); // add food item to vector

    std::cout << "Food item added\n";
}

/*-------------------------------------------------*/

void removeFoodItem() {
    std::cout << "Removing food item\n";
    
    if (foodItems.size() == 0) {
        std::cout << "No food items to remove\n";
        return;
    }

    std::cout << "Enter product name to remove: ";
    for (int i = 0; i < foodItems.size(); i++) {
        std::cout << i + 1 << ". " << foodItems[i].productName << "\n";
    }

    int choice;
    std::cout << "Enter your choice (number corresponding to food item): ";
    std::cin >> choice;

    if (choice >= 1 && static_cast<size_t>(choice) <= foodItems.size()) {
        // Remove the selected item from the vector
        foodItems.erase(foodItems.begin() + choice - 1);
        std::cout << "Food item removed successfully.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

/*-------------------------------------------------*/

void displayFoodItems() {
    if (foodItems.size() == 0) {
        std::cout << "No food items to display\n";
        return;
    }
    std::cout << "Food items:\n";
    for (int i = 0; i < foodItems.size(); i++) {
        std::cout << i + 1 << ". " << foodItems[i].productName << "\n";
    }
}

/*-------------------------------------------------*/

void checkExpirationStatus() {
    std::cout << "Checking expiration status\n";
    time_t currentTime; // in seconds since epoch
    time(&currentTime);

    // compare current date with product expiration date
    if (currentTime > productExpirationDate) {
        std::cout << "Product expired\n";
    } else {
        std::cout << "Product not expired\n";
    }
}

/*-------------------------------------------------*/

// TODO : implement notifications
class Notification {
    public:
        void sendNotification(const std::string &message) {
            std::cout << message << "\n";
        }
};

// TODO : see NotificationService class (Notification class is only a simulation)

void setupNotifications() {
    std::cout << "Setting up notifications\n";
    Notification notification;

    displayFoodItems();
    if (foodItems.size() == 0) {
        std::cout << "No food items to setup notifications for\n";
        return;
    }

    int choice;
    std::cout << "Enter your choice (number corresponding to food item): ";
    std::cin >> choice;

    if (choice >= 1 && static_cast<size_t>(choice) <= foodItems.size()) {

        const FoodItem& selectedFood = foodItems[choice - 1];

        // Calculate time difference between current time and expiration date
        std::time_t currentTime;
        std::time(&currentTime);
        double timeDifference = difftime(selectedFood.expirationDate, currentTime);

        // Set up notification based on expiration proximity (e.g., 1 day before)
        if (timeDifference <= 86400) {  // 86400 seconds = 1 day
            std::string notificationMessage = "Food item '" + selectedFood.productName + "' expires in 1 day.";
            notification.sendNotification(notificationMessage);
        } else {
            std::cout << "Notifications are set up for items expiring within 1 day.\n";
        }
        // TODO : implement other cases, and give the user the option to choose the time difference
    } else {
        std::cout << "Invalid choice.\n";
    }
}

/*-------------------------------------------------*/

int main() {
    std::cout << "Food expiration monitoring system\n";

    int choice = 0;
    while (choice != 6) {
        std::cout << "\n";
        std::cout << "1. Monitor temperature and humidity\n";
        std::cout << "2. Add food item\n";
        std::cout << "3. Remove food item\n";
        std::cout << "4. Check expiration status\n";
        std::cout << "5. Setup notifications\n";
        std::cout << "6. Quit\n";
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                monitorConditions();
                break;
            case 2:
                displayFoodItems();
                break;
            case 3:
                addFoodItem();
                break;
            case 4:
                removeFoodItem();
                break;
            case 5:
                checkExpirationStatus();
                break;
            case 6:
                setupNotifications();
                break;
            case 7:
                std::cout << "Exiting food expiration monitoring system.\n";
                break;
            default:
                std::cout << "Invalid choice. Please entre a number between 1 and 6.\n";
                break;
        }
    }

    return 0;
}