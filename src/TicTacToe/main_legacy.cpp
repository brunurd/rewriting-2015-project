#include <ctime>
#include <stdio.h>
#include <graphics.h>
#include <cstring>

using namespace std;

#define ESC 27
#define ENTER 13

struct collider {
    POINT A;
    POINT B;
    int width;
    int height;
    char valor;
};

POINT mouse;
HWND janela;
char jogador, cpu, quemGanhou;
bool quit, pause, cena[4], liberaMouse, escolhido, yourTurn;
int pag, tamanho, tecla, winX, winY, timer1, timer2, timer3, timer4, waitToClick, caraCoroa, tilesScaled, i;
struct collider continuar, sair, souBola, souXis, tile[9];

int cantos[4] = {0, 2, 6, 8};
int outros[4] = {1, 3, 5, 7};

//--------------------------------
// AQUI VEM OS POINTERS BITMAP:
//--------------------------------

void* titleScreen;
void* enter;
void* pausa;
void* pausaContinuarHover;
void* pausaSairHover;
void* chooseScreen;
void* escolha;
void* chooseXis;
void* chooseBola;
void* voceComeca;
void* cpuComeca;
void* tileScale[5];
void* tileBG;
void* tileVazia;
void* tileHover;
void* tileX;
void* tileO;
void* ganhou[4];
void* perdeu[4];
void* deuVelha[4];

//--------------------------------
// FUNCOES DE COLISAO:
//--------------------------------

struct collider makeCollider(int x, int y, int w, int h) {
    struct collider Coll;
    Coll.A.x = x;
    Coll.A.y = y;
    Coll.width = w;
    Coll.height = h;
    Coll.B.x = x + w;
    Coll.B.y = y + h;
    return Coll;
}

bool collision(POINT P, struct collider Collider) {
    if (P.x >= Collider.A.x && P.y >= Collider.A.y && P.x <= Collider.B.x && P.y <= Collider.B.y) return TRUE;
    else return FALSE;
}

//--------------------------
// FUNCOES PARA OS SPRITES:
//--------------------------

void* carregaImagem(const char* filename, int w, int h) {
    readimagefile(filename, 0, 0, w, h);
    int tamanho = imagesize(0, 0, w, h);
    void* Imagem = malloc(tamanho);
    getimage(0, 0, w, h, Imagem);
    return Imagem;
}

void spritesheet(void* sheet[], string file, int frames, int W, int H) {
    int len = file.length();
    const char* num = "0123456789";
    int iiii = frames / 1000;
    int iii = frames / 100;
    int ii = frames / 10;
    int i = frames % 10;
    if (i == 0) i = 9;
    int ciiii = 0;
    int ciii = 0;
    int cii = 0;
    int ci = 0;
    int frame = 0;
    string stringV[frames];
    const char* constCharV[frames];
    
    for (ciiii = 0; ciiii <= iiii; ciiii++) {
        for (ciii = 0; ciii <= iii; ciii++) {
            for (cii = 0; cii <= ii; cii++) {
                for (ci = 0; ci <= i; ci++) {
                    file[len - 8] = num[ciiii];
                    file[len - 7] = num[ciii];
                    file[len - 6] = num[cii];
                    file[len - 5] = num[ci];
                    
                    if (frame < frames) {
                        stringV[frame] = file;
                        frame++;
                    }
                }
            }
        }
    }
        
    for (int cont = 0; cont < frames; cont++) {
        constCharV[cont] = stringV[cont].c_str();
        sheet[cont] = carregaImagem(constCharV[cont], W, H);
        cleardevice();
    }
}

//---------------------
// FUNCOES DO JOGO:
//---------------------

void retornarAoMenu() {
    tecla = 0;
    timer1 = 0;
    timer2 = -282;
    timer3 = 600;
    timer4 = 100;
    cena[0] = TRUE;
    cena[1] = FALSE;
    cena[2] = FALSE;
    cena[3] = FALSE;
    pause = FALSE;
    liberaMouse = FALSE;
    escolhido = FALSE;
    tilesScaled = 0;
    yourTurn = FALSE;
    
    souXis = makeCollider(-221, 221, 221, 220);
    souBola = makeCollider(600, 220, 222, 220);
    
    for (i = 0; i < 3; i++) {
        tile[i].valor = ' ';
    }
    
    for (i = 3; i < 6; i++) {
        tile[i].valor = ' ';
    }
    
    for (i = 6; i < 9; i++) {
        tile[i].valor = ' ';
    }
}

