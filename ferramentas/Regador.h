//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_REGADOR_H
#define SIMGARDEN_REGADOR_H

#include "Ferramenta.h"

/**
 * @brief Regador - Watering can that adds water to soil
 *
 * - Capacity: 200 units
 * - Each use adds 10 water to current position
 * - Runs out after 20 uses
 */
class Regador : public Ferramenta {
public:
    Regador(int numeroSerie);

    void usar() override;
};

#endif //SIMGARDEN_REGADOR_H