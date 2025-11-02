//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>

class Ferramenta;

class Jardineiro {
    bool noJardim;
    int linha;
    int coluna;

    std::vector<Ferramenta*> ferramentas; // Ferramentas que transporta
    Ferramenta* ferramentaNaMao;          // Ferramenta ativa

    int movimentosTurno;

public:
    Jardineiro();
    ~Jardineiro();

    // Estado
    bool estaNoJardim() const { return noJardim; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Movimento
    void entra(int l, int c);
    void sai();
    void move(int novaLinha, int novaCol);
    bool podeMoverse() const;
    void resetaMovimentosTurno();

    // Ferramentas
    void adicionaFerramenta(Ferramenta* f);
    bool pegaFerramenta(int numSerie);
    bool largaFerramenta();
    void removeFerramentaGasta();
    Ferramenta* getFerramentaNaMao() const { return ferramentaNaMao; }
    void listaFerramentas() const;

private:
    Ferramenta* encontraFerramenta(int numSerie);
};

#endif