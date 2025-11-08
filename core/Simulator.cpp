//
// Created by Celso Jordão on 01/11/2025.
//
#include "Simulator.h"
#include "Interface.h"
#include "../plantas/Cacto.h"
#include "../plantas/Roseira.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"
#include "../ferramentas/Regador.h"
#include "../ferramentas/PacoteAdubo.h"
#include "../ferramentas/TesouraPoda.h"
#include "../ferramentas/FerramentaZ.h"

#include <iostream>

Simulator::Simulator()
    : jardim(nullptr), jardineiro(std::make_unique<Jardineiro>()),
      plantasColhidasTurno(0), plantasPlantadasTurno(0),
      entrouEsteTurno(false), saiuEsteTurno(false) {
}

Simulator::~Simulator() {
    // Smart pointers automatically clean up
    // No manual delete needed
}

void Simulator::criaJardim(int linhas, int colunas) {
    // unique_ptr automatically deletes old jardim if it exists
    jardim = std::make_unique<Jardim>(linhas, colunas);
    std::cout << "Jardim " << linhas << "x" << colunas << " criado!" << std::endl;
}

void Simulator::avanca(int numInstantes) {
    std::cout << "[TODO] Avancar " << numInstantes << " instantes" << std::endl;
    // TODO Meta 2: Implementar lógica completa
}

void Simulator::renderizaJardim() const {
    if (!jardim) {
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

// Factory method for creating plants
Planta* Simulator::criaPlanta(char tipo) const {
    switch (tipo) {
        case 'c':
        case 'C':
            return new Cacto();
        case 'r':
        case 'R':
            return new Roseira();
        case 'e':
        case 'E':
            return new ErvaDaninha();
        case 'x':
        case 'X':
            return new PlantaExotica();
        default:
            return nullptr;
    }
}

// Factory method for creating tools
Ferramenta* Simulator::criaFerramenta(char tipo) const {
    static int proximoNumeroSerie = 1;

    switch (tipo) {
        case 'g':
        case 'G':
            return new Regador(proximoNumeroSerie++);
        case 'a':
        case 'A':
            return new PacoteAdubo(proximoNumeroSerie++);
        case 't':
        case 'T':
            return new TesouraPoda(proximoNumeroSerie++);
        case 'z':
        case 'Z':
            return new FerramentaZ(proximoNumeroSerie++);
        default:
            return nullptr;
    }
}