void pauseMenu() {
    
    if (tecla == ESC && pause == FALSE) {
        pause = TRUE;
        tecla = 0;
    }
        
    if (tecla == ESC && pause == TRUE) {
        pause = FALSE;
        liberaMouse = FALSE;
        timer2 = -282;
        tecla = 0;
    }
    
    if (pause == TRUE) {
        
        putimage(135, timer2, pausa, 0);
        
        if (collision(mouse, continuar) && liberaMouse == TRUE) {
            putimage(continuar.A.x, continuar.A.y, pausaContinuarHover, 0);
            if (GetKeyState(VK_LBUTTON) & 0x80) {
                tecla = 0;
                waitToClick = 50;
                pause = FALSE;
                liberaMouse = FALSE;
                timer2 = -282;
            }
        }
        
        if (collision(mouse, sair) && liberaMouse == TRUE) {
            putimage(sair.A.x, sair.A.y, pausaSairHover, 0);
            if (GetKeyState(VK_LBUTTON) & 0x80) {
                if (cena[2]) {
                    waitToClick = 50;
                    retornarAoMenu();
                }
                else quit = TRUE;
            }
        }
        
        if (timer2 < 159) timer2 += 50;
        else if (timer2 > 159) timer2 = 159;
        else liberaMouse = TRUE;
    }
}

void quemComeca() {
    if (escolhido == TRUE) {
        if (timer1 > -221) timer1 -= 20;
        else if (timer1 < -221) timer1 = -221;
        if (timer3 < 600) timer3 += 20;
        else if (timer3 > 600) timer3 = 600;
        
        if (timer1 == -221 && timer3 == 600) {
            
            if (caraCoroa == 1) {
                yourTurn = TRUE;
                putimage(84, 297, voceComeca, 0);
            }
            
            else {
                yourTurn = FALSE;
                putimage(84, 297, cpuComeca, 0);
            }
            
            timer4--;
            
            if (timer4 <= 0) {
                cena[1] = FALSE;
                cena[2] = TRUE;
                liberaMouse = FALSE;
                timer1 = 0;
                timer3 = 0;
                tecla = 0;
            }
        }
    }
}

