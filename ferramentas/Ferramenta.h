//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

class Ferramenta {
protected:
    int numeroSerie;
    std::string nome;
    int capacidadeAtual;   // por ex. água/adubo que resta
    int capacidadeMax;     // capacidade máxima

public:
    Ferramenta(int ns, const std::string& n, int capMax)
        : numeroSerie(ns),
          nome(n),
          capacidadeAtual(capMax),
          capacidadeMax(capMax) {}

    virtual ~Ferramenta() = default;

    // --- getters básicos usados pelo Jardineiro ---
    int getNumeroSerie() const {
        return numeroSerie;
    }

    const std::string& getNome() const {
        return nome;
    }

    // podes usar isto mais tarde p.ex. para saber se já está gasta
    int getCapacidadeAtual() const {
        return capacidadeAtual;
    }

    int getCapacidadeMax() const {
        return capacidadeMax;
    }

    bool estaGasta() const {
        return capacidadeAtual <= 0;
    }

    // Ação típica da ferramenta (virtual para ser override nas derivadas)
    virtual void usar() {
        if (capacidadeAtual > 0)
            capacidadeAtual--;
    }

    // Símbolo para visualização no jardim (deve ser implementado pelas derivadas)
    virtual char getSimbolo() const = 0;

    // Aplicar ferramenta numa posição (deve ser implementado pelas derivadas)
    virtual void aplicar(class Posicao* pos) = 0;
};

#endif // FERRAMENTA_H