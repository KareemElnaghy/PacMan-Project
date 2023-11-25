#include "game.h"
#include<QFile>
#include<QKeyEvent>
#include<queue>
Game::Game()
{
    p.x=0;p.y=0;
    died=false;
    g=new mapGraph(MapRows,MapCols);
    pacmoving=false;
    pacTimer=new QTimer(this);
    animationTimer=new QTimer(this);


    collisionTimer=new QTimer(this);
    generateGame();

    Gho1->chaseTimer = new QTimer(this);
    Gho2->chaseTimer = new QTimer(this);
    Gho3->chaseTimer = new QTimer(this);
    Gho4->chaseTimer = new QTimer(this);

    Gho1->runTimer = new QTimer(this);
    Gho2->runTimer = new QTimer(this);
    Gho3->runTimer = new QTimer(this);
    Gho4->runTimer = new QTimer(this);

    Gho1->runMode = new QTimer(this);
    Gho2->runMode = new QTimer(this);
    Gho3->runMode = new QTimer(this);
    Gho4->runMode = new QTimer(this);

    Gho1->escapeTimer = new QTimer(this);
    Gho2->escapeTimer = new QTimer(this);
    Gho3->escapeTimer = new QTimer(this);
    Gho4->escapeTimer = new QTimer(this);

    Gho1->panicModeTimer = new QTimer(this);
    Gho2->panicModeTimer = new QTimer(this);
    Gho3->panicModeTimer = new QTimer(this);
    Gho4->panicModeTimer = new QTimer(this);


    connect(Gho1->panicModeTimer, &QTimer::timeout, this, &Game::endPanicMode1);
    connect(Gho2->panicModeTimer, &QTimer::timeout, this, &Game::endPanicMode2);
    connect(Gho3->panicModeTimer, &QTimer::timeout, this, &Game::endPanicMode3);
    connect(Gho4->panicModeTimer, &QTimer::timeout, this, &Game::endPanicMode4);

    connect(Gho1->escapeTimer, &QTimer::timeout, this, &Game::escapefrompac1);
    connect(Gho2->escapeTimer, &QTimer::timeout, this, &Game::escapefrompac2);
    connect(Gho3->escapeTimer, &QTimer::timeout, this, &Game::escapefrompac3);
    connect(Gho4->escapeTimer, &QTimer::timeout, this, &Game::escapefrompac4);

    connect(pacTimer,&QTimer::timeout, this,&Game::movePacman);
    connect(animationTimer, &QTimer::timeout, this, &Game::updateAnimation);


    connect(Gho1->chaseTimer, &QTimer::timeout, this, &Game::chasePacman1);
    connect(Gho2->chaseTimer, &QTimer::timeout, this, &Game::chasePacman2);
    connect(Gho3->chaseTimer, &QTimer::timeout, this, &Game::chasePacman3);
    connect(Gho4->chaseTimer, &QTimer::timeout, this, &Game::chasePacman4);


    connect(Gho1->runTimer, &QTimer::timeout, this, &Game::backToCage1);
    connect(Gho2->runTimer, &QTimer::timeout, this, &Game::backToCage2);
    connect(Gho3->runTimer, &QTimer::timeout, this, &Game::backToCage3);
    connect(Gho4->runTimer, &QTimer::timeout, this, &Game::backToCage4);

    connect(Gho1->runMode, &QTimer::timeout, this, &Game::endRunMode1);
    connect(Gho2->runMode, &QTimer::timeout, this, &Game::endRunMode2);
    connect(Gho3->runMode, &QTimer::timeout, this, &Game::endRunMode3);
    connect(Gho4->runMode, &QTimer::timeout, this, &Game::endRunMode4);

    connect(collisionTimer, &QTimer::timeout, this, &Game::collision);
    Gho1->chaseTimer->start(150);
    //Gho2->chaseTimer->start(150);
    //Gho3->chaseTimer->start(150);
    //Gho4->chaseTimer->start(150);
    animationTimer->start(100);
    collisionTimer->start(0);
    startGame();

}

