//
// Created by Celso Jordão on 01/11/2025.
//

#include "PacoteAdubo.h"
#include "../jardim/Posicao.h"
#include "../config/Settings.h"

PacoteAdubo::PacoteAdubo(int numeroSerie)
    : Ferramenta(numeroSerie, "Pacote Adubo", Settings::Adubo::capacidade) {
}

void PacoteAdubo::usar() {
    if (capacidadeAtual >= Settings::Adubo::dose) {
        capacidadeAtual -= Settings::Adubo::dose;
    }
}

void PacoteAdubo::aplicar(Posicao* pos) {
    if (pos == nullptr || estaGasta()) {
        return;
    }

    if (capacidadeAtual >= Settings::Adubo::dose) {
        pos->adicionaNutrientes(Settings::Adubo::dose);
        capacidadeAtual -= Settings::Adubo::dose;
    }
}