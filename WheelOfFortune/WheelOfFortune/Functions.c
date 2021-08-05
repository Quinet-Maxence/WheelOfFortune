#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include "Functions.h"

//==================		VARIABLES		==================

//==== Player names ====
Player player[20];
Player player2[20];
Player player3[20];
// ==== Here is the setup of players & their turn during the game, ====
// ==== "temporaire" is used when trying to guess the secret word  ====
int numberOfturn = 0;
int nombresJoueurs = 0;
char* temporaire[20];
int round = 0;
// ==== Secret word and pointer to player ====
char* result = NULL;
char* p = NULL;
// ==== Here is the secret word that players will see, it will be displayed ====
// ====		    using "*" char for remaining unfounded letters			   	====
char* hidderLetter = NULL;
char* phidder = NULL;
// ==== 
unsigned int start = 0;
int mystery = 0;
int stars = '*';
int space = ' ';
//==== Vowels ====
char vowels[] = { 'A', 'E', 'I', 'O', 'U', 'Y' };

//======== Emptying Buffer from '\n' Function ============

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

//=================== MENU ====================

void printMenu() {
	int choice = 5;
	while (1 <= choice <= 3)
	{

		// Multiple choices menu :
		printf("\t\t\t\t\t======= WHAT DO YOU WANT TO DO ? =======\n");
		printf("\t\t\t\t\t\t0 = Exit\n");
		printf("\t\t\t\t\t\t1 = Play\n");
		printf("\t\t\t\t\t\t2 = See the rules\n");

		scanf_s("%d", &choice);
		switch (choice)
		{
		case 0:
			// exit(0) close the application
			printf("Thank you for playing the games !");
			exit(0);
		case 1:
			Play();
		case 2:
			printRules();
		default:
			printf("Please, enter a valid number ( 1, 2 or 3 )\n");
			printMenu();
			break;
		}
	}

}
void printRules() {
	int choice;
	printf("\n============ WELCOME TO THE RULEBOOK ===========\n");
	printf("== IF YOU WANT TO COMEBACK IN MENU, PRESS '0' == \n");
	printf("To play, there must be 2 or 3 players, as well as a game Master who will choose the secret word !\n");
	printf("1) Your objective is to get as much money as you can by giving letters\n");
	printf("2) At every turn you must turn the wheel and let your luck decide how much money you can earn\n");
	printf("3) There are different amounts of money available in the weel ranging from 300$ to 900$ !\n");
	printf("4) You earn the sum of money from the wheel if you find a consonant of the secret word !\n");
	printf("5) If you find a letter, you are able to play again another one or trying to find the word\n");
	printf("6) Side note : If you want a vowel, you must buy it for a cost of 250$ !\n");
	printf("7) In the wheel, there is 3 'specials' cases : Bankrupt / Extra Turn / Lose a Turn\n ");
	printf("8) Bankrupt : You are not lucky, your money bank drops to 0, and you give up your turn :(\n");
	printf("9) Lose a Turn : You loose the ability to play your turn :(\n");
	printf("10) Extra Turn : Grant you with a joker card : It allows you when the game asks you, to play another turn. \n");
	printf("== That's All ! If you want to comeback in menu, press '0' ! ==\n");
	scanf_s("%d", &choice);
	if (choice == 0)
	{
		printMenu();

	}

}

//============== NBR OF PLAYERS ===============

