#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
//#include <windows.h>

using namespace std;
using namespace std;

 // ajudam o jogador durante a batalha , sao chamados de acordo com o nivel do jogador
struct Aliados{

    int hp;
    //int hpMax = 300; pode ser implementado para que um aliado possa se curar
    int ataque;
    int danoMagico;
    int defesa;
    int defesaMagica;
    int velocidade;
    int mana;
    int manaMax;
    bool status;
    int lvl;

}susanoo, amaterasu, tsukuyomi, xehanort;

// estrutura das magias do jogo
struct Magia{
    int dano;
    int mana;
    int lvl;
}explosion, thundara ;
// no nosso jogo existem dois tipos de dano fisico e magico esse metodo � responsavel pelo calculo do dano fisico
int calculaDanoFisico(float dano, float defesa){
    defesa = defesa / 100.0;
    return dano / (defesa + 1.0);
}
// analogo ao metodo anterior , contudo para o dano magico
int calculaDanoMagico(float danoMagico, float defesaMagica){
    defesaMagica = defesaMagica / 100.0;
    return danoMagico / (defesaMagica + 1.0);
}

struct Player{

    string nomeDoJogador = "X";
    int hp = 300; // Pontos de vida do jogador
    int hpMax = 300; // quantidade max de hp do jogador
    int velocidade = 15; // Pontos de velocidade do jogador (influencia em quem ataca primeiro)
    int exp = 0; // Pontos de experiencia do jogador
    int ataque = 10; // pontos de ataque do jogador
    int danoMagico = 20;
    int defesa = 10; // pontos de defesa do jogador
    int defesaMagica = 15; // pontos de defesa magica do jogador
    int controlNivel = 100; // quando os pontos de experiencia do jogador atigem o valor dessa variavel o jogador passa de nivel
    int nivel = 1; // atributo que rege as outras caracteristicas do jogador
    int mana = 200; // responsavel por conjura��o de magia
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


    void printAcoes(){

        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Selecione uma a��o :" << endl;
        cout << "1 - Atague fisico "<< endl;
        cout << "2 - Cura  " << endl;
        cout << "3 - Magia " << endl << endl;
        cout << "-------------------------------------------------------------" << endl << endl << endl;

    }

    // Responsavel por realizar a��o escolhida pelo jogador
    int seletorDeAcoes(int defesa, int defesaMagica){
        int escolha;
        int danoCausado;

        printAcoes();

        cout << "Digite o numero referente a a��o desejada : ";
        cin >> escolha;
        cout << "" << endl;

        switch (escolha) {
            case 1:{
                cout << "Voc� ataca o inimigo fisicamente " << endl << endl;
                danoCausado = calculaDanoFisico((float) ataque, (float) defesa);
                break;
        }
        case 2:{
            cout << "Voc� sente que precisa recuperar suas energias" << endl;
            danoCausado = cura();
            break;
        }
        case 3:{
            cout << "Voc� resolve chamar as for�as aliadas" << endl;
            float magicalDamange = (float) magic();
            danoCausado = calculaDanoMagico(magicalDamange, defesaMagica);
            break;
        }
        default:{
            cout << "Op��o invalida : por favor selecione uma op��o valida " << endl;
            danoCausado = seletorDeAcoes(defesa, defesaMagica);
        }
    }

    return danoCausado;

}

