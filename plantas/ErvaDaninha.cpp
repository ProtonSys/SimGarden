//
// Created by Celso Jordão on 01/11/2025.
//

#include "ErvaDaninha.h"
#include "../jardim/Jardim.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

ErvaDaninha::ErvaDaninha() : Planta(Beleza::FEIA) {
    aguaAcumulada = Settings::ErvaDaninha::inicial_agua;
    nutrientesAcumulados = Settings::ErvaDaninha::inicial_nutrientes;
}

void ErvaDaninha::avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) {
    instantesVida++;

    // Absorver do solo
    absorveDoSolo(pos, Settings::ErvaDaninha::absorcao_agua,
                  Settings::ErvaDaninha::absorcao_nutrientes);

    // Tentativa de multiplicação (a cada 5 instantes, se nutrientes solo > 30)
    if (instantesVida % Settings::ErvaDaninha::multiplica_instantes == 0) {
        int nutrientesSolo = pos.getNutrientes();
        if (nutrientesSolo > Settings::ErvaDaninha::multiplica_nutrientes_maior) {
            int linhaViz, colViz;
            if (jardim.temVizinhoVazio(linha, col, linhaViz, colViz)) {
                // Nova planta fica com 5 nutrientes
                // Planta original fica com 5 nutrientes
                // TODO: Implementar criação de nova planta
                // nutrientesAcumulados = Settings::ErvaDaninha::original_nutrientes;
                // jardim.adicionaPlanta(linhaViz, colViz, new ErvaDaninha());
            }
        }
    }
}

bool ErvaDaninha::deveMorrer() const {
    // Morre após 60 instantes
    return instantesVida >= Settings::ErvaDaninha::morre_instantes;
}

void ErvaDaninha::aoMorrer(Posicao& pos) {
    // Erva daninha não faz nada especial ao morrer
    (void)pos;
}