void confere(char conferir, char resultado) {
    
    // Verificar se há vitória ou derrota na diagonal pelos cantos:
    if (tile[4].valor == conferir) {
        if (tile[0].valor == conferir && tile[8].valor == ' ') { tile[8].valor = resultado; yourTurn = TRUE; }
        else if (tile[1].valor == conferir && tile[7].valor == ' ') { tile[7].valor = resultado; yourTurn = TRUE; }
        else if (tile[2].valor == conferir && tile[6].valor == ' ') { tile[6].valor = resultado; yourTurn = TRUE; }
        else if (tile[3].valor == conferir && tile[5].valor == ' ') { tile[5].valor = resultado; yourTurn = TRUE; }
        else if (tile[5].valor == conferir && tile[3].valor == ' ') { tile[3].valor = resultado; yourTurn = TRUE; }
        else if (tile[6].valor == conferir && tile[2].valor == ' ') { tile[2].valor = resultado; yourTurn = TRUE; }
        else if (tile[7].valor == conferir && tile[1].valor == ' ') { tile[1].valor = resultado; yourTurn = TRUE; }
        else if (tile[8].valor == conferir && tile[0].valor == ' ') { tile[0].valor = resultado; yourTurn = TRUE; }
    }
    
    // Verificar se há vitória ou derrota pelo centro:
    else if (tile[0].valor == conferir && tile[8].valor == conferir && tile[4].valor == ' ') { tile[4].valor = resultado; yourTurn = TRUE; }
    else if (tile[1].valor == conferir && tile[7].valor == conferir && tile[4].valor == ' ') { tile[4].valor = resultado; yourTurn = TRUE; }
    else if (tile[2].valor == conferir && tile[6].valor == conferir && tile[4].valor == ' ') { tile[4].valor = resultado; yourTurn = TRUE; }
    else if (tile[3].valor == conferir && tile[5].valor == conferir && tile[4].valor == ' ') { tile[4].valor = resultado; yourTurn = TRUE; }
    
    // Verificar se há vitória ou derrota na vertical pelos centros:
    else if (tile[0].valor == conferir && tile[6].valor == conferir && tile[3].valor == ' ') { tile[3].valor = resultado; yourTurn = TRUE; }
    else if (tile[2].valor == conferir && tile[8].valor == conferir && tile[5].valor == ' ') { tile[5].valor = resultado; yourTurn = TRUE; }
    
    // Verificar se há vitória ou derrota na horizontal pelos centros:
    else if (tile[0].valor == conferir && tile[2].valor == conferir && tile[1].valor == ' ') { tile[1].valor = resultado; yourTurn = TRUE; }
    else if (tile[6].valor == conferir && tile[8].valor == conferir && tile[7].valor == ' ') { tile[7].valor = resultado; yourTurn = TRUE; }
    
    // Verificar se há vitória ou derrota na vertical por baixo:
    else if (tile[0].valor == conferir && tile[3].valor == conferir && tile[6].valor == ' ') { tile[6].valor = resultado; yourTurn = TRUE; }
    else if (tile[2].valor == conferir && tile[5].valor == conferir && tile[8].valor == ' ') { tile[8].valor = resultado; yourTurn = TRUE; }
    
    // Verificar se há vitória ou derrota na vertical por cima:
    else if (tile[3].valor == conferir && tile[6].valor == conferir && tile[0].valor == ' ') { tile[0].valor = resultado; yourTurn = TRUE; }
    else if (tile[5].valor == conferir && tile[8].valor == conferir && tile[2].valor == ' ') { tile[2].valor = resultado; yourTurn = TRUE; }
    
    // Verificar se há vitória ou derrota na horizontal pela direita:
    else if (tile[0].valor == conferir && tile[1].valor == conferir && tile[2].valor == ' ') { tile[2].valor = resultado; yourTurn = TRUE; }
    else if (tile[6].valor == conferir && tile[7].valor == conferir && tile[8].valor == ' ') { tile[8].valor = resultado; yourTurn = TRUE; }

    // Verificar se há vitória ou derrota na horizontal pela esquerda:
    else if (tile[1].valor == conferir && tile[2].valor == conferir && tile[0].valor == ' ') { tile[0].valor = resultado; yourTurn = TRUE; }
    else if (tile[7].valor == conferir && tile[8].valor == conferir && tile[6].valor == ' ') { tile[6].valor = resultado; yourTurn = TRUE; }
}

bool fim (char ganhador) {
    if (tile[0].valor == ganhador && tile[1].valor == ganhador && tile[2].valor == ganhador) return TRUE;
    else if (tile[3].valor == ganhador && tile[4].valor == ganhador && tile[5].valor == ganhador) return TRUE;
    else if (tile[6].valor == ganhador && tile[7].valor == ganhador && tile[8].valor == ganhador) return TRUE;
    
    else if (tile[0].valor == ganhador && tile[3].valor == ganhador && tile[6].valor == ganhador) return TRUE;
    else if (tile[1].valor == ganhador && tile[4].valor == ganhador && tile[7].valor == ganhador) return TRUE;
    else if (tile[2].valor == ganhador && tile[5].valor == ganhador && tile[8].valor == ganhador) return TRUE;
    
    else if (tile[0].valor == ganhador && tile[4].valor == ganhador && tile[8].valor == ganhador) return TRUE;
    else if (tile[2].valor == ganhador && tile[4].valor == ganhador && tile[6].valor == ganhador) return TRUE;
    
    else return FALSE;
}

void mostrarTiles(int i) {
    if (tile[i].valor == ' ') putimage(tile[i].A.x, tile[i].A.y, tileVazia, 0);
    else if (tile[i].valor == 'x') putimage(tile[i].A.x, tile[i].A.y, tileX, 0);
    else if (tile[i].valor == 'o') putimage(tile[i].A.x, tile[i].A.y, tileO, 0);
}

