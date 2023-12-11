#include "qtimer.h"
#include<QGraphicsItem>
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#define pacLives 3;
class Game;

enum CellType {open = 0,closed = 1};
enum type{Ball, Wall, Gate, Pacman, Ghost, Blank, PowerBall};
enum direction {Up = 0, Down = 1, Left = 2, Right = 3};
enum ghostColor {Red = 0, Orange = 1, Pink = 2, Green = 3};
enum ghostCondition {Normal, Panic, Running};

struct Cell {
    int x, y;
    CellType type;
    bool operator<(const Cell& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
        }
};


class GameObject: public QGraphicsPixmapItem
{
public:
    static const int Width = 20;
    GameObject(enum type,QPixmap);
    friend class Game;
protected:
    int xcor,ycor;
    enum direction dir;
    enum type objectType;
    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
};


class PacMan : public GameObject{
public:
    PacMan(QPixmap pacpix);
    friend class Game;
private:
    bool pacmoving,dead,won;
    int initx,inity,lives,currentframe,score,highScore;
    QTimer *pacTimer;
    QPixmap right[6],left[6],up[6],down[6];
    void loadGraphics();
    void moveUp()override;
    void moveDown()override;
    void moveLeft()override;
    void moveRight()override;
    void loadHighScore();
    void saveHighScore();
    void setpic();
    void animate();
};


class Gh0st: public GameObject
{
public:
    const static int GhostNum = 4;
    Gh0st(ghostColor col,QPixmap ghoPix);
    friend class Game;
private:
    bool released;
    ghostColor color;
    ghostCondition condition;
    bool OutofCage,escapepath;
    int initx,inity;
    QTimer *chaseTimer,*escapeTimer,*panicModeTimer,*runTimer,*runMode;
    QPixmap orange[4][2],red[4][2],pink[4][2],green[4][2],peacful[2],eyes;
    int currentframe;
    void loadGraphics();
    void setGhostPic();
    void animateGhost();
    void moveUp()override;
    void moveDown()override;
    void moveLeft()override;
    void moveRight()override;
};


#endif // GAMEOBJECT_H
