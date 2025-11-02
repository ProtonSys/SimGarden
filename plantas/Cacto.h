//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"

// Declaração da classe Cacto
class Cacto : public Planta {
public:
    Cacto();

    // Avança 1 instante de tempo
    void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) override;

    // Indica se deve morrer
    bool deveMorrer() const override;

    // Ação ao morrer
    void aoMorrer(Posicao& pos) override;

    // Info
    char getSimbolo() const override { return 'c'; }
    std::string getNome() const override { return "Cacto"; }
};

#endif // CACTO_H