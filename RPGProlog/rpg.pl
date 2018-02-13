dynamic player(Nome, Hp, HpMax, Velocidade, Exp, Ataque, DanoMagico, Defesa, DefesaMagica, ControlNivel, Nivel, Mana, ManaMax, IsAlive).
dynamic aliado(Nome, Hp, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Mana, ManaMax, IsAlive, Nivel ).
dynamic inimigo(Nome, Hp, Velocidade, Ataque, Defesa, DefesaMagica, XpDrop, Nivel, IsAlive).

playerMaker(1, Nome):- assert(player(Nome, 400, 300, 20, 0, 50, 0, 80, 15, 100, 1, 10, 200, True)). % Guerreiro
playerMaker(2, Nome):- assert(player(Nome, 400, 300, 20, 0, 30, 40, 60, 50, 100, 1, 200, 200, True)). % Paladino
playerMaker(3, Nome):- assert(player(Nome, 200, 300, 100, 0, 45, 0, 30, 15, 100, 1, 0, 200, True)). % Caçador
playerMaker(4, Nome):- assert(player(Nome, 200, 300, 8, 0, 15, 40, 40, 15, 100, 1, 400, 200, True)). % Mago

%no lugar disso poderiamos adiconar outro termo ao player para determinar sua classe.
classe(1, Nome, X):- string_concat(Nome, " -- (Classe : Guerreiro)", X).
classe(2, Nome, X):- string_concat(Nome, " -- (Classe : Paladino) ", X).
classe(3, Nome, X):- string_concat(Nome, " -- (Classe : Caçador) ", X).
classe(4, Nome, X):- string_concat(Nome, " -- (Classe : Mago) ", X).

:- initialization(main).
main:-
  write("RPG"), nl,
  write("Qual seu nome?"),nl,
  read(Nome),nl,
  write("Escolha sua classe..."), nl,
  read(Classe), nl,
  classe(Classe, Nome, X),
  playerMaker(Classe, X).