Game::~Game()
{
    delete g;
    delete animationTimer;
    delete pacTimer;


}
void Game::startPanicMode1() {
    Gho1->chaseTimer->stop();
    Gho1->runTimer->stop();
    Gho1->runMode->stop();
    Gho1->condition=ghostCondition::Panic;

    // Set the duration of panic mode (3 seconds)
    Gho1->panicModeTimer->start(3000);
    Gho1->escapeTimer->start(150);
}
void Game::startPanicMode2() {
    Gho2->chaseTimer->stop();
    Gho2->runTimer->stop();
    Gho2->runMode->stop();
    Gho2->condition=ghostCondition::Panic;

    // Set the duration of panic mode (3 seconds)
    Gho2->panicModeTimer->start(3000);
    Gho2->escapeTimer->start(150);
}
void Game::startPanicMode3() {
    Gho3->chaseTimer->stop();
    Gho3->runTimer->stop();
    Gho3->runMode->stop();
    Gho3->condition=ghostCondition::Panic;

    // Set the duration of panic mode (3 seconds)
    Gho3->panicModeTimer->start(3000);
    Gho3->escapeTimer->start(150);
}
void Game::startPanicMode4() {
    Gho4->chaseTimer->stop();
    Gho4->runTimer->stop();
    Gho4->runMode->stop();
    Gho4->condition=ghostCondition::Panic;

    // Set the duration of panic mode (3 seconds)
    Gho4->panicModeTimer->start(3000);
    Gho4->escapeTimer->start(150);
}

void Game::generateGame()
{
    int ghostNum=0;
    int x=0,y=0,mapWidth=30,mapHeight=25;
    QPixmap Wall("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/wall.png");
    QPixmap Gate("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/gate.png");
    QPixmap Ball("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/ball.png");
    QPixmap PowerBall("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/powerBall.png");
    QPixmap Pacpix("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r3.png");
    QFile file("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/map.txt");
    gameMap = new GameObject**[mapHeight];
    for (int i = 0; i < mapHeight; i++) {
        gameMap[i] = new GameObject*[mapWidth];
        for (int j = 0; j < mapWidth; j++)
            gameMap[i][j] = nullptr;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the text file";
        return;
    }
    QTextStream in(&file);

    for(int i=0;i<mapHeight;i++)
    {
        QString line = in.readLine();
        for(int j=0;j<mapWidth;j++)
        {
            int X=x+(j*20);
            int Y=y+(i*20);
            if(line[j]=='0')
            {

                gameMap[i][j]=new GameObject(type::Ball,Ball);
                gameMap[i][j]->setPos(X,Y);
                addItem(gameMap[i][j]);
            }
            else if(line[j]=='1')
            {
                gameMap[i][j]=new GameObject(type::Wall,Wall);
                gameMap[i][j]->setPos(X,Y);
                addItem(gameMap[i][j]);
            }
            else if(line[j]=='2')
            {
                gameMap[i][j]=new GameObject(type::Gate,Gate);
                gameMap[i][j]->setPos(X,Y);
                addItem(gameMap[i][j]);
            }
            else if(line[j]=='3')
            {
                gameMap[i][j]=new GameObject(type::Blank,blank);
                gameMap[i][j]->setPos(X,Y);
                addItem(gameMap[i][j]);
            }
            else if(line[j]=='4')
            {
                gameMap[i][j]=new GameObject(type::PowerBall,PowerBall);
                gameMap[i][j]->setPos(X,Y);
                addItem(gameMap[i][j]);


            }
            else if(line[j]=='p')
            {
                Pac=new PacMan(Pacpix);
                Pac->setPos(X,Y);
                Pac->xcor=j;
                Pac->ycor=i;
                Pac->initx=j;
                Pac->inity=i;
                addItem(Pac);
                gameMap[i][j]=Pac;

            }
            else if(line[j]=='g')
            {
               if(ghostNum==0)
               {
                   Gho1=new Gh0st(ghostColor::Red,blank);
                   Gho1->setPos(X,Y);
                   Gho1->xcor=j;
                   Gho1->ycor=i;
                   Gho1->initx=j;
                   Gho1->inity=i;
                   addItem(Gho1);
                   gameMap[i][j]=Gho1;
               }
               else if(ghostNum==1)
               {
                   Gho2=new Gh0st(ghostColor::Orange,blank);
                   Gho2->setPos(X,Y);
                   Gho2->xcor=j;
                   Gho2->ycor=i;
                   Gho2->initx=j;
                   Gho2->inity=i;
                   addItem(Gho2);
                   gameMap[i][j]=Gho2;
               }
               else if(ghostNum==2)
               {
                    Gho3=new Gh0st(ghostColor::Pink,blank);
                    Gho3->setPos(X,Y);
                    Gho3->xcor=j;
                    Gho3->ycor=i;
                    Gho3->initx=j;
                    Gho3->inity=i;
                    addItem(Gho3);
                    gameMap[i][j]=Gho3;
               }
               else if(ghostNum==3)
               {
                   Gho4=new Gh0st(ghostColor::Green,blank);
                   Gho4->setPos(X,Y);
                   Gho4->xcor=j;
                   Gho4->ycor=i;
                   Gho4->initx=j;
                   Gho4->inity=i;
                   addItem(Gho4);
                   gameMap[i][j]=Gho4;
               }
                ghostNum++;

            }
            if (gameMap[i][j]) {
                gameMap[i][j]->xcor = j;
                gameMap[i][j]->ycor = i;
            }
        }
    }
    file.close();
    scoreDisplay = new QGraphicsTextItem();
    highScoreDisplay = new QGraphicsTextItem();
    scoreDisplay->setPos(620, 0);
    highScoreDisplay->setPos(600, 20);
    updateScore(); // Helper function to update the score text
    addItem(scoreDisplay);
    addItem(highScoreDisplay);
    h1=new QGraphicsPixmapItem;
    h2=new QGraphicsPixmapItem;
    h3=new QGraphicsPixmapItem;
    heart.load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Heart.png");
    h1->setPixmap(heart);
    h2->setPixmap(heart);
    h3->setPixmap(heart);
    h1->setPos(645,50);h2->setPos(675,50);h3->setPos(705,50);
    addItem(h1);addItem(h2);addItem(h3);
    livesDisplay=new QGraphicsTextItem();
    livesDisplay->setPos(600,47);
    livesDisplay->setPlainText(QString("Lives:"));
    QFont font("Comic Sans MS", 12, QFont::Bold);  // Adjust the font size as needed
    livesDisplay->setFont(font);
    livesDisplay->setDefaultTextColor(QColor(Qt::white));
    addItem(livesDisplay);
}

