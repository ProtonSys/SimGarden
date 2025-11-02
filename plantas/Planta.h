//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef PLANTA_H
#define PLANTA_H

#include <string>

class Posicao;
class Jardim;

// Enum para beleza
enum class Beleza {
    FEIA,
    NEUTRA,
    BONITA
};

class Planta {
protected:
    int aguaAcumulada;
    int nutrientesAcumulados;
    Beleza beleza;
    int instanteNascimento;
    int instantesVida;

    // Para controle de condições de morte
    int contadorCondicaoMorte;

public:
    Planta(Beleza b);
    virtual ~Planta();

    // Métodos virtuais puros (obrigam subclasses a implementar)
    virtual void avancaInstante(Posicao& pos, Jardim& jardim, int linha, int col) = 0;
    virtual bool deveMorrer() const = 0;
    virtual void aoMorrer(Posicao& pos) = 0;
    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;

    // Métodos comuns
    void mostraInfo() const;
    Beleza getBeleza() const { return beleza; }
    int getAgua() const { return aguaAcumulada; }
    int getNutrientes() const { return nutrientesAcumulados; }

protected:
    // Helpers para subclasses
    void absorveDoSolo(Posicao& pos, int agua, int nutrientes);
};

#endif