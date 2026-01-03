//
// Created by Celso Jordão on 01/11/2025.
//
// SIMULATOR.CPP - Implementação do controlador central do simulador
//
// RESPONSABILIDADES:
// - Coordenar jardim, jardineiro, plantas e ferramentas
// - Implementar o loop principal (avanca)
// - Aplicar regras de negócio (limites por turno)
// - Factory methods para plantas e ferramentas

#include "Simulator.h"
#include "Interface.h"
#include "../plantas/Cacto.h"
#include "../plantas/Roseira.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"
#include "../ferramentas/Regador.h"
#include "../ferramentas/PacoteAdubo.h"
#include "../ferramentas/TesouraPoda.h"
#include "../ferramentas/FerramentaZ.h"
#include "../config/RandomGenerator.h"
#include "../config/Settings.h"

#include <iostream>
#include <algorithm>

/**
 * @brief Construtor - Inicializa o simulador
 *
 * NOTA: Jardim começa nullptr (será criado pelo comando 'jardim')
 *       Jardineiro é criado imediatamente com unique_ptr
 */
Simulator::Simulator()
    : jardim(nullptr), jardineiro(std::make_unique<Jardineiro>()),
      plantasColhidasTurno(0), plantasPlantadasTurno(0),
      entrouEsteTurno(false), saiuEsteTurno(false) {
}

/**
 * @brief Destrutor
 *
 * GESTÃO DE MEMÓRIA:
 * - unique_ptr deleta automaticamente jardim e jardineiro
 * - Não é necessário delete manual!
 */
Simulator::~Simulator() {
    // Smart pointers fazem cleanup automático
    libertaEstadosGravados();
}

/**
 * @brief Cria o jardim com as dimensões especificadas
 *
 * @param linhas Número de linhas (1-26)
 * @param colunas Número de colunas (1-26)
 *
 * INICIALIZAÇÃO:
 * 1. Cria grelha 2D SEM std::vector (conforme enunciado)
 * 2. Cada posição recebe água e nutrientes aleatórios
 * 3. Coloca 3 ferramentas aleatórias em posições aleatórias
 *
 * NOTA: Se já existir jardim, unique_ptr deleta o antigo automaticamente
 */
void Simulator::criaJardim(int linhas, int colunas) {
    jardim = std::make_unique<Jardim>(linhas, colunas);
    std::cout << "Jardim " << linhas << "x" << colunas << " criado!" << std::endl;

    // Conforme enunciado: 3 ferramentas iniciais aleatórias
    for (int i = 0; i < 3; i++) {
        colocaFerramentasIniciais();
    }
}

/**
 * @brief LOOP PRINCIPAL DO SIMULADOR - Avança o tempo
 *
 * @param numInstantes Quantos "turnos" avançar
 *
 * ALGORITMO (a cada instante):
 * 1. Resetar contadores (permite novas ações)
 * 2. Incrementar instante no jardim
 * 3. Aplicar ferramenta ativa (se jardineiro no jardim)
 * 4. Processar TODAS as plantas (polimorfismo!)
 *    - Cada planta absorve recursos
 *    - Cada planta verifica condições de morte
 *    - Cada planta pode multiplicar-se
 * 5. Verificar mortes (remover plantas mortas)
 * 6. Processar multiplicações
 * 7. Renderizar estado atualizado
 *
 * POLIMORFISMO:
 * - planta->avancaInstante() chama implementação específica
 * - Cacto, Roseira, ErvaDaninha têm comportamentos diferentes
 * - Mesma interface, lógica diferente!
 */