void partida() {
    
    for (int i = 0; i < 9; i++) {
        
        if (timer3 == 1000) {
            cena[2] = FALSE;
            cena[3] = TRUE;
            timer3 = 0;
        }
        
        if (timer3 == 0) { 
            
            if (fim(jogador)) {
                timer3 = 1;
                timer4 = 0;
                quemGanhou = 0;
            }
        
            else if (fim(cpu)) {
                timer3 = 1;
                timer4 = 0;
                quemGanhou = 1;
            }
        
            else {
                for (int I = 0; tile[I].valor != ' ' && I < 9; I++) {
                    if (I == 8) {
                        timer3 = 1;
                        timer4 = 0;
                        quemGanhou = 2;
                    }
                }
            }
        
            if (collision(mouse, tile[i]) && yourTurn == TRUE && pause == FALSE) {
            
                if (tile[i].valor == ' ') putimage(tile[i].A.x, tile[i].A.y, tileHover, 0);
                else if (tile[i].valor == 'x') putimage(tile[i].A.x, tile[i].A.y, tileX, 0);
                else if (tile[i].valor == 'o') putimage(tile[i].A.x, tile[i].A.y, tileO, 0);
            
                if (GetKeyState(VK_LBUTTON) & 0x80 && waitToClick == 0) {
                    if (tile[i].valor == ' ') {
                        waitToClick = 50;
                        tile[i].valor = jogador;
                        yourTurn = FALSE;
                    }
                }
            
            }
        
            //--------------------------
            // INTELIGENCIA ARTIFICIAL:
            //--------------------------
        
            else if (yourTurn == FALSE && pause == FALSE) {
                
                if (timer1 == -200) {
            
                    confere(cpu, cpu); // VITORIA
                    if (yourTurn == FALSE) confere(jogador, cpu); // DEFESA
                    
                    // SE FOR A PRIMEIRA JOGADA, JOGAR NOS CANTOS:
                    for (int i = 0; tile[i].valor == ' ' && i < 9; i++) {
                        if (i == 8) {
                            tile[cantos[rand()%4]].valor = cpu;
                            yourTurn = TRUE;
                        }
                    }
                    
                    // JOGAR NOS CANTOS:
                    for (int i = 0; i < 4 && yourTurn == FALSE; i++) {
                        if (tile[cantos[i]].valor == ' ') {
                            tile[cantos[i]].valor = cpu;
                            yourTurn = TRUE;
                        }
                    }
                    
                    // JOGAR NO CENTRO:
                    if (tile[4].valor == ' ' && yourTurn == FALSE) {
                        tile[4].valor = cpu;
                        yourTurn = TRUE;
                    }
                    
                    // JOGAR NOS OUTROS:
                    for (int i = 0; i < 4 && yourTurn == FALSE; i++) {
                        if (tile[outros[i]].valor == ' ') {
                            tile[outros[i]].valor = cpu;
                            yourTurn = TRUE;
                        }
                    }
                
                    timer1 = 0;
                }
                
                else {
                    mostrarTiles(i);
                    timer1--;
                }
            }
    
            //---------------------------
        
            else {
                mostrarTiles(i);
            }
        }
        
        else {
            mostrarTiles(i);
            timer3++;
        }

    }
    
    pauseMenu();
}

//----------------------------------------
// O JOGO TODO VEM NESSA FUNCAO UPDATE:
//----------------------------------------

