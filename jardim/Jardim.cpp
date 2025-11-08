//
// Created by Celso Jordão on 01/11/2025.
//

#include "Jardim.h"
#include "Posicao.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

#include <iostream>
#include <vector>
#include <utility>

Jardim::Jardim(int l, int c)
    : grelha(nullptr), linhas(l), colunas(c), instanteAtual(0) {

    // Alocar array de ponteiros para linhas
    grelha = new Posicao*[linhas];

    // Alocar cada linha
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas];

        // Inicializar com valores aleatórios usando modern C++ <random>
        for (int j = 0; j < colunas; j++) {
            int agua = RandomGenerator::getInt(Settings::Jardim::agua_min,
                                               Settings::Jardim::agua_max);

            int nutrientes = RandomGenerator::getInt(Settings::Jardim::nutrientes_min,
                                                     Settings::Jardim::nutrientes_max);

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

bool Jardim::posicaoValida(int linha, int col) const {
    return (linha >= 0 && linha < linhas && col >= 0 && col < colunas);
}

bool Jardim::temVizinhoVazio(int linha, int col, int& linhaViz, int& colViz) const {
    // Check all 4 adjacent positions (up, down, left, right)
    int direcoes[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto& dir : direcoes) {
        int novaLinha = linha + dir[0];
        int novaCol = col + dir[1];

        if (posicaoValida(novaLinha, novaCol)) {
            // TODO: Check if position is actually empty (no plant)
            // For now, just return first valid neighbor
            linhaViz = novaLinha;
            colViz = novaCol;
            return true;
        }
    }
    return false;
}

bool Jardim::temVizinhoAleatorio(int linha, int col, int& linhaViz, int& colViz) const {
    // Check all 8 surrounding positions
    int direcoes[][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                          {0, -1},           {0, 1},
                          {1, -1},  {1, 0},  {1, 1}};

    std::vector<std::pair<int, int>> vizinhosValidos;
    for (auto& dir : direcoes) {
        int novaLinha = linha + dir[0];
        int novaCol = col + dir[1];

        if (posicaoValida(novaLinha, novaCol)) {
            vizinhosValidos.push_back({novaLinha, novaCol});
        }
    }

    if (vizinhosValidos.empty()) {
        return false;
    }

    // Pick a random neighbor
    int idx = RandomGenerator::getInt(0, vizinhosValidos.size() - 1);
    linhaViz = vizinhosValidos[idx].first;
    colViz = vizinhosValidos[idx].second;
    return true;
}
