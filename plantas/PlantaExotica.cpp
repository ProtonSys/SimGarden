//
// Created by Celso Jordão on 01/11/2025.
//

#include "PlantaExotica.h"
#include "../jardim/Jardim.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

PlantaExotica::PlantaExotica() : Planta(Beleza::NEUTRA), comportamento(0) {
    // Random initial beauty
    int belezaRandom = RandomGenerator::getInt(0, 2);
    switch (belezaRandom) {
        case 0: beleza = Beleza::FEIA; break;
        case 1: beleza = Beleza::NEUTRA; break;
        case 2: beleza = Beleza::BONITA; break;
    }

    // Random initial behavior pattern
    comportamento = RandomGenerator::getInt(0, 2);

    // Random initial resources
    aguaAcumulada = RandomGenerator::getInt(5, 30);
    nutrientesAcumulados = RandomGenerator::getInt(5, 30);
}

void PlantaExotica::avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) {
    instantesVida++;

    // Occasionally change behavior (10% chance each turn)
    if (RandomGenerator::getBool(0.1)) {
        comportamento = RandomGenerator::getInt(0, 2);
    }

    // Behavior depends on current mode
    switch (comportamento) {
        case 0:  // Cacto-like behavior
            {
                int aguaSolo = pos.getAgua();
                int aguaAbsorver = (aguaSolo * 20) / 100;  // 20% absorption
                absorveDoSolo(pos, aguaAbsorver, 3);
            }
            break;

        case 1:  // Roseira-like behavior
            aguaAcumulada -= 3;
            nutrientesAcumulados -= 3;
            absorveDoSolo(pos, 6, 10);
            break;

        case 2:  // Erva-like behavior
            absorveDoSolo(pos, 2, 2);
            break;
    }

    // Random multiplication chance (5% if nutrients > 80)
    if (nutrientesAcumulados > 80 && RandomGenerator::getBool(0.05)) {
        int linhaViz, colViz;
        if (jardim.temVizinhoVazio(linha, col, linhaViz, colViz)) {
            // TODO: Add multiplication logic
            // jardim.adicionaPlanta(linhaViz, colViz, new PlantaExotica());
        }
    }
}

bool PlantaExotica::deveMorrer() const {
    // Dies if resources are critically low or too high
    return (aguaAcumulada < 0 || nutrientesAcumulados < 0 ||
            aguaAcumulada > 200 || nutrientesAcumulados > 200 ||
            instantesVida > 100);
}

void PlantaExotica::aoMorrer(Posicao& pos) {
    // Returns some nutrients to soil on death
    int nutrientesSolo = pos.getNutrientes();
    pos.setNutrientes(nutrientesSolo + nutrientesAcumulados / 2);
}