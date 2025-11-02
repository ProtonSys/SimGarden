//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <functional>
#include "Validator.h"

class Simulator; // Forward declaration

class Interface {
    Simulator* sim;

    // Map de comandos: comando -> funcao
    std::map<std::string, std::function<bool(std::istringstream&)>> comandos;

public:
    Interface(Simulator* s);

    // Processa um comando (retorna false se for "fim")
    bool processaComando(const std::string& linha);

    // Renderiza o jardim na consola
    void mostraJardim() const;

    // Mensagens de erro/sucesso
    void erro(const std::string& msg) const;
    void sucesso(const std::string& msg) const;
    void info(const std::string& msg) const;

private:
    // Inicializar mapa de comandos
    void inicializaComandos();

    // Validação de coordenadas (ex: "ab" -> linha=0, col=1)
    bool validaCoordenada(const std::string& coord, int& linha, int& col) const;

    // Validação de número inteiro
    bool validaInt(const std::string& str, int& valor) const;

    // Comandos individuais
    bool cmdJardim(std::istringstream& iss);
    bool cmdAvanca(std::istringstream& iss);
    bool cmdLPlantas(std::istringstream& iss);
    bool cmdLPlanta(std::istringstream& iss);
    bool cmdLArea(std::istringstream& iss);
    bool cmdLSolo(std::istringstream& iss);
    bool cmdLFerr(std::istringstream& iss);
    bool cmdColhe(std::istringstream& iss);
    bool cmdPlanta(std::istringstream& iss);
    bool cmdLarga(std::istringstream& iss);
    bool cmdPega(std::istringstream& iss);
    bool cmdCompra(std::istringstream& iss);
    bool cmdMove(std::istringstream& iss, char direcao);
    bool cmdEntra(std::istringstream& iss);
    bool cmdSai(std::istringstream& iss);
    bool cmdGrava(std::istringstream& iss);
    bool cmdRecupera(std::istringstream& iss);
    bool cmdApaga(std::istringstream& iss);
    bool cmdExecuta(std::istringstream& iss);
};

#endif