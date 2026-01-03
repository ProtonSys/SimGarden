//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include "Posicao.h"
#include <iostream>

class Posicao;
class Planta;
class Ferramenta;

class Jardim {
    Posicao** grelha;  // Array 2D alocado dinamicamente (NÃO É VECTOR!)
    int linhas;
    int colunas;
    int instanteAtual;

public:
    Jardim(int l, int c);
    ~Jardim();

    // Prevenir cópia (para segurança)
    Jardim(const Jardim&) = delete;
    Jardim& operator=(const Jardim&) = delete;

    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    int getInstante() const { return instanteAtual; }

    // Acesso a posições
    Posicao* getPosicao(int linha, int col);
    const Posicao* getPosicao(int linha, int col) const;

    // Validação
    bool posicaoValida(int linha, int col) const;

    // Avançar tempo
    void avancaInstante();

    // Renderização
    void renderiza(bool temJardineiro = false, int linhaJard = -1, int colJard = -1) const;

    // Adicionar/remover elementos
    bool adicionaPlanta(int linha, int col, class Planta* planta);
    bool removePlanta(int linha, int col);
    bool adicionaFerramenta(int linha, int col, class Ferramenta* ferr);
    bool removeFerramenta(int linha, int col);

    // Iteração para comandos de listagem
    void percorrePosicoes(void (*funcao)(const Posicao*, int, int, void*), void* dados) const;

    // Para multiplicação de plantas - encontrar posição vizinha vazia
    bool temVizinhoVazio(int linha, int col, int& linhaViz, int& colViz) const;
    bool temVizinhoAleatorio(int linha, int col, int& linhaViz, int& colViz) const;

private:
    void inicializaGrelha();
    void libertaGrelha();
    char getCaracter(int linha, int col, bool temJardineiro,
                     int linhaJard, int colJard) const;
};

#endif