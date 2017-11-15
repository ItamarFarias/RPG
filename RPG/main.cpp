#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
//#include <windows.h>

using namespace std;
using namespace std;


struct Player{

    string nomeDoJogador = "X";
    int hp = 300; // Pontos de vida do jogador
    int hpMax = 300; // quantidade max de hp do jogador
    int velocidade = 15; // Pontos de velocidade do jogador (influencia em quem ataca primeiro)
    int exp = 0; // Pontos de experiencia do jogador
    int ataque = 10; // pontos de ataque do jogador
    int defesa = 10; // pontos de defesa do jogador
    int defesaMagica = 15; // pontos de defesa magica do jogador
    int controlNivel = 100; // quando os pontos de experiencia do jogador atigem o valor dessa variavel o jogador passa de nivel
    int nivel = 1; // atributo que rege as outras caracteristicas do jogador
    int mana = 200; // responsavel por conjuração de magia
    int manaMax = 200; // quantidade maxima de mana do jogador
    bool status = true; // Indica se o jogador esta vivo ou morto

    void changeName(){

        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Digite o nome do seu personagem: ";
        string novoNome;

        getline(cin, novoNome); //Para pegar a linha toda
        nomeDoJogador = novoNome;

        cout << "-------------------------------------------------------------" << endl << endl;

    }

// Responsavel por realizar ação escolhida pelo jogador
    int action(){
        string escolha;
        int danocausado ;

        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Selecione uma ação :" << endl;
        cout << "1 - Atague fisico "<< endl;
        cout << "2 - Cura  " << endl;
        cout << "3 - Magia " << endl;
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl << endl << endl;
        cout << "Digite o numero referente a ação desejada : ";
        cin >> escolha;
        cout << "" << endl;

        if(escolha == "1"){

            cout << "Você ataca o inimigo fisicamente " << endl << endl;
            danocausado =  ataque;
        }

        else if( escolha == "2"){

            cout << "Você sente que precisa recuperar suas energias" << endl;
            danocausado = cura();

        }

        else if ( escolha == "3"){

            cout << "Você resolve usar artes arcanas" << endl;
            danocausado = magia();

        }

        else{
            cout << "Opção invalida : por favor selecione uma opção valida " << endl;
            danocausado = action();

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
        cout << "-------------------------------------------------------------" << endl;
        cout << " 1 - Fogo Arcano|Consome 10 de mana| causa 30 de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        cout << "Selecione o numero referente a magia desejada: ";

        cin >> escolha;

        if(escolha == "1"){

            if(mana >= 10){
                mana -= 10;

                system("clear");

                cout <<"-------------------------------------------------------------" << endl;
                cout << "Você gastou 10 de mana para conjurar o feitiço ";
                cout << mana;
                cout << " / ";
                cout << manaMax << endl;
                cout <<"-------------------------------------------------------------" << endl;
                cout << "Uma esfera de fogo surge em sua mão" << endl << endl;

                dano =  30;
            }
            else {
                cout << "Voce não possui mana  suficiente para conjurar tal arte" << endl;
            }
        }

        else{
            cout << "Opção invalida : por favor selecione uma opção valida " << endl;
        }

     return dano;

    }

// Metodo que enche o hp do personagem ao custo de mana
    int cura(){
        int totalDeCura = hpMax / 2;
        int manaParaCura = 10 * nivel;
        mana -= manaParaCura;

        system("clear");

        cout << "-------------------------------------------------------------" << endl;
        cout << "- Oh grande Frigg ouça meu chamado e me cure." << endl ;
        cout << "A atmosfera ilumina-se ao seu redor e você recupera " << totalDeCura << " hp" << endl << endl;
        cout << "Você gastou " << manaParaCura << " de mana";
        cout << mana << " / " << manaMax << endl;
        cout << "-------------------------------------------------------------" << endl;

        if(totalDeCura + hp >= hp)
            hp = hpMax;
        else
            hp += totalDeCura;

        return 0;

    }

// Remove hp do jogador de acordo com o dano sofrido
    void damangeRecieve(int dano){

        hp -= dano ;
        if(hp <= 0){

            status = false;
        }

    }

// faz alterações nos atributos do jogado quando o mesmo sobe de nivel
    int gerenciadorExp(){
        if(exp >= nivel){
            hpMax+= hpMax/5;
            manaMax += manaMax/5;
            velocidade+= velocidade  / 3 ;
            ataque+= ataque/5 ;
            defesa+= defesa/5;
            defesaMagica+= defesaMagica/5;
            nivel++;
            controlNivel= controlNivel * 2;
            hp =  hpMax;
            mana = manaMax;
        }
    }
// a cada termino de batalha enche o hp e mana do jogador e tambem verifica se o jogador possui xp suficiente para subir de nivel
    int update( int xp ) {

        exp += xp;
        hp =  hpMax;
        mana =  manaMax;

        if(exp >= controlNivel){
            gerenciadorExp();

        }

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
        cout << "-------------------------------------------------------------" << endl << endl;

    }

};

struct inimigo{
    string nome;
    int hp = 0;
    int velocidade;
    int ataque;
    int defesa;
    int defesaMagica;
    int xpDrop; // esse atributo indica quanto de xp o inimigo dara ao ser derrotado
    bool status = true;

