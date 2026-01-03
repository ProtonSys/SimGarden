//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef PLANTA_H
#define PLANTA_H

#include <string>

class Posicao;
class Jardim;

/**
 * @brief Enumeração para classificação estética das plantas
 *
 * IMPORTÂNCIA PARA DEFESA:
 * - FEIA: ErvaDaninha (pode ser removida por TesouraPoda)
 * - NEUTRA: Cacto
 * - BONITA: Roseira
 */
enum class Beleza {
    FEIA,
    NEUTRA,
    BONITA
};

/**
 * @brief Classe base ABSTRATA para todas as plantas
 *
 * PADRÃO DE DESIGN: Template Method
 * - Define estrutura comum (atributos, absorção)
 * - Deixa comportamento específico para subclasses (avancaInstante, deveMorrer)
 *
 * POLIMORFISMO:
 * - Métodos virtuais puros forçam implementação nas subclasses
 * - No runtime, planta->avancaInstante() chama a versão CORRETA
 * - Exemplo: Cacto absorve diferente de Roseira
 *
 * GESTÃO DE MEMÓRIA:
 * - Destrutor virtual é ESSENCIAL para polimorfismo
 * - Permite delete correto através de ponteiro base
 *
 * PERGUNTA TÍPICA DE DEFESA:
 * "Como funciona o polimorfismo nas plantas?"
 * R: A classe Planta define interface comum com métodos virtuais puros.
 *    Cada subclasse implementa de forma diferente. No Simulator::avanca(),
 *    chamo planta->avancaInstante() e o C++ resolve em runtime qual
 *    implementação executar (Cacto, Roseira, etc).
 */
class Planta {
protected:
    // === RECURSOS ACUMULADOS ===
    int aguaAcumulada;          // Água que a planta absorveu do solo
    int nutrientesAcumulados;   // Nutrientes que a planta absorveu

    // === PROPRIEDADES ===
    Beleza beleza;              // Classificação estética (FEIA/NEUTRA/BONITA)
    int instanteNascimento;     // Quando foi plantada
    int instantesVida;          // Quantos turnos já viveu

    // === CONTROLE DE MORTE ===
    int contadorCondicaoMorte;  // Conta quantos turnos em condição de morte

public:
    Planta(Beleza b);
    virtual ~Planta();  // Virtual OBRIGATÓRIO para polimorfismo!

    // === MÉTODOS VIRTUAIS PUROS (= 0) ===
    // Subclasses DEVEM implementar estes métodos

    /**
     * @brief Executa lógica da planta a cada turno
     * CADA PLANTA IMPLEMENTA DE FORMA DIFERENTE:
     * - Cacto: absorve pouco, multiplica se muito nutriente
     * - Roseira: absorve médio, multiplica se muito água
     * - ErvaDaninha: absorve muito, multiplica facilmente
     * - PlantaExotica: comportamento especial
     */
    virtual void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) = 0;

    /**
     * @brief Verifica se a planta deve morrer
     * REGRA: Se ficar 3+ turnos sem recursos suficientes
     */
    virtual bool deveMorrer() const = 0;

    /**
     * @brief Ações ao morrer (ex: deixar nutrientes no solo)
     */
    virtual void aoMorrer(Posicao& pos) = 0;

    /**
     * @brief Símbolo para renderização ('c', 'r', 'e', 'x')
     */
    virtual char getSimbolo() const = 0;

    /**
     * @brief Nome legível para listagens
     */
    virtual std::string getNome() const = 0;

    // === MÉTODOS COMUNS ===
    void mostraInfo() const;
    Beleza getBeleza() const { return beleza; }
    int getAgua() const { return aguaAcumulada; }
    int getNutrientes() const { return nutrientesAcumulados; }

protected:
    /**
     * @brief Helper para subclasses absorverem recursos
     * Remove do solo e adiciona à planta
     */
    void absorveDoSolo(Posicao& pos, int agua, int nutrientes);
};

#endif