void Simulator::avanca(int numInstantes) {
    if (!jardim) {
        std::cout << "Erro: Jardim nao existe!" << std::endl;
        return;
    }

    for (int i = 0; i < numInstantes; i++) {
        // PASSO 1: Resetar contadores (novo turno)
        resetaContadoresTurno();

        // PASSO 2: Incrementar contador de tempo
        jardim->avancaInstante();

        // PASSO 3: Aplicar ferramenta (automático a cada turno)
        aplicaFerramentaAtiva();

        // PASSO 4: Processar TODAS as plantas
        // IMPORTANTE: Percorrer toda a grelha linha a linha
        for (int l = 0; l < jardim->getLinhas(); l++) {
            for (int c = 0; c < jardim->getColunas(); c++) {
                Posicao* pos = jardim->getPosicao(l, c);
                if (pos && pos->temPlanta()) {
                    Planta* planta = pos->getPlanta();
                    // POLIMORFISMO: cada planta implementa de forma diferente
                    planta->avancaInstante(*pos, *jardim, l, c);
                }
            }
        }

        // PASSO 5: Verificar e remover plantas mortas
        verificaMortes();

        // PASSO 6: Processar multiplicações (plantas que se reproduzem)
        processaMultiplicacoes();

        // PASSO 7: Mostrar estado atualizado
        renderizaJardim();
    }
}

void Simulator::renderizaJardim() const {
    if (!jardim) {
        std::cout << "[Jardim ainda nao foi criado]" << std::endl;
        return;
    }

    // Passar informação do jardineiro para renderização
    if (jardineiro && jardineiro->estaNoJardim()) {
        jardim->renderiza(true, jardineiro->getLinha(), jardineiro->getColuna());
    } else {
        jardim->renderiza(false, -1, -1);
    }
}

void Simulator::listaPlantas() const {
    if (!jardim) {
        std::cout << "Jardim nao existe!" << std::endl;
        return;
    }

    std::cout << "\n=== PLANTAS NO JARDIM ===" << std::endl;
    int count = 0;

    for (int l = 0; l < jardim->getLinhas(); l++) {
        for (int c = 0; c < jardim->getColunas(); c++) {
            const Posicao* pos = jardim->getPosicao(l, c);
            if (pos && pos->temPlanta()) {
                const Planta* planta = pos->getPlanta();
                count++;
                std::cout << count << ". " << planta->getNome()
                          << " (" << planta->getSimbolo() << ") em "
                          << (char)('a'+l) << (char)('a'+c)
                          << " - Agua:" << planta->getAgua()
                          << " Nutr:" << planta->getNutrientes()
                          << " | Solo - Agua:" << pos->getAgua()
                          << " Nutr:" << pos->getNutrientes()
                          << std::endl;
            }
        }
    }

    if (count == 0) {
        std::cout << "Nenhuma planta no jardim." << std::endl;
    }
}

void Simulator::listaPlanta(int linha, int col) const {
    if (!jardim) {
        std::cout << "Jardim nao existe!" << std::endl;
        return;
    }

    const Posicao* pos = jardim->getPosicao(linha, col);
    if (!pos) {
        std::cout << "Posicao invalida!" << std::endl;
        return;
    }

    std::cout << "\n=== POSICAO " << (char)('a'+linha) << (char)('a'+col) << " ===" << std::endl;

    if (pos->temPlanta()) {
        const Planta* planta = pos->getPlanta();
        std::cout << "Planta: " << planta->getNome() << " (" << planta->getSimbolo() << ")" << std::endl;
        std::cout << "  Agua acumulada: " << planta->getAgua() << std::endl;
        std::cout << "  Nutrientes acumulados: " << planta->getNutrientes() << std::endl;
    } else {
        std::cout << "Sem planta" << std::endl;
    }

    std::cout << "Solo - Agua: " << pos->getAgua()
              << ", Nutrientes: " << pos->getNutrientes() << std::endl;
}

