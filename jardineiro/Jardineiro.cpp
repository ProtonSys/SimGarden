//
// Created by Celso Jordão on 01/11/2025.
//

//
// Created by Celso Jordão on 01/11/2025.
//

#include "Jardineiro.h"
#include "Ferramenta.h"
#include "Settings.h"

#include <iostream>
#include <algorithm> // std::find_if

Jardineiro::Jardineiro()
    : noJardim(false),
      linha(-1),
      coluna(-1),
      ferramentaNaMao(nullptr),
      movimentosTurno(0) {
    // nada especial ainda
}

Jardineiro::~Jardineiro() {
    // Libertar ferramentas se forem ownership do jardineiro
    // (por agora assumimos que o jardineiro é dono delas)
    for (const Ferramenta* f : ferramentas) {
        delete f;
    }
    ferramentas.clear();

    // A ferramentaNaMao não é delete aqui porque é a mesma
    // que já está dentro do vector ferramentas.
    ferramentaNaMao = nullptr;
}

// ======================= Estado / posição =======================

void Jardineiro::entra(int l, int c) {
    noJardim = true;
    linha = l;
    coluna = c;
    movimentosTurno = 0;
    std::cout << "[Jardineiro] entrou em "
              << char('a' + l) << char('a' + c) << std::endl;
}

void Jardineiro::sai() {
    noJardim = false;
    linha = -1;
    coluna = -1;
    movimentosTurno = 0;
    std::cout << "[Jardineiro] saiu do jardim" << std::endl;
}

bool Jardineiro::podeMoverse() const {
    // Regras de turno: limitar nº de movimentos
    // Usa Settings::Jardineiro::max_movimentos se existir
    return movimentosTurno < Settings::Jardineiro::max_movimentos;
}

void Jardineiro::move(int novaLinha, int novaCol) {
    if (!noJardim) {
        std::cout << "[ERRO] Jardineiro nao esta no jardim." << std::endl;
        return;
    }

    if (!podeMoverse()) {
        std::cout << "[ERRO] Limite de movimentos atingido neste turno." << std::endl;
        return;
    }

    linha = novaLinha;
    coluna = novaCol;
    movimentosTurno++;

    std::cout << "[Jardineiro] moveu-se para "
              << char('a' + linha) << char('a' + coluna)
              << " (movimentos este turno: " << movimentosTurno << ")"
              << std::endl;
}

void Jardineiro::resetaMovimentosTurno() {
    movimentosTurno = 0;
}

// ======================= Ferramentas =======================

void Jardineiro::adicionaFerramenta(Ferramenta* f) {
    if (!f) return;
    ferramentas.push_back(f);

    // Se não tiver nada na mão, pega automaticamente nesta
    if (ferramentaNaMao == nullptr) {
        ferramentaNaMao = f;
    }

    std::cout << "[Jardineiro] apanhou ferramenta #" << f->getNumeroSerie()
              << " (" << f->getNome() << ")" << std::endl;
}

Ferramenta* Jardineiro::encontraFerramenta(int numSerie) {
    auto it = std::find_if(ferramentas.begin(), ferramentas.end(),
                           [numSerie](Ferramenta* f) {
                               return f && f->getNumeroSerie() == numSerie;
                           });
    if (it == ferramentas.end())
        return nullptr;
    return *it;
}

// pegaFerramenta: escolhe da mochila qual vai ficar "na mão"
bool Jardineiro::pegaFerramenta(int numSerie) {
    Ferramenta* f = encontraFerramenta(numSerie);
    if (!f) {
        std::cout << "[ERRO] Ferramenta #" << numSerie
                  << " nao encontrada." << std::endl;
        return false;
    }

    ferramentaNaMao = f;
    std::cout << "[Jardineiro] agora tem na mao a ferramenta #"
              << numSerie << " (" << f->getNome() << ")"
              << std::endl;
    return true;
}

// Remove do inventário ferramentas que já ficaram gastas
// (por ex. capacidade 0). Isto depende da interface de Ferramenta.
// Vamos deixar em branco para já, mas com mensagem de debug.
void Jardineiro::removeFerramentaGasta() {
    // TODO: verificar estado de cada ferramenta e apagar as vazias/gastas
    // Neste momento só mostramos informação.
    std::cout << "[DEBUG] removeFerramentaGasta() ainda nao implementado\n";
}

// Lista todo o inventário do jardineiro
void Jardineiro::listaFerramentas() const {
    if (ferramentas.empty()) {
        std::cout << "[Inventario] (vazio)\n";
        return;
    }

    std::cout << "[Inventario do Jardineiro]\n";
    for (auto* f : ferramentas) {
        if (!f) continue;
        std::cout << " - #" << f->getNumeroSerie()
                  << " " << f->getNome();
        if (f == ferramentaNaMao)
            std::cout << "  [NA MAO]";
        std::cout << "\n";
    }
}