int playerNumbers() {

	while (nombresJoueurs != 2 && nombresJoueurs != 3)
	{
		printf("\nHow many players are you ? 2 or 3 ? : \n");
		scanf_s("%d", &nombresJoueurs);
		viderBuffer();
	}

	if (nombresJoueurs == 2)
	{
		printf("Player 1, enter your name : \n");
		fgets(temporaire, BUFFER_SIZE, stdin);
		*player = (Player){ .bank = 0, .score = 0, .ExtraTurn = 0, .win = 0, .roundwin = 0, .name = _strdup(temporaire) };

		printf("Player 2, enter your name : \n");
		fgets(temporaire, BUFFER_SIZE, stdin);
		*player2 = (Player){ .bank = 0, .score = 0, .ExtraTurn = 0, .win = 0, .roundwin = 0, .name = _strdup(temporaire) };

		printf("\nPlayer 1 : %s\n", *player->name);
		printf("Player 2 : %s\n", *player2->name);

	}
	else
	{
		printf("Enter your name : \n");
		fgets(temporaire, BUFFER_SIZE, stdin);
		*player = (Player){ .bank = 0, .score = 0, .ExtraTurn = 0, .win = 0, .roundwin = 0, .name = _strdup(temporaire) };

		printf("Enter your name : \n");
		fgets(temporaire, BUFFER_SIZE, stdin);
		*player2 = (Player){ .bank = 0, .score = 0, .ExtraTurn = 0, .win = 0, .roundwin = 0, .name = _strdup(temporaire) };

		printf("Enter your name : \n");
		fgets(temporaire, BUFFER_SIZE, stdin);
		*player3 = (Player){ .bank = 0, .score = 0, .ExtraTurn = 0, .win = 0, .roundwin = 0, .name = _strdup(temporaire) };

		printf("Player 1 : %s\n", *player->name);
		printf("Player 2 : %s\n", *player2->name);
		printf("Player3 : %s \n", *player3->name);

	}
	return nombresJoueurs;
}

//=============== functions for wheel special cases ===============

void bankrupt(Player* player) {
	player->bank = 0;
}
// LoseATurn is only about passing a turn
void extraTurn(Player* player) {
	player->ExtraTurn++;
}

//=================== wheel possibilities ===================

void wheelResult(Player* p) {
	// we've added a loading time for "tension" purpose
	loadingTime();
	// Seed for the random number generator of the wheel
	srand(time(NULL));
	int random = rand() % 24 + 1;
	// Display of the secret word
	displayword();
	// Wheel result
	// as its the same for every cases only one comment is enough to explain its behavior.
	printf("%s, your turn [%d]\n", *p->name, p->bank);
	if (random <= 5) {
		printf("\nYou hit 300$ field\n");
		// "lirelettre" function will check if the letter played is in the secret word, if so, adding the sum in ones bank.
		lireLettre(p, 300);	
	}
	else if (random <= 7) {
		printf("\nYou hit 400$ field\n");
		lireLettre(p, 400);
	}
	else if (random <= 8) {
		printf("\nYou hit 450$ field\n");
		lireLettre(p, 450);
	}
	else if (random <= 11) {
		printf("\nYou hit 500$ field\n");
		lireLettre(p, 500);
	}
	else if (random <= 14) {
		printf("\nYou hit 600$ field\n");
		lireLettre(p, 600);
	}
	else if (random <= 16) {
		printf("\nYou hit 700$ field\n");
		lireLettre(p, 700);
	}
	else if (random <= 18) {
		printf("\nYou hit 800$ field\n");
		lireLettre(p, 800);
	}
	else if (random <= 20) {
		printf("\nYou hit 900$ field\n");
		lireLettre(p, 900);
	}
	else if (random <= 21) {
		printf("\n%s, you earn a ExtraTurn !\n", *p->name);
		extraTurn(p);
		wheelResult(p);
		numberOfturn--; // To balance out a bit this function
	}
	else if (random <= 23) {
		printf(" \n%s NOOOO, you fell into 'Bankrupt' !\n", *p->name);
		if (p->ExtraTurn > 0)
		{
			useExtraTurn(p);
			if (useExtraTurn(p) == 1)
			{
				p->ExtraTurn--;
				// Otherwise the next player will pass its turn
				numberOfturn--;
			}
			else
			{
				bankrupt(p);
			}
		}
		bankrupt(p);
	}
	else if (random <= 24)
	{
		printf("\n%s NOOOO, you fell into 'Lose a Turn'\n", *p->name);
		if (p->ExtraTurn > 0)
		{
			useExtraTurn(p);
			if (useExtraTurn(p) == 1)
			{
				p->ExtraTurn--;
			}
			else
			{
				// NOTHING
			}
			
		}
	}
	numberOfturn++;
}

