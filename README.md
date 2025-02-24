# Projet Pong Multijoueur C++

###### Auters: Dounia Bakalem, Yanis Sadoun, Vasileios Filippos Skarleas

## Versions

* V4.2.2 Saving the demi correct viwes
* V4.2.3 The views logic has been completed
* V5.0.1: Added lamda functions on the paddle.cpp. The reason why we do this is found on the paddle.cpp file and added mutliple notixes support
* V5.1.1: Functors added for the differet ball shaped renders on the renderers.cpp file (it includes also the explication why we use functors [purposes])
* V5.1.2: Added getter and setter for the notices (it will be needed on the game's main logic to showcase the correct notices) + on Makefile added the mode_menu implementation
* V5.1.3: Prepared notices so that we can return back to the mode menu
* V5.1.4: Added logic for showng the paude button or not on the game
* V6.0.1: We added the change views functionality succefully
* V6.1.0: Added updates pages structures and logic for correct AI and balls selection to their respective modes
* V6.1.1: Changes GameState to game_sate for normalisation reasons
* V6.1.2: Renamed files according to teh pages structure below for clarity reasons. The classes on those files has not been updated yet
* V6.1.3: Updates class names according to the pages structures below and AI logic has been implemented. Needs to be added on the game's global logic
* V7.0.1: Added the AI on the global game's logic
* V7.1.2: Added game over page and Cmake structure. Changed some function names on the game.cpp and we added an automatic installer and handler of packages.
* V8.1.0: Added user class, started network codebase, added special effects support for game's actions and buttons click actions, updated saving state to include players names and updated the game's logic to support the definition of the player's names.
* V8.1.1: Added support for showing player's names when we play
* V9.0.1: Added high score functionality on two players mode. The game now ends when the users ask for it, so this is what makes a high score. Also added support to add user names on SDL interface
* V9.1.0: Updated the gui.cpp for better results and cohesion

## Pages structures

This game comes with some specific predefined page structures that we use in order to render different content dynamicly or not (depending the extensive usage on the program). Here are the specifications for those files:

- page_3b_1t : There are three buttons on the center and one title in bold on top (previous middle_menu)
- page_2b_1t : There are two buttons and one grand part for long text (previous notices)
- page_4b_1t: There four buttons and 1 title in bold (previous mode_menu)
- page_3b_0t: There are three buttons, the two on top of the page and the third one close to the end (previous menu)
- page_3b : There are 3 buttons, all of them centered in the middle of the screen (previous pause menu)

## TO-DO list

* [X] Find a way to prpose an initial SDL window that show cases the instructionsof the game. Then when teh user taps on a button "Let's go", then this SDL windows closes and a new one Appears where a user chooses between the modes of the game that exist. The "Simple" one which is the current version of the game, the "Storytime" one where is the game without the saving functionality, but with the user class and the hisgh score board, and the third one which is "Hardcore" which is the same with the "Storytime" but now there is a single user that plays against an AI on the opposite Paddle. There is also the exit game button that terminates the game. When a mode is slected this SDL window closes and we are presented with the menu window of the different game modes. (definitely there are modification son the main.cpp for this functionaity to take place)
* [X] Add a message when the game is saved succesfully
* [X] Create a user class and use this to attribute the scores
* [X] Remove the end of game logic when score is greater than 10 for a user. Instead use the logic of the two previous points (not actually remove, but instead develop the new game mode like game_storytime.cpp). This new mode comes with its new menu_storytime.cpp that doesn't include the continue game functionality (as expected) but there is button that allows to see the high scores table (it opens on a new SDL window). The exit game button is transfored to exit mode button allowing to go back to the SDL window where we can choose the game mode.
* [X] Have a high scores table where if any time in the future a user has a score greater than the last maximum one, then he is added on top of the Leaderboard. The leaderboard is a file that is always present on the directory of the game and it is also encrypted.
* [X] Add the AI player

## Usage of the CMake

### First time setup

mkdir build
cd build
cmake ..
cmake --build .

### For subsequent code changes, just run

cmake --build .

## Guide de Démarrage

### Prérequis

```bash
# macOS avec Homebrew
brew install sdl2 sdl2_mixer sdl2_ttf sdl2_image

# Ubuntu/Debian
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev

```

## Compilation

Pour compiler le codebase du jeu, vous pouvez tout simplement sur le repertoire build une fois que vous avez installé les Prérequis. Il faut suivre les instructions suivantes:

1. `cd build`
2. `cmake ..`
3. `cmake --build .`

Donc, pour lancer le jeu il suffit de faire `./Pong`

For your convinience, we are including on the codebase a launch file that will automaticly process everything for you. You simply need to do make sure that this file has the right to execute on your computer. This installer will make sure that you have all the dependencies installed and it will prepare all the executables for you.

1. `chmod 777 play.sh`
2. `bash play.sh`

## Dépendances et Structure

### Structure des Includes

```
game.cpp
├── game.hpp
├── ClassicBall.hpp
├── SquareBall.hpp
├── TriangleBall.hpp
├── GameStateHandler.hpp
└── SDL headers (SDL.h, SDL_mixer.h, SDL_ttf.h)


ball_base.cpp (classes dérivées)
├── BallBase.hpp
├── paddle.hpp
└── SDL headers

paddle.cpp
├── paddle.hpp
└── SDL headers
```

## Sécurité et Sauvegarde de l'état du jeu

### Chiffrement des Données

La sauvegarde des données utilise un système de chiffrement XOR simple avec une clé rotative :

```cpp
class SavingEncryption {
private:
    static const std::vector<uint8_t> KEY;
  
    static void encryptData(std::vector<uint8_t>& data) {
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] ^= KEY[i % KEY.size()];
        }
    }
};
```

Les données sont chiffrées avant l'écriture sur le disque et déchiffrées lors de la lecture, assurant une protection basique des sauvegardes.

## Système Audio et Graphique

### Gestion Audio avec SDL_mixer

Le jeu utilise SDL_mixer pour gérer différents effets sonores :

- Collision balle-raquette
- Points marqués
- Musique de fond

```cpp
Mix_Chunk* mPaddleHitSound;
Mix_Music* mBackgroundMusic;
```

### Système de Couleurs Dynamique

Les couleurs évoluent en fonction du score :

- Score > 3 : Bleu (Début de progression)
- Score > 5 : Rouge (Progression intermédiaire)
- Score > 7 : Vert (Proche de la victoire)
- Score Max : 10 points

## Modes de Jeu

1. Mode Classique

Score maximum : 10 points
Changements de couleur aux scores 3, 5 et 7
Sauvegarde automatique
Mode Sans Limite (à venir)

2. Pas de score maximum
   Table des meilleurs scores
   Sauvegarde des records
   Mode IA (à venir)
3. Intelligence artificielle pour joueur 2
   Plusieurs niveaux de difficulté

## Améliorations Futures

### Instructions du Jeu

Implémentation prévue d'un écran d'instructions au démarrage :

```cpp
class GameInstructions {
public:
    void Display();
    bool HandleInput();
private:
    std::vector<std::string> mInstructions;
};
```

### Système de Noms d'Utilisateur

Ajout d'une interface de saisie des noms :

```cpp
class PlayerManager {
public:
    void RequestUsernames();
    std::string GetPlayer1Name();
    std::string GetPlayer2Name();
private:
    std::string mPlayer1Name;
    std::string mPlayer2Name;
};
```

### Mode High Score

Nouveau mode de jeu sans limite de points :

```cpp
class HighScoreManager {
public:
    void AddScore(const std::string& player, int score);
    std::vector<std::pair<std::string, int>> GetTopScores(int limit = 10);
private:
    std::vector<std::pair<std::string, int>> mHighScores;
};
```

## L'algorithme de l'IA

L'algorithme de l'IA pour le joueur 2 utilisera une approche prédictive :

```cpp
class AIPlayer {
public:
    float DecideMovement(const Ball* ball, const Paddle* paddle) {
        // Prédiction de la position future de la balle
        float predictedY = Predictball_y(ball);
        float currentY = paddle->get_pos_y();
  
        // Décision de mouvement avec une marge d'erreur pour simulation humaine
        return (predictedY > currentY + ERROR_MARGIN) ? 1.0f : 
               (predictedY < currentY - ERROR_MARGIN) ? -1.0f : 0.0f;
    }
private:
    const float ERROR_MARGIN = 10.0f;
    float Predictball_y(const Ball* ball);
};
```

## L'utilisation des Lambda Functions

Les lambda functions sont utilisées pour plusieurs raisons :

- Callbacks d'événements menu
- Validation des entrées
- Menu callbacks

Voici queques implementations pour ceux cas spécifiques:

1. Gestionnaire d'Événements
   auto handleCollision = [this](const Ball* ball, const Paddle* paddle) -> bool {
   return CheckCollision(ball->GetBounds(), paddle->GetBounds());
   };
2. Validation des Entrées
   auto validateScore = [](int score) -> bool {
   return score >= 0 && score <= 10;
   };
3. Callbacks du Menu
   mMenu->SetStartCallback(this {
   mGameState = game_state::Playing;
   resetGame();
   });

Les lambda functions permettent une syntaxe plus claire pour les callbacks et une maintenance simplifiée. En plus, l'utilisation des lambda functions est particulièrement pertinente pour le mode IA où elles permettent de définir différentes stratégies de jeu de manière concise et modulaire.
