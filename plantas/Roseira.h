//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_ROSEIRA_H
#define SIMGARDEN_ROSEIRA_H

#include "Planta.h"

/**
 * @brief Roseira - Beautiful plant that requires careful water/nutrient balance
 *
 * - Starts with 25 agua and 25 nutrients
 * - Loses 4 agua and 4 nutrients per turn
 * - Absorbs 5 agua and 8 nutrients from soil
 * - Dies if agua < 1, nutrients < 1, or nutrients > 199
 * - Multiplies when nutrients > 100
 */
class Roseira : public Planta {
public:
    Roseira();

    void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) override;
    bool deveMorrer() const override;
    void aoMorrer(Posicao& pos) override;

    char getSimbolo() const override { return 'r'; }
    std::string getNome() const override { return "Roseira"; }
};

#endif //SIMGARDEN_ROSEIRA_H