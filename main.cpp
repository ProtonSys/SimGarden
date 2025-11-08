#include "core/Interface.h"
#include "core/Simulator.h"
#include <iostream>
#include <string>

void mostraBanner() {
    std::cout << "========================================" << std::endl;
    std::cout << "    SIMULADOR DE JARDIM - POO 25/26    " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Comandos disponiveis:" << std::endl;
    std::cout << "  jardim <linhas> <colunas>  - Criar jardim" << std::endl;
    std::cout << "  avanca [n]                 - Avancar n instantes" << std::endl;
    std::cout << "  lplantas                   - Listar todas as plantas" << std::endl;
    std::cout << "  lplanta <pos>              - Info de uma planta" << std::endl;
    std::cout << "  larea                      - Listar area nao vazia" << std::endl;
    std::cout << "  lsolo <pos> [raio]         - Info do solo" << std::endl;
    std::cout << "  lferr                      - Listar ferramentas" << std::endl;
    std::cout << "  colhe <pos>                - Colher planta" << std::endl;
    std::cout << "  planta <pos> <tipo>        - Plantar (c/r/e/x)" << std::endl;
    std::cout << "  larga                      - Largar ferramenta" << std::endl;
    std::cout << "  pega <num>                 - Pegar ferramenta" << std::endl;
    std::cout << "  compra <tipo>              - Comprar ferramenta (g/a/t/z)" << std::endl;
    std::cout << "  e/d/c/b                    - Mover jardineiro" << std::endl;
    std::cout << "  entra <pos>                - Entrar no jardim" << std::endl;
    std::cout << "  sai                        - Sair do jardim" << std::endl;
    std::cout << "  grava <nome>               - Gravar estado" << std::endl;
    std::cout << "  recupera <nome>            - Recuperar estado" << std::endl;
    std::cout << "  apaga <nome>               - Apagar estado gravado" << std::endl;
    std::cout << "  executa <ficheiro>         - Executar comandos de ficheiro" << std::endl;
    std::cout << "  fim                        - Terminar simulador" << std::endl;
    std::cout << std::endl;
    std::cout << "Nota: Posicoes sao indicadas com duas letras (ex: aa, bc, kj)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

int main() {
    // Mostrar banner inicial
    mostraBanner();

    // Criar simulador e interface
    Simulator sim;
    Interface interface(&sim);

    std::string comando;
    bool continuar = true;

    // Loop principal
    while (continuar) {
        std::cout << "> ";

        // Ler linha completa (pode ter espacos)
        if (!std::getline(std::cin, comando)) {
            // EOF ou erro de leitura
            break;
        }

        // Processar comando
        // processaComando retorna false se for "fim"
        continuar = interface.processaComando(comando);
    }

    // Mensagem de despedida
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "   Simulador encerrado. Ate breve!     " << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}