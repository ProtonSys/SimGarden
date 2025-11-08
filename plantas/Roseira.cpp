//
// Created by Celso Jordão on 01/11/2025.
//

#include "Roseira.h"
#include "../jardim/Jardim.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

Roseira::Roseira() : Planta(Beleza::BONITA) {
    aguaAcumulada = Settings::Roseira::inicial_agua;
    nutrientesAcumulados = Settings::Roseira::inicial_nutrientes;
}

void Roseira::avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) {
    instantesVida++;

    // Perder água e nutrientes por turno
    aguaAcumulada -= Settings::Roseira::perda_agua;
    nutrientesAcumulados -= Settings::Roseira::perda_nutrientes;

    // Absorver do solo
    absorveDoSolo(pos, Settings::Roseira::absorcao_agua,
                  Settings::Roseira::absorcao_nutrientes);

    // Tentativa de multiplicação
    if (nutrientesAcumulados > Settings::Roseira::multiplica_nutrientes_maior) {
        int linhaViz, colViz;
        if (jardim.temVizinhoVazio(linha, col, linhaViz, colViz)) {
            // Nova planta fica com 25 nutrientes e 50% da água da mãe
            // Planta original fica com 100 nutrientes e 50% da água
            // TODO: Implementar criação de nova planta
            // int aguaNova = (aguaAcumulada * Settings::Roseira::nova_agua_percentagem) / 100;
            // aguaAcumulada = (aguaAcumulada * Settings::Roseira::original_agua_percentagem) / 100;
            // nutrientesAcumulados = Settings::Roseira::original_nutrientes;
            // jardim.adicionaPlanta(linhaViz, colViz, new Roseira());
        }
    }
}

bool Roseira::deveMorrer() const {
    // Morre se água < 1, nutrientes < 1, ou nutrientes > 199
    return (aguaAcumulada < Settings::Roseira::morre_agua_menor ||
            nutrientesAcumulados < Settings::Roseira::morre_nutrientes_menor ||
            nutrientesAcumulados > Settings::Roseira::morre_nutrientes_maior);
}

void Roseira::aoMorrer(Posicao& pos) {
    // Roseira não faz nada especial ao morrer
    (void)pos;
}