//
// Created by Celso Jordão on 01/11/2025.
//

#include "Validator.h"

// Headers STL
#include <cctype>
#include <algorithm>

bool Validator::validaCoordenada(const std::string& coord, int& linha, int& col) {
    if (coord.length() != 2) return false;

    char l = paraMinuscula(coord[0]);
    char c = paraMinuscula(coord[1]);

    if (l < 'a' || l > 'z' || c < 'a' || c > 'z') return false;

    linha = l - 'a';
    col = c - 'a';
    return true;
}

bool Validator::validaInt(const std::string& str, int& valor) {
    if (str.empty()) return false;

    try {
        size_t pos;
        valor = std::stoi(str, &pos);
        return pos == str.length() && valor >= 0;
    } catch (...) {
        return false;
    }
}

bool Validator::validaTipoPlanta(char tipo) {
    tipo = paraMinuscula(tipo);
    return tipo == 'c' || tipo == 'r' || tipo == 'e' || tipo == 'x';
}

bool Validator::validaTipoFerramenta(char tipo) {
    tipo = paraMinuscula(tipo);
    return tipo == 'g' || tipo == 'a' || tipo == 't' || tipo == 'z';
}

bool Validator::validaDimensoesJardim(int linhas, int colunas) {
    return linhas >= 1 && linhas <= 26 && colunas >= 1 && colunas <= 26;
}

bool Validator::validaNomeFicheiro(const std::string& nome) {
    if (nome.empty() || nome.length() > 255) return false;

    for (char c : nome) {
        if (c == '\0' || c == '\n' || c == '\r') return false;
    }

    return true;
}

bool Validator::validaNomeEstado(const std::string& nome) {
    if (nome.empty() || nome.length() > 100) return false;

    if (nome.find_first_not_of(' ') == std::string::npos) return false;

    return true;
}

char Validator::paraMinuscula(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

std::string Validator::paraMinusculas(const std::string& str) {
    std::string resultado = str;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return resultado;
}