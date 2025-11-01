#include "Plant.h"
#include <iostream>
#include <iomanip>

Plant::Plant(const std::string& name, const std::string& species)
    : name(name), species(species), height(5.0), waterLevel(50.0), 
      healthLevel(100.0), age(0), isAlive(true) {
}

void Plant::water(double amount) {
    if (!isAlive) return;
    
    waterLevel += amount;
    if (waterLevel > 100.0) {
        waterLevel = 100.0;
    }
    
    updateHealth();
}

void Plant::grow(int days) {
    if (!isAlive) return;
    
    for (int i = 0; i < days; ++i) {
        age++;
        
        // Water evaporates over time
        waterLevel -= 5.0;
        if (waterLevel < 0) waterLevel = 0;
        
        // Plants grow when they have adequate water
        if (waterLevel > 20.0) {
            height += 0.5 + (waterLevel / 100.0);
        }
        
        updateHealth();
    }
}

void Plant::updateHealth() {
    if (!isAlive) return;
    
    // Health depends on water level
    if (waterLevel < 10.0) {
        healthLevel -= 10.0;
    } else if (waterLevel < 30.0) {
        healthLevel -= 2.0;
    } else if (waterLevel > 60.0) {
        healthLevel += 1.0;
        if (healthLevel > 100.0) healthLevel = 100.0;
    }
    
    // Check if plant dies
    if (healthLevel <= 0.0) {
        healthLevel = 0.0;
        isAlive = false;
    }
}

void Plant::printStatus() const {
    std::cout << "\n=== Plant Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Species: " << species << std::endl;
    std::cout << "Age: " << age << " days" << std::endl;
    std::cout << "Height: " << std::fixed << std::setprecision(2) << height << " cm" << std::endl;
    std::cout << "Water Level: " << std::fixed << std::setprecision(1) << waterLevel << "%" << std::endl;
    std::cout << "Health: " << std::fixed << std::setprecision(1) << healthLevel << "%" << std::endl;
    std::cout << "Status: " << (isAlive ? "Alive" : "Dead") << std::endl;
    std::cout << "===================" << std::endl;
}
