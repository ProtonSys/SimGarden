#include "core/Interface.h"
#include "core/Simulator.h"
#include <iostream>

using namespace std;

void mostraBanner() {
    cout << "========================================" << endl;
    cout << "    SIMULADOR DE JARDIM - POO 25/26    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Comandos disponiveis:" << endl;
    cout << "  jardim <linhas> <colunas>  - Criar jardim" << endl;
    cout << "  avanca [n]                 - Avancar n instantes" << endl;
    cout << "  lplantas                   - Listar todas as plantas" << endl;
    cout << "  lplanta <pos>              - Info de uma planta" << endl;
    cout << "  larea                      - Listar area nao vazia" << endl;
    cout << "  lsolo <pos> [raio]         - Info do solo" << endl;
    cout << "  lferr                      - Listar ferramentas" << endl;
    cout << "  colhe <pos>                - Colher planta" << endl;
    cout << "  planta <pos> <tipo>        - Plantar (c/r/e/x)" << endl;
    cout << "  larga                      - Largar ferramenta" << endl;
    cout << "  pega <num>                 - Pegar ferramenta" << endl;
    cout << "  compra <tipo>              - Comprar ferramenta (g/a/t/z)" << endl;
    cout << "  e/d/c/b                    - Mover jardineiro" << endl;
    cout << "  entra <pos>                - Entrar no jardim" << endl;
    cout << "  sai                        - Sair do jardim" << endl;
    cout << "  grava <nome>               - Gravar estado" << endl;
    cout << "  recupera <nome>            - Recuperar estado" << endl;
    cout << "  apaga <nome>               - Apagar estado gravado" << endl;
    cout << "  executa <ficheiro>         - Executar comandos de ficheiro" << endl;
    cout << "  fim                        - Terminar simulador" << endl;
    cout << endl;
    cout << "Nota: Posicoes sao indicadas com duas letras (ex: aa, bc, kj)" << endl;
    cout << "========================================" << endl;
    cout << endl;
}

int main() {
    // Inicializar seed para numeros aleatorios
    srand(static_cast<unsigned>(time(nullptr)));

    // Mostrar banner inicial
    mostraBanner();

    // Criar simulador e interface
    Simulator sim;
    Interface interface(&sim);

    string comando;
    bool continuar = true;

    // Loop principal
    while (continuar) {
        cout << "> ";

        // Ler linha completa (pode ter espacos)
        if (!getline(cin, comando)) {
            // EOF ou erro de leitura
            break;
        }

        // Processar comando
        // processaComando retorna false se for "fim"
        continuar = interface.processaComando(comando);
    }

    // Mensagem de despedida
    cout << endl;
    cout << "========================================" << endl;
    cout << "   Simulador encerrado. Ate breve!     " << endl;
    cout << "========================================" << endl;

    return 0;
}