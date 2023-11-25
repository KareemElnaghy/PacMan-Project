#include "qtimer.h"
#include<QGraphicsItem>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
enum CellType {open = 0,closed = 1};
struct Cell {
    int x, y;
    CellType type;
    bool operator<(const Cell& other) const {
            // You can define the comparison logic based on your requirements.
            // For example, you might compare based on x and then y.
            if (x != other.x) {
                return x < other.x;
            }
            return y < other.y;
        }
};
enum type{Ball, Wall, Gate, Pacman, Ghost, Blank, PowerBall};
enum direction {Up = 0, Down = 1, Left = 2, Right = 3};
enum ghostColor {Red = 0, Orange = 1, Pink = 2, Green = 3};
enum ghostCondition {Normal, Panic, Running};
class Game;
class Gh0st;
class GameObject: public QGraphicsPixmapItem
{

public:
    static const int Width = 20;
    GameObject(enum type,QPixmap);
    virtual ~GameObject();
    int getx();
    int gety();
    enum direction getDirection();
    void setDirection(enum direction);
    friend class Game;
protected:
    int xcor,ycor;
    enum direction dir;
    virtual void setpic();
    enum type objectType;
    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();



};

class PacMan : public GameObject{
public:
    PacMan(QPixmap pacpix);
    void move();
    Game*game;
    friend class Game;
private:
    int initx;int inity;
    int lives;
    void moveUp()override;
    void moveDown()override;
    void moveLeft()override;
    void moveRight()override;
    void saveHighScore();
    QPixmap right[6];
    QPixmap left[6];
    QPixmap up[6];
    QPixmap down[6];
    void eat();
    void setpic()override;
    void animate();
    int currentframe;
    int score;
    int highScore;
};

class Gh0st: public GameObject
{
public:
    const static int GhostNum = 4;
    Game*game;
    Gh0st(ghostColor col,QPixmap ghoPix);
    void move();
    enum ghostColor getColor();
    friend class Game;
private:
    bool OutofCage;
    bool escapepath;
    int initx,inity;
    QTimer *chaseTimer;
    QTimer *runTimer;
    QTimer *runMode;
    QTimer *escapeTimer;
    QTimer *panicModeTimer;
    QPixmap orange[4][2];
    QPixmap red[4][2];
    QPixmap pink[4][2];
    QPixmap green[4][2];
    QPixmap peacful[2];
    QPixmap eyes;
    int currentframe;
    void setGhostPic();
    void animateGhost();
    void moveUp()override;
    void moveDown()override;
    void moveLeft()override;
    void moveRight()override;
    void escapeCage(std::vector<Cell> v);
    void backCage();
    void chase();
    void canMove();
    ghostColor color;
    ghostCondition condition;
};

#endif // GAMEOBJECT_H
