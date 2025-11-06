# 🌱 Simulador de Jardim - POO 2025/2026

**Autores:** CelsoJordão - 2003008910  
**Curso:** Engenharia Informática - ISEC  
**Cadeira:** Programação Orientada a Objetos  
**Meta:** 1 (de 2)

---

## 📋 Descrição

Simulador de jardim baseado em turnos implementado em C++. O utilizador controla um jardineiro virtual que pode:
- Criar e gerir um jardim representado por uma grelha bidimensional
- Plantar e colher diferentes tipos de plantas (Cacto, Roseira, Erva Daninha, Planta Exótica)
- Usar ferramentas (Regador, Pacote de Adubo, Tesoura de Poda, Super Fertilizador)
- Movimentar-se pelo jardim
- Gravar e recuperar estados do jogo

---

## ⚙️ Requisitos

- **Compilador:** C++17 ou superior
- **Build System:** CMake 3.20+
- **IDE:** CLion (recomendado) ou qualquer editor com suporte CMake
- **Sistema Operativo:** Linux, macOS, Windows

---

## 🚀 Compilação

### Usando CLion
1. Abrir CLion
2. `File` → `Open` → Selecionar pasta do projeto
3. CMake carrega automaticamente
4. `Build` → `Build Project` (Ctrl+F9 / Cmd+F9)
5. `Run` → `Run 'SimuladorJardim'` (Shift+F10)

### Linha de Comandos
```bash
# Criar diretório de build
mkdir build
cd build

# Configurar com CMake
cmake ..

# Compilar
make

# Executar
./SimuladorJardim
```

### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
Release\SimuladorJardim.exe
```

---

## 📂 Estrutura do Projeto

```
SimuladorJardim/
│
├── core/
│   ├── Simulator.h / .cpp        # Coordenador central
│   ├── Interface.h / .cpp        # Processamento de comandos
│   └── Validador.h / .cpp        # Validações centralizadas
│
├── jardim/
│   ├── Jardim.h / .cpp           # Grelha 2D (SEM vector!)
│   └── Posicao.h / .cpp          # Célula individual
│
├── jardineiro/
│   └── Jardineiro.h / .cpp       # Personagem jogável
│
├── plantas/
│   ├── Planta.h / .cpp           # Base abstrata
│   ├── Cacto.h / .cpp            # Planta neutra
│   ├── Roseira.h / .cpp          # Planta bonita
│   ├── ErvaDaninha.h / .cpp      # Planta feia
│   └── PlantaExotica.h / .cpp    # Planta especial
│
├── ferramentas/
│   ├── Ferramenta.h / .cpp       # Base abstrata
│   ├── Regador.h / .cpp          # Adiciona água
│   ├── PacoteAdubo.h / .cpp      # Adiciona nutrientes
│   ├── TesouraPoda.h / .cpp      # Remove plantas feias
│   └── FerramentaZ.h / .cpp      # Super fertilizador
│
├── config/
│   └── Settings.h                # Constantes do jogo
│
├── main.cpp                      # Ponto de entrada
├── CMakeLists.txt                # Configuração CMake
└── README.md                     # Este ficheiro
```

---

## 🎮 Como Usar

### Iniciar o Programa
```bash
./SimuladorJardim
```

### Interface
```
Simulador de Jardim - POO 25/26
Digite 'fim' para sair

