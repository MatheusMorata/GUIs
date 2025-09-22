# Exercício 2.1

Este programa implementa um sistema de detecção de combinações de cliques do mouse inspirado nas sequências de comandos dos jogos de luta arcade. O comportamento segue uma máquina de estados que reconhece padrões temporais de cliques:

### Estados

- Parado: Estado inicial, aguardando clique

- 1 Clique: Primeiro clique detectado

- 2 Cliques: Sequência rápida detectada

- 3 Cliques: Combinação máxima reconhecida

### Ações

- 2 Cliques: Executa animação completa + disparo de munição

- 3 Cliques: Executa animação completa + disparo de espada

A inspiração direta vem dos famosos comandos especiais dos jogos de luta como: 

- Street Fighter 
- Mortal Kombat

A solução proposta para o exercício captura a essência dos combos dos jogos de luta, onde a precisão temporal e a sequência correta de inputs determinam a execução de movimentos especiais.