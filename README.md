# 2x2RubikAI 

Um projeto em **C** para resolver o **Cubo Mágico 2x2 (Pocket Cube)** utilizando algoritmos de busca.  
O objetivo é implementar e comparar diferentes estratégias de resolução, como **Busca em Largura (BFS)**, **Busca em Profundidade Iterativa**, **A\***, analisando desempenho e custo computacional.  
 
---

## 🚀 Funcionalidades  

- Representação do cubo 2x2 em estrutura de dados.  
- Aplicação de movimentos básicos do cubo.  
- Implementação dos diferentes algoritmos de busca.  
- Interface em linha de comando (CLI) para interação com o usuário.  
- Exibição passo a passo da solução encontrada.  
- **Entrada personalizada**: o usuário pode inserir o estado atual do **seu próprio cubo** para a IA resolver.  
- **Modo jogador (livre)**:  
  - O usuário pode manipular **seu próprio cubo inserido**.  
  - Ou pode jogar em um **cubo aleatório** embaralhado pelo programa.  

## 📂 Estrutura do Projeto  

    2x2RubikAI/
    ├── include/   # Arquivos de cabeçalho (.h)
    ├── src/       # Implementações principais (.c)
    ├── obj/       # Objetos compilados
    ├── bin/       # Executáveis gerados
    ├── Makefile   # Script de build
    └── README.md  # Este arquivo

---
## 🔧 Como rodar a aplicação 

### Pré-requisitos  
- GCC ou outro compilador C  
- Make  

### Compilação 
---
- Primeiro compilar as dependências de app/lookup_table_gen.c 
```bash
make lookup_table
```
- Executar o arquivo gerado
```bash
./bin/lookup-tb
```
---
- Compilar as dependências de app/main.c
```bash
make lookup_table
```

### Execução
- Executar o arquivo gerado
```bash
./bin/rubik
```
---

### *Sem makefile*

Para gerar o rubik
```bash
gcc -Wall -Wextra -g -Iinclude src/*.c apps/main.c -o bin/rubik
```
Para gerar o lookup-tb
```bash

gcc -Wall -Wextra -g -Iinclude src/*.c apps/main.c -o bin/rubik
```

## 📊 Algoritmos suportados
- BFS (Busca em Largura)
- Iterative Deepening
- A* com heurísticas

## 🎯 Objetivos Acadêmicos

Este projeto também tem caráter experimental e educacional, com foco em:

- Explorar a aplicação de algoritmos clássicos de busca em problemas combinatórios;

- Comparar eficiência e custo entre diferentes estratégias;

- Desenvolver base para pesquisas em Inteligência Artificial e Heurísticas de Busca.
