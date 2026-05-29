# Global Solution - Data Structures and Algorithms


# Participantes


Lucca Bracco RM: 570175


João Pedro Ferrari RM: 573037


Vitor Nascimento RM: 571873


# Explicação da Lógica Utilizada

Relatório Técnico do Sistema de Telemetria:

Modelagem dos Dados através de Estruturas (struct): As variáveis globais de telemetria foram centralizadas em uma struct customizada nomeada MissaoEspacial. O grande diferencial desta nova versão do software foi a inclusão do campo inteiro alertas_emitidos dentro da própria estrutura. Isso permite que a contagem e análise dos riscos ocorram no exato momento da aquisição dos dados (Caso 1), fixando o estado crítico da nave de maneira imutável para posterior consulta.


Persistência de Dados via Vetores (Histórico): Para implementar a funcionalidade de histórico sem o uso de arquivos externos, foi alocado um vetor estático de estruturas (MissaoEspacial historicoLeituras[10]). Uma lógica de deslocamento de memória (shift queue) foi implementada: caso o limite de 10 leituras seja atingido, as posições mais antigas do vetor são empurradas para trás, abrindo espaço no final para o registro mais recente.


Tratamento Preventivo de Erros (Simulação de Exceções): Como a linguagem C padrão carece de blocos nativos de try-catch, o software utiliza uma validação lógica sobre o retorno da função scanf(). Caso o usuário forneça um caractere alfabético inesperado no terminal, o programa intercepta a falha, executa uma rotina manual de limpeza de buffer com getchar() e evita travamentos ou loops infinitos no menu principal.


Modularização e Clean Code: O sistema foi dividido inteiramente em funções reutilizáveis (inserirDados, visualizarStatus, exibirHistorico), reduzindo a complexidade do escopo da função main e tornando a manutenção e expansão do código mais eficientes.
