//
// Created by Celso Jordão on 01/11/2025.
//

#include "TesouraPoda.h"

TesouraPoda::TesouraPoda(int numeroSerie)
    : Ferramenta(numeroSerie, "Tesoura de Poda", 9999) {
    // Never runs out - set high capacity
}

void TesouraPoda::usar() {
    // Does not consume capacity
    // Removal of ugly plants happens in Jardineiro/Simulator
}