    void ImprimeInfoInimigo(){
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Informações do Inimigo:  " << nome << endl;
        cout << "HP: " << hp << endl;
        cout << "Velocidade: " << velocidade << endl;
        cout << "Pontos de ataque: " << ataque << endl;
        cout << "Pontos de defesa: " << defesa << endl;
        cout << "Pontos de defesa magica: " << defesaMagica << endl;
        cout << "-------------------------------------------------------------" << endl << endl;

    }

     // remove a quantidade recebida do hp do inimigo
    void damangeRecieve(int dano){

        hp -= dano ;
        if(hp <= 0){

            status = false;
        }
    }

};

void printAcoes(){

    cout << "" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Selecione uma ação :" << endl;
    cout << "1 - Atague fisico "<< endl;
    cout << "2 - Cura  " << endl;
    cout << "3 - Magia " << endl << endl;
    cout << "-------------------------------------------------------------" << endl << endl << endl;

}


int seletorDeAcoes(Player player, inimigo inimigo){
    int escolha;
    int danoCausado ;

    printAcoes();

    cout << "Digite o numero referente a ação desejada : ";
    cin >> escolha;
    cout << "" << endl;

    switch (escolha) {
        case 1:{
            cout << "Você ataca o inimigo fisicamente " << endl << endl;
            float dano = (float) player.ataque;
            float defesa = ((float) inimigo.defesa) / 100.0;
            float calculoDeDano = dano / (defesa + 1.0);
            danoCausado = (int) calculoDeDano;
            break;
        }
        case 2:{
            cout << "Você sente que precisa recuperar suas energias" << endl;
            danoCausado = player.cura();
            break;
        }
        case 3:{
            cout << "Você resolve chamar as forças aliadas" << endl;
            float danoMagico = (float) player.magia();
            float defesaMagica = ((float) inimigo.defesaMagica) / 100.0;
            float calculoDeDano = danoMagico / (defesaMagica + 1.0);
            danoCausado = (int) calculoDeDano;
            break;
        }
        default:{
            cout << "Opção invalida : por favor selecione uma opção valida " << endl;
            danoCausado = seletorDeAcoes(player, inimigo);
        }
    }

    return danoCausado;

}


//array com nomes de inimigos
string enemyname[] = {"morcego","dragão", "troll","goblin","orc","mago negro","rato","barata" ,
                        "demonio ","harpia", "Cerberus","cobra", "espirito","Cavaleiro Negro","Corrompido"};


// responsavel pela criação de inimigo randomico
inimigo enemyMaker (Player player){

    inimigo i;
    srand (time(NULL));
    int indice = rand()% 15;
    string nome = enemyname[indice];

    i.nome = nome ; // seleciona um nome aleatorio do array de inimigos;
    i.ataque = rand()% player.ataque *3;
    i.velocidade = rand()% player.velocidade +5 ;
    i.hp = player.hp /2;
    i.defesa =  rand() % (player.defesa *2);
    i.defesaMagica = rand() % (player.defesaMagica*2);

    return i;

}


// responsavel por controlar o sitema de batalha do jogo
// recebe um jogador e um inteiro com o numero de inimigos
void gerenciadorBatalha (Player player){

    inimigo enemy;
    enemy = enemyMaker(player);
    bool alive = true;

    cout << "" << endl;
    cout << "Um novo inimigo surge :" << endl << endl;

    usleep(3000000);
    system("clear");

    cout<< enemy.nome << endl;

    while(alive == true){

        alive = false;

        if(player.status == true and enemy.status == true){ // se o jogador e o inimigo estão vivos ambos podem atacar
           alive = true;

           enemy.ImprimeInfoInimigo();
           usleep(3000000);

           cout << "Seu turno" << endl << endl;
           cout << "-------------------------------------------------------------" << endl;
           cout << "HP: " << player.hp << endl;
           cout << "Mana: " << player.mana << endl;
           cout << "-------------------------------------------------------------" << endl;

           int dano = player.action();

           enemy.damangeRecieve(dano);

           cout<< "Voce causou "<< dano << " de dano em " << enemy.nome << endl << endl;

           usleep(4000000);
           system("clear");

           if(enemy.status){
                cout << "Turno inimigo" << endl << endl;

                usleep(2000000);
                system("clear");

                player.damangeRecieve(enemy.ataque);
                cout << " O inimigo lhe causou  " << enemy.ataque << " de dano" << endl << endl;

                usleep(3000000);

            }

        }

        else {
            if(enemy.status == false){
                cout << "Voce venceu";
                player.update(enemy.xpDrop);
            }

            else {
                cout << "Você Morreu";
                system("clear");
                cout << "Game Over";
            }
          }

    }

}


int main()
{
    setlocale(LC_ALL, ""); // permite acentuação
    Player player1;
    player1.changeName();
    player1.imprimeInfoJogador();
    gerenciadorBatalha(player1);

}
