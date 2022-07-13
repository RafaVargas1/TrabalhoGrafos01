# TrabalhoGrafos01

# Execução

- Para executar o arquivo é necessário primeiro compilar o código e depois executá-lo. Os comandos para fazer isso através do terminal são respectivamente:
  
    ``` 
    g++ main.cpp -o execGrupo26
    ./execGrupo26 grafo_1000_1.txt saida.txt 0 0 0
    ```
    
 Obs.: A execução segue o padrão: 
```
  ./[nomeExecutável] [arquivoEntrada] [ArquivoSaida] [Direcionado] 0|1 [Ponderado] 0|1 [Peso nos Vertices] 0|1 
```
# Classes 

<h3> Graph </h3>

Atributos
  - Node *firstNode;
  - int nodesTotal;
  - int edgesTotal;

Representa um grafo. Normalmente é instânciada uma vez por execução e vai guardar as informações descritivas sobre o grafo e também a referência ao ponto inicial chamado de firstNode

<hr/>

<h3> Node </h3>

Atributos 
  - int pk; // Primary Key = ID Único 
  - int id;
  - int degree;
  - int peso;
  - int grauIn;
  - int grauOut;
  - Node *nextNode;
  - Edge *firstEdge;
  
  Representa um nó. Tem uma instância única para cada nó. Está armazenada de forma encadeada e "randômica" (Segue a ordem de aparição no arquivo de texto lido). 
  
  Além disso foi adicionar um atributo pk (Primary Key - Chave Primária) que serve para indentificação única, independente de nomenclatura. Os demais atributos são descritivos em realação ao próprio nó.
  
  O atributo id é igual ao nome do nó.
  
<hr/>

<h3> Edges </h3>
  
Atributos
  - int id;
  - int weight;        
  - Node *tailNode;
  - Edge *nextEdge;   
  
Representa uma aresta. Tem uma instância única para cada relacionamento entre dois nós. Seu total será igual ao total de linhas que tem o arquivo de entrada. 

A aresta referencía no atributo *nextEdge* uma proxima aresta que tenha um nó cabeça em comum com ela. Um nó cabeça referencía uma só aresta, que por sua vez referencía uma proxima aresta que tabém tenha aquele nó como cabeça. As caldas, por serem diferentes, são armazenadas em cada aresta através do atributo *tailNode*

O atributo id é um valor único gerado, e o valor weight é um valor que deve ser preenchido pelo usuário. 
