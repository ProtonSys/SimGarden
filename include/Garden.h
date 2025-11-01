#ifndef GARDEN_H
#define GARDEN_H

#include "Plant.h"
#include <vector>
#include <memory>
#include <string>

class Garden {
private:
    std::string name;
    std::vector<std::shared_ptr<Plant>> plants;
    int currentDay;

public:
    Garden(const std::string& name);
    
    void addPlant(const std::string& plantName, const std::string& species);
    void waterAllPlants(double amount);
    void waterPlant(const std::string& plantName, double amount);
    void simulateDays(int days);
    
    void printGardenStatus() const;
    int getPlantCount() const { return plants.size(); }
    int getCurrentDay() const { return currentDay; }
    std::shared_ptr<Plant> getPlant(const std::string& plantName);
};

#endif // GARDEN_H
