//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

/**
 * @brief Classe base ABSTRATA para todas as ferramentas
 *
 * PADRÃO DE DESIGN: Strategy Pattern
 * - Cada ferramenta tem algoritmo diferente em aplicar()
 * - Regador: adiciona água
 * - PacoteAdubo: adiciona nutrientes
 * - TesouraPoda: remove plantas feias
 * - FerramentaZ: super boost (água + nutrientes)
 *
 * IDENTIFICAÇÃO:
 * - Número de série ÚNICO (gerado automaticamente)
 * - Permite ao jardineiro "pegar 3" para selecionar ferramenta específica
 *
 * DESGASTE:
 * - Cada ferramenta tem capacidade limitada
 * - Ao gastar-se completamente (capacidade = 0), é removida
 *
 * PERGUNTA TÍPICA DE DEFESA:
 * "Qual o padrão de design usado nas ferramentas?"
 * R: Strategy Pattern. Cada ferramenta implementa aplicar() de forma diferente.
 *    O Simulator não precisa saber qual ferramenta está ativa, apenas chama
 *    ferramenta->aplicar(pos) e o comportamento correto é executado.
 */
class Ferramenta {
protected:
    int numeroSerie;       // ID único para comando "pega N"
    std::string nome;      // Nome legível ("Regador", "Adubo", etc)
    int capacidadeAtual;   // Quanto resta (ex: água/adubo)
    int capacidadeMax;     // Capacidade inicial

public:
    Ferramenta(int ns, const std::string& n, int capMax)
        : numeroSerie(ns),
          nome(n),
          capacidadeAtual(capMax),
          capacidadeMax(capMax) {}

    virtual ~Ferramenta() = default;  // Virtual para polimorfismo

    // === GETTERS ===
    int getNumeroSerie() const {
        return numeroSerie;
    }

    const std::string& getNome() const {
        return nome;
    }

    int getCapacidadeAtual() const {
        return capacidadeAtual;
    }

    int getCapacidadeMax() const {
        return capacidadeMax;
    }

    /**
     * @brief Verifica se está gasta (deve ser removida)
     */
    bool estaGasta() const {
        return capacidadeAtual <= 0;
    }

    /**
     * @brief Usar ferramenta (decrementa capacidade)
     * Pode ser sobrescrito se necessário
     */
    virtual void usar() {
        if (capacidadeAtual > 0)
            capacidadeAtual--;
    }

    /**
     * @brief Símbolo para renderização ('g', 'a', 't', 'z')
     * VIRTUAL PURO - subclasses devem implementar
     */
    virtual char getSimbolo() const = 0;

    /**
     * @brief Aplicar efeito da ferramenta numa posição
     * VIRTUAL PURO - cada ferramenta implementa de forma diferente
     *
     * EXEMPLOS:
     * - Regador: pos->adicionaAgua(Settings::Regador::dose)
     * - PacoteAdubo: pos->adicionaNutrientes(Settings::Adubo::dose)
     * - TesouraPoda: if (planta->getBeleza() == FEIA) pos->removePlanta()
     */
    virtual void aplicar(class Posicao* pos) = 0;
};

#endif // FERRAMENTA_H