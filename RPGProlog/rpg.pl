dynamic player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive).
dynamic aliado(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Nivel, IsAlive ).
dynamic inimigo(Nome, Hp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, IsAlive).

playerMaker(1, Nome):- assert(player(Nome, 400, 400, 10, 10, 50, 0, 80, 15, 20, 0, 1, 100, true)). % Guerreiro
playerMaker(2, Nome):- assert(player(Nome, 400, 400, 200, 200, 30, 40, 60, 50, 20, 0, 1, 100, true)). % Paladino
playerMaker(3, Nome):- assert(player(Nome, 250, 250, 80, 80, 45, 20, 30, 15, 100, 0, 1, 100 true)). % Caçador
playerMaker(4, Nome):- assert(player(Nome, 200, 200, 400, 400, 15, 60, 20, 40, 15, 0, 1, 100, true)). % Mago

%no lugar disso poderiamos adiconar outro termo ao player para determinar sua classe.
class(1, Nome, X):- string_concat(Nome, " -- (Classe : Guerreiro)", X).
class(2, Nome, X):- string_concat(Nome, " -- (Classe : Paladino) ", X).
class(3, Nome, X):- string_concat(Nome, " -- (Classe : Caçador) ", X).
class(4, Nome, X):- string_concat(Nome, " -- (Classe : Mago) ", X).

%Implementação do comando if/then/else. O uso do cut "!" significa que o programa nao ira mais fazer buscas por outra regra if / n vai atras de queries mais.
if(Condition,Then,Else) :- Condition, !, Then.
if(_,_,Else) :- Else.

%Provavelmente deve ser modificado para usar também o retract para excluir o fato que representa o player existente!
%Foi testado no "shell" do prolog e aparenta estar funcional
receiveDamageByEnemy(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive), DanoRecebido, NovoHP) :-
	NovoHP is (Hp - DanoRecebido),
	retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
	if(NovoHP =< 0,
		assert(player(Nome, NovoHP, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, false)),
		assert(player(Nome, NovoHP, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive))).

%modelo 2.0 de receiveDamageByEnemy
receiveDamageByEnemy(Dano):- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
							NovoHp is (Hp - Dano),
							(retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
							(NovoHp >= 0) -> assert(player(Nome, NovoHp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)) ;
															 assert(player(Nome, NovoHp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, false))).

increaseExp(MoreExp):- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
									 retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
									 assert(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, MoreExp, Nivel, ControlNivel, IsAlive)).

updatePlayer():- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
	(Exp >= ControlNivel) ->
		NewHp is (HpMax + (HpMax // 5)),
		NewMana is (ManaMax + (ManaMax // 5)),
		NewAtaque is (Ataque + (Ataque // 5)),
		NewDanoMagico is (DanoMagico + (DanoMagico // 5)),
		NewDefesa is (Defesa + (Defesa // 5)),
		NewDefesaMagica is (DefesaMagica + (DefesaMagica // 5)),
		NewVelocidade is (Velocidade + (Velocidade // 3)),
		NewNivel is (Nivel + 1),
		NewControlNivel is (ControlNivel * 2),
		retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
		assert(player(Nome, NewHp, NewHp, NewMana, NewMana, NewAtaque, NewDanoMagico, NewDefesa, NewDefesaMagica, NewVelocidade, Exp, NewNivel, NewControlNivel, IsAlive)).

playerRegen():- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
								retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
								assert(player(Nome, HpMax, HpMax, ManaMax, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)).

:- initialization(main).
main:-
  write("RPG"), nl,
  write("Qual seu nome?"),nl,
  read(Nome),nl,
  write("Escolha sua classe..."), nl,
  read(Classe), nl,
  class(Classe, Nome, X),
  playerMaker(Classe, X).
