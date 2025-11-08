//
// Created by Celso Jordão on 01/11/2025.
//

#include "PacoteAdubo.h"
#include "../config/Settings.h"

PacoteAdubo::PacoteAdubo(int numeroSerie)
    : Ferramenta(numeroSerie, "Pacote Adubo", Settings::Adubo::capacidade) {
}

void PacoteAdubo::usar() {
    if (capacidadeAtual >= Settings::Adubo::dose) {
        capacidadeAtual -= Settings::Adubo::dose;
        // Actual nutrient application happens in Jardineiro/Simulator
    }
}