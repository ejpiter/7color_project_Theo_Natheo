#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Requis pour srand() et time()

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

int main(int argc, char** argv){
    // Convertit l'argument texte en entier
    int size = atoi(argv[1]);

    // On initialise notre variable globale 'state'
    create_empty_game_state(&state, size);
    fill_map(&state);

    //On appelle la fonction d'affichage
    GR11_afficher(&state);

    // On libère la mémoire à la fin
    free(state.map);
    return 0;
}

