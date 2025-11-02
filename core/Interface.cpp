//
// Created by Celso Jordão on 01/11/2025.
//

#include "Interface.h"
#include "Validator.h"
#include <fstream>

#include "Simulator.h"

Interface::Interface(Simulator* s) : sim(s) {
    inicializaComandos();
}

void Interface::inicializaComandos() {
    // Usar lambda para capturar 'this' e chamar métodos da classe
    comandos["jardim"] = [this](std::istringstream& iss) { return cmdJardim(iss); };
    comandos["avanca"] = [this](std::istringstream& iss) { return cmdAvanca(iss); };
    comandos["lplantas"] = [this](std::istringstream& iss) { return cmdLPlantas(iss); };
    comandos["lplanta"] = [this](std::istringstream& iss) { return cmdLPlanta(iss); };
    comandos["larea"] = [this](std::istringstream& iss) { return cmdLArea(iss); };
    comandos["lsolo"] = [this](std::istringstream& iss) { return cmdLSolo(iss); };
    comandos["lferr"] = [this](std::istringstream& iss) { return cmdLFerr(iss); };
    comandos["colhe"] = [this](std::istringstream& iss) { return cmdColhe(iss); };
    comandos["planta"] = [this](std::istringstream& iss) { return cmdPlanta(iss); };
    comandos["larga"] = [this](std::istringstream& iss) { return cmdLarga(iss); };
    comandos["pega"] = [this](std::istringstream& iss) { return cmdPega(iss); };
    comandos["compra"] = [this](std::istringstream& iss) { return cmdCompra(iss); };
    comandos["e"] = [this](std::istringstream& iss) { return cmdMove(iss, 'e'); };
    comandos["d"] = [this](std::istringstream& iss) { return cmdMove(iss, 'd'); };
    comandos["c"] = [this](std::istringstream& iss) { return cmdMove(iss, 'c'); };
    comandos["b"] = [this](std::istringstream& iss) { return cmdMove(iss, 'b'); };
    comandos["entra"] = [this](std::istringstream& iss) { return cmdEntra(iss); };
    comandos["sai"] = [this](std::istringstream& iss) { return cmdSai(iss); };
    comandos["grava"] = [this](std::istringstream& iss) { return cmdGrava(iss); };
    comandos["recupera"] = [this](std::istringstream& iss) { return cmdRecupera(iss); };
    comandos["apaga"] = [this](std::istringstream& iss) { return cmdApaga(iss); };
    comandos["executa"] = [this](std::istringstream& iss) { return cmdExecuta(iss); };
}

bool Interface::processaComando(const std::string& linha) {
    if (linha.empty()) return true;

    std::istringstream iss(linha);
    std::string cmd;
    iss >> cmd;

    // Converte para minúsculas usando Validador
    cmd = Validator::paraMinusculas(cmd);

    // Comando especial "fim"
    if (cmd == "fim") return false;

    // Procurar no map
    auto it = comandos.find(cmd);
    if (it != comandos.end()) {
        // Executar comando encontrado
        return it->second(iss);
    } else {
        erro("Comando desconhecido: " + cmd);
        return true;
    }
}

bool Interface::validaCoordenada(const std::string& coord, int& linha, int& col) const {
    if (coord.length() != 2) return false;

    char l = std::tolower(coord[0]);
    char c = std::tolower(coord[1]);

    if (l < 'a' || l > 'z' || c < 'a' || c > 'z') return false;

    linha = l - 'a';
    col = c - 'a';
    return true;
}

bool Interface::validaInt(const std::string& str, int& valor) const {
    try {
        size_t pos;
        valor = std::stoi(str, &pos);
        return pos == str.length() && valor >= 0;
    } catch (...) {
        return false;
    }
}

bool validaInt(const std::string& str, int& valor) {
    try {
        size_t pos;
        valor = std::stoi(str, &pos);
        return pos == str.length() && valor >= 0;
    } catch (...) {
        return false;
    }
}

bool Interface::cmdJardim(std::istringstream& iss) {
    std::string strLinhas, strCols;
    int linhas, colunas;

    if (!(iss >> strLinhas >> strCols)) {
        erro("Sintaxe: jardim <linhas> <colunas>");
        return true;
    }

    if (!Validator::validaInt(strLinhas, linhas) || !Validator::validaInt(strCols, colunas)) {
        erro("Os valores devem ser numeros inteiros positivos");
        return true;
    }

    if (!Validator::validaDimensoesJardim(linhas, colunas)) {
        erro("Dimensoes invalidas (min: 1x1, max: 26x26)");
        return true;
    }

    if (sim->temJardim()) {
        erro("Jardim ja foi criado");
        return true;
    }

    sim->criaJardim(linhas, colunas);
    sucesso("Jardim criado com sucesso");
    mostraJardim();
    return true;
}

bool Interface::cmdAvanca(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string strN;
    int n = 1;

    if (iss >> strN) {
        if (!Validator::validaInt(strN, n) || n < 1) {
            erro("Numero de instantes invalido");
            return true;
        }
    }

    sim->avanca(n);
    mostraJardim();
    return true;
}

bool Interface::cmdLPlantas(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }
    sim->listaPlantas();
    return true;
}

