#include "Garden.h"
#include <iostream>
#include <algorithm>

Garden::Garden(const std::string& name) : name(name), currentDay(0) {
}

void Garden::addPlant(const std::string& plantName, const std::string& species) {
    auto plant = std::make_shared<Plant>(plantName, species);
    plants.push_back(plant);
    std::cout << "Added plant '" << plantName << "' (species: " << species << ") to the garden." << std::endl;
}

void Garden::waterAllPlants(double amount) {
    std::cout << "\nWatering all plants with " << amount << "% water..." << std::endl;
    for (auto& plant : plants) {
        plant->water(amount);
    }
}

void Garden::waterPlant(const std::string& plantName, double amount) {
    auto plant = getPlant(plantName);
    if (plant) {
        std::cout << "Watering '" << plantName << "' with " << amount << "% water..." << std::endl;
        plant->water(amount);
    } else {
        std::cout << "Plant '" << plantName << "' not found in the garden." << std::endl;
    }
}

void Garden::simulateDays(int days) {
    std::cout << "\nSimulating " << days << " day(s)..." << std::endl;
    for (auto& plant : plants) {
        plant->grow(days);
    }
    currentDay += days;
    std::cout << "Current day: " << currentDay << std::endl;
}

void Garden::printGardenStatus() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Garden: " << name << std::endl;
    std::cout << "Current Day: " << currentDay << std::endl;
    std::cout << "Total Plants: " << plants.size() << std::endl;
    std::cout << "========================================" << std::endl;
    
    int aliveCount = 0;
    for (const auto& plant : plants) {
        if (plant->alive()) aliveCount++;
        plant->printStatus();
    }
    
    std::cout << "\nAlive: " << aliveCount << " / Dead: " << (plants.size() - aliveCount) << std::endl;
    std::cout << "========================================\n" << std::endl;
}

std::shared_ptr<Plant> Garden::getPlant(const std::string& plantName) {
    auto it = std::find_if(plants.begin(), plants.end(),
        [&plantName](const std::shared_ptr<Plant>& p) {
            return p->getName() == plantName;
        });
    
    if (it != plants.end()) {
        return *it;
    }
    return nullptr;
}
