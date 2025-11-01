#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
private:
    std::string name;
    std::string species;
    double height;          // in cm
    double waterLevel;      // percentage (0-100)
    double healthLevel;     // percentage (0-100)
    int age;                // in days
    bool isAlive;

public:
    Plant(const std::string& name, const std::string& species);
    
    void water(double amount);
    void grow(int days);
    void updateHealth();
    
    // Getters
    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    double getHeight() const { return height; }
    double getWaterLevel() const { return waterLevel; }
    double getHealthLevel() const { return healthLevel; }
    int getAge() const { return age; }
    bool alive() const { return isAlive; }
    
    void printStatus() const;
};

#endif // PLANT_H
