# SimGarden
TP_POO

# Simulador de Jardim - POO 2025/2026
## Meta 1 - Estrutura e Validação de Comandos

### Estrutura de Ficheiros

```
projeto/
├── CMakeLists.txt          # Configuração CLion
├── main.cpp                # Ponto de entrada
│
├── Simulador.h/.cpp        # Coordenador central
├── Interface.h/.cpp        # Processamento de comandos
├── Validador.h/.cpp        # Validações centralizadas (NOVO!)
├── Jardim.h/.cpp           # Grelha 2D (SEM vectors!)
├── Posicao.h/.cpp          # Célula do jardim
├── Jardineiro.h/.cpp       # Personagem controlável
│
├── Planta.h/.cpp           # Classe base abstrata
├── Cacto.h/.cpp            # Subclasse (stub)
├── Roseira.h/.cpp          # Subclasse (stub)
├── ErvaDaninha.h/.cpp      # Subclasse (stub)
├── PlantaExotica.h/.cpp    # Subclasse (stub)
│
├── Ferramenta.h/.cpp       # Classe base abstrata
├── Regador.h/.cpp          # Subclasse (stub)
├── PacoteAdubo.h/.cpp      # Subclasse (stub)
├── TesouraPoda.h/.cpp      # Subclasse (stub)
├── FerramentaZ.h/.cpp      # Subclasse (stub)
│
└── Settings.h              # Constantes (fornecido)
```

### Compilação no CLion

1. Abrir o CLion
2. File → Open → Selecionar pasta do projeto
3. CMake carrega automaticamente
4. Build → Build Project (Ctrl+F9)
5. Run → Run 'SimuladorJardim' (Shift+F10)

### Funcionalidades Implementadas (Meta 1)

#### ✅ Sistema de Comandos
- Parsing completo de todos os comandos
- Validação de sintaxe e parâmetros
- Mensagens de erro apropriadas
- Suporte para ficheiros de comandos

#### ✅ Estrutura de Classes
- Hierarquia de Plantas (base + 4 subclasses)
- Hierarquia de Ferramentas (base + 4 subclasses)
- Jardim com array 2D dinâmico (SEM vectors)
- Jardineiro com controle de estado
- Simulador coordenando tudo

#### ✅ Validações
- Limites de ações por turno
- Coordenadas no formato letra-letra
- Tipos válidos de plantas e ferramentas
- Dimensões do jardim (1-26 x 1-26)

### Comandos Disponíveis

**Criação:**
- `jardim <linhas> <colunas>` - Criar jardim (obrigatório primeiro)

**Tempo:**
- `avanca [n]` - Avançar n instantes (padrão: 1)

**Listagem:**
- `lplantas` - Listar todas as plantas
- `lplanta <pos>` - Info de planta específica (ex: `lplanta bc`)
- `larea` - Listar posições não vazias
- `lsolo <pos> [raio]` - Info do solo (ex: `lsolo df 2`)
- `lferr` - Listar ferramentas do jardineiro

**Ações:**
- `colhe <pos>` - Colher planta (max 5/turno)
- `planta <pos> <tipo>` - Plantar (c/r/e/x, max 2/turno)
- `compra <tipo>` - Comprar ferramenta (g/a/t/z)
- `pega <num>` - Pegar ferramenta pelo número série
- `larga` - Largar ferramenta da mão

**Movimento:**
- `entra <pos>` - Entrar no jardim
- `sai` - Sair do jardim
- `e/d/c/b` - Mover esquerda/direita/cima/baixo (max 10/turno)

**Persistência:**
- `grava <nome>` - Gravar estado
- `recupera <nome>` - Recuperar estado
- `apaga <nome>` - Apagar estado gravado

**Sistema:**
- `executa <ficheiro>` - Executar comandos de ficheiro
- `fim` - Terminar simulador

### Exemplos de Uso

```bash
> jardim 10 12
> entra aa
> compra g
> pega 1
> avanca 5
> lplantas
> fim
```

### Ficheiro de Teste (teste.txt)

```
jardim 8 8
entra dd
compra g
compra a
pega 1
planta aa c
planta bb r
planta cc e
avanca 3
lplantas
larea
sai
fim
```

Executar: `executa teste.txt`

### Para Meta 2

As seguintes funcionalidades estão como stubs (TODO):
- ❌ Lógica completa de comportamento das plantas
- ❌ Condições de morte específicas
- ❌ Multiplicação de plantas
- ❌ Aplicação completa de ferramentas
- ❌ Cópia profunda para grava/recupera

### Notas Importantes

1. **Grelha do Jardim**: Usa `Posicao**` (array 2D), NÃO usa `vector`
2. **Ferramentas do Jardineiro**: Pode usar `std::vector` 
3. **Números de Série**: Contador estático automático
4. **Coordenadas**: Formato `aa` a `zz` (linha-coluna)
5. **Prioridade Visual**: Jardineiro > Planta > Ferramenta

### Checklist Meta 1

- [x] Parsing de todos os comandos
- [x] Validação completa de sintaxe
- [x] Estrutura de classes definida
- [x] Hierarquia de herança (Planta, Ferramenta)
- [x] Organização em .h e .cpp
- [x] Jardim sem usar vectors
- [x] Compila sem warnings
- [x] Relatório (máx 5 páginas)
