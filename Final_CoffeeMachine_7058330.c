#include <stdio.h> // headers 
#include <stdlib.h>
#include <time.h>
#include <string.h>

// we define the constants first as per the given table
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define ESPRESSO_MILK 0
#define ESPRESSO_CHOCOLATE 0

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
#define CAPPUCCINO_CHOCOLATE 0

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_CHOCOLATE 30

#define ADMIN_PASSWORD "1234taha"
#define LOW_THRESHOLD_BEANS 10
#define LOW_THRESHOLD_WATER 50
#define LOW_THRESHOLD_MILK 170
#define LOW_THRESHOLD_CHOCOLATE 40

// we assign starting ingredient quantities
float total_amount = 0.0;
float beans_quantity = 999.0;
float water_quantity = 999.0;
float milk_quantity = 999.0;
float chocolate_quantity = 999.0;

// We add coffee prices as float variable so they can be updated later
float ESPRESSO_PRICE = 3.5;
float CAPPUCCINO_PRICE = 4.5;
float MOCHA_PRICE = 5.5;

// all the functions for the code are declared
void OrderACoffee();
void adminMode();
void displayIngredients();
void replenishIngredients();
void changeCoffeePrice();
void checkThresholds();

// start of main code

int main() {
    int choice;

    while (1) {
        printf("\nWelcome to Taha's Coffee Machine\n"); //menu driven interface 
        printf("What would you like to do today?\n");
        printf("1. Order a delicious coffee\n");
        printf("2. Access Admin mode\n");
        printf("3. Exit the coffee machine\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                OrderACoffee();
                break;
            case 2:
                adminMode();
                break;
            case 3:
                printf("Thank you for using Taha's Coffee Machine! Have a great day!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
// This functions displays all available coffee types with prices and if their ingredients are available, lets the user choose one, confirm his choice and pay for their coffee
void OrderACoffee() {
    int coffee_choice;
    char confirmation;
    float payment; 
    float price = 0;

    while (1) {
        payment = 0; // we reset the payment so previous coins are not counted repeatedly
        printf("Please select your coffee:\n");
        printf("1. Press 1 for Espresso - AED %.2f\n", ESPRESSO_PRICE);
        printf("2. Press 2 for Cappuccino - AED %.2f\n", CAPPUCCINO_PRICE);
        printf("3. Press 3 for Mocha - AED %.2f\n", MOCHA_PRICE);
        printf("0. Exit to main menu\n");
        printf("Select your coffee: ");
        scanf("%d", &coffee_choice);
        
        if (coffee_choice == 0) {
            return;
        }
        // each case checks if the ingredients are sufficient to make the coffee
        switch (coffee_choice) {
            case 1:
                if (beans_quantity >= ESPRESSO_BEANS && water_quantity >= ESPRESSO_WATER) {
                    price = ESPRESSO_PRICE;
                    printf("Great choice! You selected Espresso. Price: AED %.2f\n", price);
                } else {
                    printf("Sorry, Espresso Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            case 2:
                if (beans_quantity >= CAPPUCCINO_BEANS && water_quantity >= CAPPUCCINO_WATER && milk_quantity >= CAPPUCCINO_MILK) {
                    price = CAPPUCCINO_PRICE;
                    printf("Great choice! You selected Cappuccino. Price: AED %.2f\n", price);
                } else {
                    printf("Sorry, Cappuccino Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            case 3:
                if (beans_quantity >= MOCHA_BEANS && water_quantity >= MOCHA_WATER && milk_quantity >= MOCHA_MILK && chocolate_quantity >= MOCHA_CHOCOLATE) {
                    price = MOCHA_PRICE;
                    printf("Great choice! You selected Mocha. Price: AED %.2f\n", price);
                } else {
                    printf("Sorry, Mocha Unavailable due to temporarily insufficient ingredients.\n");
                    continue;
                }
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // segment to let user confirm his choice
        printf("Do you want to confirm your order? (y/n): ");
        scanf(" %c", &confirmation);
        if (confirmation != 'y') {
            printf("Order not confirmed. Returning to coffee selection.\n");
            continue; // Goes back to the coffee selection menu if not confirmed
        }
        // segment for user to pay for coffee with coins where change is also given back
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
        //updates the total amount of sales for all coffee for admin mode
        total_amount += price;
        printf("You bought a cup of coffee for AED %.2f. You paid AED %.2f. Change: AED %.2f. Enjoy!\n", price, payment, payment - price);

        // We update the ingredient quantities as per what was used 
        beans_quantity -= (coffee_choice == 1) ? ESPRESSO_BEANS : (coffee_choice == 2) ? CAPPUCCINO_BEANS : MOCHA_BEANS;
        water_quantity -= (coffee_choice == 1) ? ESPRESSO_WATER : (coffee_choice == 2) ? CAPPUCCINO_WATER : MOCHA_WATER;
        milk_quantity -= (coffee_choice == 2) ? CAPPUCCINO_MILK : (coffee_choice == 3) ? MOCHA_MILK : 0;
        chocolate_quantity -= (coffee_choice == 3) ? MOCHA_CHOCOLATE : 0;
        // function added to check the ingredient quantity and display if less
        checkThresholds();
    }
}

//This function enables admin mode given the password is inputed correctly
void adminMode() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) != 0) {
        printf("Incorrect password. Exiting admin mode.\n");
        return;
    }
    // menu driven interface to choose from admin commands and exit if needed
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

// This function displays all current ingredient quantity values and total saled, also gives the admin the option to reset saled if needed
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

//This function resplenishes ALL ingredients using a random function where it replenishes enough for atleast two coffee's each before running low
void replenishIngredients() {
    srand(time(NULL));
    beans_quantity = rand() % 50 + 30;
    water_quantity = rand() % 150 + 100;
    milk_quantity = rand() % 600 + 500;
    chocolate_quantity = rand() % 150 + 90;
    printf("Ingredients replenished.\n");
}

//This function changes the coffee price to a new one set by the admin
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
            ESPRESSO_PRICE = new_price;
            break;
        case 2:
            CAPPUCCINO_PRICE = new_price;
            break;
        case 3:
            MOCHA_PRICE = new_price;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

//This function checks each threshold to let operator know the ingredients are running low
void checkThresholds() {
    if (beans_quantity <= LOW_THRESHOLD_BEANS) {
        printf("Low beans threshold reached. Please replenish ASAP.\n");
    }
    if (water_quantity <= LOW_THRESHOLD_WATER) {
        printf("Low water threshold reached. Please replenish ASAP.\n");
    }
    if (milk_quantity <= LOW_THRESHOLD_MILK) {
        printf("Low milk threshold reached. Please replenish ASAP.\n");
    }
    if (chocolate_quantity <= LOW_THRESHOLD_CHOCOLATE) {
        printf("Low chocolate threshold reached. Please replenish ASAP.\n");
    }
}