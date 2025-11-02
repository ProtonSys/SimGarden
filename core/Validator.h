//
// Created by Celso Jordão on 01/11/2025.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

/**
 * Classe responsável por todas as validações de entrada do sistema
 * Centraliza lógica de validação para melhor organização e reutilização
 */
class Validator {
public:
    /**
     * Valida coordenadas no formato letra-letra (ex: "aa", "bc", "zz")
     * @param coord String com 2 caracteres representando linha e coluna
     * @param linha Referência onde será armazenado o índice da linha (0-25)
     * @param col Referência onde será armazenado o índice da coluna (0-25)
     * @return true se coordenada válida, false caso contrário
     */
    static bool validaCoordenada(const std::string& coord, int& linha, int& col);

    /**
     * Valida se uma coordenada está dentro dos limites do jardim
     * @param linha Índice da linha
     * @param col Índice da coluna
     * @param maxLinhas Número máximo de linhas do jardim
     * @param maxCols Número máximo de colunas do jardim
     * @return true se dentro dos limites, false caso contrário
     */
    static bool coordenadaDentroLimites(int linha, int col, int maxLinhas, int maxCols);

    /**
     * Valida e converte string para número inteiro positivo
     * @param str String a ser convertida
     * @param valor Referência onde será armazenado o valor convertido
     * @return true se conversão bem-sucedida e valor >= 0, false caso contrário
     */
    static bool validaInt(const std::string& str, int& valor);

    /**
     * Valida se número inteiro está dentro de um intervalo
     * @param valor Valor a validar
     * @param min Valor mínimo (inclusive)
     * @param max Valor máximo (inclusive)
     * @return true se valor está no intervalo [min, max], false caso contrário
     */
    static bool validaIntervalo(int valor, int min, int max);

    /**
     * Valida tipo de planta (c, r, e, x)
     * @param tipo Caracter representando o tipo
     * @return true se tipo válido, false caso contrário
     */
    static bool validaTipoPlanta(char tipo);

    /**
     * Valida tipo de ferramenta (g, a, t, z)
     * @param tipo Caracter representando o tipo
     * @return true se tipo válido, false caso contrário
     */
    static bool validaTipoFerramenta(char tipo);

    /**
     * Valida dimensões do jardim (1-26 x 1-26)
     * @param linhas Número de linhas
     * @param colunas Número de colunas
     * @return true se dimensões válidas, false caso contrário
     */
    static bool validaDimensoesJardim(int linhas, int colunas);

    /**
     * Valida se string representa uma direção válida (e, d, c, b)
     * @param direcao String com a direção
     * @return true se direção válida, false caso contrário
     */
    static bool validaDirecao(const std::string& direcao);

    /**
     * Valida nome de ficheiro (não vazio, sem caracteres especiais)
     * @param nome Nome do ficheiro
     * @return true se nome válido, false caso contrário
     */
    static bool validaNomeFicheiro(const std::string& nome);

    /**
     * Valida nome de estado para gravar/recuperar (não vazio)
     * @param nome Nome do estado
     * @return true se nome válido, false caso contrário
     */
    static bool validaNomeEstado(const std::string& nome);

    /**
     * Converte caracter para minúscula
     * @param c Caracter a converter
     * @return Caracter em minúscula
     */
    static char paraMinuscula(char c);

    /**
     * Converte string para minúsculas
     * @param str String a converter
     * @return String convertida
     */
    static std::string paraMinusculas(const std::string& str);

private:
    // Construtor privado - classe com apenas métodos estáticos
    Validator() = delete;

    // Constantes para validação
    static constexpr int MIN_DIMENSAO_JARDIM = 1;
    static constexpr int MAX_DIMENSAO_JARDIM = 26;
    static constexpr char MIN_COORD = 'a';
    static constexpr char MAX_COORD = 'z';
};

#endif