int useExtraTurn(Player* p) {
	int choice = 0;
	while (choice != 1 && choice != 3)
	{
		printf("%s, do you want to use you extra Turn ? ( 1 = YES / 2 = NO )", p->name);
		scanf_s("%d", choice);
	}
	return choice;
}
// ====================== PLAY : First function which act as a player setup for the game to come ========================
void Play() {
	// Player creation
	playerNumbers();
	do
	{
		// Here is the secret word creation
		motmystere();
		// We are dispalying using stars char '*'
		displayword();
		//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n (We have hidden the mystery word)\n");
		clearSCR;
		if (nombresJoueurs == 2)
		{
			player->win = 0;
			player2->win = 0;
			// Modulo 2 is used as a variator to swap to one player to another at each turn.
			while (player->win == 0 && player2->win == 0)
			{


				switch (numberOfturn % 2)
				{
				case 1:
					wheelResult(player);
					break;
				case 0:
					wheelResult(player2);
				default:
					break;
				}
			}
			// Games stops if a player wins the game.
			if (player->win > 0)
			{
				printf("\n%s YOU WIN THIS ROUND!\n", *player->name);
				printf("\n%s, you earn : %d $ !\n\n\n ", *player->name, player->bank);
				printf("==============================================================================\n");
				player->roundwin++;
			}
			else if (player2->win > 0)
			{
				printf("\n%s YOU WIN THIS ROUND!\n", *player2->name);
				printf("\n%s, you earn : %d $ !\n\n\n ", *player2->name, player2->bank);
				printf("==============================================================================\n");
				player2->roundwin++;
			}
		}
		else if (nombresJoueurs == 3)
		{
			player->win = 0;
			player2->win = 0;
			player3->win = 0;
			while (player->win == 0 && player2->win == 0 && player3->win == 0)
			{
				// redefinition of the function for 3 player, we didn't use "n" number of player, but we could replace these 2 functions 
				// by only one that use an "n" number of player. Its easier like that.
				if (numberOfturn % 3 == 2)
				{
					wheelResult(player);
				}
				else if (numberOfturn % 3 == 1)
				{
					wheelResult(player2);
				}
				else
				{
					wheelResult(player3);
				}
				// Games stops if a player wins the game 
				if (player->win > 0)
				{
					printf("\n%s YOU WIN THIS ROUND!\n", *player->name);
					printf("\n%s, you earn : %d $ !\n\n\n ", *player->name, player->bank);
					printf("==============================================================================\n");
					player->roundwin++;
				}
				else if (player2->win > 0)
				{
					printf("\n%s YOU WIN THIS ROUND!\n", *player2->name);
					printf("\n%s, you earn : %d $ !\n\n\n ", *player2->name, player2->bank);
					printf("==============================================================================\n");
					player2->roundwin++;
				}
				else if (player3->win)
				{
					printf("\n%s YOU WIN THIS ROUND!\n", *player3->name);
					printf("\n%s, you earn : %d $ !\n\n\n ", *player3->name, player3->bank);
					printf("==============================================================================\n");
					player3->roundwin++;
				}
			}
		}
		free(result);
		round++;
	} while (round != 3);
	if (nombresJoueurs == 2)
	{
		if (player->roundwin > player2->roundwin)
		{
			printf("\nThe BIG winner is : %s ! \n You earn %d $ !\n", *player->name, player->bank);
		}
		else
		{
			printf("\nThe BIG winner is : %s ! \n You earn %d $ !\n", *player2->name, player2->bank);
		}
	}
	else
	{
		if (player->roundwin > player2->roundwin && player->roundwin > player3->roundwin)
		{
			printf("\nThe BIG winner is : %s ! \n You earn %d $ !\n", *player->name, player->bank);
		}
		else if (player2->roundwin > player->roundwin && player2->roundwin > player3->roundwin)
		{
			printf("\nThe BIG winner is : %s ! \n You earn %d $ !\n", *player2->name, player2->bank);
		}
		else if (player3->roundwin > player->roundwin && player3->roundwin > player2->roundwin)
		{
			printf("\nThe BIG winner is : %s ! \n You earn %d $ !\n", *player3->name, player3->bank);
		}
		else if (player3->roundwin == player2->roundwin == player->roundwin)
		{
			printf("\nUnbelievable ! There is equality ! No one won !\n");
		}
	}
}