void Simulator::listaArea() const {
    if (!jardim) {
        std::cout << "Jardim nao existe!" << std::endl;
        return;
    }

    std::cout << "\n=== POSICOES NAO VAZIAS ===" << std::endl;
    int count = 0;

    for (int l = 0; l < jardim->getLinhas(); l++) {
        for (int c = 0; c < jardim->getColunas(); c++) {
            const Posicao* pos = jardim->getPosicao(l, c);
            if (pos && !pos->estaVazia()) {
                count++;
                std::cout << (char)('a'+l) << (char)('a'+c) << ": ";
                if (pos->temPlanta()) {
                    std::cout << "Planta " << pos->getPlanta()->getSimbolo() << " ";
                }
                if (pos->temFerramenta()) {
                    std::cout << "Ferramenta " << pos->getFerramenta()->getSimbolo() << " ";
                }
                std::cout << "| Agua:" << pos->getAgua()
                          << " Nutr:" << pos->getNutrientes() << std::endl;
            }
        }
    }

    if (count == 0) {
        std::cout << "Todas as posicoes estao vazias." << std::endl;
    }
}

void Simulator::listaSolo(int linha, int col, int raio) const {
    if (!jardim) {
        std::cout << "Jardim nao existe!" << std::endl;
        return;
    }

    std::cout << "\n=== SOLO EM " << (char)('a'+linha) << (char)('a'+col);
    if (raio > 0) {
        std::cout << " (raio " << raio << ")";
    }
    std::cout << " ===" << std::endl;

    for (int l = std::max(0, linha - raio); l <= std::min(jardim->getLinhas() - 1, linha + raio); l++) {
        for (int c = std::max(0, col - raio); c <= std::min(jardim->getColunas() - 1, col + raio); c++) {
            const Posicao* pos = jardim->getPosicao(l, c);
            if (pos) {
                std::cout << (char)('a'+l) << (char)('a'+c) << ": "
                          << "Agua:" << pos->getAgua()
                          << " Nutr:" << pos->getNutrientes();
                if (pos->temPlanta()) {
                    std::cout << " [" << pos->getPlanta()->getSimbolo() << "]";
                }
                if (pos->temFerramenta()) {
                    std::cout << " {" << pos->getFerramenta()->getSimbolo() << "}";
                }
                std::cout << std::endl;
            }
        }
    }
}

void Simulator::listaFerramentas() const {
    if (!jardineiro) {
        std::cout << "Jardineiro nao existe!" << std::endl;
        return;
    }

    jardineiro->listaFerramentas();
}

bool Simulator::colhePlanta(int linha, int col) {
    if (!jardim) {
        std::cout << "Erro: Jardim nao existe!" << std::endl;
        return false;
    }

    // Verificar limite de colheitas por turno
    if (plantasColhidasTurno >= Settings::Jardineiro::max_colheitas) {
        std::cout << "Erro: Ja colheu " << Settings::Jardineiro::max_colheitas
                  << " plantas neste turno!" << std::endl;
        return false;
    }

    Posicao* pos = jardim->getPosicao(linha, col);
    if (!pos) {
        std::cout << "Erro: Posicao invalida!" << std::endl;
        return false;
    }

    if (!pos->temPlanta()) {
        std::cout << "Erro: Nao ha planta nessa posicao!" << std::endl;
        return false;
    }

    // Colher a planta
    if (jardim->removePlanta(linha, col)) {
        plantasColhidasTurno++;
        std::cout << "Planta colhida em " << (char)('a'+linha) << (char)('a'+col) << std::endl;
        return true;
    }

    return false;
}

bool Simulator::plantaPlanta(int linha, int col, char tipo) {
    if (!jardim) {
        std::cout << "Erro: Jardim nao existe!" << std::endl;
        return false;
    }

    // Verificar limite de plantações por turno
    if (plantasPlantadasTurno >= Settings::Jardineiro::max_plantacoes) {
        std::cout << "Erro: Ja plantou " << Settings::Jardineiro::max_plantacoes
                  << " plantas neste turno!" << std::endl;
        return false;
    }

    Posicao* pos = jardim->getPosicao(linha, col);
    if (!pos) {
        std::cout << "Erro: Posicao invalida!" << std::endl;
        return false;
    }

    if (pos->temPlanta()) {
        std::cout << "Erro: Ja existe uma planta nessa posicao!" << std::endl;
        return false;
    }

    // Criar nova planta
    Planta* novaPlanta = criaPlanta(tipo);
    if (!novaPlanta) {
        std::cout << "Erro: Tipo de planta invalido!" << std::endl;
        return false;
    }

    // Plantar
    if (jardim->adicionaPlanta(linha, col, novaPlanta)) {
        plantasPlantadasTurno++;
        std::cout << "Planta '" << tipo << "' plantada em "
                  << (char)('a'+linha) << (char)('a'+col) << std::endl;
        return true;
    }

    delete novaPlanta;
    return false;
}

