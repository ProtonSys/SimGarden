//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"

/**
 * @brief Cacto - Planta NEUTRA que suporta seca
 *
 * CARACTERÍSTICAS (Settings::Cacto):
 * - Beleza: NEUTRA (não afetada por TesouraPoda)
 * - Absorção: 25% água do solo, 5 nutrientes
 * - Multiplicação: Se nutrientes solo > 100 E água > 50
 * - Morte: Se água solo > 100 OU nutrientes solo < 1 por 3+ turnos
 *
 * COMPORTAMENTO ESPECÍFICO:
 * - Resiste bem à seca (absorve pouca água)
 * - Morre se houver MUITA água (excesso)
 * - Multiplica-se quando há muitos nutrientes
 *
 * EXEMPLO DE POLIMORFISMO:
 * - Este método implementa comportamento ESPECÍFICO do Cacto
 * - Roseira implementa de forma DIFERENTE
 * - Mas ambos são chamados via Planta* no Simulator::avanca()
 */
class Cacto : public Planta {
public:
    Cacto();

    /**
     * @brief Lógica específica do Cacto a cada turno
     * 1. Absorve recursos do solo (pouca água, alguns nutrientes)
     * 2. Verifica condições de morte (excesso de água OU falta nutrientes)
     * 3. Tenta multiplicar se condições favoráveis
     */
    void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) override;

    /**
     * @brief Verifica se deve morrer
     * REGRA: 3+ turnos consecutivos em condição adversa
     */
    bool deveMorrer() const override;

    /**
     * @brief Ação ao morrer
     * Cacto deixa 10 nutrientes no solo ao morrer
     */
    void aoMorrer(Posicao& pos) override;

    // Identificação
    char getSimbolo() const override { return 'c'; }
    std::string getNome() const override { return "Cacto"; }
};

#endif // CACTO_H