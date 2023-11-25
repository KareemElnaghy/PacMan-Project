#include<QMainWindow>
#include"gameobject.h"
#include<QGraphicsView>
#include<QTimer>
#include <cmath>
#include<QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#ifndef GAME_H
#define GAME_H

#define ballScore 10

class PlayAgainDialog : public QWidget {
    Q_OBJECT
public:
    PlayAgainDialog(QWidget *parent = nullptr) : QWidget(parent) {
        initUI();
    }

private:
    void initUI() {
        QVBoxLayout *vbox = new QVBoxLayout(this);

        QLabel *label = new QLabel("Do you want to play again?", this);
        vbox->addWidget(label);

        QPushButton *yesButton = new QPushButton("Yes", this);
        QPushButton *noButton = new QPushButton("No", this);

        connect(yesButton, &QPushButton::clicked, this, &PlayAgainDialog::playAgain);
        connect(noButton, &QPushButton::clicked, this, &QWidget::close);

        vbox->addWidget(yesButton);
        vbox->addWidget(noButton);

        setLayout(vbox);
        setWindowTitle("Play Again?");
        setGeometry(300, 300, 300, 150);
    }

private slots:
    void playAgain() {
        close();
        // Add your code here to restart the game or perform any other action
    }
};
struct Point {
    int x;
    int y;
};
class mapGraph{
public:
    mapGraph(int r,int c);
    int rows;
    int cols;
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
    void keyPressEvent(QKeyEvent *ev);
    friend class mapGraph;
    mapGraph *g;
private:
    GameObject ***gameMap;
    PacMan *Pac;
    QTimer *pacTimer;
    QTimer *animationTimer;

    QTimer *collisionTimer;
    QGraphicsTextItem *scoreDisplay;
    QGraphicsTextItem *highScoreDisplay;
    QPixmap heart;
    QGraphicsTextItem *livesDisplay;
    QGraphicsPixmapItem *h1;
    QGraphicsPixmapItem *h2;
    QGraphicsPixmapItem *h3;
    Gh0st *Gho1;
    Gh0st *Gho2;
    Gh0st *Gho3;
    Gh0st *Gho4;
    bool pacmoving;
    QPixmap blank;
    void startGame();

    void moveGhosts(Gh0st *Gho1,int tarx,int tary,int time);
    void updateScore();
    bool died;
    void startPanicMode1();
    void startPanicMode2();
    void startPanicMode3();
    void startPanicMode4();
    void generateGame();
    Point p;

    void startRunMode(Gh0st *g);
private slots:
    void chasePacman1();
    void chasePacman2();
    void chasePacman3();
    void chasePacman4();

    void  backToCage1();
    void  backToCage2();
    void  backToCage3();
    void  backToCage4();

    void movePacman();
    void updateAnimation();
    void collision();

    void escapefrompac1();
    void escapefrompac2();
    void escapefrompac3();
    void escapefrompac4();

    void endPanicMode1();
    void endPanicMode2();
    void endPanicMode3();
    void endPanicMode4();

    void endRunMode1();
    void endRunMode2();
    void endRunMode3();
    void endRunMode4();
};


#endif // GAME_H