void Simulator::largaFerramenta() {
    if (jardineiro->largaFerramenta()) {
        std::cout << "Ferramenta largada" << std::endl;
    } else {
        std::cout << "Nao ha ferramenta na mao" << std::endl;
    }
}

bool Simulator::pegaFerramenta(int numSerie) {
    if (jardineiro->pegaFerramenta(numSerie)) {
        std::cout << "Ferramenta #" << numSerie << " pegada" << std::endl;
        return true;
    }
    std::cout << "Ferramenta #" << numSerie << " nao encontrada" << std::endl;
    return false;
}

void Simulator::compraFerramenta(char tipo) {
    Ferramenta* nova = criaFerramenta(tipo);
    if (!nova) {
        std::cout << "Tipo de ferramenta invalido!" << std::endl;
        return;
    }

    jardineiro->adicionaFerramenta(nova);
    std::cout << "Ferramenta '" << tipo << "' #" << nova->getNumeroSerie()
              << " comprada!" << std::endl;
}

bool Simulator::moveJardineiro(char direcao) {
    if (!jardineiro->estaNoJardim()) {
        std::cout << "Jardineiro nao esta no jardim!" << std::endl;
        return false;
    }

    if (!jardineiro->podeMoverse()) {
        std::cout << "Limite de movimentos atingido! Avance o tempo." << std::endl;
        return false;
    }

    int linha = jardineiro->getLinha();
    int col = jardineiro->getColuna();

    // Calcular nova posição
    switch (direcao) {
        case 'c': linha--; break;  // cima
        case 'b': linha++; break;  // baixo
        case 'e': col--; break;    // esquerda
        case 'd': col++; break;    // direita
        default:
            std::cout << "Direcao invalida!" << std::endl;
            return false;
    }

    // Verificar se a nova posição é válida
    if (!jardim || !jardim->posicaoValida(linha, col)) {
        std::cout << "Movimento invalido!" << std::endl;
        return false;
    }

    // Mover
    jardineiro->move(linha, col);

    // Apanhar ferramenta se existir
    apanhaFerramentaSeExistir(linha, col);

    std::cout << "Jardineiro moveu para " << (char)('a'+linha) << (char)('a'+col) << std::endl;
    return true;
}

bool Simulator::entraJardineiro(int linha, int col) {
    jardineiro->entra(linha, col);
    std::cout << "[OK] Jardineiro entrou em " << (char)('a'+linha) << (char)('a'+col) << std::endl;
    return true;
}

bool Simulator::saiJardineiro() {
    jardineiro->sai();
    std::cout << "[OK] Jardineiro saiu do jardim" << std::endl;
    return true;
}

void Simulator::gravaEstado(const std::string& nome) {
    std::cout << "[TODO] Gravar estado '" << nome << "'" << std::endl;
    // TODO Meta 2: Implementar cópia profunda
}

bool Simulator::recuperaEstado(const std::string& nome) {
    std::cout << "[TODO] Recuperar estado '" << nome << "'" << std::endl;
    // TODO Meta 2: Implementar cópia profunda
    return false;
}

void Simulator::apagaEstado(const std::string& nome) {
    std::cout << "[TODO] Apagar estado '" << nome << "'" << std::endl;
    // TODO Meta 2
}

// Factory method for creating plants
Planta* Simulator::criaPlanta(char tipo) const {
    switch (tipo) {
        case 'c':
        case 'C':
            return new Cacto();
        case 'r':
        case 'R':
            return new Roseira();
        case 'e':
        case 'E':
            return new ErvaDaninha();
        case 'x':
        case 'X':
            return new PlantaExotica();
        default:
            return nullptr;
    }
}

