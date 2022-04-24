# Sistema para 	Biblioteca

 ##  Introdução:

* Nosso sistema foi desenvolvido para atender o funcionário de uma biblioteca em seu trabalho no dia a dia. O programa trabalha com um sistema de login, que ao ser autenticado, abre um menu principal com as funções de empréstimo e devolução de livro. Criamos uma conta de Admininstrador para teste, cujo usuário e senha = teste. Conta também com uma terceira opção, que chamamos de menu do admininstrador. Nele há outras oito opções, incluindo mostrar registro de todos estudantes cadastrados, adicionar um livro ao acervo, ver informações sobre um estudante em específico, guardar informações de vários livros e alunos, mantendo controle de quais livros foram emprestados para quais alunos.
Guardar a data de empréstimo de cada livro, para se necessário, calcular uma multa para o aluno caso ele tenha passado do prazo.
Login com usuário e senha para que somente os administradores tenha acesso ao sistema;

## Implementação e funcionamento:
  - Para montar o projeto utilizamos os Conceitos de Orientação à Objetos(Classes, objetos etc), Standard Template Library(STL) e manipulação de arquivos; 
  - Para compilar basta estar na pasta raiz do projeto e dar um $ make e depois um $ make run;
  - Ao inciar o programa, uma lista contendo o nome e senha dos administradores é incializada, logo, o programa pede usuário e senha para continuar a execução; 
  - Caso o login seja bem sucedido, o programa lê os dados guardados nos arquivos de texto para
inicializar listas contendo as informações dos alunos e livros para facilitar a leitura no futuro; 
  - Em seguida a função show_menu() é chamada pra apresentar ao usuário as opções disponíveis no sistema; 
  - As opções principais são emprestar um livro ou registar que um livro foi devolvido pelo estudante; 
      - Se a opção emprestar livro for selecionada, o programa pede o isbn do livro e matricula do estudante, e verifica se os mesmos existem. Caso positivo ele adiciona o isbn do livro, juntamente ao prazo de devolução, ao arquivo de texto de nome "matricula do aluno".txt e remove um da quantidade possuida; 
  - Se não há desse livro no acervo ele não é emprestado;
  - Se o usuário escolher verificar se o livro foi devolvido, o sistema verifica que o aluno realmente pegou aquele livro emprestado e remove da lista de livros do aluno; 
  - Se o aluno demorar mais que o tempo estipulado para devolver o livro (15 dias), é calculada multa (1$ por dia passado do prazo);
  - Entre as outras opções, o usuário pode escolher registrar ou remover um livro ou aluno do sistema, ou exibir na tela as informações de um ou todos livros ou estudantes;
  
#### Principais funções na classe System:
- ##### System::show_menu(): 
  como dito anteriormente, mostra para o usuário as opções das funcionalidades básicas;

- ##### System::borrow_book(): 
  pergunta ao usuário sua matrícula, o código isbn do livro requerido e verifica se está disponível no acervo, se sim, faz o empréstimo; 

- ##### System::get_book(): 
  este método é muito utilizado e é o responsável por vasculhar o acervo e devolver um objeto de book com todas suas informações: Título, Autor, ISBN, quantidade; 

- ##### System::return_book(): 
  este método pergunta ao usuário a matrícula do estudantee o código ISBN do livro devolvido. Vasculha o .txt do estudante pela matrícula dada e remove o livro. Se o a diferença da data de empréstimo e devolução do livro for maior que 15 dias, escreve na tela uma mensagem dizendo que o aluno tem uma pendência de R$1 por cada dia de atraso;

- ##### System::show_adm_menu(): 
  mostra para o usuário o menu adicional do admininstrador com mais funcionalidades como por exemplo: Adicionar aluno ao students.txt, adicionar livro ao acervo em books.txt, mostrar lista de livros, registro de todos estudantes, mostrar aluno ou livro específico, remover estudante do students.txt, remover livro do acervo;