bool Interface::cmdLPlanta(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string coord;
    int linha, col;

    if (!(iss >> coord) || !Validator::validaCoordenada(coord, linha, col)) {
        erro("Sintaxe: lplanta <coord> (ex: lplanta bc)");
        return true;
    }

    sim->listaPlanta(linha, col);
    return true;
}

bool Interface::cmdLArea(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }
    sim->listaArea();
    return true;
}

bool Interface::cmdLSolo(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string coord, strRaio;
    int linha, col, raio = 0;

    if (!(iss >> coord) || !Validator::validaCoordenada(coord, linha, col)) {
        erro("Sintaxe: lsolo <coord> [raio] (ex: lsolo bc 2)");
        return true;
    }

    if (iss >> strRaio) {
        if (!Validator::validaInt(strRaio, raio) || raio < 0) {
            erro("Raio invalido");
            return true;
        }
    }

    sim->listaSolo(linha, col, raio);
    return true;
}

bool Interface::cmdLFerr(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }
    sim->listaFerramentas();
    return true;
}

bool Interface::cmdColhe(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string coord;
    int linha, col;

    if (!(iss >> coord) || !Validator::validaCoordenada(coord, linha, col)) {
        erro("Sintaxe: colhe <coord> (ex: colhe bc)");
        return true;
    }

    if (sim->colhePlanta(linha, col)) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdPlanta(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string coord, tipo;
    int linha, col;

    if (!(iss >> coord >> tipo) || !Validator::validaCoordenada(coord, linha, col)) {
        erro("Sintaxe: planta <coord> <tipo> (ex: planta bc c)");
        return true;
    }

    if (tipo.length() != 1) {
        erro("Tipo de planta invalido");
        return true;
    }

    char t = Validator::paraMinuscula(tipo[0]);
    if (!Validator::validaTipoPlanta(t)) {
        erro("Tipo invalido. Use: c (cacto), r (roseira), e (erva), x (exotica)");
        return true;
    }

    if (sim->plantaPlanta(linha, col, t)) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdLarga(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }
    sim->largaFerramenta();
    return true;
}

bool Interface::cmdPega(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string strNum;
    int num;

    if (!(iss >> strNum) || !Validator::validaInt(strNum, num)) {
        erro("Sintaxe: pega <numero> (ex: pega 3)");
        return true;
    }

    sim->pegaFerramenta(num);
    return true;
}

bool Interface::cmdCompra(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string tipo;
    if (!(iss >> tipo) || tipo.length() != 1) {
        erro("Sintaxe: compra <tipo> (ex: compra g)");
        return true;
    }

    char t = Validator::paraMinuscula(tipo[0]);
    if (!Validator::validaTipoFerramenta(t)) {
        erro("Tipo invalido. Use: g (regador), a (adubo), t (tesoura), z (ferramentaz)");
        return true;
    }

    sim->compraFerramenta(t);
    return true;
}

bool Interface::cmdMove(std::istringstream& iss, char direcao) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    if (sim->moveJardineiro(direcao)) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdEntra(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string coord;
    int linha, col;

    if (!(iss >> coord) || !Validator::validaCoordenada(coord, linha, col)) {
        erro("Sintaxe: entra <coord> (ex: entra bc)");
        return true;
    }

    if (sim->entraJardineiro(linha, col)) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdSai(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    if (sim->saiJardineiro()) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdGrava(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string nome;
    if (!(iss >> nome) || !Validator::validaNomeEstado(nome)) {
        erro("Sintaxe: grava <nome> (ex: grava teste)");
        return true;
    }

    sim->gravaEstado(nome);
    return true;
}

bool Interface::cmdRecupera(std::istringstream& iss) {
    if (!sim->temJardim()) {
        erro("Deve criar o jardim primeiro");
        return true;
    }

    std::string nome;
    if (!(iss >> nome) || !Validator::validaNomeEstado(nome)) {
        erro("Sintaxe: recupera <nome> (ex: recupera teste)");
        return true;
    }

    if (sim->recuperaEstado(nome)) {
        mostraJardim();
    }
    return true;
}

bool Interface::cmdApaga(std::istringstream& iss) {
    std::string nome;
    if (!(iss >> nome) || !Validator::validaNomeEstado(nome)) {
        erro("Sintaxe: apaga <nome> (ex: apaga teste)");
        return true;
    }

    sim->apagaEstado(nome);
    return true;
}

bool Interface::cmdExecuta(std::istringstream& iss) {
    std::string nomeFicheiro;
    if (!(iss >> nomeFicheiro) || !Validator::validaNomeFicheiro(nomeFicheiro)) {
        erro("Sintaxe: executa <ficheiro> (ex: executa cmds.txt)");
        return true;
    }

    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro) {
        erro("Nao foi possivel abrir o ficheiro: " + nomeFicheiro);
        return true;
    }

    std::string linha;
    while (std::getline(ficheiro, linha)) {
        if (!linha.empty()) {
            std::cout << "> " << linha << std::endl;
            if (!processaComando(linha)) {
                return false; // Comando "fim"
            }
        }
    }

    return true;
}

void Interface::mostraJardim() const {
    sim->renderizaJardim();
}

void Interface::erro(const std::string& msg) const {
    std::cout << "[ERRO] " << msg << std::endl;
}

void Interface::sucesso(const std::string& msg) const {
    std::cout << "[OK] " << msg << std::endl;
}

void Interface::info(const std::string& msg) const {
    std::cout << msg << std::endl;
}