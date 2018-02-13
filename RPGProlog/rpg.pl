dynamic player(Nome, Hp, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, IsAlive).
dynamic aliado(Nome, Hp, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Mana, ManaMax, IsAlive, Nivel ).
dynamic inimigo(Nome, Hp, Velocidade, Ataque, Defesa, DefesaMagica, XpDrop, Nivel, IsAlive).

playerMaker(1, Nome):- assert(player(Nome, 400, 300, 20, 0, 50, 0, 80, 15, 100, 1, 10, 200, true)). % Guerreiro
playerMaker(2, Nome):- assert(player(Nome, 400, 300, 20, 0, 30, 40, 60, 50, 100, 1, 200, 200, true)). % Paladino
playerMaker(3, Nome):- assert(player(Nome, 200, 300, 100, 0, 45, 0, 30, 15, 100, 1, 0, 200, true)). % Caçador
playerMaker(4, Nome):- assert(player(Nome, 200, 300, 8, 0, 15, 40, 40, 15, 100, 1, 400, 200, true)). % Mago

%no lugar disso poderiamos adiconar outro termo ao player para determinar sua classe.
classe(1, Nome, X):- string_concat(Nome, " -- (Classe : Guerreiro)", X).
classe(2, Nome, X):- string_concat(Nome, " -- (Classe : Paladino) ", X).
classe(3, Nome, X):- string_concat(Nome, " -- (Classe : Caçador) ", X).
classe(4, Nome, X):- string_concat(Nome, " -- (Classe : Mago) ", X).

%Implementação do comando if/then/else. O uso do cut "!" significa que o programa nao ira mais fazer buscas por outra regra if / n vai atras de queries mais. 
if(Condition,Then,Else) :- Condition, !, Then.
if(_,_,Else) :- Else. 


%Provavelmente deve ser modificado para usar também o retract para excluir o fato que representa o player existente!
%Foi testado no "shell" do prolog e aparenta estar funcional
receiveDamageByEnemy(player(Nome, Hp, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, IsAlive), DanoRecebido, NovoHP) :-
	NovoHP is (Hp - DanoRecebido), 
	retract(player(Nome, Hp, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, IsAlive)),
	if(NovoHP =< 0, 
		assert(player(Nome, NovoHP, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, false)), 
		assert(player(Nome, NovoHP, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, IsAlive))).




:- initialization(main).
main:-
  write("RPG"), nl,
  write("Qual seu nome?"),nl,
  read(Nome),nl,
  write("Escolha sua classe..."), nl,
  read(Classe), nl,
  classe(Classe, Nome, X),
  playerMaker(Classe, X).
