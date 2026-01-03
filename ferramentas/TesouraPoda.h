//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_TESOURAPODA_H
#define SIMGARDEN_TESOURAPODA_H

#include "Ferramenta.h"

/**
 * @brief TesouraPoda - Pruning shears that remove ugly plants
 *
 * - Never runs out (infinite uses)
 * - Removes plants with Beleza::FEIA
 * - Does not consume capacity
 */
class TesouraPoda : public Ferramenta {
public:
    TesouraPoda(int numeroSerie);

    void usar() override;
    char getSimbolo() const override { return 't'; }
    void aplicar(class Posicao* pos) override;
};

#endif //SIMGARDEN_TESOURAPODA_H