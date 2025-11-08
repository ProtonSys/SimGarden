//
// Created by Celso Jordão on 01/11/2025.
//

#include "Planta.h"
#include "../jardim/Jardim.h"
#include <iostream>

Planta::Planta(Beleza b)
    : aguaAcumulada(0), nutrientesAcumulados(0), beleza(b),
      instanteNascimento(0), instantesVida(0), contadorCondicaoMorte(0) {
}

Planta::~Planta() {
}

void Planta::mostraInfo() const {
    std::cout << "Nome: " << getNome() << std::endl;
    std::cout << "Simbolo: " << getSimbolo() << std::endl;
    std::cout << "Agua acumulada: " << aguaAcumulada << std::endl;
    std::cout << "Nutrientes acumulados: " << nutrientesAcumulados << std::endl;
    std::cout << "Instantes de vida: " << instantesVida << std::endl;
    std::cout << "Beleza: ";
    switch (beleza) {
        case Beleza::FEIA: std::cout << "FEIA"; break;
        case Beleza::NEUTRA: std::cout << "NEUTRA"; break;
        case Beleza::BONITA: std::cout << "BONITA"; break;
    }
    std::cout << std::endl;
}

void Planta::absorveDoSolo(Posicao& pos, int agua, int nutrientes) {
    // Absorver do solo e adicionar à planta
    int aguaSolo = pos.getAgua();
    int nutrientesSolo = pos.getNutrientes();

    // Calcular quanto pode absorver
    int aguaAbsorvida = (agua <= aguaSolo) ? agua : aguaSolo;
    int nutrientesAbsorvidos = (nutrientes <= nutrientesSolo) ? nutrientes : nutrientesSolo;

    // Atualizar planta
    aguaAcumulada += aguaAbsorvida;
    nutrientesAcumulados += nutrientesAbsorvidos;

    // Remover do solo
    pos.setAgua(aguaSolo - aguaAbsorvida);
    pos.setNutrientes(nutrientesSolo - nutrientesAbsorvidos);
}