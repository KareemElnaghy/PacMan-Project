#include<QMainWindow>
#include"gameobject.h"
#include<QGraphicsView>
#include<QTimer>
#ifndef GAME_H
#define GAME_H

#define ballScore 10
#define powerBallScore 20
#define ghostScore 30


struct Point {
    int x;
    int y;
};


class mapGraph{
public:
    mapGraph(int r,int c);
    int rows,cols;
    std::vector<std::vector<Cell>> Graph;
    bool isValidCell(int x, int y) const ;
    const Cell& getCell(int x, int y) const;
    bool areAdjacent(const Cell& cell1, const Cell& cell2) const;
    std::vector<Cell> getNeighbors(const Cell& cell) const ;
    std::vector<Cell> findShortestPath(const Cell& start, const Cell& goal) const;
    int heuristic(const Cell& a, const Cell& b) const ;
    std::vector<Cell> dijkstra(const Cell &start, const Cell &goal) const;
    Point findFarthestPoint(int x0, int y0) ;
};


class Game: public QGraphicsScene
{
    Q_OBJECT
public:
    static const int MapRows = 25;
    static const int MapCols = 30;
    Game();
    ~Game();
    friend class mapGraph;
private:
    Point p;
    int powerBalls;
    QPixmap gameover,gamewon;
    QGraphicsPixmapItem *gameOver;

    QPixmap start;
    QGraphicsPixmapItem *mainMenu;


    QPixmap menu;
    QGraphicsPixmapItem *escapeMenu;
    bool paused;
    bool gameStarted;


    GameObject ***gameMap;
    mapGraph *g;
    PacMan *Pac;
    Gh0st *Gho1,*Gho2,*Gho3,*Gho4;

    QTimer *animationTimer,*collisionTimer,*releaseTimer,*spawnTimer;

    QGraphicsTextItem *scoreDisplay,*highScoreDisplay,*livesDisplay,*escdisplay;
    QPixmap blank,heart;
    QGraphicsPixmapItem *h1,*h2,*h3;

    void keyPressEvent(QKeyEvent *ev);
    void mousePressEvent(QMouseEvent *ev);

    void moveGhost(Gh0st *Gho1,int tarx,int tary,int time);
    void updateScore();
    void startPanicMode(Gh0st *Gho);
    void startRunMode(Gh0st *Gho);
    void generateGame();
    void pauseGame();
    void resumeGame();
    void deleteTimer(QTimer *&timer);
    void restartGame();
    void releaseGhosts();
    bool gameWon();
    void spawnPowerUp();
private slots:

    void chasePacman(Gh0st *Gho,int xcor,int ycor);
    void escapefromPacman(Gh0st *Gho);
    void  backToCage(Gh0st *Gho);

    void endPanicMode(Gh0st *Gho);
    void endRunMode(Gh0st *Gho);

    void movePacman();
    void collision();    
};


#endif // GAME_H