> _
```

### Primeiro Comando (Obrigatório)
```bash
> jardim 10 12
Jardim 10x12 criado!
```

Cria um jardim com 10 linhas e 12 colunas (dimensões: 1-26 x 1-26)

---

## 📖 Comandos Disponíveis

### 🏗️ Criação
```bash
jardim <linhas> <colunas>    # Criar jardim (1-26 x 1-26)
```

### ⏰ Tempo
```bash
avanca [n]                   # Avançar n instantes (padrão: 1)
```

### 📊 Listagem
```bash
lplantas                     # Listar todas as plantas
lplanta <pos>                # Info de planta específica (ex: lplanta bc)
larea                        # Listar posições não vazias
lsolo <pos> [raio]           # Info do solo (ex: lsolo df 2)
lferr                        # Listar ferramentas do jardineiro
```

### 🌱 Ações sobre Plantas
```bash
colhe <pos>                  # Colher planta (max 5/turno)
planta <pos> <tipo>          # Plantar (c/r/e/x, max 2/turno)
```

**Tipos de planta:**
- `c` - Cacto (neutra)
- `r` - Roseira (bonita)
- `e` - Erva Daninha (feia)
- `x` - Planta Exótica

### 🔧 Ferramentas
```bash
compra <tipo>                # Comprar ferramenta (g/a/t/z)
pega <numero>                # Pegar ferramenta pelo nº série
larga                        # Largar ferramenta da mão
```

**Tipos de ferramenta:**
- `g` - Regador (200 água)
- `a` - Pacote Adubo (100 nutrientes)
- `t` - Tesoura Poda (nunca gasta)
- `z` - Super Fertilizador (5 usos)

### 🚶 Movimento do Jardineiro
```bash
entra <pos>                  # Entrar no jardim (ex: entra dd)
sai                          # Sair do jardim
e                            # Mover esquerda
d                            # Mover direita
c                            # Mover cima
b                            # Mover baixo
```

**Limites:** 10 movimentos por turno

### 💾 Persistência
```bash
grava <nome>                 # Gravar estado atual
recupera <nome>              # Recuperar estado gravado
apaga <nome>                 # Apagar estado gravado
```

### 📁 Ficheiros
```bash
executa <ficheiro>           # Executar comandos de ficheiro
```

### 🚪 Sistema
```bash
fim                          # Terminar simulador
```

---

## 📝 Exemplos de Uso

### Exemplo 1: Criar e Explorar Jardim
```bash
> jardim 5 5
Jardim 5x5 criado!
 ABCDE
A     A
B     B
C     C
D     D
E     E
 ABCDE
Instante: 0

> entra cc
[OK] Jardineiro entrou em cc

> d
[TODO] Mover jardineiro d

> sai
[OK] Jardineiro saiu do jardim
```

### Exemplo 2: Plantar e Colher
```bash
> jardim 8 8
> planta aa c
[OK] Comando valido (nao implementado)

> planta bb r
[OK] Comando valido (nao implementado)

> avanca 5
[TODO] Avancar 5 instantes

> colhe aa
[OK] Comando valido (nao implementado)
```

### Exemplo 3: Usar Ficheiro de Comandos
Criar `teste.txt`:
```
jardim 10 10
entra ee
compra g
compra a
pega 1
planta aa c
planta bb r
avanca 3
lplantas
sai
fim
```

Executar:
```bash
> executa teste.txt
```

---

## 🗺️ Sistema de Coordenadas

As posições são indicadas com **duas letras** (linha e coluna):

```
 ABCDEFGH