    // este metodo contem magias
    // retorna -1 caso o jogador nao possua os requisitos
    // caso possua retorna o dano
    int magic(){
        explosion.dano = 70;
        explosion.mana = 10 * nivel;
        explosion.lvl = 1;

        thundara.dano = int (((float) danoMagico) * 1.30);
        thundara.mana = 15 * nivel;
        thundara.lvl = 2;

        if(nivel >= explosion.lvl){
            cout << "-------------------------------------------------------------" << endl;
            cout << " 1 - Explosion|Consome " << explosion.mana << " de mana| causa " << explosion.dano <<" de dano"<< endl;
            cout << "-------------------------------------------------------------" << endl << endl;
        }if(nivel >= thundara.lvl){
            cout << "-------------------------------------------------------------" << endl;
            cout << " 2 - Thundara|Consome " << thundara.mana << " de mana| causa " << thundara.dano  * 2 <<" de dano"<< endl;
            cout << "-------------------------------------------------------------" << endl << endl;
        }

        cout << "Selecione o numero referente a magia desejada: ";

        int escolha;
        cin >> escolha;

        int danoCausado = 0;

        switch(escolha){
        case 1:
            if(mana >= explosion.mana){
                mana -= explosion.mana;

                system("clear");

                cout <<"-------------------------------------------------------------" << endl;
                cout << "Voc� gastou " << explosion.mana << " de mana para chamar Megumin";
                cout << mana;
                cout << " / ";
                cout << manaMax << endl;
                cout <<"-------------------------------------------------------------" << endl;
                cout << "Megumin, aquela que detem todo o poder do fogo e da explosao, eu a invoco, subjulgue meus inimigos: EXPLOSION!!!" << endl << endl;

                danoCausado = explosion.dano;
            }
            else {
                cout << "Voce n�o possui mana  suficiente para conjurar tal arte" << endl;
            }
            break;
        case 2:
            if(nivel <= thundara.lvl){

                cout << endl << "Voce ainda nao � forte o suficiente para fazer esse chamado" << endl << endl;
                break;
            }
            if(mana >= thundara.mana){
                mana -= thundara.mana;

                system("clear");

                cout <<"-------------------------------------------------------------" << endl;
                cout << "Voc� gastou " << thundara.mana << " de mana para chamar Thor ";
                cout << mana;
                cout << " / ";
                cout << manaMax << endl;
                cout <<"-------------------------------------------------------------" << endl;
                cout << "Grande Thor, digno do poderoso Mjolnir venha at� meus inimigos como o trovao: THUNDARA!!!" << endl << endl;

                danoCausado = thundara.dano;
            }
            else {
                cout << "Voce n�o possui mana  suficiente para conjurar tal arte" << endl;
            }
            break;
        default:
            cout << "Op��o invalida : por favor selecione uma op��o valida " << endl;
        }
        return danoCausado;

    }
// Metodo que enche o hp do personagem ao custo de mana
    int cura(){
        int totalDeCura = hpMax / 2;
        int manaParaCura = 10 * nivel;
        mana -= manaParaCura;

        system("clear");

        cout << "-------------------------------------------------------------" << endl;
        cout << "- Oh grande Frigg ou�a meu chamado e me cure." << endl ;
        cout << "A atmosfera ilumina-se ao seu redor e voc� recupera " << totalDeCura << " hp" << endl << endl;
        cout << "Voc� gastou " << manaParaCura << " de mana";
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

// faz altera��es nos atributos do jogado quando o mesmo sobe de nivel
    int gerenciadorExp(){
       cout << "-------------------------------------------------------------" << endl << endl;
       cout << "Com o frenesi da batalha voc� sente um aumento subito de suas habilidades" <<endl;
                cout << "-------------------------------------------------------------" << endl << endl;
        if(exp >= controlNivel){
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
            imprimeInfoJogador();

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
        cout << "Informa��es do Inimigo:  " << nome << endl;
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




//array com nomes de inimigos
string enemyname[] = {"morcego","drag�o", "troll","goblin","orc","mago negro","rato","barata" ,
                        "demonio ","harpia", "Cerberus","cobra", "espirito","Cavaleiro Negro","Corrompido"};


// responsavel pela cria��o de inimigo randomico
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
    i.xpDrop =  rand() % 1000;

    return i;

}

void setSusanoo(Player player){

    susanoo.hp = int (((float) player.hp) * 1.50);
    susanoo.ataque = int (((float) player.ataque) * 1.35);
    susanoo.danoMagico = int (((float) player.danoMagico) * 0.25);
    susanoo.defesa = int (((float) player.defesa) * 1.25);
    susanoo.defesaMagica = int (((float) player.defesaMagica) * 0.75);
    susanoo.velocidade = int (((float) player.velocidade) * 0.95);
    susanoo.mana = int (((float) player.mana) * 0.30);
    susanoo.manaMax = int (((float) player.mana) * 0.30);
    susanoo.status = true;
    susanoo.lvl = 1;

}

void setAmaterasu(Player player){

    amaterasu.hp = int (((float) player.hp) * 1.0);
    amaterasu.ataque = int (((float) player.ataque) * 0.50);
    amaterasu.danoMagico = int (((float) player.danoMagico) * 1.50);
    amaterasu.defesa = int (((float) player.defesa) * 0.90);
    amaterasu.defesaMagica = int (((float) player.defesaMagica) * 1.25);
    amaterasu.velocidade = int (((float) player.velocidade) * 0.90);
    amaterasu.mana = int (((float) player.mana) * 1.60);
    amaterasu.manaMax = int (((float) player.mana) * 1.60);
    amaterasu.status = true;
    amaterasu.lvl = 2;

}

void setTsukuyomi(Player player){
    tsukuyomi.hp = int (((float) player.hp) * 1.20);
    tsukuyomi.ataque = int (((float) player.ataque) * 1.15);
    tsukuyomi.danoMagico = int (((float) player.danoMagico) * 1.15);
    tsukuyomi.defesa = int (((float) player.defesa) * 1.15);
    tsukuyomi.defesaMagica = int (((float) player.defesaMagica) * 1.10);
    tsukuyomi.velocidade = int (((float) player.velocidade) * 0.80);
    tsukuyomi.mana = int (((float) player.mana) * 1.0);
    tsukuyomi.manaMax = int (((float) player.mana) * 1.0);
    tsukuyomi.status = true;
    tsukuyomi.lvl = 3;

}

void setXehanort(Player player){

    xehanort.hp = int (((float) player.hp) * 2.0);
    xehanort.ataque = int (((float) player.ataque) * 1.75);
    xehanort.danoMagico = int (((float) player.danoMagico) * 1.0);
    xehanort.defesa = int (((float) player.defesa) * 1.60);
    xehanort.defesaMagica = int (((float) player.defesaMagica) * 1.0);
    xehanort.velocidade = int (((float) player.velocidade) * 2.0);
    xehanort.mana = int (((float) player.mana) * 1.0);
    xehanort.manaMax = int (((float) player.mana) * 1.0);
    xehanort.status = true;
    xehanort.lvl = 4;

}

void imprimeAliados(){

    string aliados[] = {"Susano-o", "Amaterasu", "Tsukuyomi", "Xehanort"};

    for(int i = 0; i < 4; i++){
        cout << " " << i+1 << " - " << aliados[i] <<"          nivel necessario: " << i+1 << endl;
    }

}

void enemyFirst (Player player , inimigo enemy) {

    cout << "Turno inimigo" << endl << endl;

                usleep(2000000);
                system("clear");

                int danoCalculado = calculaDanoFisico((float) enemy.ataque, (float) player.defesa);
                player.damangeRecieve(danoCalculado);

                cout << " O inimigo lhe causou  " << danoCalculado << " de dano" << endl << endl;

                usleep(3000000);

}

int ataqueAliado(string aliado){
    int danoCausado;

    if(aliado == "Susano-o"){

        danoCausado = susanoo.ataque;

    }else if(aliado == "Amaterasu"){

        danoCausado = amaterasu.ataque;

      }else if(aliado == "Tsukuyomi"){

        danoCausado = tsukuyomi.ataque;

    }else if(aliado == "Xehanort"){

        danoCausado = xehanort.ataque;
    }
    return danoCausado;

}

int magiaAliado(string aliado){
    int danoCausado;
    if(aliado == "Susano-o"){
        cout << "-------------------------------------------------------------" << endl;
        cout << " 1 - Kusanagi|Consome 20 de mana| causa " << susanoo.danoMagico <<" de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;

        cout << "Escolha a magia: ";
        int escolha;
        cin >> escolha;

        if(escolha == 1){
            danoCausado = susanoo.danoMagico;
            susanoo.mana =  susanoo.mana - 20;
        }else{
            cout << "Magia invalida";
            danoCausado = 0;
        }
      }else if(aliado == "Amaterasu"){
        cout << "-------------------------------------------------------------" << endl;
        cout << " 1 - Hiken|Consome 20 de mana| causa " << amaterasu.danoMagico <<" de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        cout << " 2 - Sun Blade|Consome 40 de mana| causa " << amaterasu.danoMagico  * 2 <<" de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        cout << " 3 - Solar Spear|Consome 60 de mana| causa " << amaterasu.danoMagico * 3 <<" de dano"<< endl;

        cout << "Escolha a magia: ";
        int escolha;
        cin >> escolha;

        if(escolha == 1){
            if(amaterasu.mana > 20){
            danoCausado = amaterasu.danoMagico;
            amaterasu.mana =  amaterasu.mana - 20;}
            else {

             cout << "-------------------------------------------------------------" << endl << endl;
             cout << "Voc� n�o possui mana suficente para conjurar tal magia"<<endl;
              cout << "-------------------------------------------------------------" << endl << endl;


            }

        }
        else if(escolha == 2){
            if(amaterasu.mana > 40){
            danoCausado = amaterasu.danoMagico *2;
             amaterasu.mana =  amaterasu.mana - 40;}
             else {

                cout << "-------------------------------------------------------------" << endl << endl;
                cout << "Voc� n�o possui mana suficente para conjurar tal magia"<<endl;
                cout << "-------------------------------------------------------------" << endl << endl;

             }
        }
           else if(escolha == 3){
           if(amaterasu.mana < 60){
            danoCausado = amaterasu.danoMagico *3;
            amaterasu.mana =  amaterasu.mana - 60;}
            else{
                cout << "-------------------------------------------------------------" << endl << endl;
                cout << "Voc� n�o possui mana suficente para conjurar tal magia"<<endl;
                cout << "-------------------------------------------------------------" << endl << endl;
            }
        }

        else{
            cout << "Magia invalida";
        }
      }else if(aliado == "Tsukuyomi"){
        cout << "-------------------------------------------------------------" << endl;
        cout << " 1 - Moon Blast|Consome 20 de mana| causa " << tsukuyomi.danoMagico <<" de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;

        cout << "Escolha a magia: ";
        int escolha;
        cin >> escolha;

        if(escolha == 1 ){
            if(tsukuyomi.mana < 20){
                danoCausado = tsukuyomi.danoMagico;
                tsukuyomi.mana = tsukuyomi.mana - 20;}
            else{
                cout << "-------------------------------------------------------------" << endl << endl;
                cout << "Voc� n�o possui mana suficente para conjurar tal magia"<<endl;
                cout << "-------------------------------------------------------------" << endl << endl;

            }
        }else{
            cout << "Magia invalida";
        }
    }else if(aliado == "Xehanort"){
        cout << "-------------------------------------------------------------" << endl;
        cout << " 1 - Ethereal Blades|Consome 20 de mana| causa " << xehanort.danoMagico <<" de dano"<< endl;
        cout << "-------------------------------------------------------------" << endl << endl;

        cout << "Escolha a magia: ";
        int escolha;
        cin >> escolha;

        if(escolha == 1){
            if(xehanort.mana < 20){
                danoCausado = xehanort.danoMagico;
                xehanort.mana = xehanort.mana - 20;}
            else{
                cout << "-------------------------------------------------------------" << endl << endl;
                cout << "Voc� n�o possui mana suficente para conjurar tal magia"<<endl;
                cout << "-------------------------------------------------------------" << endl << endl;
            }
        }else{
            cout << "Magia invalida";
        }
    }

}
// responsavel por controlar o sitema de batalha do jogo
// recebe um jogador e um inteiro com o numero de inimigos
void gerenciadorBatalha (Player player){

    srand(time(NULL));
    int number = rand();
    inimigo enemy;
    enemy = enemyMaker(player);
    bool alive = true;

    cout << "" << endl;
    cout << "Um novo inimigo surge :" << endl << endl;

    usleep(3000000);
    system("clear");

    cout<< enemy.nome << endl;

    if(number%2 == 0){
        enemyFirst(player, enemy);
    }

    cout << endl << "Chame seus aliados" << endl << endl;
    cout << "Aliados disponiveis:" << endl;

    imprimeAliados();
    string aliado[] = { "", ""};
    int n;              //numero de aliados
    player.nivel == 1 ? n = 1 : n = 0;
    int opcao;

    while(n < 2){
        cout << "Digite o numero referente ao aliado desejado : ";
        cin >> opcao;

        if(player.nivel >= opcao){
            cout << "Voce ainda n�o tem for�as para realizar esse chamado" << endl << endl;
        }else{
            if(opcao == 1 && "Susano-o" != aliado[0]){
                setSusanoo(player);
                aliado[0] == "" ? aliado[0] = "Susano-o" : aliado[1] = "Susano-o";
                n++;
            }else if(opcao == 2 && "Amaterasu"  != aliado[0]){
                setAmaterasu(player);
                aliado[0] == "" ? aliado[0] = "Amaterasu" : aliado[1] = "Amaterasu" ;
                n++;
            }else if(opcao == 3 && "Tsukuyomi" != aliado[0]){
                setTsukuyomi(player);
                aliado[0] == "" ? aliado[0] = "Tsukuyomi" : aliado[1] = "Tsukuyomi";
                n++;
            }else if(opcao == 4 && "Xehanort" != aliado[0]){
                setXehanort(player);
                aliado[0] == "" ? aliado[0] = "Xehanort" : aliado[1] = "Xehanort";
                n++;
            }else{
                cout << "Opcao invalida, tente novamente" << endl;
            }
        }
    }




    while(alive == true){

        alive = false;

        if(player.status == true and enemy.status == true){ // se o jogador e o inimigo est�o vivos ambos podem atacar
           alive = true;

           enemy.ImprimeInfoInimigo();
           usleep(3000000);

           cout << "Seu turno" << endl << endl;
           cout << "-------------------------------------------------------------" << endl;
           cout << "HP: " << player.hp << endl;
           cout << "Mana: " << player.mana << endl;
           cout << "-------------------------------------------------------------" << endl;

           int dano = player.seletorDeAcoes(enemy.defesa, enemy.defesaMagica);
           enemy.damangeRecieve(dano);

           cout<< "Voce causou "<< dano << " de dano em " << enemy.nome << endl << endl;

           usleep(4000000);
           system("clear");

           int n;
           player.nivel == 1 ? n = 1 : n = 2;

           for(int i = 0; i < n; i++){

                cout << endl << "Turno de " << aliado[0] << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "Selecione uma a��o :" << endl;
                cout << "1 - Atague fisico "<< endl;
                cout << "2 - Magia " << endl << endl;
                cout << "-------------------------------------------------------------" << endl << endl ;

                int escolha;
                cout << "Digite o numero referente a a��o desejada : ";
                cin >> escolha;
                cout << "" << endl;

                switch (escolha) {
                    case 1:{
                        cout << aliado[0] << " ataca o inimigo fisicamente ";
                        int dano = ataqueAliado(aliado[0]);
                        dano = calculaDanoFisico(dano, enemy.defesa);
                        cout << "causando " << dano << " de dano" << endl;
                        enemy.damangeRecieve(dano);
                        break;
                    }
                    case 2:{
                        cout << aliado[0] << " utiliza de suas forcas para invocar uma magia" << endl;
                        int dano = magiaAliado(aliado[0]);
                        dano = calculaDanoMagico(dano, enemy.defesaMagica);
                        cout << aliado[0] << " causou " << dano << " de dano" << endl << endl;
                        enemy.damangeRecieve(dano);
                        break;
                    }
                }
           }

           if(enemy.status){
                cout << "Turno inimigo" << endl << endl;

                usleep(2000000);
                system("clear");

                int danoCalculado = calculaDanoFisico((float) enemy.ataque, (float) player.defesa);
                player.damangeRecieve(danoCalculado);

                cout << " O inimigo lhe causou  " << danoCalculado << " de dano" << endl << endl;

                usleep(3000000);

            }

        }else {
            if(enemy.status == false){
                cout << "Voce venceu" << endl;
                player.update(enemy.xpDrop);
            }

            else {
                cout << "Voc� Morreu";
                system("clear");
                cout << "Game Over";
            }
          }

    }

}

int main()
{
    bool continua =  true;
    int aux ;
    setlocale(LC_ALL, ""); // permite acentua��o
    Player player1;
    player1.changeName();
    player1.imprimeInfoJogador();
    while(continua){
    gerenciadorBatalha(player1);
    cout << "-------------------------------------------------------------" << endl << endl;
    cout << "Deseja Continuar ?" << endl << endl;
    cout << " 1- Sim   |   2 N�o" << endl;
    cin >>  aux;
    if(aux == 2) { continua = false;}




    }
}
