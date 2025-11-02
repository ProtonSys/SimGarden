//
// Created by Celso Jordão on 01/11/2025.
//

#include "Jardim.h"
#include "Posicao.h"
#include "../config/Settings.h"

#include <iostream>

Jardim::Jardim(int l, int c)
    : grelha(nullptr), linhas(l), colunas(c), instanteAtual(0) {

    // Alocar array de ponteiros para linhas
    grelha = new Posicao*[linhas];

    // Alocar cada linha
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas];

        // Inicializar com valores aleatórios
        for (int j = 0; j < colunas; j++) {
            int agua = Settings::Jardim::agua_min +
                       rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);

            int nutrientes = Settings::Jardim::nutrientes_min +
                             rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);

            grelha[i][j].setAgua(agua);
            grelha[i][j].setNutrientes(nutrientes);
        }
    }
}

Jardim::~Jardim() {
    if (grelha != nullptr) {
        for (int i = 0; i < linhas; i++) {
            delete[] grelha[i];
        }
        delete[] grelha;
        grelha = nullptr;
    }
}

void Jardim::renderiza() const {
    std::cout << "\n";

    // Régua superior
    std::cout << " ";
    for (int j = 0; j < colunas; j++) {
        std::cout << (char)('A' + j);
    }
    std::cout << std::endl;

    // Linhas do jardim
    for (int i = 0; i < linhas; i++) {
        std::cout << (char)('A' + i);

        for (int j = 0; j < colunas; j++) {
            std::cout << ' ';  // Por agora só espaços
        }

        std::cout << (char)('A' + i) << std::endl;
    }

    // Régua inferior
    std::cout << " ";
    for (int j = 0; j < colunas; j++) {
        std::cout << (char)('A' + j);
    }
    std::cout << std::endl;

    std::cout << "Instante: " << instanteAtual << std::endl;
}
