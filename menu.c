#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FOOD_NAME_LENGTH 100

time_t productExpirationDate;

struct FoodItem {
    char name[MAX_FOOD_NAME_LENGTH];
    int quantity;
    time_t expirationDate;
};

FoodItem *foodItems; // array to store food items
size_t foodItemsSize = 0; // size of the array

double getTemperature() {
    // TODO : get temperature from sensor
    return 0.0;
}

double getHumidity() {
    // TODO : get humidity from sensor
    return 0.0;
}

void monitorConditions() {
    printf("Monitoring temperature and humidity\n");

    double temperature = getTemperature();
    double humidity = getHumidity();

    printf("Temperature: %f\n", temperature);
    printf("Humidity: %f\n", humidity);
}

void addFoodItem() {
    printf("Adding food item\n");

    FoodItem foodItem;
    printf("Enter food name: ");
    getchar();
    fgets(foodItem.name, MAX_FOOD_NAME_LENGTH, stdin);

    printf("Enter quantity: ");
    scanf("%d", &foodItem.quantity);

    printf("Enter expiration date (YYYY-MM-DD): ");
    struct tm expirationDate = {};
    scanf("%d-%d-%d", &expirationDate.tm_year, &expirationDate.tm_mon, &expirationDate.tm_mday);

    // convert expiration date to seconds since epoch for further computations
    foodItem.expirationDate = mktime(&expirationDate);

    // resize the array to accommodate the new item
    foodItems = realloc(foodItems, (foodItemCount + 1) * sizeof(FoodItem));
    if (foodItems == NULL) {
        perror("Failed to allocate memory for food items");
        exit(EXIT_FAILURE);
    }

    // add food item to array
    foodItems[foodItemCount++] = foodItem;

    printf("Food item added\n");
    
}

void removeFoodItem() {
    printf("Removing food item\n");

    if (foodItemCount == 0) {
        printf("No food items to remove\n");
        return;
    }

    printf("Enter product name to remove: ");
    for (size_t i = 0; i < foodItemCount; i++) {
        printf("%zu. %s\n", i + 1, foodItems[i].productName);
    }

    int choice;
    printf("Enter your choice (number corresponding to food item): ");
    scanf("%d", &choice);

    if (choice >= 1 && (size_t)choice <= foodItemCount) {
        // Remove the selected item from the array
        for (size_t i = choice - 1; i < foodItemCount - 1; i++) {
            foodItems[i] = foodItems[i + 1];
        }

        // resize the array to remove the last element
        foodItems = realloc(foodItems, (foodItemCount - 1) * sizeof(FoodItem));
        if (foodItems == NULL) {
            perror("Failed to reallocate memory for food items");
            exit(EXIT_FAILURE);
        }

        foodItemCount--;

        printf("Food item removed successfully.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void displayFoodItems() {
    if (foodItemCount == 0) {
        printf("No food items to display\n");
        return;
    }
    printf("Food items:\n");
    for (size_t i = 0; i < foodItemCount; i++) {
        printf("%zu. %s\n", i + 1, foodItems[i].productName);
    }
}

void checkExpirationStatus() {
    printf("Checking expiration status\n");
    time_t currentTime; // in seconds since epoch
    time(&currentTime);

    // compare the current date with product expiration date
    if (currentTime > productExpirationDate) {
        printf("Product expired\n");
    } else {
        printf("Product not expired\n");
    }
}

// TODO : implement notifications
void sendNotification(const char* message) {
    printf("%s\n", message);
}

void setupNotifications() {
    printf("Setting up notifications\n");

    displayFoodItems();
    if (foodItemCount == 0) {
        printf("No food items to set up notifications for\n");
        return;
    }

    int choice;
    printf("Enter your choice (number corresponding to food item): ");
    scanf("%d", &choice);

    if (choice >= 1 && (size_t)choice <= foodItemCount) {
        const FoodItem* selectedFood = &foodItems[choice - 1];

        // Calculate time difference between the current time and expiration date
        time_t currentTime;
        time(&currentTime);
        double timeDifference = difftime(selectedFood->expirationDate, currentTime);

        // Set up notification based on expiration proximity (e.g., 1 day before)
        if (timeDifference <= 86400) { // 86400 seconds = 1 day
            char notificationMessage[256];
            snprintf(notificationMessage, sizeof(notificationMessage),
                     "Food item '%s' expires in 1 day.", selectedFood->productName);
            sendNotification(notificationMessage);
        } else {
            printf("Notifications are set up for items expiring within 1 day.\n");
        }
        // TODO : set up notifications for other time intervals
    } else {
        printf("Invalid choice.\n");
    }
}

int main() {
    int choice;
    do {
        printf("1. Monitor conditions\n");
        printf("2. Add food item\n");
        printf("3. Remove food item\n");
        printf("4. Display food items\n");
        printf("5. Check expiration status\n");
        printf("6. Setup notifications\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                monitorConditions();
                break;
            case 2:
                addFoodItem();
                break;
            case 3:
                removeFoodItem();
                break;
            case 4:
                displayFoodItems();
                break;
            case 5:
                checkExpirationStatus();
                break;
            case 6:
                setupNotifications();
                break;
            case 7:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);

    return 0;
}