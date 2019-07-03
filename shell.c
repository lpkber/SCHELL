#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#include <locale.h>
  
/* limpa a tela */
#define CLEAR() printf("\033[H\033[J")

void diretorio() {
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); // Pega o caminho do diretorio atual
	printf("\nDiretório atual: %s\n", cwd); 
}

int linha(char* comando) {
	char* linha, *usuario;

    diretorio();
	linha = readline("Digite seu comando: "); // Digita a linha e recebe o que foi digitado
    add_history(linha); // Adiciona no histório, para q se possa apertar na seta para cima e ver o que já foi digitado
    strcpy(comando, linha); // Salva o que foi digitado na variável comando (passada por ponteiro)
}

void formataComando(char* comando, char** comandoFormatado) {
	int i;

	for (i = 0; i < 100; i++) { 
		comandoFormatado[i] = strsep(&comando, " "); // Separa todas as palavras

		if (comandoFormatado[i] == NULL)
			break;
		if (strlen(comandoFormatado[i]) == 0)
			i--;
	}
}

void help() {
	printf("\nLista de comandos:"
		"\n- hello: diga algo"
		"\n- cd: muda de pasta"
		"\n- exit: sai do programa"
		"\n\n");
}

void procuraComando(char** comando) {
    if(strcmp(comando[0], "exit") == 0) { // Compara o que foi digitado com "exit"
        printf("\nAté mais\n"); 
		exit(0);
    }
    else if(strcmp(comando[0], "help") == 0) { // Compara o que foi digitado com "help"
        help();
    }
    else if(strcmp(comando[0], "hello") == 0) { // Compara o que foi digitado com "hello"
		char* user;
        user = getenv("USER");
        printf("\nEae %s, tudo bem?\n", user); 
	}
	else if(strcmp(comando[0], "cd") == 0) { // Compara o que foi digitado com "cd"
		chdir(comando[1]);
	}
    else { // Se o comando não exite na nossa shell, tenta execular pelo linux
        system(comando[0]);
    }
} 

int leComando(char* comando, char** comandoFormatado) { 
	formataComando(comando, comandoFormatado); // Separa todas as palavras digitadas
	procuraComando(comandoFormatado); // Procura o comando digitado
}

int main() {
	char comando[100], *comandoFormatado[100];

    CLEAR();
    printf("\nBem vindo!\n\n");

	while(1) { // Loop infinito
        linha(comando); // Mostra a linha
		leComando(comando, comandoFormatado); // Recebe o comando
	}
} 
