#include <iostream>

using namespace std;
using namespace std;

struct Player{

    string nomeDoJogador = "X";
    int hp =300 ; // Pontos de vida do jogador
    int velocidade =  15; // Pontos de velocidade do jogador (influencia em quem ataca primeiro)
    int exp = 0; // Pontos de experiencia do jogador
    int ataque =10; // pontos de ataque do jogador
    int defesa = 10; // pontos de defesa do jogador
    int defesaMagica = 15; // pontos de defesa magica do jogador
    int controlNivel = 100; // quando os pontos de experiencia do jogador atigem o valor dessa variavel o jogador passa de nivel
    int nivel  = 1; // atributo que rege as outras caracteristicas do jogador


    void changeName(){
        cout << "" << endl;
        cout <<"-------------------------------------------------------------" << endl;
        cout << "Digite o nome do seu personagem: ";
        string novoNome;
        getline(cin, novoNome); //Para pegar a linha toda
        nomeDoJogador = novoNome;
        cout <<"-------------------------------------------------------------" << endl;
        cout << "" << endl;
    }






    // gerencia o exp e aumenta o nivel do jogador
    int gerenciadorExp(){
        if(exp >= nivel){
        hp+= hp/15;
        velocidade+= velocidade  / 3 ;
        ataque+= ataque/5 ;
        defesa+= defesa/5;
        defesaMagica+= defesaMagica/5;
        nivel++;
        controlNivel= controlNivel * 2;
        }
    }

    int atributoUpdate( int nivel ,string atriName ) {
        int result;
        if(atriName == "hp") {
        }
        if(atriName == "velocidade"){}
        else if(atriName  == "ataque"){}
        else if(atriName  == "defesa"){}
        else if(atriName == "defesaMagica"){}
        else if(atriName == "controlNivel"){}
    }

    void imprimeInfoJogador(){
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Informacoes de " << nomeDoJogador <<":" <<endl;
        cout << "HP: " << hp << endl;
        cout << "EXP: " << exp << endl;
        cout << "Nivel: " << nivel << endl;
        cout << "Pontos de ataque: " << ataque << endl;
        cout << "Pontos de defesa: " << defesa << endl;
        cout << "Velocidade: " << velocidade << endl;
        cout << "Pontos de defesa magica: " << defesaMagica << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "" << endl;
    }


};

struct inimigo{
    string nomeDoInimigo;
    int hp;
    int velocidade;
    int ataque;
    int defesa;
    int defesaMagica;

    void ImprimeInfoInimigo(){
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Informações de " << nomeDoInimigo << endl;
        cout << "HP: " << hp << endl;
        cout << "Velocidade: " << velocidade << endl;
        cout << "Pontos de ataque: " << ataque << endl;
        cout << "Pontos de defesa: " << defesa << endl;
        cout << "Pontos de defesa magica: " << defesaMagica << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "" << endl;
    }
};



string enemyname[] = {"morcego","dragão", "troll","goblin","orc","mago negro" ,"rato","barata possuida" , "demonio ","harpia", "Cerberus","cobra", "espirito","Cavaleiro Negro","Corrompido"};



int main()
{

    Player player1;
    player1.changeName();
    player1.imprimeInfoJogador();







}



//cria inimigos de forma randomica - retornar string? -Ver esse metodo, nao entendi??
/* cria inimigos de forma randomica
 string[] enemyFactroy( int n) {
string enemyname[] = {"morcego","dragão", "troll","goblin","orc","mago negro" ,"rato","barata possuida" , "demonio ","harpia", "Cerberus","cobra", "funkeiro" , "espirito","Cavaleiro Negro","Corrompido"};
int enemyPower = nivel * enemypower;
for(int i  = 0 ; i <  n ; i++){
    int indnome = random_r(0,enemyname..length) ; // indice do nome no array;
    string inimigo = enemyname[indnome] + " " +
 }
} */


// responsavel por controlar o sitema de batalha do jogo
void gerenciadorBatalha (){


}
