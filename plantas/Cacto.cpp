//
// Created by Celso Jordão on 01/11/2025.
//

#include "Cacto.h"
#include "../jardim/Jardim.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

Cacto::Cacto() : Planta(Beleza::NEUTRA) {
}

void Cacto::avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) {
    instantesVida++;

    // Absorver água (25% da água do solo)
    int aguaSolo = pos.getAgua();
    int aguaAbsorver = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) / 100;

    // Absorver nutrientes (5 unidades)
    int nutrientesAbsorver = Settings::Cacto::absorcao_nutrientes;

    absorveDoSolo(pos, aguaAbsorver, nutrientesAbsorver);

    // Verificar condições de morte
    int aguaSoloAtual = pos.getAgua();
    int nutrientesSoloAtual = pos.getNutrientes();

    // Condição 1: Água do solo > 100 por 3 instantes
    if (aguaSoloAtual > Settings::Cacto::morre_agua_solo_maior) {
        contadorCondicaoMorte++;
    } else if (nutrientesSoloAtual < Settings::Cacto::morre_nutrientes_solo_menor) {
        // Condição 2: Nutrientes do solo < 1 por 3 instantes
        contadorCondicaoMorte++;
    } else {
        contadorCondicaoMorte = 0;  // Reset contador
    }

    // Tentativa de multiplicação (se nutrientes > 100 e água > 50 no solo)
    if (nutrientesSoloAtual > Settings::Cacto::multiplica_nutrientes_maior &&
        aguaSoloAtual > Settings::Cacto::multiplica_agua_maior) {
        // Tentar multiplicar para vizinho aleatório
        int linhaViz, colViz;
        if (jardim.temVizinhoAleatorio(linha, col, linhaViz, colViz)) {
            // TODO: Adicionar nova planta na posição vizinha
            // jardim.adicionaPlanta(linhaViz, colViz, new Cacto());
        }
    }
}

bool Cacto::deveMorrer() const {
    return contadorCondicaoMorte >= Settings::Cacto::morre_agua_solo_instantes;
}

void Cacto::aoMorrer(Posicao& pos) {
    // Cacto não faz nada especial ao morrer
    (void)pos;  // Suppress unused parameter warning
}
