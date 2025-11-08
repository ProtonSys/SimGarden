//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_PACOTEADUBO_H
#define SIMGARDEN_PACOTEADUBO_H

#include "Ferramenta.h"

/**
 * @brief PacoteAdubo - Fertilizer package that adds nutrients to soil
 *
 * - Capacity: 100 units
 * - Each use adds 10 nutrients to current position
 * - Runs out after 10 uses
 */
class PacoteAdubo : public Ferramenta {
public:
    PacoteAdubo(int numeroSerie);

    void usar() override;
};

#endif //SIMGARDEN_PACOTEADUBO_H