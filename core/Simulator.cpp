//
// Created by Celso Jordão on 01/11/2025.
//
#include "Simulator.h"
#include "Interface.h"

#include <iostream>

Simulator::Simulator() 
    : jardim(nullptr), jardineiro(nullptr),
      plantasColhidasTurno(0), plantasPlantadasTurno(0),
      entrouEsteTurno(false), saiuEsteTurno(false) {
    
    jardineiro = new Jardineiro();
}

Simulator::~Simulator() {
    if (jardim != nullptr) {
        delete jardim;
    }
    if (jardineiro != nullptr) {
        delete jardineiro;
    }
}

void Simulator::criaJardim(int linhas, int colunas) {
    if (jardim != nullptr) {
        delete jardim;
    }
    jardim = new Jardim(linhas, colunas);
    std::cout << "Jardim " << linhas << "x" << colunas << " criado!" << std::endl;
}

void Simulator::avanca(int numInstantes) {
    std::cout << "[TODO] Avancar " << numInstantes << " instantes" << std::endl;
    // TODO Meta 2: Implementar lógica completa
}

void Simulator::renderizaJardim() const {
    if (jardim == nullptr) {
        std::cout << "[Jardim ainda nao foi criado]" << std::endl;
        return;
    }
    jardim->renderiza();
}

void Simulator::listaPlantas() const {
    std::cout << "[TODO] Listar plantas" << std::endl;
    // TODO Meta 2
}

void Simulator::listaPlanta(int linha, int col) const {
    std::cout << "[TODO] Listar planta em " << (char)('a'+linha) << (char)('a'+col) << std::endl;
    // TODO Meta 2
}

void Simulator::listaArea() const {
    std::cout << "[TODO] Listar area" << std::endl;
    // TODO Meta 2
}

void Simulator::listaSolo(int linha, int col, int raio) const {
    std::cout << "[TODO] Listar solo" << std::endl;
    // TODO Meta 2
}

void Simulator::listaFerramentas() const {
    std::cout << "[TODO] Listar ferramentas" << std::endl;
    // TODO Meta 2
}

bool Simulator::colhePlanta(int linha, int col) {
    std::cout << "[TODO] Colher planta" << std::endl;
    // TODO Meta 2
    return false;
}

bool Simulator::plantaPlanta(int linha, int col, char tipo) {
    std::cout << "[TODO] Plantar planta tipo " << tipo << std::endl;
    // TODO Meta 2
    return false;
}

void Simulator::largaFerramenta() {
    std::cout << "[TODO] Largar ferramenta" << std::endl;
    // TODO Meta 2
}

bool Simulator::pegaFerramenta(int numSerie) {
    std::cout << "[TODO] Pegar ferramenta #" << numSerie << std::endl;
    // TODO Meta 2
    return false;
}

void Simulator::compraFerramenta(char tipo) {
    std::cout << "[TODO] Comprar ferramenta " << tipo << std::endl;
    // TODO Meta 2
}

bool Simulator::moveJardineiro(char direcao) {
    std::cout << "[TODO] Mover jardineiro " << direcao << std::endl;
    // TODO Meta 2
    return false;
}

bool Simulator::entraJardineiro(int linha, int col) {
    jardineiro->entra(linha, col);
    std::cout << "[OK] Jardineiro entrou em " << (char)('a'+linha) << (char)('a'+col) << std::endl;
    return true;
}

bool Simulator::saiJardineiro() {
    jardineiro->sai();
    std::cout << "[OK] Jardineiro saiu do jardim" << std::endl;
    return true;
}

void Simulator::gravaEstado(const std::string& nome) {
    std::cout << "[TODO] Gravar estado '" << nome << "'" << std::endl;
    // TODO Meta 2: Implementar cópia profunda
}

bool Simulator::recuperaEstado(const std::string& nome) {
    std::cout << "[TODO] Recuperar estado '" << nome << "'" << std::endl;
    // TODO Meta 2: Implementar cópia profunda
    return false;
}

void Simulator::apagaEstado(const std::string& nome) {
    std::cout << "[TODO] Apagar estado '" << nome << "'" << std::endl;
    // TODO Meta 2
}
