//
// Created by Celso Jordão on 01/11/2025.
//

#include "Regador.h"
#include "../jardim/Posicao.h"
#include "../config/Settings.h"

Regador::Regador(int numeroSerie)
    : Ferramenta(numeroSerie, "Regador", Settings::Regador::capacidade) {
}

void Regador::usar() {
    if (capacidadeAtual >= Settings::Regador::dose) {
        capacidadeAtual -= Settings::Regador::dose;
    }
}

void Regador::aplicar(Posicao* pos) {
    if (pos == nullptr || estaGasta()) {
        return;
    }

    if (capacidadeAtual >= Settings::Regador::dose) {
        pos->adicionaAgua(Settings::Regador::dose);
        capacidadeAtual -= Settings::Regador::dose;
    }
}