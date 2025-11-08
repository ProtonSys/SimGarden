//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_PLANTAEXOTICA_H
#define SIMGARDEN_PLANTAEXOTICA_H

#include "Planta.h"

/**
 * @brief PlantaExotica - Special plant with unpredictable behavior
 *
 * - Random initial beauty (can be any type)
 * - Variable absorption rates
 * - Unpredictable death conditions
 * - May change behavior over time
 */
class PlantaExotica : public Planta {
private:
    int comportamento;  // 0=Cacto-like, 1=Roseira-like, 2=Erva-like

public:
    PlantaExotica();

    void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) override;
    bool deveMorrer() const override;
    void aoMorrer(Posicao& pos) override;

    char getSimbolo() const override { return 'x'; }
    std::string getNome() const override { return "Planta Exotica"; }
};

#endif //SIMGARDEN_PLANTAEXOTICA_H