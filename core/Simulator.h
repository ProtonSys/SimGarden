//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include <string>
#include <map>
#include <memory>

class Jardim;
class Jardineiro;

class Simulator {
    std::unique_ptr<Jardim> jardim;
    std::unique_ptr<Jardineiro> jardineiro;

    // Para gravação/recuperação de estados
    std::map<std::string, std::unique_ptr<Jardim>> estadosGravados;
    std::map<std::string, std::unique_ptr<Jardineiro>> jardineirosGravados;

    // Contadores de ações por turno
    int plantasColhidasTurno;
    int plantasPlantadasTurno;

    // Estado do último turno para entrada/saída
    bool entrouEsteTurno;
    bool saiuEsteTurno;

public:
    Simulator();
    ~Simulator();

    // Criação do jardim
    void criaJardim(int linhas, int colunas);
    bool temJardim() const { return jardim != nullptr; }

    // Avançar tempo
    void avanca(int numInstantes);

    // Renderização
    void renderizaJardim() const;

    // Comandos de listagem
    void listaPlantas() const;
    void listaPlanta(int linha, int col) const;
    void listaArea() const;
    void listaSolo(int linha, int col, int raio) const;
    void listaFerramentas() const;

    // Ações sobre plantas
    bool colhePlanta(int linha, int col);
    bool plantaPlanta(int linha, int col, char tipo);

    // Ferramentas
    void largaFerramenta();
    bool pegaFerramenta(int numSerie);
    void compraFerramenta(char tipo);

    // Movimento do jardineiro
    bool moveJardineiro(char direcao); // e, d, c, b
    bool entraJardineiro(int linha, int col);
    bool saiJardineiro();

    // Gravação/recuperação
    void gravaEstado(const std::string& nome);
    bool recuperaEstado(const std::string& nome);
    void apagaEstado(const std::string& nome);

    // Getters
    Jardim* getJardim() { return jardim.get(); }
    Jardineiro* getJardineiro() { return jardineiro.get(); }

private:
    void resetaContadoresTurno();
    void colocaFerramentasIniciais();
    void aplicaFerramentaAtiva();
    void apanhaFerramentaSeExistir(int linha, int col);
    void verificaMortes();
    void processaMultiplicacoes();
    void libertaEstadosGravados();

    // Helper para criar plantas
    class Planta* criaPlanta(char tipo) const;

    // Helper para criar ferramentas
    class Ferramenta* criaFerramenta(char tipo) const;
};

#endif