//
// Created by Celso Jordão on 01/11/2025.
//
// CACTO.CPP - Implementação da planta Cacto
//
// DEMONSTRA POLIMORFISMO:
// - Implementa métodos virtuais puros da classe base Planta
// - Comportamento DIFERENTE de Roseira e ErvaDaninha
// - Chamado via ponteiro base (Planta*) no Simulator

#include "Cacto.h"
#include "../jardim/Jardim.h"
#include "../config/Settings.h"
#include "../config/RandomGenerator.h"

/**
 * @brief Construtor - inicializa como planta NEUTRA
 */
Cacto::Cacto() : Planta(Beleza::NEUTRA) {
}

/**
 * @brief IMPLEMENTAÇÃO ESPECÍFICA do comportamento do Cacto
 *
 * ALGORITMO:
 * 1. Incrementa idade
 * 2. Absorve recursos (POUCA água - 25%, ALGUNS nutrientes - 5)
 * 3. Verifica condições de morte:
 *    - Muita água (> 100) = morre afogado
 *    - Poucos nutrientes (< 1) = morre de fome
 * 4. Tenta multiplicar se bem nutrido (nutrientes > 100 E água > 50)
 *
 * POLIMORFISMO EM AÇÃO:
 * - Roseira absorve MÉDIA água e multiplica por água
 * - Cacto absorve POUCA água e multiplica por nutrientes
 * - MESMA interface (avancaInstante), LÓGICA diferente!
 */
void Cacto::avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) {
    instantesVida++;

    // === FASE 1: ABSORÇÃO ===
    // Cacto absorve POUCA água (é resistente à seca)
    int aguaSolo = pos.getAgua();
    int aguaAbsorver = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) / 100;

    // Absorve nutrientes fixos
    int nutrientesAbsorver = Settings::Cacto::absorcao_nutrientes;

    absorveDoSolo(pos, aguaAbsorver, nutrientesAbsorver);

    // === FASE 2: VERIFICAÇÃO DE MORTE ===
    int aguaSoloAtual = pos.getAgua();
    int nutrientesSoloAtual = pos.getNutrientes();

    // Condição 1: EXCESSO de água (cacto não gosta de muita água!)
    if (aguaSoloAtual > Settings::Cacto::morre_agua_solo_maior) {
        contadorCondicaoMorte++;
    }
    // Condição 2: FALTA de nutrientes
    else if (nutrientesSoloAtual < Settings::Cacto::morre_nutrientes_solo_menor) {
        contadorCondicaoMorte++;
    }
    // Condições OK - reseta contador
    else {
        contadorCondicaoMorte = 0;
    }

    // === FASE 3: MULTIPLICAÇÃO ===
    // Cacto multiplica quando tem MUITOS nutrientes
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
