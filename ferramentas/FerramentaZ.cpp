//
// Created by Celso Jordão on 01/11/2025.
//

#include "FerramentaZ.h"
#include "../jardim/Posicao.h"

FerramentaZ::FerramentaZ(int numeroSerie)
    : Ferramenta(numeroSerie, "Super Fertilizador", 5) {
    // Only 5 uses
}

void FerramentaZ::usar() {
    if (capacidadeAtual > 0) {
        capacidadeAtual--;
    }
}

void FerramentaZ::aplicar(Posicao* pos) {
    if (pos == nullptr || estaGasta()) {
        return;
    }

    // Super fertilizador - aumenta dramaticamente água e nutrientes
    pos->adicionaAgua(50);
    pos->adicionaNutrientes(30);
    capacidadeAtual--;
}