//


void Game::endPanicMode1() {

    Gho1->panicModeTimer->stop();
    Gho1->condition=ghostCondition::Normal;
    Gho1->escapeTimer->stop();
    Gho1->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endPanicMode2() {

    Gho2->panicModeTimer->stop();
    Gho2->condition=ghostCondition::Normal;
    Gho2->escapeTimer->stop();
    Gho2->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endPanicMode3() {

    Gho3->panicModeTimer->stop();
    Gho3->condition=ghostCondition::Normal;
    Gho3->escapeTimer->stop();
    Gho3->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endPanicMode4() {

    Gho4->panicModeTimer->stop();
    Gho4->condition=ghostCondition::Normal;
    Gho4->escapeTimer->stop();
    Gho4->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}








void Game::startRunMode(Gh0st *g) {
        g->panicModeTimer->stop();
        g->escapeTimer->stop();
        g->runMode->start(10000);
        g->chaseTimer->stop();
        g->runTimer->start(150);
        g->condition=ghostCondition::Running;
}

void Game::endRunMode1() {

    Gho1->runTimer->stop();
    Gho1->runMode->stop();
    Gho1->condition=ghostCondition::Normal;
    Gho1->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endRunMode2() {
    Gho2->runTimer->stop();
    Gho2->runMode->stop();
    Gho2->condition=ghostCondition::Normal;
    Gho2->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endRunMode3() {
    Gho3->runTimer->stop();
    Gho3->runMode->stop();
    Gho3->condition=ghostCondition::Normal;
    Gho3->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}
void Game::endRunMode4() {
    Gho4->runTimer->stop();
    Gho4->runMode->stop();
    Gho4->condition=ghostCondition::Normal;
    Gho4->chaseTimer->start(150);
    // Resume normal behavior after panic mode ends
}





void Game::keyPressEvent(QKeyEvent *ev)
{

       if(!pacmoving)
       {
           if (ev->key() == Qt::Key_Up) {
               // Update Pacman's y-coordinate to move up

               Pac->dir=direction::Up;
           } else if (ev->key() == Qt::Key_Down) {
               // Update Pacman's y-coordinate to move down

               Pac->dir=direction::Down;
           } else if (ev->key() == Qt::Key_Left) {
               // Update Pacman's x-coordinate to move left

               Pac->dir=direction::Left;
           } else if (ev->key() == Qt::Key_Right) {
               // Update Pacman's x-coordinate to move right

               Pac->dir=direction::Right;
           }
       }
        pacTimer->start(150);
        pacmoving=true;
        if(pacmoving){
            pacTimer->stop();
            pacmoving = false;
            if (ev->key() == Qt::Key_Up) {
                Pac->dir = direction::Up;
                    } else if (ev->key() == Qt::Key_Down) {
                        Pac->dir = direction::Down;
                    } else if (ev->key() == Qt::Key_Left) {
                        Pac->dir = direction::Left;
                    } else if (ev->key() == Qt::Key_Right) {
                        Pac->dir = direction::Right;
                    }
                    // Start the timer again
                    pacTimer->start(150);
                    pacmoving = true;
                }

        // Check if the new position is within bounds before updating

}

void Game::startGame()
{

}

void Game::chasePacman1()
{
    if(!died)
    {
        moveGhosts(Gho1,Pac->xcor,Pac->ycor,160);

    }

}
void Game::chasePacman2()
{
    if(!died)
    {
        moveGhosts(Gho2,Pac->xcor,Pac->ycor,160);

    }

}
void Game::chasePacman3()
{
    if(!died)
    {
        moveGhosts(Gho3,Pac->xcor,Pac->ycor,160);

    }

}
void Game::chasePacman4()
{
    if(!died)
    {
        moveGhosts(Gho4,Pac->xcor,Pac->ycor,160);

    }

}

void Game::backToCage1()
{
    moveGhosts(Gho1,Gho1->initx,Gho1->inity,160);
}

void Game::backToCage2()
{
    moveGhosts(Gho2,Gho2->initx,Gho2->inity,160);
}
void Game::backToCage3()
{
    moveGhosts(Gho3,Gho3->initx,Gho3->inity,160);
}
void Game::backToCage4()
{
    moveGhosts(Gho4,Gho4->initx,Gho4->inity,160);
}
void Game::movePacman()
{

    int newX = Pac->getx();
    int newY = Pac->gety();
    direction initial;
    initial=Pac->dir;
    if (Pac->dir == direction::Up) {
            newY--;
        } else if (Pac->dir == direction::Down) {
            newY++;
        } else if (Pac->dir == direction::Left) {
            newX--;
        } else if (Pac->dir == direction::Right) {
            newX++;
        }
    if(initial!=Pac->dir)
    {
        pacTimer->stop();
        pacmoving = false;
    }
    else if (newX >= 1 && newX < MapCols-1 && newY >= 1 && newY < MapRows-1 && gameMap[newY][newX]->objectType!=type::Wall) {
        Pac->setPos(newX * GameObject::Width, newY * GameObject::Width);
        Gho1->escapepath=true;
        Gho2->escapepath=true;
        Gho3->escapepath=true;
        Gho4->escapepath=true;
        if (Pac->dir == direction::Up) {
                Pac->moveUp();
            } else if (Pac->dir == direction::Down) {
                Pac->moveDown();
            } else if (Pac->dir == direction::Left) {
                Pac->moveLeft();
            } else if (Pac->dir == direction::Right) {
                Pac->moveRight();
            }
        if(gameMap[newY][newX]->objectType==type::Ball)
        {
            Pac->score+=ballScore;
            updateScore();
        }
        if( gameMap[newY][newX]->objectType==type::Ball || gameMap[newY][newX]->objectType==type::PowerBall)
        {
            if(gameMap[newY][newX]->objectType==type::PowerBall)
            {
                p=g->findFarthestPoint(Pac->xcor,Pac->ycor);
                if(Gho1->condition==Normal)
                {
                    startPanicMode1();
                }
                if(Gho2->condition==Normal)
                {
                    //startPanicMode2();
                }
                if(Gho3->condition==Normal)
                {
                    //startPanicMode3();
                }
                if(Gho4->condition==Normal)
                {
                    //startPanicMode4();
                }

            }
            gameMap[newY][newX]->setPixmap(blank);
            gameMap[newY][newX]->objectType=type::Blank;
        }
    }
    else
    {
        pacTimer->stop();
        pacmoving = false;
    }
}

void Game::updateAnimation()
{
    Pac->animate();
}

void Game::collision()
{
    if(Pac->lives==0)
    {
        died=true;
        Gho1->chaseTimer->stop();
        Gho2->chaseTimer->stop();
        Gho3->chaseTimer->stop();
        Gho4->chaseTimer->stop();
        pacTimer->stop();
        animationTimer->stop();
        //collisionTimer->stop();
        //PlayAgainDialog *d=new PlayAgainDialog;
        //d->show();
    }
    else if((Pac->xcor==Gho1->xcor && Pac->ycor==Gho1->ycor)||(Pac->xcor==Gho2->xcor && Pac->ycor==Gho2->ycor)||(Pac->xcor==Gho3->xcor && Pac->ycor==Gho3->ycor)||(Pac->xcor==Gho4->xcor && Pac->ycor==Gho4->ycor))
    {
        if(Gho1->condition==ghostCondition::Panic && Pac->xcor==Gho1->xcor && Pac->ycor==Gho1->ycor)
        {
            startRunMode(Gho1);
        }
        else if(Gho2->condition==ghostCondition::Panic && Pac->xcor==Gho2->xcor && Pac->ycor==Gho2->ycor)
        {
            startRunMode(Gho2);
        }
        else if(Gho3->condition==ghostCondition::Panic && Pac->xcor==Gho3->xcor && Pac->ycor==Gho3->ycor)
        {
            startRunMode(Gho3);
        }
        else if(Gho4->condition==ghostCondition::Panic && Pac->xcor==Gho4->xcor && Pac->ycor==Gho4->ycor)
        {
            startRunMode(Gho4);
        }
        else if(Gho1->condition==ghostCondition::Normal && Pac->xcor==Gho1->xcor && Pac->ycor==Gho1->ycor)
        {
            Pac->lives--;
            Pac->xcor=Pac->initx;
            Pac->ycor=Pac->inity;
            Pac->setPos(Pac->initx*20,Pac->inity*20);
            if(Pac->lives==2)
            {
                h3->setPixmap(blank);
            }
            else if(Pac->lives==1)
            {
                h2->setPixmap(blank);
            }
            else if(Pac->lives==0)
            {
                h1->setPixmap(blank);
            }

        }

    }
}

void Game::escapefrompac1()
{

    moveGhosts(Gho1,p.x,p.y,160);

}
void Game::escapefrompac2()
{


    moveGhosts(Gho2,p.x,p.y,160);

}
void Game::escapefrompac3()
{


    moveGhosts(Gho3,p.x,p.y,160);

}
void Game::escapefrompac4()
{


    moveGhosts(Gho4,p.x,p.y,160);
}

void Game::moveGhosts(Gh0st *Gho1,int tarx,int tary,int time)
{
    Gho1->escapepath=false;
    Cell start;start.x=Gho1->xcor;start.y=Gho1->ycor;
    Cell end;end.x=tarx;end.y=tary;
    // Initialize a timer with a timeout of 100 milliseconds
    QTimer *movementTimer=new QTimer(this);
    // Counter to keep track of the current move
    int currentMove = 0;
    std::vector<Cell> v1=g->dijkstra(start,end);
    // Connect the timer to a lambda function for handling each movement
    connect(movementTimer, &QTimer::timeout, [=]() mutable{
        // Check if there are more moves
        movementTimer->setInterval(time);
        if (currentMove < v1.size()) {

        if (v1[currentMove].x > Gho1->xcor) {
             Gho1->moveRight();}
        else if (v1[currentMove].x < Gho1->xcor) {
            Gho1->moveLeft();}
        else if (v1[currentMove].y > Gho1->ycor) {
            Gho1->moveDown();
                }
        else if (v1[currentMove].y < Gho1->ycor) {
            Gho1->moveUp();
         }
            //qDebug()<<Gho1->xcor<<","<<Gho1->ycor;
            // Increment the counter for the next move
            ++currentMove;
        } else {
            // Stop the timer when all moves are done
            movementTimer->stop();
           // delete Gho1->movementTimer;
           //Gho1->movementTimer = nullptr;
        }
        if(Gho1->escapepath)
        {
            currentMove = 0;
            v1.clear();
            //qDebug()<<"changed and recalculated";
            //moveGhosts(Gho1,160);
        }
    });
    // Start the timer
    movementTimer->start();
    Gho1->OutofCage=true;
}

void Game::updateScore()
{
    // Set the text for the score display
    if(Pac->score>Pac->highScore)
    {
        Pac->highScore=Pac->score;
        Pac->saveHighScore();
    }
        scoreDisplay->setPlainText(QString("Score: %1").arg(Pac->score));
        highScoreDisplay->setPlainText(QString("High Score: %1").arg(Pac->highScore));

        // Set the font and formatting
        QFont font("Comic Sans MS", 12, QFont::Bold);  // Adjust the font size as needed
        scoreDisplay->setFont(font);
        highScoreDisplay->setFont(font);
        scoreDisplay->setDefaultTextColor(QColor(Qt::white));
        highScoreDisplay->setDefaultTextColor(QColor(Qt::white));
}


mapGraph::mapGraph(int r, int c)
{

    QFile file("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/map.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the text file";
        return;
    }
    QTextStream in(&file);
    rows=r;
    cols=c;
    Graph.resize(r, std::vector<Cell>(c));

    CellType cell;

    for(int i=0;i<rows;i++)
    {
        QString line = in.readLine();
        for(int j=0;j<cols;j++)
        {
            if(line[j]=='1')
            {
                 cell=CellType::closed;
            }
            else
            {
                 cell=CellType::open;
            }
            Graph[i][j].x=j;Graph[i][j].y=i;Graph[i][j].type=cell;
        }
    }

    file.close();

}

bool mapGraph::isValidCell(int x, int y) const
{
    return x >= 1 && x < cols-1 && y >= 1 && y < rows-1 &&  Graph[y][x].type!=closed;
}
const Cell &mapGraph::getCell(int x, int y) const
{
    return Graph[x][y];
}
//check starting here
bool mapGraph::areAdjacent(const Cell &cell1, const Cell &cell2) const
{
    return std::abs(cell1.x - cell2.x) + std::abs(cell1.y - cell2.y) == 1;
}

std::vector<Cell> mapGraph::getNeighbors(const Cell &cell) const
{
    std::vector<Cell> neighbors;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int newX = cell.x + dx;
            int newY = cell.y + dy;

            if (isValidCell(newX, newY) && (dx == 0 || dy == 0) && !(dx == 0 && dy == 0)) {
                neighbors.push_back(Graph[newY][newX]);
            }
        }
    }

    return neighbors;

}

std::vector<Cell> mapGraph::findShortestPath(const Cell &start, const Cell &goal) const
{
    // A* algorithm implementation
    std::priority_queue<std::pair<int, Cell>,std::vector<std::pair<int, Cell>>, std::greater<>> pq;
    std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, INT_MAX));
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, {-1, -1, open}));

    distance[start.x][start.y] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [dist, current] = pq.top();
        pq.pop();

        if (current.x == goal.x && current.y == goal.y) {
            // Reconstruct the path
            std::vector<Cell> path;
            while (current.x != -1) {
                path.push_back(current);
                current = parent[current.x][current.y];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : getNeighbors(current)) {
            int newDist = distance[current.x][current.y] + 1;  // Assuming uniform cost

            if (newDist < distance[neighbor.x][neighbor.y] && neighbor.type != closed) {
                distance[neighbor.x][neighbor.y] = newDist;
                parent[neighbor.x][neighbor.y] = current;
                pq.push({newDist + heuristic(neighbor, goal), neighbor});
            }
        }
    }

    return {};  // No path found
}

