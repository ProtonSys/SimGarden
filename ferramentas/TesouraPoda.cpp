//
// Created by Celso Jordão on 01/11/2025.
//

#include "TesouraPoda.h"
#include "../jardim/Posicao.h"
#include "../plantas/Planta.h"

TesouraPoda::TesouraPoda(int numeroSerie)
    : Ferramenta(numeroSerie, "Tesoura de Poda", 9999) {
    // Never runs out - set high capacity
}

void TesouraPoda::usar() {
    // Does not consume capacity
}

void TesouraPoda::aplicar(Posicao* pos) {
    if (pos == nullptr) {
        return;
    }

    // Remove plantas feias (ugly plants)
    if (pos->temPlanta()) {
        Planta* planta = pos->getPlanta();
        if (planta != nullptr && planta->getBeleza() == Beleza::FEIA) {
            // Planta feia! Cortar!
            Planta* p = pos->removePlanta();
            if (p != nullptr) {
                // Ao morrer, a planta pode deixar nutrientes no solo
                p->aoMorrer(*pos);
                delete p;
            }
        }
    }
}