//============== Loading time is defined here ==============

void loadingTime() {
	int i;
	printf("\n\t\tThe wheel spin\n");
	for (i = 0; i < 3; i++) {
		printf(".");
		Sleep(1000);
	}
	printf("\n");
}

//============== Secret word ( IL FAUDRA METTRE LE FREE A LA FIN DU JEUX )==============

void motmystere() {
	result = NULL;
	p = NULL;
	// === Secret word under its real format and with '*'
	hidderLetter = NULL;
	phidder = NULL;
	start = 0;
	mystery = 0;
	// creation of the secret word "hidderLetter" qui signifie la version cachée des lettres ( sous formes '*' )
	printf("The secret word must be entered by a game master for the game to begin, enter the secret word ? :\n");
	mystery = getchar();
	while (mystery != EOF && mystery != '\n') {
		start += 1;
		if (result == NULL) {
			result = malloc(start + 1);/* for the '\0' ending the string */
			hidderLetter = malloc(start + 1);
			if (result == NULL) return 1;
			if (hidderLetter == NULL) return 1;
		}
		else {
			p = realloc(result, start + 1);
			phidder = realloc(hidderLetter, start + 1);
			if (p == NULL) {
				if (result != NULL) {
					free(result);
				}
			}

			if (phidder == NULL)
			{
				if (hidderLetter != NULL) {
					free(hidderLetter);
				}
			}
			result = p;
			hidderLetter = phidder;
		}
		result[start - 1] = (char)mystery;
		hidderLetter[start - 1] = (char)stars;
		mystery = getchar();
	}

	result[start] = '\0';
	hidderLetter[start] = '\0';
	majuscule(result);

	/*Affichage du mot pour test
	for (int i = 0; i < strlen(result); i++)
	{

		printf("%c\n", result[i]);
	}*/

	// Il faudra évidemment mettre les free() à la fin du jeux Et non à la fin de cette fonction! 
	//free(result);
	//free(hidderLetter);
}

//Here is a function to put letters in CAPITAL LETTERS
void majuscule(char* chaine)
{
	int i = 0;
	for (i = 0; chaine[i] != '\0'; i++)
	{
		if (chaine[i] >= 'a' && chaine[i] <= 'z')
			chaine[i] -= 'a' - 'A';
	}
}

// Word display in the console
void displayword() {
	printf("\t\tSecret Word :");
	for (int i = 0; i < strlen(result); i++)
	{
		if (result[i] == space) {
			hidderLetter[i] = space;
		}
	}
	puts(hidderLetter);
}

