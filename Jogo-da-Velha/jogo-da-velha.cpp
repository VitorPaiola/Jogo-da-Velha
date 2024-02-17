#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale.h>
#include <cstdlib>

using namespace std;

// �rea de defini��o de cabe�alho de fun��o
void menuInicial();

static void limpaTela() {
	system("CLS");
}

static void iniciaTabuleiro(char tabuleiro[3][3]) {

	// Navega por cada posi��o do tabuleiro e coloca o s�mbolo de '-'
	int linha, coluna;
	for (linha = 0; linha < 3; linha++) {
		for (coluna = 0; coluna < 3; coluna++) {
			tabuleiro[linha][coluna] = '-';
		}
	}

}

static void exibeTabuleiro(char tabuleiro[3][3]) {

	// Exibe o tabuleiro com suas linhas e colunas quebrando a linha ao sair de um for
	int linha, coluna;
	cout << "\n";
	for (linha = 0; linha < 3; linha++) {
		for (coluna = 0; coluna < 3; coluna++) {
			cout << tabuleiro[linha][coluna];
		}
		cout << "\n";
	}

}

// 1 = X venceu, 2 = O venceu, 0 = nada aconteceu
static int confereTabuleiro(char tabuleiro[3][3]) {

	int linha, coluna;

	// Confere linhas
	for (linha = 0; linha < 3; linha++) {
		if (tabuleiro[linha][0] == 'X' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
			return 1;
		} else if (tabuleiro[linha][0] == 'O' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
			return 2;
		}
	}

	// Confere colunas
	for (coluna = 0; coluna < 3; coluna++) {
		if (tabuleiro[0][coluna] == 'X' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
			return 1;
		} else if (tabuleiro[0][coluna] == 'O' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
			return 2;
		}
	}

	// Diagonal Principal
	if (tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
		if (tabuleiro[0][0] == 'X') {
			return 1;
		} else {
			return 2;
		}
	}

	// Diagonal Secund�ria
	if (tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
		if (tabuleiro[0][2] == 'X') {
			return 1;
		} else {
			return 2;
		}
	}

	return 0;
}

static void exibeInstrucoes() {

	cout << "\nMapa de posi��es:";
	cout << "\n 7 | 8 | 9";
	cout << "\n 4 | 5 | 6";
	cout << "\n 1 | 2 | 3";

}

static void jogo(string nomeDoJogadorUm, string nomeDoJogadorDois, int pontuacaoJogadorUm, int pontuacaoJogadorDois) {

	/// Vari�veis Gerais
	string nomeDoJogadorAtual;													// Nome dos jogadores
	char tabuleiro[3][3];														// Tabuleiro do Jogo
	int linha, coluna;															// Auxiliares para tabuleiro
	int linhaJogada, colunaJogada, posicaoJogada;								// Posi��o em que o jogador posiciona sua marca
	int estadoDeJogo = 1;														// 0 = Sem jogo, 1 = Em jogo
	int turnoDoJogador = 1;														// 1 = X, 2 = O
	int rodada = 0;																// Quantas vezes os jogadores jogaram no total
	int opcao;																	// Op��o de reinicio
	bool posicionouJogada;														// Verifica se o jogador colocou um marcador no tabuleiro

	// Coloca os '-' no tabuleiro para indicar o vazio
	iniciaTabuleiro(tabuleiro);

	while (rodada < 9 && estadoDeJogo == 1) {

		limpaTela();

		cout << "\nRodada: " << rodada << "\n";
		cout << "Pontua��o: " << nomeDoJogadorUm << " " << pontuacaoJogadorUm << " x " << pontuacaoJogadorDois << " " << nomeDoJogadorDois;

		// Exibe o tabuleiro na tela
		exibeTabuleiro(tabuleiro);

		// Exibe qual n�mero corresponde a qual posi��o
		exibeInstrucoes();

		// Atualiza o nome do jogador atual
		if (turnoDoJogador == 1) {
			nomeDoJogadorAtual = nomeDoJogadorUm;
		} else {
			nomeDoJogadorAtual = nomeDoJogadorDois;
		}

		posicionouJogada = false;

		// Matriz de posi��es poss�veis
		int posicoes[9][2] = { {2,0}, {2,1}, {2,2}, {1,0}, {1,1}, {1,2}, {0,0}, {0,1}, {0,2} };

		while (posicionouJogada == false) {

			// L� a jogada
			cout << "\n\n" << nomeDoJogadorAtual << " digite uma posi��o conforme o mapa acima: ";
			cin >> posicaoJogada;

			// Passa a linha e coluna de acordo com a matriz de posi��es exibidas no mapa
			linhaJogada = posicoes[posicaoJogada-1][0];
			colunaJogada = posicoes[posicaoJogada-1][1];

			// Verifica se a posi��o � vazia
			if (tabuleiro[linhaJogada][colunaJogada] == '-') {

				// Conseguiu posicionar um marcador
				posicionouJogada = true;

				// Verifica de quem � a vez para posicionar o marcador
				if (turnoDoJogador == 1) {
					tabuleiro[linhaJogada][colunaJogada] = 'X';

					turnoDoJogador = 2;

				}
				else {
					tabuleiro[linhaJogada][colunaJogada] = 'O';

					turnoDoJogador = 1;

				}
			}
		}

		// Confere se o jogo acabou
		if (confereTabuleiro(tabuleiro) == 1) {
			cout << "\nO jogador X venceu \n";
			pontuacaoJogadorUm++;
			estadoDeJogo = 0;
		} else if (confereTabuleiro(tabuleiro) == 2) {
			cout << "\nO jogador O venceu \n";
			pontuacaoJogadorDois++;
			estadoDeJogo = 0;
		}

		// Aumenta uma rodada
		rodada++;

	}

	//exibeTabuleiro(tabuleiro);
	cout << "\nFim de jogo\n";
	cout << "O que deseja fazer?";
	cout << "\n1 - Continuar Jogando";
	cout << "\n2 - Menu Inicial";
	cout << "\n3 - Sair\n";
	cin >> opcao;
	if (opcao == 1) {
		jogo(nomeDoJogadorUm, nomeDoJogadorDois, pontuacaoJogadorUm, pontuacaoJogadorDois);
	} else if (opcao == 2) {
		menuInicial();
	}
}

static void menuInicial() {

	// Op��o escolhida pelo usu�rio
	int opcao = 0;

	// Nome dos jogadores
	string nomeDoJogadorUm, nomeDoJogadorDois;

	// Enquanto o jogador n�o digita uma op��o valida, mostra o menu novamente
	while (opcao < 1 || opcao > 3) {

		limpaTela();

		cout << "Bem-vindo ao Jogo da Velha";
		cout << "\n1 - Jogar";
		cout << "\n2 - Sobre";
		cout << "\n3 - Sair";
		cout << "\nEscolha uma op��o e pressione ENTER: ";
		cin >> opcao;

		// Faz algo de acordo com a op��o escolhida
		switch (opcao) {
		case 1:
			cout << "Digite o nome do jogador 1: ";
			cin >> nomeDoJogadorUm;
			cout << "Digite o nome do jogador 2: ";
			cin >> nomeDoJogadorDois;
			jogo(nomeDoJogadorUm, nomeDoJogadorDois, 0, 0);
			break;
		case 2:
			// Mostra informa��es do jogo
			cout << "Informa��es do jogo";
			break;
		case 3:
			cout << "At� mais!";
			break;
		}

	}

}

int main() {
	setlocale(LC_ALL, "");

	menuInicial();

	return 0;
}