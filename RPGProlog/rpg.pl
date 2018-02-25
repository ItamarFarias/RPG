dynamic player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive).
dynamic aliado(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Nivel, IsAlive ).
dynamic inimigo(Nome, Hp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, IsAlive).

playerMaker(1, Nome):- assert(player(Nome, 400, 400, 10, 10, 50, 0, 80, 15, 20, 0, 1, 100, true)). % Guerreiro
playerMaker(2, Nome):- assert(player(Nome, 400, 400, 200, 200, 30, 40, 60, 50, 20, 0, 1, 100, true)). % Paladino
playerMaker(3, Nome):- assert(player(Nome, 250, 250, 80, 80, 45, 20, 30, 15, 100, 0, 1, 100, true)). % Caçador
playerMaker(4, Nome):- assert(player(Nome, 200, 200, 400, 400, 15, 60, 20, 40, 15, 0, 1, 100, true)). % Mago

%no lugar disso poderiamos adiconar outro termo ao player para determinar sua classe.
class(1, Nome, X):- string_concat(Nome, " -- (Classe : Guerreiro)", X).
class(2, Nome, X):- string_concat(Nome, " -- (Classe : Paladino) ", X).
class(3, Nome, X):- string_concat(Nome, " -- (Classe : Caçador) ", X).
class(4, Nome, X):- string_concat(Nome, " -- (Classe : Mago) ", X).

%Implementação do comando/regra if/then/else. O uso do cut "!" significa que o programa nao ira mais fazer buscas por outra regra if / n vai atras de queries mais.
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


%Regra responsavel por realizar a cura do player.
curaPlayer(TotalDeCura) :- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
											TotalDeCura is DanoMagico * 5,
											if(Hp >= HpMax, onlyReducesMana(NovoMana), reduceManaAndRestorePlayer(NovoMana, NovoHP)).

%Reduz a quantidade de mana do player, que é definido como um fato. Logo, temos de reescrever o fato. -Regra usada na cura.
onlyReducesMana(NovoMana) :- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
												NovoMana is (Mana -(10 * Nivel)),
												retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
												assert(player(Nome, Hp, HpMax, NovoMana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)).