void update() {
    
    if (GetCursorPos(&mouse)) if (ScreenToClient(janela, &mouse));
    
    if (waitToClick > 0) waitToClick--;
    
    if (cena[0]) {
        
        timer1 += 10;
        
        if (timer1 < 250) {
            putimage(0, 0, titleScreen, 0);
            putimage(104, 438, enter, 0);
        }
    
        else if (timer1 >= 250 && timer1 < 400) {
            putimage(0, 0, titleScreen, 0);
        }
    
        else if (timer1 >= 400) timer1 = 0;
        
        pauseMenu();
        
        if (GetKeyState(VK_LBUTTON) & 0x80 && pause == FALSE && waitToClick <= 30) {
            cena[0] = FALSE;
            cena[1] = TRUE;
            liberaMouse = FALSE;
            tecla = 0;
            timer1 = -221;
        }
    }
    
    if (cena[1]) {
        putimage(0, 0, chooseScreen, 0);
        putimage(timer1, 221, chooseXis, 0);
        putimage(timer3, 220, chooseBola, 0);

        souXis.A.x = timer1;
        souXis.B.x = timer1 + souXis.width;
        souBola.A.x = timer3;
        souBola.B.x = timer3 + souBola.width;
        
        if (escolhido == FALSE) {
            if (timer1 < 62) timer1 += 20;
            else if (timer1 > 62) timer1 = 62;
            if (timer3 > 319) timer3 -= 20;
            else if (timer3 < 319) timer3 = 319;
            if (timer1 == 62 && timer3 == 319) putimage(110, 152, escolha, 0);
        }
        
        quemComeca();
        pauseMenu();
        
        if (collision(mouse, souXis) && pause == FALSE && waitToClick == 0) {
            if (GetKeyState(VK_LBUTTON) & 0x80) {
                jogador = 'x';
                cpu = 'o';
                waitToClick = 50;
                caraCoroa = rand()%2;
                souXis = makeCollider(-1, -1, -1, -1);
                souBola = makeCollider(-1, -1, -1, -1);
                escolhido = TRUE;
            }
        }
        
        if (collision(mouse, souBola) && pause == FALSE && waitToClick == 0) {
            if (GetKeyState(VK_LBUTTON) & 0x80) {
                jogador = 'o';
                cpu = 'x';
                waitToClick = 50;
                caraCoroa = rand()%2;
                souXis = makeCollider(-1, -1, -1, -1);
                souBola = makeCollider(-1, -1, -1, -1);
                escolhido = TRUE;
            }
        }
    }
    
    if (cena[2]) {
        
        if (tilesScaled == 0) {
            for (int i = 0; i < 9; i++) {
                putimage(tile[i].A.x, tile[i].A.y, tileBG, 0);
            }
        }
        
        if (timer1 < 4)
            timer1++;
        
        else if (timer1 >= 4 && tilesScaled < 9) {
            timer1 = 0;
            tilesScaled++;
        }
        
        if (tilesScaled == 0) putimage(tile[0].A.x, tile[0].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 0) putimage(tile[0].A.x, tile[0].A.y, tileVazia, 0);
        if (tilesScaled == 1) putimage(tile[1].A.x, tile[1].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 1) putimage(tile[1].A.x, tile[1].A.y, tileVazia, 0);
        if (tilesScaled == 2) putimage(tile[2].A.x, tile[2].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 2) putimage(tile[2].A.x, tile[2].A.y, tileVazia, 0);
        if (tilesScaled == 3) putimage(tile[3].A.x, tile[3].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 3) putimage(tile[3].A.x, tile[3].A.y, tileVazia, 0);
        if (tilesScaled == 4) putimage(tile[4].A.x, tile[4].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 4) putimage(tile[4].A.x, tile[4].A.y, tileVazia, 0);
        if (tilesScaled == 5) putimage(tile[5].A.x, tile[5].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 5) putimage(tile[5].A.x, tile[5].A.y, tileVazia, 0);
        if (tilesScaled == 6) putimage(tile[6].A.x, tile[6].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 6) putimage(tile[6].A.x, tile[6].A.y, tileVazia, 0);
        if (tilesScaled == 7) putimage(tile[7].A.x, tile[7].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 7) putimage(tile[7].A.x, tile[7].A.y, tileVazia, 0);
        if (tilesScaled == 8) putimage(tile[8].A.x, tile[8].A.y, tileScale[timer1], 0);
        else if (tilesScaled > 8) putimage(tile[8].A.x, tile[8].A.y, tileVazia, 0);
        
        if (tilesScaled > 8) {
            if (timer1 == 4) timer1 = 0;
            partida();
        }
    }
    
    if (cena[3]) {
        
        if (timer3 <= 100) {
            
            if (timer4 < 3) {
                timer4++;
            }
            
            else timer4 = 0;
            
            if (quemGanhou == 0) putimage(0, 0, ganhou[timer4], 0);
            else if (quemGanhou == 1) putimage(0, 0, perdeu[timer4], 0);
            else if (quemGanhou == 2) putimage(0, 0, deuVelha[timer4], 0);
            
            timer3++;
        
        }
        
        else retornarAoMenu();
    }
}