A        A    aa = linha A, coluna A (canto superior esquerdo)
B        B    bc = linha B, coluna C
C        C    hh = linha H, coluna H
D        D
```

**Exemplos:**
- `aa` = posição (0,0)
- `bc` = posição (1,2)
- `zz` = posição (25,25) - máximo

---

## ⚡ Funcionalidades Meta 1

### ✅ Implementado
- [x] Validação completa de todos os comandos
- [x] Parsing robusto com mensagens de erro
- [x] Estrutura de classes bem definida
- [x] Grelha 2D dinâmica **SEM vector**
- [x] Sistema de coordenadas (aa-zz)
- [x] Jardineiro entra/sai do jardim
- [x] Renderização com réguas
- [x] Execução de ficheiros de comandos
- [x] Hierarquias de herança (Planta, Ferramenta)
- [x] Includes organizados
- [x] Código compila sem warnings

### ⏳ Para Meta 2
- [ ] Comportamento completo das plantas
- [ ] Sistema de multiplicação
- [ ] Ferramentas ativas (aplicação automática)
- [ ] Movimento completo do jardineiro
- [ ] Comandos de listagem com informação real
- [ ] Sistema save/load funcional
- [ ] Limites de ações por turno

---

## 🏗️ Arquitetura

### Design Patterns Aplicados

**Factory Method**
```cpp
Planta* Simulator::criaPlanta(char tipo) {
    switch (tipo) {
        case 'c': return new Cacto();
        case 'r': return new Roseira();
        // ...
    }
}
```

**Strategy (Map de Comandos)**
```cpp
std::map<string, function<bool(istringstream&)>> comandos;
comandos["jardim"] = [this](auto& iss) { return cmdJardim(iss); };
```

**Template Method**
```cpp
class Planta {
    virtual void avancaInstante(...) = 0;  // Implementado nas subclasses
};
```

**Utility Class**
```cpp
class Validador {
    static bool validaCoordenada(...);  // Apenas métodos estáticos
private:
    Validador() = delete;  // Não pode instanciar
};
```

### Princípios SOLID

- **S**ingle Responsibility: Cada classe tem um propósito único
- **O**pen/Closed: Fácil adicionar plantas/ferramentas sem modificar base
- **L**iskov Substitution: Subclasses substituíveis pelas bases
- **I**nterface Segregation: Interfaces mínimas e específicas
- **D**ependency Inversion: Depende de abstrações (Planta, Ferramenta)

---

## 🎓 Decisões Técnicas

### Grelha SEM vector
```cpp
class Jardim {
    Posicao** grelha;  // Array 2D dinâmico
    
    Jardim(int l, int c) {
        grelha = new Posicao*[l];
        for (int i = 0; i < l; i++) {
            grelha[i] = new Posicao[c];
        }
    }
};
```

**Razão:** Enunciado proíbe `std::vector` para solo.

### Map de Comandos
```cpp
std::map<string, function<bool(istringstream&)>> comandos;
```

**Vantagens:**
- Busca O(log n) vs O(n) linear
- Fácil adicionar comandos
- Código limpo

### Validador Centralizado
```cpp
class Validador {
public:
    static bool validaCoordenada(...);
    static bool validaInt(...);
    // ...
};
```

**Vantagens:**
- Reutilização total
- Manutenção centralizada
- Zero duplicação

---

## 🐛 Resolução de Problemas

### Erro: "Jardim já foi criado"
**Causa:** Tentativa de criar jardim múltiplas vezes  
**Solução:** O comando `jardim` só pode ser usado uma vez por execução

### Erro: "Deve criar o jardim primeiro"
**Causa:** Comando executado sem jardim criado  
**Solução:** Executar `jardim <l> <c>` primeiro

### Erro: "Dimensoes invalidas"
**Causa:** Dimensões fora do intervalo 1-26  
**Solução:** Usar valores entre 1 e 26 para linhas e colunas

### Erro: "Coordenada invalida"
**Causa:** Formato incorreto (não são duas letras)  
**Solução:** Usar formato "aa" a "zz" (duas letras minúsculas)

### Warning: "unused parameter"
**Causa:** Parâmetro não usado em métodos stub  
**Solução:** Adicionar `(void)param;` ou aguardar Meta 2

---

## 📊 Estatísticas

- **Classes:** 16
- **Ficheiros:** ~35 (.h + .cpp)
- **Linhas de código:** ~2000
- **Comandos:** 20
- **Validações:** 10 tipos

---

## 📚 Referências

- **Enunciado:** POO - 2526 - Enunciado Trabalho Pratico.pdf
- **Linguagem:** C++17
- **Build System:** CMake
- **IDE:** CLion 2024

---

## 👥 Autores

- **Celso Jordão** - 2003008910 - a21130067@isec.pt


**Turma:** [Turma]  
**Ano Letivo:** 2025/2026  
**Data: Novembro 2025

---

## 📄 Licença

Este projeto é trabalho académico para a cadeira de Programação Orientada a Objetos do ISEC.

---

## 🙏 Agradecimentos

Agradecemos aos docentes da cadeira pelo acompanhamento e esclarecimentos durante o desenvolvimento do trabalho.
