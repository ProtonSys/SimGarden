//
// Created by Celso Jordão on 01/11/2025.
//

#include "Jardim.h"
#include "Posicao.h"
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"
#include "../jardineiro/Jardineiro.h"
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

void Jardim::renderiza(bool temJardineiro, int linhaJard, int colJard) const {
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
            char c = getCaracter(i, j, temJardineiro, linhaJard, colJard);
            std::cout << c;
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
            // Check if position actually has no plant
            if (!grelha[novaLinha][novaCol].temPlanta()) {
                linhaViz = novaLinha;
                colViz = novaCol;
                return true;
            }
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

// Acesso a posições
Posicao* Jardim::getPosicao(int linha, int col) {
    if (!posicaoValida(linha, col)) {
        return nullptr;
    }
    return &grelha[linha][col];
}

const Posicao* Jardim::getPosicao(int linha, int col) const {
    if (!posicaoValida(linha, col)) {
        return nullptr;
    }
    return &grelha[linha][col];
}

// Avançar instante
void Jardim::avancaInstante() {
    instanteAtual++;
}

// Adicionar/remover plantas
bool Jardim::adicionaPlanta(int linha, int col, Planta* planta) {
    if (!posicaoValida(linha, col)) {
        return false;
    }

    if (grelha[linha][col].temPlanta()) {
        return false;  // Já existe uma planta
    }

    grelha[linha][col].setPlanta(planta);
    return true;
}

bool Jardim::removePlanta(int linha, int col) {
    if (!posicaoValida(linha, col)) {
        return false;
    }

    if (!grelha[linha][col].temPlanta()) {
        return false;  // Não há planta para remover
    }

    Planta* p = grelha[linha][col].removePlanta();
    delete p;  // Deletar a planta
    return true;
}

// Adicionar/remover ferramentas
bool Jardim::adicionaFerramenta(int linha, int col, Ferramenta* ferr) {
    if (!posicaoValida(linha, col)) {
        delete ferr;  // Evitar memory leak
        return false;
    }

    if (grelha[linha][col].temFerramenta()) {
        delete ferr;  // Já existe uma ferramenta, deletar a nova
        return false;
    }

    grelha[linha][col].setFerramenta(ferr);
    return true;
}

bool Jardim::removeFerramenta(int linha, int col) {
    if (!posicaoValida(linha, col)) {
        return false;
    }

    if (!grelha[linha][col].temFerramenta()) {
        return false;  // Não há ferramenta para remover
    }

    Ferramenta* f = grelha[linha][col].removeFerramenta();
    delete f;  // Deletar a ferramenta
    return true;
}

// Iteração para comandos de listagem
void Jardim::percorrePosicoes(void (*funcao)(const Posicao*, int, int, void*), void* dados) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            funcao(&grelha[i][j], i, j, dados);
        }
    }
}

// Helper para renderização - obter o caracter a mostrar numa posição
char Jardim::getCaracter(int linha, int col, bool temJardineiro,
                         int linhaJard, int colJard) const {
    // Prioridade: Jardineiro > Planta > Ferramenta > Vazio
    if (temJardineiro && linha == linhaJard && col == colJard) {
        return '*';
    }

    const Posicao* pos = getPosicao(linha, col);
    if (pos == nullptr) {
        return ' ';
    }

    if (pos->temPlanta()) {
        return pos->getPlanta()->getSimbolo();
    }

    if (pos->temFerramenta()) {
        return pos->getFerramenta()->getSimbolo();
    }

    return ' ';
}
