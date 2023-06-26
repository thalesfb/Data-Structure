# Implementação de uma Tabela Hash

## Instruções Gerais

Este projeto implementa uma lista encadeada dupla para a inserção, consulta, contagem de elementos por chave e remoção de uma tabela hash. Ele também inclui um método de ordenação QuickSort e hashing com encadeamento. A base de dados utilizada contém 100.788 nomes de brasileiros registrados no ano de 2018 e a função de hash modular foi a modular que gerou uma tabela com 53 chaves.

## Metodologia

Foram utilizados os materiais disponibilizados pelo professor, livro TENENBAUM, Aaron M.; LANGSAM, Yedidyah; AUGENSTEIN, Moshe. Estruturas de dados usando C. São Paulo: Pearson Makron Books, 1995. xx, 884 p. ISBN 8534603480 e também pesquisas na internet.

## Tratamento de Colisão

Como foi imposto pelo professor a utilização de lista duplamente encadeada, não ocorrem colisões, mas poderiamos imaginar um cenário onde se tem um limite de dados por chave em que devemos avaliar antes da inserção de novos elementos.

### Quando Deveria Ser Implementado o Tratamento de Colisão?

A colisão deveria ser implantada quando excedido o limite de registros em uma determinada chave.

### Como Poderia Ser Esta Implementação?

O tratamento da colisão poderia ser feito através da solução mais comum, a sondagem linear, que após identificar que uma determinada chave está no seu limite, é avaliado a próxima chave, se estiver disponível é inserido o registro, caso contrário, é avaliada a próxima chave, e assim por diante.

### Avaliação da Tabela Hash

A tabela hash gerada ficou visualmente uniforme, tendo média de 1.902 nomes por chave. Um descio padrão de 55 nomes que representa 2,89% em relação a média

## Análise de Frequência

Aproximadamente uniforme, a tabela hash gerada, se enquadra.

## Ordenação dos Elementos

A ordenação, como proposto, foi utilizado o método quick sort,

## Distribuição dos Nomes

[Apresente e explique o histograma que mostra a distribuição dos nomes em cada uma das chaves.]

## Conclusão

[Aqui você pode responder à pergunta: a hipótese do hashing uniforme foi alcançada? Além disso, resuma os resultados do seu projeto e qualquer outra conclusão que você tenha.]

## Figuras e Gráficos

[Inclua quaisquer figuras ou gráficos que demonstrem a resolução e os resultados obtidos.]

---

Este projeto foi desenvolvido por Thales Ferreira para o Th. Para mais detalhes, consulte o código-fonte no [link do repositório do GitHub].