//----------------
// COMECA O MAIN:
//----------------

int main() {
    
    pag = 1;
    quit = FALSE;
    winX = 600;
    winY = 600;
    timer1 = 0;
    timer2 = -282;
    timer3 = 600;
    timer4 = 100;
    waitToClick = 0;
    cena[0] = TRUE;
    pause = FALSE;
    liberaMouse = FALSE;
    escolhido = FALSE;
    tilesScaled = 0;
    yourTurn = FALSE;
    
    srand(time(NULL));
    
    initwindow(winX, winY, "Jogo da velha - Single Player", 340, 50);
    
    janela = GetForegroundWindow();
    
    continuar = makeCollider(174, 266, 256, 58);
    sair = makeCollider(174, 340, 256, 58);
    souXis = makeCollider(-221, 221, 221, 220);
    souBola = makeCollider(600, 220, 222, 220);
    
    for (i = 0; i < 3; i++) {
        tile[i] = makeCollider(i * 200, 0, 200, 200);
        tile[i].valor = ' ';
    }
    
    for (i = 3; i < 6; i++) {
        tile[i] = makeCollider((i - 3) * 200, 200, 200, 200);
        tile[i].valor = ' ';
    }
    
    for (i = 6; i < 9; i++) {
        tile[i] = makeCollider((i - 6) * 200, 400, 200, 200);
        tile[i].valor = ' ';
    }
    
    titleScreen = carregaImagem("img/title-screen.jpg", winX, winY);
    cleardevice();
    enter = carregaImagem("img/enter.jpg", 385, 32);
    cleardevice();
    pausa = carregaImagem("img/pausa.jpg", 330, 282);
    cleardevice();
    pausaContinuarHover = carregaImagem("img/pausa-continuar-hover.jpg", continuar.width, continuar.height);
    cleardevice();
    pausaSairHover = carregaImagem("img/pausa-sair-hover.jpg", sair.width, sair.height);
    cleardevice();
    chooseScreen = carregaImagem("img/choose-screen.jpg", winX, winY);
    cleardevice();
    chooseBola = carregaImagem("img/choose-bola.jpg", 222, 220);
    cleardevice();
    chooseXis = carregaImagem("img/choose-xis.jpg", 221, 220);
    cleardevice();
    escolha = carregaImagem("img/escolha.jpg", 376, 31);
    cleardevice();
    voceComeca = carregaImagem("img/voce.jpg", 433, 46);
    cleardevice();
    cpuComeca = carregaImagem("img/computador.jpg", 433, 46);
    cleardevice();
    spritesheet(tileScale, "img/200tile/200-tile0000.jpg", 5, 200, 200);
    cleardevice();
    tileBG = carregaImagem("img/bg-tile.jpg", 200, 200);
    cleardevice();
    tileVazia = carregaImagem("img/tile-vazia.jpg", 200, 200);
    cleardevice();
    tileHover = carregaImagem("img/tile-hover.jpg", 200, 200);
    cleardevice();
    tileX = carregaImagem("img/x-tile.jpg", 200, 200);
    cleardevice();
    tileO = carregaImagem("img/o-tile.jpg", 200, 200);
    cleardevice();
    spritesheet(ganhou, "img/ganhou/ganhou0000.jpg", 4, 600, 600);
    cleardevice();
    spritesheet(perdeu, "img/perdeu/perdeu0000.jpg", 4, 600, 600);
    cleardevice();
    spritesheet(deuVelha, "img/empate/empate0000.jpg", 4, 600, 600);
    cleardevice();
        
    while (quit != TRUE) {
        
        if (pag == 1) pag = 2; else pag = 1;
        setactivepage(pag);
        
        update();
        
        setvisualpage(pag);
        
        delay(17);
        fflush(stdin);
        
        if (kbhit()) {
            tecla = getch();
        }
    }
    
    free(titleScreen);
    free(enter);
    free(pausa);
    free(pausaContinuarHover);
    free(pausaSairHover);
    free(chooseScreen);    
    free(escolha);
    free(chooseXis);
    free(chooseBola);
    free(voceComeca);
    free(cpuComeca);
    
    closegraph();
    return 0;
}
