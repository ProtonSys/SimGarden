#include "Garden.h"
#include <iostream>
#include <string>
#include <limits>

void printMenu() {
    std::cout << "\n=== Garden Simulator Menu ===" << std::endl;
    std::cout << "1. Add a plant" << std::endl;
    std::cout << "2. Water all plants" << std::endl;
    std::cout << "3. Water specific plant" << std::endl;
    std::cout << "4. Simulate days" << std::endl;
    std::cout << "5. View garden status" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Welcome to Garden Simulator!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    std::string gardenName;
    std::cout << "\nEnter your garden name: ";
    std::getline(std::cin, gardenName);
    
    Garden garden(gardenName);
    std::cout << "\nGarden '" << gardenName << "' created successfully!" << std::endl;
    
    bool running = true;
    while (running) {
        printMenu();
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            clearInputBuffer();
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                std::string plantName, species;
                std::cout << "Enter plant name: ";
                std::getline(std::cin, plantName);
                std::cout << "Enter plant species: ";
                std::getline(std::cin, species);
                garden.addPlant(plantName, species);
                break;
            }
            case 2: {
                double amount;
                std::cout << "Enter water amount (0-100%): ";
                std::cin >> amount;
                if (std::cin.fail() || amount < 0 || amount > 100) {
                    clearInputBuffer();
                    std::cout << "Invalid amount. Please enter a value between 0 and 100." << std::endl;
                } else {
                    clearInputBuffer();
                    garden.waterAllPlants(amount);
                }
                break;
            }
            case 3: {
                std::string plantName;
                double amount;
                std::cout << "Enter plant name: ";
                std::getline(std::cin, plantName);
                std::cout << "Enter water amount (0-100%): ";
                std::cin >> amount;
                if (std::cin.fail() || amount < 0 || amount > 100) {
                    clearInputBuffer();
                    std::cout << "Invalid amount. Please enter a value between 0 and 100." << std::endl;
                } else {
                    clearInputBuffer();
                    garden.waterPlant(plantName, amount);
                }
                break;
            }
            case 4: {
                int days;
                std::cout << "Enter number of days to simulate: ";
                std::cin >> days;
                if (std::cin.fail() || days < 1) {
                    clearInputBuffer();
                    std::cout << "Invalid number of days. Please enter a positive number." << std::endl;
                } else {
                    clearInputBuffer();
                    garden.simulateDays(days);
                }
                break;
            }
            case 5: {
                garden.printGardenStatus();
                break;
            }
            case 6: {
                std::cout << "\nThank you for using Garden Simulator!" << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << "Invalid choice. Please select 1-6." << std::endl;
                break;
        }
    }
    
    return 0;
}
