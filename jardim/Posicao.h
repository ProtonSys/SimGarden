//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef POSICAO_H
#define POSICAO_H

class Planta;
class Ferramenta;

/**
 * @brief Representa UMA célula/posição do jardim
 *
 * RESPONSABILIDADES:
 * - Armazena recursos do solo (água e nutrientes)
 * - Guarda NO MÁXIMO 1 planta E 1 ferramenta
 * - Gere ownership: ao destruir, deleta planta e ferramenta
 *
 * DECISÃO DE DESIGN:
 * - Posicao é DONA dos seus objetos (delete no destrutor)
 * - Previne cópia (copy constructor = delete) para evitar problemas
 * - Os valores de água/nutrientes nunca ficam negativos
 */
class Posicao {
private:
    // === RECURSOS DO SOLO ===
    int agua;              // Quantidade de água nesta posição
    int nutrientes;        // Quantidade de nutrientes nesta posição

    // === CONTEÚDO DA POSIÇÃO ===
    Planta* planta;        // Ponteiro para planta (nullptr se vazia)
    Ferramenta* ferramenta;// Ponteiro para ferramenta (nullptr se vazia)

public:
    Posicao();
    ~Posicao();

    // Prevenir cópia para evitar problemas com ponteiros
    Posicao(const Posicao&) = delete;
    Posicao& operator=(const Posicao&) = delete;

    // Getters e Setters para água e nutrientes
    void setAgua(int a);
    void setNutrientes(int n);
    int getAgua() const;
    int getNutrientes() const;

    // Adicionar/modificar água e nutrientes
    void adicionaAgua(int quantidade);
    void adicionaNutrientes(int quantidade);
    void removeAgua(int quantidade);
    void removeNutrientes(int quantidade);

    // Gestão de plantas
    bool temPlanta() const;
    Planta* getPlanta();
    const Planta* getPlanta() const;
    void setPlanta(Planta* p);
    Planta* removePlanta();  // Remove e retorna a planta

    // Gestão de ferramentas
    bool temFerramenta() const;
    Ferramenta* getFerramenta();
    const Ferramenta* getFerramenta() const;
    void setFerramenta(Ferramenta* f);
    Ferramenta* removeFerramenta();  // Remove e retorna a ferramenta

    // Verificar se está vazia (sem planta e sem ferramenta)
    bool estaVazia() const;
};

#endif // POSICAO_H
