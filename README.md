<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/640px-ISO_C%2B%2B_Logo.svg.png" width="80px"/>
  <br>
</p>
<div align=center>
    <a href="#desc">Descrição</a> | <a href="#prerequisites">Pré Requisitos</a> | <a href="#running">Rodando</a> | <a href="#results">Resutlados</a>
</div>
<br>
<hr>
<h2 id="desc">
    Descrição
</h2>

Para ordenar grandes arquivos em memŕoia secundária, é preciso passar os valores presentes no arquivo para memória primária. 
Esse processo pode ocupar bastante da memória RAM do computador. Pensando nesse caso, esse algoritmo foi construído utilizando 
um limitador da memória principal, no qual o usuário escolhe o quanto da memória será usada durante a ordenação (Merge Sort Externo). Ademais, 
o programa faz o uso da compressão e descompressão do arquivo em binário para reduzir o custo de armazenamento.

- - - -

<h2 id="prerequisites">
    Pré Requisitos
</h2>

Basta ter algum compilador de C/C++ em sua máquina, sugestão: [C CompileRun](https://github.com/danielpinto8zz6/c-cpp-compile-run)

- - - -

<h2 id="running">
    Rodando
</h2>

O projeto conta com três programas, sendo eles: 

1. [Transformar](https://github.com/acmachado14/external-sorting/blob/main/transforma_binario.cpp) um arquivo CSV em binário

```
make compile-conversion && make run-conversion
```

2. [Listar](https://github.com/acmachado14/external-sorting/blob/main/manipulacao_dados.cpp) as informações presentes no arquivo

```
make compile-treatment && make run-treatment
```

3. [Ordenar](https://github.com/acmachado14/external-sorting/blob/main/order.cpp) o arquivo binário

```
make compile-ordering && make run-ordering
```

- - - -

<h2 id="results">
    Resutaldos
</h2>

Devido ao uso do limitador de memória RAM, é perceptível que quanto menos memória principal é usada mais será gasto com memória 
secundária e consequentemente terá um maior tempo de execução, 
devido a quantidade de arquivos temporários criados e o custo de acesso dos mesmos.

