#include <iostream>
#include<cstdlib>
using namespace std;
int hp =300 ; // Pontos de vida do jogador
int velocidade =  15; // Pontos de velocidade do jogador (influencia em quem ataca primeiro)
int exp = 0; // Pontos de experiencia do jogador
int ataque =10; // pontos de ataque do jogador
int defesa = 10; // pontos de defesa do jogador
int defmag = 15; // pontos de defesa magica do jogador
int Controlnivel = 100; // quando os pontos de experiencia do jogador atigem o valor dessa variavel o jogador passa de nivel
int nivel  = 1; // atributo que rege as outras caracteristicas do jogador





int main()
{


   system("cls");




}

// responsavel por aumentar o nivel do jogador
int gerenciadorExp(){

    if(exp >=  nivel){

     hp +=  hp/15;
     velocidade += velocidade  / 3 ;
     ataque +=  ataque/5 ;
     defesa += defesa/5;
     defmag += defmag/5;
     nivel ++ ;
     Controlnivel  =  Controlnivel * 2;




    }}

// cria inimigos de forma randomica
 string[] enemyFactroy( int n) {


string enemyname[] = {"morcego","dragão", "troll","goblin","orc","mago negro" ,"rato","barata possuida" , "demonio ","harpia", "Cerberus","cobra", "funkeiro" , "espirito","Cavaleiro Negro","Corrompido","Leonardo",
"hitler","petralha" ,"Bolsominion "};

int enemyPower = nivel * enemypower;

for(int i  = 0 ; i <  n ; i++){

    int indnome = random_r(0,enemyname..length) ; // indice do nome no array;
    string inimigo = enemyname[indnome] + " " +

 }


}

// recebe o nivel do inimigo desejado e o nome do atributo e calcula seu valor;

int atributoUpdate( int nivel ,string atriName ) {
 int result;
 if(atriName == "hp") {




 }

 if(atriName == "velocidade"){}

 else if(atriName  == "ataque"){}

 else if(atriName  == "defesa"){}

 else if(atriName == "defmag"){}

 else if(atriName == "Controlnivel"){}



}

// responsavel por controlar o sitema de batalha do jogo
void gerenciadorBatalha (){








}







