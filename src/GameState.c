#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Requis pour srand() et time()

// Codes ANSI pour modifier la couleur de fond (Background Colors)
#define RESET "\033[0m"      // Remet la couleur par défaut
#define BGC_RED     "\033[41m"
#define BGC_GREEN   "\033[42m"
#define BGC_YELLOW  "\033[43m"
#define BGC_BLUE    "\033[44m"
#define BGC_MAGENTA "\033[45m"
#define BGC_CYAN    "\033[46m"
#define BGC_WHITE   "\033[47m"
#define BGC_P1      "\033[100m" // Gris foncé pour le Joueur 1
#define BGC_P2      "\033[107m" // Blanc brillant pour le Joueur 2

GameState state = {.map = NULL, .size = 0};

void create_empty_game_state (GameState* state, int size){
    state->size = size;
    // La carte est un tableau 1D utilisé comme un tableau 2D
    state->map = (Color*)malloc(size * size * sizeof(Color));
    if (state->map == NULL) {
        printf("[ERROR] Allocation memoire echouee\n");
        exit(1);
    }
}


void set_map_value (GameState* state, int x, int y, Color value){

    // Formule pour accéder à la case (x, y) dans un tableau 1D
    state->map[y * state->size + x] = value;
    
}

Color get_map_value (GameState* state, int x, int y){
	if (state -> map == NULL || x > state -> size || y > state -> size || x < 0 || y < 0)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", state -> map, state -> size, x, y);
		return ERROR;
	}
	return state -> map[y * state -> size + x];
}
void fill_map(GameState* state){ // J'ai renommé 'map' en 'state' pour que ce soit logique
    srand(time(NULL)); // Initialise le hasard

    for (int y = 0; y < state->size; y++) {
        for (int x = 0; x < state->size; x++) {
            // Choix aléatoire d'une couleur entre RED (4) et WHITE (10)
            Color random_color = (rand() % 7) + RED;
            set_map_value(state, x, y, random_color);
        }
    }

    // Placement des joueurs selon les règles
    set_map_value(state, 0, state->size - 1, PLAYER_1); // Player1: x=0, y=size-1
    set_map_value(state, state->size - 1, 0, PLAYER_2); // Player2: x=size-1, y=0
}

// Question 2 : Fonction d'affichage avec des lettres 
void GR11_afficher(GameState* state) {
    printf("\n--- ETAT DU TERRITOIRE ---\n");
    for (int y = 0; y < state->size; y++) {
        for (int x = 0; x < state->size; x++) {
            Color c = get_map_value(state, x, y);
            
            if (c == PLAYER_1) {
                printf("1 "); // Joueur 1 [cite: 149]
            } else if (c == PLAYER_2) {
                printf("2 "); // Joueur 2 [cite: 149]
            } else {
                // Les couleurs vont de RED (0 dans notre décalage) à WHITE (6)
                // 'A' + 0 = 'A', 'A' + 1 = 'B', etc.
                printf("%c ", 'A' + (c - RED)); 
            }
        }
        printf("\n"); // Retour à la ligne à la fin de chaque ligne de la grille
    }
    printf("--------------------------\n");
}

// Bonus : Affichage graphique en couleurs 
void GR11_afficher_bonus(GameState* state) {
    printf("\n--- ETAT DU TERRITOIRE ---\n\n");

    for (int y = 0; y < state->size; y++) {
        printf("  "); // Petite marge à gauche pour faire joli
        for (int x = 0; x < state->size; x++) {
            Color c = get_map_value(state, x, y);
            
            // Selon la couleur de la case, on change le fond et on dessine un bloc
            switch(c) {
                case RED:     printf(BGC_RED     "  " RESET); break;
                case GREEN:   printf(BGC_GREEN   "  " RESET); break;
                case BLUE:    printf(BGC_BLUE    "  " RESET); break;
                case YELLOW:  printf(BGC_YELLOW  "  " RESET); break;
                case MAGENTA: printf(BGC_MAGENTA "  " RESET); break;
                case CYAN:    printf(BGC_CYAN    "  " RESET); break;
                case WHITE:   printf(BGC_WHITE   "  " RESET); break;
                case PLAYER_1: printf(BGC_P1     "1 " RESET); break; // On écrit 1  pour voir le joueur 1
                case PLAYER_2: printf(BGC_P2     "2 " RESET); break; // On écrit 2  pour le joueur 2
                default:      printf("  ");
            }
        }
        printf("\n"); // Retour à la ligne à la fin de chaque ligne de la grille
    }
    printf("\n--------------------------\n");
}

int main(int argc, char** argv){
    // Convertit l'argument texte en entier
    int size = atoi(argv[1]);

    // On initialise notre variable globale 'state'
    create_empty_game_state(&state, size);
    fill_map(&state);

    //On appelle la fonction d'affichage
    //GR11_afficher(&state);
    GR11_afficher_bonus(&state);

    // On libère la mémoire à la fin
    free(state.map);
    return 0;
}

