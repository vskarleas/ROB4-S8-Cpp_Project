# Explication des Concepts de Programmation Orientée Objet dans le Code

## Abstraction

L'abstraction est implémentée principalement à travers les classes abstraites du projet. La classe `BallBase` est un excellent exemple d'abstraction. Dans le fichier `ball_base.hpp`, nous définissons une interface commune pour tous les types de balles avec des méthodes abstraites comme `render_object()`. Cette méthode est déclarée virtuelle pure (`= 0`), obligeant toutes les classes dérivées à fournir leur propre implémentation.

```cpp
class BallBase {
public:
    // ...
    virtual void render_object(SDL_Renderer *renderer) = 0;
    // ...
};
```

De même, la classe `Power` dans `power.hpp` fournit une abstraction pour les différents types de power-ups du jeu, avec des méthodes virtuelles qui peuvent être redéfinies par les classes dérivées comme `InvisiblePower` et `InversePower`.

## Héritage (Heritage)

L'héritage est largement utilisé pour étendre la fonctionnalité des classes de base. Les trois types de balles (`ClassicBall`, `SquareBall` et `TriangleBall`) héritent tous de la classe abstraite `BallBase`. Par exemple, dans `classic_ball.hpp`, nous voyons :

```cpp
class ClassicBall : public BallBase {
public:
    ClassicBall() : BallBase(24.0f) {}
    void render_object(SDL_Renderer *renderer) override;
    // ...
};
```

Dans le domaine des power-ups, nous avons également une hiérarchie d'héritage. Les classes `InvisiblePower` et `InversePower` héritent de la classe `Power`, comme on peut le voir dans `invisible_power.hpp` et `inverse_power.hpp`. Cela permet de partager le comportement commun tout en spécialisant certaines fonctionnalités.

## Polymorphisme

Le polymorphisme est implémenté à travers l'utilisation de méthodes virtuelles et leur redéfinition dans les classes dérivées. Un exemple clair se trouve dans la hiérarchie des balles, où la méthode `render_object()` est définie différemment dans chaque type de balle :

* Dans `classic_ball.cpp`, elle dessine un cercle.
* Dans `square_ball.cpp`, elle dessine un carré.
* Dans `triangle_ball.cpp`, elle dessine un triangle.

Le jeu peut manipuler n'importe quel objet dérivé de `BallBase` de manière uniforme, en appelant `mBall->render_object(renderer)` dans `game.cpp`, sans se soucier du type spécifique de balle utilisé.

De même, les power-ups démontrent le polymorphisme avec leurs méthodes `update()` et `render()` qui sont appelées de manière générique mais exécutent un comportement spécifique à chaque type de power-up.

## Encapsulation

L'encapsulation est présente dans presque toutes les classes du projet, avec une distinction claire entre les interfaces publiques et les détails d'implémentation privés. Par exemple, la classe `User` dans `user.hpp` encapsule les données relatives au joueur :

```cpp
class User {
private:
    std::string name;  // Le nom de l'utilisateur
    int score;         // Le score actuel de l'utilisateur
    int round;         // Le numéro de round actuel

public:
    // Méthodes pour interagir avec les données encapsulées
    void increment_score();
    void reset_score();
    int get_user_score() const;
    // ...
};
```

Un autre exemple d'encapsulation se trouve dans le fichier `game_save.cpp`, où un namespace anonyme est utilisé pour encapsuler les constantes sensibles (comme la clé de chiffrement) et les fonctions utilitaires :

```cpp
namespace {
    const unsigned char KEY = 0x83;
    // ...
    unsigned char codec_byte(unsigned char byte) { /* ... */ }
    // ...
}
```

Cette approche garantit que ces éléments ne sont accessibles que depuis ce fichier, renforçant ainsi la sécurité du mécanisme de sauvegarde.

## Fonctions Lambda

Les fonctions lambda sont utilisées pour créer des fonctions anonymes, particulièrement utiles pour des opérations localisées. Dans `paddle.cpp`, deux fonctions lambda sont définies dans la méthode `update()` :

```cpp
auto move_paddle = [this](float delta, float time) {
    this->set_pos_y(this->get_pos_y() + delta * this->get_racket_speed() * time);
};

auto adjust_boundaries = [this]() {
    if (this->get_pos_y() < this->get_racket_height() / 2.0f) {
        this->set_pos_y(this->get_racket_height() / 2.0f);
    }
    else if (this->get_pos_y() > 600.0f - this->get_racket_height() / 2.0f) {
        this->set_pos_y(600.0f - this->get_racket_height() / 2.0f);
    }
};
```

Ces lambdas encapsulent la logique de déplacement et d'ajustement des limites de la raquette, rendant le code plus modulaire et facile à maintenir.

## Foncteurs

Les foncteurs sont des classes qui peuvent être utilisées comme des fonctions grâce à la surcharge de l'opérateur `()`. Dans notre projet, ils sont principalement utilisés pour le rendu des différentes formes de balle. Dans `renderers.hpp`, nous définissons trois foncteurs :

```cpp
struct circle_renderer {
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
    // ...
};

struct square_renderer {
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};

struct triangle_renderer {
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};
```

Ces foncteurs sont utilisés dans les classes de balle correspondantes pour dessiner la forme appropriée. Par exemple, dans `classic_ball.cpp`, nous utilisons :

```cpp
void ClassicBall::render_object(SDL_Renderer *renderer) {
    circle_renderer()(renderer, pos_x, pos_y, ball_size, color);
}
```

L'utilisation de foncteurs permet d'isoler la logique de rendu et de la tester indépendamment, tout en gardant une interface cohérente pour toutes les formes.

## Conclusion

Notre projet de jeu Pong exploite pleinement les concepts de la programmation orientée objet pour créer un code modulaire, extensible et maintenable. L'abstraction et l'héritage permettent de définir des interfaces communes et des hiérarchies de classes. Le polymorphisme permet d'utiliser différents types d'objets de manière uniforme. L'encapsulation protège les données et les implémentations. Enfin, les fonctions lambda et les foncteurs offrent des moyens flexibles d'encapsuler des comportements spécifiques.

Ces concepts ne sont pas seulement des exercices académiques, mais des outils pratiques qui ont rendu notre code plus robuste et plus facile à faire évoluer au fur et à mesure du développement du jeu.