#### Principais funções na classe Student:
- ##### Student::Student(int id,string name): 
  neste construtor, setamos a matrícula e o nome do estudante, gerando um arquivo .txt em Alunos/ para guardar as informações daquele;

- ##### Student::read_books(): 
  este método é importante para se ler os livros do estudante no .txt e colocar os livros no vector de livros do próprio estudante. Para isso utilizamos o método, já citado acima, System::get_book(), que retorna um objeto do livro encontrado no acervo com todas suas informações;

- ##### Student::set_one_book_in_books(std::shared_ptr<Book> book_received): 
   este método é importante para adicionarmos um livro ao vector de livros do estudante, o que ocorre por exemplo, ao realizar um empréstimo;
 
 - ##### Student::set_books(std::vector<std::shared_ptr<Book>> books_received): 
   já este método é relevante pois ao se devolver um livro, devemos setar o vector de livros do estudante sem o livro devolvido. Utilizamos esta saída pois tentamos remover direto com books.erase(posição_do_livro_devolvido) e não conseguimos.

#### Principais funções na classe Book:
- ##### Book::borrow(): 
  método chamado na classe System depois de ter achado o livro no acervo, para abrir o arquivo Acervo/books.txt e remover um na quantidade do livro;

- ##### Book::return_book(int id): 
  utilizado para fazer a devolução do livro. Abre o .txt do aluno, acha o livro especifico para devolução e vê se o tempo de devolução está OK. Se não estiver, printa quanto o aluno deverá pagar de multa. Depois abre o acervo e aumentan um na quantidade do livro devolvido;

## Dificuldades encontradas:
  - Entre as dificuldades encontradas durante o desenvolvimento do projeto, a maior delas foi escrever código sustentável
e de qualidade, o que nem sempre foi alcançado. Ao encontrar um problema, é fácil escrever uma solução rápida mas que não
segue as boas práticas de desenvolvimento e compromete a extensibilidade do programa. Outra dificuldade encontrada foi o
armazenamento de informações em arquivos de texto, o que dificulta modificações na maneira em que os dados são organizados e 
processados. Por exemplo, ao adicionar novos campos à classe Book, grande parte do programa precisou ser modificado, causando 
alta probabilidade de introdução de novos erros;
 
  - Tivemos problemas, por exemplo:
   - no processo de construção do código com o método System::borrow_book(), que estava emprestando apenas os livros de linhas ímpares no acervo;
   - o vector de students e a lista de admininstradores precisarão ser declaradas no main, pois são membros estáticos, que estava causando undefined refernece to "...";
   - outros problemas na leitura do arquivo, algumas funções como o std::cin, que pega o caracter '\n', oque tivemos que resolver utilizando cin.ignore() ou até muitas vezes arq.ignore(), sendo este a referência do arquivo lido;
   - tivemos problemas também ao fazer da classe User abstrata, com o método virtual puro print_welcome(), pois sendo declarado assim ele precisa ser implementado em todas as classes filhas;
 
 - ### Considerações Finais
  - Ao final, percebemos que cometemos muitos erros e que ainda temos muito a aprender. Métodos e funções menores, nomes mais claros para atributos/métodos, abstração maior de nossas classes, são exemplos que pretendemos e vamos por em prática cada vez mais em nossas carreiras, como tanto aconselha "Uncle Bob" em seu livro Clean Code... Mas saímos também satisfeitos com nosso trabalho, pois foi nossa primeira experiência de trabalho em equipe codificando, com prazo de entrega e tudo mais, e achamos super válido a iniciativa da disciplina de aprendermos a montar juntos, um sistema do zero.

## Bibliografia:

* ### Sites utilizados:
  * [StackOverFlow](https://stackoverflow.com/)
  * [Cplusplus](http://www.cplusplus.com/)
  * [TutorialSpointhttps](//www.tutorialspoint.com/cplusplus/)
* ### Livro:
  * Clean Code - A Handbook of Agile Software Craftsmanship - Robert C. Martin