// Factory method for creating tools
Ferramenta* Simulator::criaFerramenta(char tipo) const {
    static int proximoNumeroSerie = 1;

    switch (tipo) {
        case 'g':
        case 'G':
            return new Regador(proximoNumeroSerie++);
        case 'a':
        case 'A':
            return new PacoteAdubo(proximoNumeroSerie++);
        case 't':
        case 'T':
            return new TesouraPoda(proximoNumeroSerie++);
        case 'z':
        case 'Z':
            return new FerramentaZ(proximoNumeroSerie++);
        default:
            return nullptr;
    }
}

// Métodos helper privados
void Simulator::resetaContadoresTurno() {
    plantasColhidasTurno = 0;
    plantasPlantadasTurno = 0;
    entrouEsteTurno = false;
    saiuEsteTurno = false;
    if (jardineiro) {
        jardineiro->resetaMovimentosTurno();
    }
}

void Simulator::aplicaFerramentaAtiva() {
    if (!jardineiro || !jardineiro->estaNoJardim()) {
        return;
    }

    Ferramenta* ferr = jardineiro->getFerramentaNaMao();
    if (!ferr) {
        return;
    }

    // Aplicar ferramenta na posição do jardineiro
    Posicao* pos = jardim->getPosicao(jardineiro->getLinha(), jardineiro->getColuna());
    if (pos) {
        ferr->aplicar(pos);

        // Remover ferramenta se ficou gasta
        if (ferr->estaGasta()) {
            std::cout << "Ferramenta #" << ferr->getNumeroSerie() << " gastou-se!" << std::endl;
            jardineiro->removeFerramentaGasta();
        }
    }
}

void Simulator::apanhaFerramentaSeExistir(int linha, int col) {
    Posicao* pos = jardim->getPosicao(linha, col);
    if (pos && pos->temFerramenta()) {
        Ferramenta* ferr = pos->removeFerramenta();
        if (ferr) {
            jardineiro->adicionaFerramenta(ferr);
            std::cout << "Ferramenta #" << ferr->getNumeroSerie() << " apanhada!" << std::endl;

            // Colocar nova ferramenta aleatória no jardim
            colocaFerramentasIniciais();
        }
    }
}

void Simulator::colocaFerramentasIniciais() {
    if (!jardim) return;

    // Colocar 1 ferramenta aleatória em posição aleatória
    char tipos[] = {'g', 'a', 't', 'z'};
    char tipoAleatorio = tipos[RandomGenerator::getInt(0, 3)];

    int linhaAleatorio = RandomGenerator::getInt(0, jardim->getLinhas() - 1);
    int colAleatorio = RandomGenerator::getInt(0, jardim->getColunas() - 1);

    Ferramenta* ferr = criaFerramenta(tipoAleatorio);
    jardim->adicionaFerramenta(linhaAleatorio, colAleatorio, ferr);
}

void Simulator::verificaMortes() {
    if (!jardim) return;

    for (int l = 0; l < jardim->getLinhas(); l++) {
        for (int c = 0; c < jardim->getColunas(); c++) {
            Posicao* pos = jardim->getPosicao(l, c);
            if (pos && pos->temPlanta()) {
                Planta* planta = pos->getPlanta();
                if (planta->deveMorrer()) {
                    std::cout << "Planta " << planta->getSimbolo() << " morreu em "
                              << (char)('a'+l) << (char)('a'+c) << std::endl;
                    planta->aoMorrer(*pos);
                    jardim->removePlanta(l, c);
                }
            }
        }
    }
}

void Simulator::processaMultiplicacoes() {
    // TODO: Implementar multiplicação de plantas
    // Por agora deixamos vazio - as plantas chamam isto mas não fazem nada ainda
}

void Simulator::libertaEstadosGravados() {
    estadosGravados.clear();
    jardineirosGravados.clear();
}
