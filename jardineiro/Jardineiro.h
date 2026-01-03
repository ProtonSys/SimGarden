//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>

class Ferramenta;

/**
 * @brief Representa o jardineiro - personagem controlada pelo utilizador
 *
 * RESPONSABILIDADES:
 * - Movimentar-se pelo jardim (comandos e/d/c/b)
 * - Transportar ferramentas (max ilimitado)
 * - Ter UMA ferramenta "na mão" (ativa)
 * - Plantar e colher plantas
 * - Apanhar ferramentas automaticamente ao passar por cima
 *
 * LIMITES POR TURNO (Settings::Jardineiro):
 * - Movimentos: max 10 por turno
 * - Entrada/Saída: max 1 por turno (controlado pelo Simulator)
 * - Colheitas: max 5 por turno (controlado pelo Simulator)
 * - Plantações: max 2 por turno (controlado pelo Simulator)
 *
 * NOTA SOBRE std::vector:
 * - Jardineiro PODE usar std::vector para ferramentas
 * - Enunciado só proíbe vector para a GRELHA do jardim
 * - Vector é adequado aqui (tamanho dinâmico de ferramentas)
 *
 * PERGUNTA TÍPICA DE DEFESA:
 * "Como funcionam os limites por turno?"
 * R: O Jardineiro controla limite de movimentos. O Simulator controla
 *    limites de entrada/saída/colheita/plantação. A cada avanca(),
 *    o método resetaContadoresTurno() põe todos a zero.
 */
class Jardineiro {
    // === POSIÇÃO ===
    bool noJardim;     // Está dentro do jardim?
    int linha;         // Posição atual (linha)
    int coluna;        // Posição atual (coluna)

    // === FERRAMENTAS ===
    std::vector<Ferramenta*> ferramentas; // Todas as ferramentas transportadas
    Ferramenta* ferramentaNaMao;          // Ferramenta ativa (nullptr se nenhuma)

    // === LIMITES ===
    int movimentosTurno;  // Contador de movimentos este turno (max 10)

public:
    Jardineiro();
    ~Jardineiro();  // Deleta todas as ferramentas que possui

    // === ESTADO ===
    bool estaNoJardim() const { return noJardim; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // === MOVIMENTO ===
    void entra(int l, int c);      // Entrar no jardim
    void sai();                     // Sair do jardim
    void move(int novaLinha, int novaCol);  // Mover para nova posição
    bool podeMoverse() const;       // Verifica se ainda pode mover (< 10 movimentos)
    void resetaMovimentosTurno();   // Reseta contador (chamado em avanca())

    // === FERRAMENTAS ===
    /**
     * @brief Adiciona ferramenta ao inventário
     * Chamado quando jardineiro apanha ferramenta do chão
     */
    void adicionaFerramenta(Ferramenta* f);

    /**
     * @brief Pega ferramenta específica pelo número de série
     * Comando: "pega 3" -> pega ferramenta com número série 3
     */
    bool pegaFerramenta(int numSerie);

    /**
     * @brief Larga ferramenta ativa (deixa de ter ferramenta na mão)
     */
    bool largaFerramenta();

    /**
     * @brief Remove ferramenta gasta do inventário
     * Chamado automaticamente quando capacidade chega a 0
     */
    void removeFerramentaGasta();

    Ferramenta* getFerramentaNaMao() const { return ferramentaNaMao; }
    void listaFerramentas() const;

private:
    /**
     * @brief Procura ferramenta pelo número de série
     * Helper para pegaFerramenta()
     */
    Ferramenta* encontraFerramenta(int numSerie);
};

#endif