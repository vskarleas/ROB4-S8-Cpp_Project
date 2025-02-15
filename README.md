# Projet Pong Multijoueur C++

## Guide de Démarrage

### Prérequis

```bash
# macOS avec Homebrew
brew install sdl2 sdl2_mixer sdl2_ttf sdl2_image

# Ubuntu/Debian
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev

# Windows avec MSYS2
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image
```

### Compilation et Lancement

```bash
make clean      # Nettoie les fichiers compilés
make           # Compile le projet
make run       # Lance le jeu
```

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

menu.cpp
├── menu.hpp
├── game_save.hpp
└── SDL headers

ball.cpp (classes dérivées)
├── BallBase.hpp
├── paddle.hpp
└── SDL headers

paddle.cpp
├── paddle.hpp
└── SDL headers
```

### Structure des Fichiers

```
Projet/
├── src/
│   ├── main.cpp
│   ├── game.cpp
│   ├── menu.cpp
│   ├── paddle.cpp
│   ├── BallBase.cpp
│   ├── ClassicBall.cpp
│   ├── SquareBall.cpp
│   ├── TriangleBall.cpp
│   └── GameSave.cpp
├── include/
│   ├── game.hpp
│   ├── menu.hpp
│   └── [autres headers]
├── assets/
│   ├── sounds/
│   └── fonts/
└── Makefile
```

## Sécurité et Sauvegarde de l'état du jeu

### Chiffrement des Données

La sauvegarde des données utilise un système de chiffrement XOR simple avec une clé rotative :

```cpp
class GameSaveEncryption {
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
        float predictedY = PredictBallY(ball);
        float currentY = paddle->GetPosY();
      
        // Décision de mouvement avec une marge d'erreur pour simulation humaine
        return (predictedY > currentY + ERROR_MARGIN) ? 1.0f : 
               (predictedY < currentY - ERROR_MARGIN) ? -1.0f : 0.0f;
    }
private:
    const float ERROR_MARGIN = 10.0f;
    float PredictBallY(const Ball* ball);
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
   mGameState = GameState::Playing;
   ResetGame();
   });

Les lambda functions permettent une syntaxe plus claire pour les callbacks et une maintenance simplifiée. En plus, l'utilisation des lambda functions est particulièrement pertinente pour le mode IA où elles permettent de définir différentes stratégies de jeu de manière concise et modulaire.
