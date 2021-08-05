#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define BUFFER_SIZE 50

// definition of the clear screen function
#ifdef _WIN32
#define clearSCR system("cls");
#else
#define clearSCR system("clear");
#endif

typedef struct Player Player;

struct Player {
	char* name[20];
	int bank;
	int score;
	int ExtraTurn;
	int win;
	int roundwin;
};
//================================================
void motmystere();
void majuscule(char* chaine);
void displayword();
int wordcompare(Player* player);
//int lireConsonne(Player* player);
int lireLettre(Player* player, int money);
int isVowel(char c);
void printRules();
int playerNumbers();
void printMenu();
void bankrupt(Player* player);
void extraTurn(Player* player);
int useExtraTurn(Player* player);
void wheelResult(Player* player);
void Play();
void loadingTime();
#endif