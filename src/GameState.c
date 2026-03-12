#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // pour srand() et time()

// ANSI Background Colors
#define RESET "\033[0m"      // couleur par défaut
#define BGC_RED     "\033[41m"
#define BGC_GREEN   "\033[42m"
#define BGC_YELLOW  "\033[43m"
#define BGC_BLUE    "\033[44m"
#define BGC_MAGENTA "\033[45m"
#define BGC_CYAN    "\033[46m"
#define BGC_WHITE   "\033[47m"
#define BGC_P1      "\033[40m" // Noir Joueur 1
#define BGC_P2      "\033[100m" // Gris Joueur 2

GameState state = {.map = NULL, .size = 0};

void create_empty_game_state (GameState* state, int size){
    state->size = size;
    // tableau 1D
    state->map = (Color*)malloc(size * size * sizeof(Color));
    if (state->map == NULL) {
        printf("[ERROR] Allocation memoire echouee\n");
        exit(1);
    }
}


void set_map_value (GameState* state, int x, int y, Color value){
    // case (x, y)
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
void fill_state(GameState* state){ 
    srand(time(NULL)); // initialise le hasard

    for (int y = 0; y < state->size; y++) {
        for (int x = 0; x < state->size; x++) {
            // une couleur aléatoire entre RED 4 et WHITE 10
            Color random_color = (rand() % 7) + RED;
            set_map_value(state, x, y, random_color);
        }
    }

    // Placement des joueurs
    set_map_value(state, 0, state->size - 1, PLAYER_1);
    set_map_value(state, state->size - 1, 0, PLAYER_2);
}

// Question 2 : Fonction d'affichage avec des lettres 
void GR11_afficher(GameState* state) {
    printf("\n---------------------\n");
    for (int y = 0; y < state->size; y++) {
        for (int x = 0; x < state->size; x++) {
            Color c = get_map_value(state, x, y);
            
            if (c == PLAYER_1) {
                printf("1 "); // Joueur 1 
            } else if (c == PLAYER_2) {
                printf("2 "); // Joueur 2
            } else {
                // Les couleurs vont de RED 0 à WHITE 6
                // 'A' + 1 = 'B'
                printf("%c ", 'A' + (c - RED)); 
            }
        }
        printf("\n");
    }
    printf("----------------------\n");
}

// Bonus : Affichage graphique en couleurs 
void GR11_afficher_bonus(GameState* state) {
    printf("\n----------------------\n\n");

    for (int y = 0; y < state->size; y++) {
        for (int x = 0; x < state->size; x++) {
            Color c = get_map_value(state, x, y);
            
            // Change la couleur du fond
            if (c == RED) {
                printf(BGC_RED "  " RESET);
            } else if (c == GREEN) {
                printf(BGC_GREEN "  " RESET);
            } else if (c == BLUE) {
                printf(BGC_BLUE "  " RESET);
            } else if (c == YELLOW) {
                printf(BGC_YELLOW "  " RESET);
            } else if (c == MAGENTA) {
                printf(BGC_MAGENTA "  " RESET);
            } else if (c == CYAN) {
                printf(BGC_CYAN "  " RESET);
            } else if (c == WHITE) {
                printf(BGC_WHITE "  " RESET);
            } else if (c == PLAYER_1) {
                printf(BGC_P1 "1 " RESET); // joueur 1
            } else if (c == PLAYER_2) {
                printf(BGC_P2 "2 " RESET); // joueur 2
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n----------------------\n");
}

// Question 3 : Mise à jour du monde
void GRX_jouer_coup(GameState* state, Color joueur, Color couleur_choisie) {
    int modification = 1; // pour savoir si on a conquis au moins une case
 
    while (modification == 1) {
        modification = 0;
        // parcours linéairement 
        for (int y = 0; y < state->size; y++) {
            for (int x = 0; x < state->size; x++) {
                
                // si couleur donner par le joueur 
                if (get_map_value(state, x, y) == couleur_choisie) {
                    
                    // on vérifie les cases adjacente 
                    if (get_map_value(state, x + 1, y) == joueur ||
                        get_map_value(state, x - 1, y) == joueur ||
                        get_map_value(state, x, y + 1) == joueur ||
                        get_map_value(state, x, y - 1) == joueur) {
                         
                        set_map_value(state, x, y, joueur);
                        
                        modification = 1;
                    }
                }
            }
        }
    }  
}

int main(int argc, char** argv){
    // Convertit texte en entier
    int size = atoi(argv[1]);

    // initialise variable globale 'state'
    create_empty_game_state(&state, size);
    fill_state(&state);

    //On appelle la fonction d'affichage
    //GR11_afficher(&state);
    GR11_afficher_bonus(&state);

    // libère la mémoire à la fin
    free(state.map);
    return 0;
}