int mapGraph::heuristic(const Cell &a, const Cell &b) const
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
std::vector<Cell> mapGraph::dijkstra(const Cell &start, const Cell &goal) const
{
    // Priority queue to store vertices to be processed, ordered by distance
    std::priority_queue<std::pair<int, Cell>, std::vector<std::pair<int, Cell>>, std::greater<>> pq;

    // Vector to store distances from the start cell
    std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, INT_MAX));

    // Vector to store parent information for reconstructing the path
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, {-1, -1, open}));

    // Initialize distance for the start cell
    distance[start.y][start.x] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [dist, current] = pq.top();
        pq.pop();

        if (current.x == goal.x && current.y == goal.y) {
            // Reconstruct the path
            std::vector<Cell> path;
            while (current.x != -1) {
                path.push_back(current);
                current = parent[current.y][current.x];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &neighbor : getNeighbors(current)) {
            int newDist = distance[current.y][current.x] + 1; // Assuming uniform cost

            if (newDist < distance[neighbor.y][neighbor.x] && neighbor.type != closed) {
                distance[neighbor.y][neighbor.x] = newDist;
                parent[neighbor.y][neighbor.x] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    return {}; // No path found
}

Point mapGraph::findFarthestPoint(int x0, int y0)
{
    Point farthestPoint;
    double maxDistance = 0.0;

    for (int y = 0; y < Graph.size(); ++y) {
        for (int x = 0; x < Graph[y].size(); ++x) {
            // Skip closed cells (walls)
            if (Graph[y][x].type == closed) {
                continue;
            }

            // Calculate Euclidean distance
            double distance = std::sqrt(std::pow(x - x0, 2) + std::pow(y - y0, 2));

            // Update farthest point if the current point is farther
            if (distance > maxDistance) {
                maxDistance = distance;
                farthestPoint.x = x;
                farthestPoint.y = y;
            }
        }
    }

    return farthestPoint;
}
