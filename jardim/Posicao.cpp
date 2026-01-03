//
// Created by Celso Jordão on 01/11/2025.
//

#include "Posicao.h"
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"

Posicao::Posicao()
    : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {
}

Posicao::~Posicao() {
    // IMPORTANTE: A Posicao é responsável por deletar as plantas e ferramentas que contém
    if (planta != nullptr) {
        delete planta;
        planta = nullptr;
    }
    if (ferramenta != nullptr) {
        delete ferramenta;
        ferramenta = nullptr;
    }
}

// Getters e Setters para água e nutrientes
void Posicao::setAgua(int a) {
    agua = (a < 0) ? 0 : a;
}

void Posicao::setNutrientes(int n) {
    nutrientes = (n < 0) ? 0 : n;
}

int Posicao::getAgua() const {
    return agua;
}

int Posicao::getNutrientes() const {
    return nutrientes;
}

// Adicionar/modificar água e nutrientes
void Posicao::adicionaAgua(int quantidade) {
    agua += quantidade;
    if (agua < 0) agua = 0;
}

void Posicao::adicionaNutrientes(int quantidade) {
    nutrientes += quantidade;
    if (nutrientes < 0) nutrientes = 0;
}

void Posicao::removeAgua(int quantidade) {
    agua -= quantidade;
    if (agua < 0) agua = 0;
}

void Posicao::removeNutrientes(int quantidade) {
    nutrientes -= quantidade;
    if (nutrientes < 0) nutrientes = 0;
}

// Gestão de plantas
bool Posicao::temPlanta() const {
    return planta != nullptr;
}

Planta* Posicao::getPlanta() {
    return planta;
}

const Planta* Posicao::getPlanta() const {
    return planta;
}

void Posicao::setPlanta(Planta* p) {
    // Se já havia uma planta, deletá-la
    if (planta != nullptr) {
        delete planta;
    }
    planta = p;
}

Planta* Posicao::removePlanta() {
    Planta* p = planta;
    planta = nullptr;
    return p;  // Devolve a planta sem deletar (responsabilidade de quem chamou)
}

// Gestão de ferramentas
bool Posicao::temFerramenta() const {
    return ferramenta != nullptr;
}

Ferramenta* Posicao::getFerramenta() {
    return ferramenta;
}

const Ferramenta* Posicao::getFerramenta() const {
    return ferramenta;
}

void Posicao::setFerramenta(Ferramenta* f) {
    // Se já havia uma ferramenta, deletá-la
    if (ferramenta != nullptr) {
        delete ferramenta;
    }
    ferramenta = f;
}

Ferramenta* Posicao::removeFerramenta() {
    Ferramenta* f = ferramenta;
    ferramenta = nullptr;
    return f;  // Devolve a ferramenta sem deletar
}

// Verificar se está vazia
bool Posicao::estaVazia() const {
    return (planta == nullptr) && (ferramenta == nullptr);
}
