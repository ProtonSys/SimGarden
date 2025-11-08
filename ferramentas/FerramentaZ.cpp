//
// Created by Celso Jordão on 01/11/2025.
//

#include "FerramentaZ.h"

FerramentaZ::FerramentaZ(int numeroSerie)
    : Ferramenta(numeroSerie, "Super Fertilizador", 5) {
    // Only 5 uses
}

void FerramentaZ::usar() {
    if (capacidadeAtual > 0) {
        capacidadeAtual--;
        // Super fertilization effect happens in Jardineiro/Simulator
        // Affects 3x3 area around current position
    }
}