%Reduz mana e cura o player. -Regra usada na cura, caso o total de cura nao ultrapasse o hp maximo.
reduceManaAndRestorePlayer(NovoMana, NovoHP) :- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
																								NovoMana is (Mana - (10 * Nivel)),
																								NovoHP is ((DanoMagico * 5) + Hp),
																								retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
																								if(NovoHP > HpMax,
																								assert(player(Nome, HpMax, HpMax, NovoMana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
																								assert(player(Nome, NovoHP, HpMax, NovoMana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive))).



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


geraNomeInimigo(Nome) :- random(0,14,Z),nth0(Z,[morcego,dragao,troll,goblin,orc,mago_negro ,rato,barata ,demonio ,harpia,cerberus,cobra,espirito,cavaleiro_Negro,corrompido],Nome).

geraHpInimigo(Hp) :-  player(_,_,X,_,_,_,_,_,_,_,_,_,_,_),Y is 2*X , Z is X/2,  random(Z,Y,Hp).

geraDefesaInimigo(Defesa) :-  player(_,_,_,_,_,_,_,X,_,_,_,_,_,_),Y is 2*X , Z is X/2,  random(Z,Y,Defesa).

geraDefesaMagicaInimigo(DefesaMagica) :-  player(_,_,_,_,_,_,_,_,X,_,_,_,_,_),Y is 2*X , Z is X/2,  random(Z,Y,DefesaMagica).

geraVelocidadeInimigo(Velocidade):- player(_,_,_,_,_,_,_,_,_,X,_,_,_,_),Y is 2*X , Z is X/2,  random(Z,Y,Velocidade).

geraXpDrop(XpDrop) :-  player(_,_,_,_,_,_,_,_,_,_,_,X,_,_),random(0,200,Z) , XpDrop is X*Z.

geraNivel(Nivel):-  player(_,_,_,_,_,_,_,_,_,_,_,X,_,_),Z is X *2 , random(1,Z,Nivel).

geraAtaqueInimigo(Ataque):- player(_,_,_,_,_,_,_,X,_,_,_,_,_,_),Y is X/2 , Z is 2*X, random(Y,Z,Ataque).

% gerador de inimigo.
enemyMaker():- geraNomeInimigo(Nome),geraHpInimigo(Hp),geraDefesaInimigo(Defesa),geraDefesaMagicaInimigo(DefesaMagica),geraVelocidadeInimigo(Velocidade),geraXpDrop(XpDrop),geraNivel(Nivel),geraAtaqueInimigo(Ataque),assert(inimigo(Nome, Hp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, true)).

%Dano causado pelo player ao inimigo
calculaDanoFisico(Dano):- inimigo(_,_,_, Defesa,_,_, _, _, _), player(_, _, _, _, _, Ataque, _, _, _, _, _, _, _, _), Z is  Ataque - Defesa,(Z < 0) -> Dano is 0 ; Dano is Z  .

recieveDamageByPlayer(Dano):- inimigo(Nome, Hp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, IsAlive),
	NovoHp is (Hp - Dano),
	(retract(inimigo(Nome, Hp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, IsAlive))),
	 (NovoHp > 0) ->  assert(inimigo(Nome, NovoHp, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, IsAlive));
				assert(inimigo(Nome, 0, Ataque, Defesa, DefesaMagica, Velocidade, XpDrop, Nivel, false)).

printSeparador():- write("-------------------------------------------------------------"),nl.

printInfoPlayerInimigo():- player(_, Hp, HpMax, Mana, ManaMax, _, _, _, _, _, _, _, _, _),
	inimigo(_, HpInimigo, _, _, _, _, _, _, _),
	write("*********************************"),nl,
  write("HP do Jogador -> "), write(Hp), write("/"), write(HpMax), write("  ||  "), write("HP do Inimigo -> "), write(HpInimigo),nl,
  write("Mana do Jogador -> "), write(Mana), write("/"),write(ManaMax),nl,
  write("*********************************"),nl.

battleSystem(true,true):-
	printInfoPlayerInimigo(),
	write("Turno do Jogador"),nl,
	printSeparador(),
  write("1 - Ataque Fisico"),nl,
	write("2 - Cura"), nl,
	write("3 - Magia"), nl,
	printSeparador(),
	write("Digite o numero referente a ação desejada: "),nl,
	read(X),
	(
	 ((X =:= 1)-> write("Voce ataca o inimigo fisicamente"),nl,calculaDanoFisico(Dano),recieveDamageByPlayer(Dano));
	 ((X =:= 2) -> write("Voce sente que precisa se curar..."),nl, curaPlayer(TotalDeCura), nl, write("...Cura recebida!"), nl);
	 ((X =:= 3) -> write("Voce sente um poder subito tomar conta de seu ser "),nl,
	  printMagias(),
		write("Escolha uma das magias acima"),
		read(Escolha),
		possuiManaSuficiente(Escolha,B),
		((B) -> (magiaDano(Escolha, DanoMagico), calculaDanoMagico(DanoMagico, DanoFinal),recieveDamageByPlayer(DanoFinal));recieveDamageByPlayer(0)))
	 ),

	 write("Turno inimigo :"),nl,
	 inimigo(_,_,DanoInimigo,_,_,_,_,_,_),write("o inimigo lhe ataca"),nl,
	 receiveDamageByEnemy(DanoInimigo),
	 player(_,_,_,_,_,_,_,_,_,_,_,_,_, PlayerIsAlive),
	 inimigo(_,_,_,_,_,_,_,_, InimigoIsAlive),
	 battleSystem(PlayerIsAlive,InimigoIsAlive).

battleSystem(_,_).


battlemanager(1) :- printSeparador(),
	write("Novo inimigo encontrado"),nl,printSeparador(),
		enemyMaker(), battleSystem(true,true),
	player(_,_,_,_,_,_,_,_,_,_,_,_,_, PlayerIsAlive),(
	((PlayerIsAlive) -> write("Voce venceu"), inimigo(_,_,_,_,_,_,MoreExp,_, _) ,increaseExp(MoreExp),write("Voce venceu"),nl,write("Deseja continuar ?"),nl,write("1- Sim | 2 N�o"),read(K),battlemanager(K)); battlemanager(2)).

battlemanager(2) :- write("Game Over").

calculaDanoMagico(DanoMagico, DanoCausado):- inimigo(_, _, _, _, DefesaMagica, _, _, _, _),
	DM is DefesaMagica / 100.0,
  DanoCausado is round(DanoMagico / (DM + 1.0)).

printMagias():- printExplosion(), printThundara().

printExplosion():- player(_, _, _, _, _, _, DanoMagico, _, _, _, _, Nivel, _, _),
	printSeparador(),
	ExplosionDano is round(1.15 * DanoMagico),
	ConsumoDeMana is 10 * Nivel,
	write(" 1 - Explosion|Consome "), write(ConsumoDeMana),	write(" de mana| causa "), write(ExplosionDano), write(" de dano"), nl, printSeparador().

printThundara():- player(_, _, _, _, _, _, DanoMagico, _, _, _, _, Nivel, _, _),
	ThundaraDano is round(1.3 * DanoMagico),
	ConsumoDeMana is 20 * Nivel,
	(Nivel >= 2) -> write(" 2 - Thundara|Consome  "), write(ConsumoDeMana), write(" de mana| causa "), write(ThundaraDano), write(" de dano"), nl, printSeparador();
	nl.

possuiManaSuficiente(Magia, Possui):- player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive),
	(magiaMana(Magia, Nivel, ManaNecessaria),
	(ManaNecessaria > Mana) -> printManaInsuficiente(), Possui = false;
	magiaMana(Magia, Nivel, ManaNecessaria),
	NewMana is (Mana - ManaNecessaria),
	retract(player(Nome, Hp, HpMax, Mana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
	assert(player(Nome, Hp, HpMax, NewMana, ManaMax, Ataque, DanoMagico, Defesa, DefesaMagica, Velocidade, Exp, Nivel, ControlNivel, IsAlive)),
	Possui = true).

printManaInsuficiente():- write("Mana insuficiente para realizar tal chamado"),nl.

magiaDano(1, ExplosionDano):- player(_, _, _, _, _, _, DanoMagico, _, _, _, _, _, _, _),
	ExplosionDano is round(1.15 * DanoMagico).
magiaDano(2, ThundaraDano):- player(_, _, _, _, _, _, DanoMagico, _, _, _, _, _, _, _),
	ThundaraDano is round(1.3 * DanoMagico).

magiaMana(1, Nivel, ManaNecessaria):- ManaNecessaria is (10 * Nivel).
magiaMana(2, Nivel, ManaNecessaria):- ManaNecessaria is (20 * Nivel).

printClasses():- write("------------- Escolha a classe que seu personagem irá pertencer -------------"),nl,
  printInfoGuerreiro(),nl,
  printInfoPaladino(),nl,
  printInfoCacador(),nl,
  printInfoMago(),nl,
  printSeparador().

printInfoGuerreiro():- write("1 - Guerreiro: Guerreiros combinam força, liderança e vasto conhecimento em armas e armaduras para criar o caos no campo de batalha."),nl.

printInfoPaladino():- write("2 - Paladino: Estes guerreiros sagrados estão equipados com armaduras de placas para enfrentar os inimigos mais perigosos e são adeptos da benção da Luz que lhes permite curar feridas."),nl.

printInfoCacador():- write("3 - Caçador: Apesar de suas armas à distância serem extremamente eficientes, os caçadores se encontram em desvantagem quando seus inimigos aproximam para o combate corpo a corpo."),nl.

printInfoMago():- write("4 - Mago: Apesar de dominarem poderosas magias ofensivas, os magos são frágeis e usam armaduras leves deixando-os particularmente vulneráveis contra ataques corpo a corpo."),nl.


:- initialization(main).
main:-
  write("RRRRRRRRRRRRRRRRR   PPPPPPPPPPPPPPPPP           GGGGGGGGGGGGG
R::::::::::::::::R  P::::::::::::::::P       GGG::::::::::::G
R::::::RRRRRR:::::R P::::::PPPPPP:::::P    GG:::::::::::::::G
RR:::::R     R:::::RPP:::::P     P:::::P  G:::::GGGGGGGG::::G
  R::::R     R:::::R  P::::P     P:::::P G:::::G       GGGGGG
  R::::R     R:::::R  P::::P     P:::::PG:::::G
  R::::RRRRRR:::::R   P::::PPPPPP:::::P G:::::G
  R:::::::::::::RR    P:::::::::::::PP  G:::::G    GGGGGGGGGG
  R::::RRRRRR:::::R   P::::PPPPPPPPP    G:::::G    G::::::::G
  R::::R     R:::::R  P::::P            G:::::G    GGGGG::::G
  R::::R     R:::::R  P::::P            G:::::G        G::::G
  R::::R     R:::::R  P::::P             G:::::G       G::::G
RR:::::R     R:::::RPP::::::PP            G:::::GGGGGGGG::::G
R::::::R     R:::::RP::::::::P             GG:::::::::::::::G
R::::::R     R:::::RP::::::::P               GGG::::::GGG:::G
RRRRRRRR     RRRRRRRPPPPPPPPPP                  GGGGGG   GGGG  "),nl,
  write("Qual seu nome?"),nl,
  read(Nome),nl,
	printClasses(),
  read(Classe), nl,
  class(Classe, Nome, X),
  playerMaker(Classe, X),
  battlemanager(1).
