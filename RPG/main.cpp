#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <windows.h>

using namespace std;
using namespace std;


struct Player{

    string nomeDoJogador = "X";
    int hp =300 ; // Pontos de vida do jogador
    int hpMax = 300; // quantidade max de hp do jogador
    int velocidade =  15; // Pontos de velocidade do jogador (influencia em quem ataca primeiro)
    int exp = 0; // Pontos de experiencia do jogador
    int ataque =10; // pontos de ataque do jogador
    int defesa = 10; // pontos de defesa do jogador
    int defesaMagica = 15; // pontos de defesa magica do jogador
    int controlNivel = 100; // quando os pontos de experiencia do jogador atigem o valor dessa variavel o jogador passa de nivel
    int nivel  = 1; // atributo que rege as outras caracteristicas do jogador
    int mana =  200; // responsavel por conjuração de magia
    int manaMax = 200; // quantidade maxima de mana do jogador
    bool status = true;

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

    int action(){
        string escolha;
        int danocausado ;
        cout << "" << endl;
        cout <<"-------------------------------------------------------------" << endl;
        cout << "Selecione uma ação :" << endl;
        cout<< "1 - Atague fisico "<< endl;
        cout<< "2 - Cura  " <<endl;
        cout<< "3 - Magia " <<endl;
        cout<< "4 - Fugir" <<endl;
        cout<< "" << endl;
        cout <<"-------------------------------------------------------------" << endl;
        cout<< "" << endl;
        cout<< "" << endl;
        cout << "Digite o numero referente a ação desejada : ";
        cout << "" << endl;
        cin >> escolha;
        cout << "" <<endl;

        if(escolha == "1"){

            cout << "Você ataca o inimigo fisicamente " << endl;
            cout<< "" << endl;
            danocausado =  ataque;
        }

        else if( escolha == "2"){

            cout << "Você sente que precisa recuperar suas energias" << endl;


        }

        else if ( escolha == "3"){

            cout << "Você resolve usar artes arcanas"<<endl;
            danocausado = magia();


        }

        else{
            cout <<"Opção invalida : por favor selecione uma opção valida " <<endl;
            danocausado = -1;

        }






     return danocausado;


    }
    // este metodo contem apenas uma magia por enquanto
    // retorna -1 caso o jogador nao possua os requisitos
    // caso possua retorna o dano
    int magia(){
        string escolha ;
        int dano = -1 ;
        cout << "" << endl;
        cout <<"-------------------------------------------------------------" << endl;
        cout << " 1 - Fogo Arcano|Consome 10 de mana| causa 30 de dano"<< endl;
        cout <<"-------------------------------------------------------------" << endl;
        cout << "" << endl;
        cout << "Selecione o numero referente a magia desejada: ";
        cin >> escolha;

         if(escolha == "1"){

            if(mana >= 10){
                mana -= 10;
                cout << "Uma esfera de fogo surge em sua mão"<<endl;
                dano =  30;
                }

            else {
                cout << "Voce não possui mana  suficiente para conjurar tal arte"<<endl;

            }

        }



        else{
            cout <<"Opção invalida : por favor selecione uma opção valida " <<endl;}










    }


    int cura(){


    }

// Remove hp dp jogador de acordo com o dano sofrido e retorna seu status
void damangeRecieve(int dano){

        hp -= dano ;
        if(hp <= 0){

            status = false;
        }


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
        cout << "Mana " << mana << endl;
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
    string nome;
    int hp;
    int velocidade;
    int ataque;
    int defesa;
    int defesaMagica;
    int xpDrop;
    bool status = true;

    void ImprimeInfoInimigo(){
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Informações do Inimigo:  " << nome << endl;
        cout << nome;
        cout << "HP: " << hp << endl;
        cout << "Velocidade: " << velocidade << endl;
        cout << "Pontos de ataque: " << ataque << endl;
        cout << "Pontos de defesa: " << defesa << endl;
        cout << "Pontos de defesa magica: " << defesaMagica << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "" << endl;}


    void damangeRecieve(int dano){

        hp -= dano ;
        if(hp <= 0){

            status = false;
        }}

};



string enemyname[] = {"morcego","dragão", "troll","goblin","orc","mago negro" ,"rato","barata" , "demonio ","harpia", "Cerberus","cobra", "espirito","Cavaleiro Negro","Corrompido"};






// responsavel pela criação de inimigo randomico
string enemyMaker (inimigo i,Player player){


 int indice = rand()% 14;
 string nome = enemyname[indice];
 i.nome =  nome ; // seleciona um nome aleatorio do array de inimigos;
 i.ataque = rand()% player.ataque*3;
 i.velocidade = rand()% player.velocidade +5 ;
 i.hp = player.hp /2;
 i.defesa =  rand() % (player.defesa*2);
 i.defesaMagica = rand() % (player.defesaMagica*2);

 return nome;






}


// responsavel por controlar o sitema de batalha do jogo
// recebe um jogador e um inteiro com o numero de inimigos
void gerenciadorBatalha (Player player){



    inimigo enemy;
    string nome = enemyMaker(enemy,player);
    bool alive = true;
    cout << "" << endl;
    cout << "Um novo inimigo surge :" <<endl ;
    cout << "" <<endl;
    Sleep(3000);
    system("cls");
    cout<< nome << endl;

    while(alive == true){

        alive = false;

        if(player.status == true and enemy.status == true){ // se o jogador e o inimigo estão vivos ambos podem atacar
           alive = true;
           enemy.ImprimeInfoInimigo();
           Sleep(3000);
            cout<<"Seu turno"<<endl;
            cout<<""<<endl;
            int dano = player.action();


            enemy.damangeRecieve(dano);
            cout<< "Voce causou "<<dano;
            cout<< " de dano em  " << nome << endl;
            cout<<""<<endl;
            Sleep(3000);
            system("cls");
            cout<<"Turno inimigo"<<endl;
            cout<<""<<endl;
            Sleep(2000);
            system("cls");

            player.damangeRecieve(enemy.ataque);
            cout << " O inimigo lhe causou  " << enemy.ataque;
            cout << "de dano" << endl;
            cout << "" << endl;
            Sleep(3000);




            }

          else {
            if(enemy.status == false){
                cout<<"voce venceu";
            }

            else {
                cout << "Você Morreu";
                system("cls");
                cout << "Game Over";
            }
          }

            }

    }






int main()
{
    setlocale(LC_ALL, "Portuguese");
    Player player1;
    player1.changeName();
    player1.imprimeInfoJogador();
    gerenciadorBatalha(player1);








}
