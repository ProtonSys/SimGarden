//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMGARDEN_FERRAMENTAZ_H
#define SIMGARDEN_FERRAMENTAZ_H

#include "Ferramenta.h"

/**
 * @brief FerramentaZ - Super Fertilizer with limited uses
 *
 * - Only 5 uses total
 * - Dramatically boosts plant growth in 3x3 area
 * - Adds significant water and nutrients to soil
 */
class FerramentaZ : public Ferramenta {
public:
    FerramentaZ(int numeroSerie);

    void usar() override;
};

#endif //SIMGARDEN_FERRAMENTAZ_H