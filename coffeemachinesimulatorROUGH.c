#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// Defining constants for ingredients and prices
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define ESPRESSO_MILK 0
#define ESPRESSO_CHOCOLATE 0
#define ESPRESSO_PRICE 3.5

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
#define CAPPUCCINO_CHOCOLATE 0
#define CAPPUCCINO_PRICE 4.5

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_CHOCOLATE 30
#define MOCHA_PRICE 5.5

#define ADMIN_PASSWORD "1234taha"
#define LOW_THRESHOLD_BEANS 10
#define LOW_THRESHOLD_WATER 50
#define LOW_THRESHOLD_MILK 170
#define LOW_THRESHOLD_CHOCOLATE 40

// total quantity for ingredients 
float total_amount = 0.0;
float beans_quantity = 999.0;
float water_quantity = 999.0;
float milk_quantity = 999.0;
float chocolate_quantity = 999.0;


// ALL Function declarations
void orderCoffee();
void adminMode();
void displayIngredients();
void replenishIngredients();
void changeCoffeePrice();
void checkThresholds();

int main() {
    int choice;

    while (1) {
        printf("\nWelcome to Taha's Coffee Machine\n");
        printf("1. Order a coffee type\n");
        printf("2. Admin mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                orderCoffee();
                break;
            case 2:
                adminMode();
                break;
            case 3:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


void orderCoffee() {
    int coffee_choice;
    char confirmation;
    float payment = 0;
    float price = 0;

    while (1) {
        printf("Select a coffee type:\n");
        printf("1. Press 1 for Espresso - AED %.2f\n", ESPRESSO_PRICE);
        printf("2. Press 2 for Cappuccino - AED %.2f\n", CAPPUCCINO_PRICE);
        printf("3. Press 3 for Mocha - AED %.2f\n", MOCHA_PRICE);
        printf("0. Exit\n");
        printf("Select your coffee: ");
        scanf("%d", &coffee_choice);
        
        if(coffee_choice == 0){
            return;
        }

        switch (coffee_choice) {
            case 1:
                if (beans_quantity >= ESPRESSO_BEANS && water_quantity >= ESPRESSO_WATER) {
                    price = ESPRESSO_PRICE;
                    printf("You selected Espresso. Price: AED %.2f\n", price);
                    
                } else {
                    printf("Espresso Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            case 2:
                if (beans_quantity >= CAPPUCCINO_BEANS && water_quantity >= CAPPUCCINO_WATER && milk_quantity >= CAPPUCCINO_MILK) {
                    price = CAPPUCCINO_PRICE;
                    
                    printf("You selected Cappuccino. Price: AED %.2f\n", price);
                } else {
                    printf("Cappuccino Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            case 3:
                if (beans_quantity >= MOCHA_BEANS && water_quantity >= MOCHA_WATER && milk_quantity >= MOCHA_MILK && chocolate_quantity >= MOCHA_CHOCOLATE) {
                    price = MOCHA_PRICE;
                    printf("You selected Mocha. Price: AED %.2f\n", price);
                } else {
                    printf("Mocha Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        float coin;
        while (payment < price) {
            printf("Insert coin (1 or 0.5): ");
            scanf("%f", &coin);
            if (coin == 1.0 || coin == 0.5) {
                payment += coin;
            } else {
                printf("Invalid coin. Please collect your coin and insert a valid one.\n");
            }
        }

        total_amount += price;
        printf("You bought a cup of coffee for AED %.2f. You paid AED %.2f. Change: AED %.2f\n", price, payment, payment - price);

        // Updating the ingredient quantities
        beans_quantity -= (coffee_choice == 1) ? ESPRESSO_BEANS : (coffee_choice == 2) ? CAPPUCCINO_BEANS : MOCHA_BEANS;
        water_quantity -= (coffee_choice == 1) ? ESPRESSO_WATER : (coffee_choice == 2) ? CAPPUCCINO_WATER : MOCHA_WATER;
        milk_quantity -= (coffee_choice == 2) ? CAPPUCCINO_MILK : (coffee_choice == 3) ? MOCHA_MILK : 0;
        chocolate_quantity -= (coffee_choice == 3) ? MOCHA_CHOCOLATE : 0;

        checkThresholds();
    }
}

void adminMode() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) != 0) {
        printf("Incorrect password. Exiting admin mode.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Display ingredients and total sales\n");
        printf("2. Replenish ingredients\n");
        printf("3. Change coffee price\n");
        printf("0. Exit admin mode\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayIngredients();
                break;
            case 2:
                replenishIngredients();
                break;
            case 3:
                changeCoffeePrice();
                break;
            case 0:
                printf("Exiting admin mode.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void displayIngredients() {
    printf("\nIngredients:\n");
    printf("Beans: %f\n", beans_quantity);
    printf("Water: %f\n", water_quantity);
    printf("Milk: %f\n", milk_quantity);
    printf("Chocolate: %f\n", chocolate_quantity);
    printf("Total sales: AED %.2f\n", total_amount);

    char reset;
    printf("Do you want to reset total sales? (y/n): ");
    scanf(" %c", &reset);

    if (reset == 'y') {
        total_amount = 0;
        printf("Total sales reset to zero. Please collect the money from the machine.\n");
    }
}

void replenishIngredients() {
    srand(time(NULL));
    beans_quantity = rand() % 50 + 30;
    water_quantity = rand() % 150 + 100;
    milk_quantity = rand() % 600 + 500;
    chocolate_quantity = rand() % 150 + 90;
    printf("Ingredients replenished.\n");
}

void changeCoffeePrice() {
    int coffee_choice;
    float new_price;

    printf("Select coffee type to change price:\n");
    printf("1. Espresso\n");
    printf("2. Cappuccino\n");
    printf("3. Mocha\n");
    printf("Enter your choice: ");
    scanf("%d", &coffee_choice);

    printf("Enter new price: ");
    scanf("%f", &new_price);

    switch (coffee_choice) {
        case 1:
            new_price = ESPRESSO_PRICE;
            break;
        case 2:
            new_price = CAPPUCCINO_PRICE;
            break;
        case 3:
            new_price = MOCHA_PRICE;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void checkThresholds() {
    if (beans_quantity <= LOW_THRESHOLD_BEANS) {
        printf("Low beans threshold reached. Please replenish.\n");
    }
    if (water_quantity <= LOW_THRESHOLD_WATER) {
        printf("Low water threshold reached. Please replenish.\n");
    }
    if (milk_quantity <= LOW_THRESHOLD_MILK) {
        printf("Low milk threshold reached. Please replenish.\n");
    }
    if (chocolate_quantity <= LOW_THRESHOLD_CHOCOLATE) {
        printf("Low chocolate threshold reached. Please replenish.\n");
    }
}