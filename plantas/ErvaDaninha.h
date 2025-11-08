//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_ERVADANINHA_H
#define SIMGARDEN_ERVADANINHA_H

#include "Planta.h"

/**
 * @brief ErvaDaninha - Ugly weed that spreads quickly
 *
 * - Starts with 5 agua and 5 nutrients
 * - Absorbs 1 agua and 1 nutrient from soil per turn
 * - Dies after 60 instants
 * - Multiplies every 5 instants if soil nutrients > 30
 */
class ErvaDaninha : public Planta {
public:
    ErvaDaninha();

    void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) override;
    bool deveMorrer() const override;
    void aoMorrer(Posicao& pos) override;

    char getSimbolo() const override { return 'e'; }
    std::string getNome() const override { return "Erva Daninha"; }
};

#endif //SIMGARDEN_ERVADANINHA_H