//============== SCANNER LA LETTRE ===========================
/*int lireConsonne(Player* player)
{
	printf("Enter a consonnant : ");
	char caractere = 0;

	caractere = getchar(); // On lit le premier caractère
	caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

	// On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
	while (getchar() != '\n');

	int numberfounds = 0;// Le nombre de fois que la lettre est présente

	if (isVowel(caractere) == 1)
	{
		viderBuffer();
		lireConsonne(player);
	}
	for (int i = 0; i < strlen(result); i++)
	{
		if (result[i] == caractere) {
			hidderLetter[i] = caractere;
			numberfounds++;
		}
	}

	printf(" \nThe letter %c is present %d time(s) !\n", caractere, numberfounds);
	puts(hidderLetter);
	return numberfounds; // On retourne le premier caractère qu'on a lu
}*/
int isVowel(char c) {
	if (strchr(vowels, c) != NULL)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
int lireLettre(Player* joueur, int money)
{
	// Letter scanning
	printf("Enter a consonnant or buy a vowel (250$) :");
	char caractere = 0;

	caractere = getchar(); // reading of the letter from the keyboard input stream
	caractere = toupper(caractere); // letters to Uppercase letters using a already defined function,
	//it was a test tu see if this function would work, but otherwise we use our function called "majuscule"

	// read every character to empty the buffer until \n
	while (getchar() != '\n');

	int numberfounds = 0;

	// If its a vowel, we need to check player's bank
	if (isVowel(caractere) == 1)
	{
		// If not enough money, the player can redo its choice
		if (joueur->bank < 250)
		{
			printf("\nYou do not have enough money\n");
			caractere = 0;
			lireLettre(joueur, money);
		}
		// Otherwise vowel is bought
		else {
			joueur->bank -= 250;

			for (int i = 0; i < strlen(result); i++)
			{
				if (result[i] == caractere) {
					hidderLetter[i] = caractere;
					numberfounds++;
				}
			}
			// If the letter isn't part of the secret word, the following message is printed :
			if (numberfounds == 0)
			{
				printf("\n%c is not present in the mysterious word ! ", caractere);
			}
			//if the played letter is contained in the mysterious word, the game is updated and its asking the player if he wants to try to find the Secret word.
			else {
				displayword;
				printf(" \nThe letter %c is present %d time(s) !\n", caractere, numberfounds);

				int wordattempt;
				printf("Do you want to guess the Word ? [ 1 = YES / 2 = NO ]\n");
				scanf_s("%d", &wordattempt);
				if (wordattempt == 1)
				{
					viderBuffer();
					int wordguess = 0;
					wordguess = wordcompare(joueur);
					if (wordguess == 1)
					{
						joueur->win++;
					}
					else;
					// If he dont want to try a guess, he still plays because he has previously found a letter.
				}
				else {
					viderBuffer();
					printf("\nOK , let s continue !\n");
				}
				
				numberOfturn--; // In order to give another turn to the one who find a letter
				joueur->bank += money * numberfounds; // This line assure that the player gets his money before playing again
				wheelResult(joueur);
			}
			return numberfounds;
			puts(hidderLetter);
		}
	}
	// else we look for the consonant 
	else {

		for (int i = 0; i < strlen(result); i++)
		{
			if (result[i] == caractere) {
				hidderLetter[i] = caractere;
				numberfounds++;
			}
		}
		if (numberfounds == 0)
		{
			printf("\nThere is no %c in the Secret word unfortunately ! ", caractere);
		}
		else {
			printf(" \nThe letter %c is present %d time(s) !\n", caractere, numberfounds);
			int wordattempt;
			printf("Do you want to guess the mysterious word ? [ 1 = YES / 2 = NO ]\n");
			scanf_s("%d", &wordattempt);
			if (wordattempt == 1)
			{
				viderBuffer();
				int wordguess = 0;
				wordguess = wordcompare(joueur);
				if (wordguess == 1)
				{
					joueur->win++;
				}
				else;
			}
			else {
				viderBuffer();
				printf("\nOK , let s continue !\n");
			}
			
			numberOfturn--; 
			joueur->bank += money * numberfounds;
			wheelResult(joueur);
		}
		return numberfounds;
	}
	puts(hidderLetter);
}
// ============== Scanning the guess & comparing it to the secret word ==================

int wordcompare(Player* joueur) {
	char* guessedWord = NULL;
	char* pguess = NULL;
	int guess;
	unsigned int startguess = 0;
	printf("\n Enter your guess : ");
	guess = getchar();
	while (guess != EOF && guess != '\n') {
		startguess += 1;
		if (guessedWord == NULL) {
			guessedWord = malloc(start + 1);
			if (guessedWord == NULL) return 1;
		}
		else {
			pguess = realloc(guessedWord, startguess);
			if (pguess == NULL) {
				if (guessedWord != NULL) {
					free(guessedWord);
				}
			}
			guessedWord = pguess;
		}
		guessedWord[startguess - 1] = (char)guess;
		guess = getchar();
	}

	guessedWord[startguess] = '\0';
	majuscule(guessedWord);

	// This is the final comparison
	if (strcmp(result, guessedWord) == 0) {
		printf(" True :D !\n");
		//puts(guessedWord);
		return 1; // == True 
	}
	else {
		printf("False :( !\n");
		//puts(guessedWord);
		return 0; // == False
	}
	free(guessedWord);
}
