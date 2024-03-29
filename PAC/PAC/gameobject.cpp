#include "gameobject.h"
#include<QTimer>
#include<QMainWindow>
#include<QFile>

GameObject::GameObject(enum type t, QPixmap pixmap)
    : QGraphicsPixmapItem(pixmap)
{
    objectType = t;
}

void GameObject::moveUp()
{
    ycor--;
}

void GameObject::moveDown()
{
    ycor++;
}

void GameObject::moveLeft()
{
    xcor--;
}

void GameObject::moveRight()
{
    xcor++;
}




PacMan::PacMan(QPixmap pacpix):GameObject(type::Pacman,pacpix)
{
    pacmoving=dead=won=false;
    lives=pacLives;currentframe=0;score=0;highScore=0;
    loadHighScore();
    loadGraphics();
}

void PacMan::loadGraphics()
{
    right[0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/common.png");
    right[1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r2.png");
    right[2].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r3.png");
    right[3].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r4.png");
    right[4].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r5.png");
    right[5].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/r6.png");

    left[0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/common.png");
    left[1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/l2.png");
    left[2].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/l3.png");
    left[3].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/l4.png");
    left[4].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/l5.png");
    left[5].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/l6.png");

    up[0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/common.png");
    up[1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/u2.png");
    up[2].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/u3.png");
    up[3].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/u4.png");
    up[4].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/u5.png");
    up[5].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/u6.png");

    down[0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/common.png");
    down[1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/d2.png");
    down[2].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/d3.png");
    down[3].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/d4.png");
    down[4].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/d5.png");
    down[5].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/pacman/d6.png");
}

void PacMan::loadHighScore()
{
    QFile file("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/PAC/highScore.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the text file";
        return;
    }
    QTextStream in(&file);
    QString line=in.readLine();
    highScore=line.toInt();
    file.close();
}

void PacMan::saveHighScore()
{
    QFile file("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/PAC/highScore.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << highScore;
        file.close();
    }
}


void PacMan::moveUp()
{
    ycor--;
    animate();
}
void PacMan::moveDown()
{
    ycor++;
    animate();
}
void PacMan::moveLeft()
{
    xcor--;
    animate();
}
void PacMan::moveRight()
{
    xcor++;
    animate();
}

void PacMan::setpic()
{
    if (dir == direction::Up) {
        setPixmap(up[currentframe]);
    } else if (dir == direction::Down) {
        setPixmap(down[currentframe]);
    } else if (dir == direction::Left) {
        setPixmap(left[currentframe]);
    } else if (dir == direction::Right) {
        setPixmap(right[currentframe]);
    }
}

void PacMan::animate()
{
    currentframe = (currentframe + 1) % 6;
    setpic();
}




Gh0st::Gh0st(ghostColor col,QPixmap ghoPix):GameObject(type::Ghost,ghoPix)
{
    released=false;
    this->color=col;
    escapepath=false;currentframe=0;
    condition=ghostCondition::Normal;
    loadGraphics();
    dir=direction::Up;
    if(col==ghostColor::Green)
    {
        setPixmap(green[0][0]);
    }
    else if(col==ghostColor::Red)
    {
        setPixmap(red[0][0]);
    }
    else if(col==ghostColor::Orange)
    {
        setPixmap(orange[0][0]);
    }
    else if(col==ghostColor::Pink)
    {
        setPixmap(pink[0][0]);
    }
}

void Gh0st::loadGraphics()
{
    green[0][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gu1.png");
    green[0][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gu2.png");
    green[1][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gd1.png");
    green[1][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gd2.png");
    green[2][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gl1.png");
    green[2][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gl2.png");
    green[3][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gr1.png");
    green[3][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/gr2.png");

    red[0][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ru1.png");
    red[0][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ru2.png");
    red[1][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rd1.png");
    red[1][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rd2.png");
    red[2][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rl1.png");
    red[2][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rl2.png");
    red[3][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rr1.png");
    red[3][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/rr2.png");

    orange[0][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ou1.png");
    orange[0][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ou2.png");
    orange[1][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/od1.png");
    orange[1][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/od2.png");
    orange[2][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ol1.png");
    orange[2][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/ol2.png");
    orange[3][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/or1.png");
    orange[3][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/or2.png");

    pink[0][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pu1.png");
    pink[0][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pu2.png");
    pink[1][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pd1.png");
    pink[1][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pd2.png");
    pink[2][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pl1.png");
    pink[2][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pl2.png");
    pink[3][0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pr1.png");
    pink[3][1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/pr2.png");

    peacful[0].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/peacful1.png");
    peacful[1].load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/peacful2.png");

    eyes.load("C:/Users/3mrr3/OneDrive/Desktop/AUC/Fall 2023/Applied Data Structures/PAC/Objects/Ghosts/eyes.png");
}

void Gh0st::setGhostPic()
{
    if(condition==ghostCondition::Normal)
    {
        if(color==ghostColor::Green)
        {
            if (dir == direction::Up) {
                setPixmap(green[Up][currentframe]);
            } else if (dir == direction::Down) {
                setPixmap(green[Down][currentframe]);
            } else if (dir == direction::Left) {
                setPixmap(green[Left][currentframe]);
            } else if (dir == direction::Right) {
                setPixmap(green[Right][currentframe]);
            }
        }
        else if(color==ghostColor::Red)
        {
            if (dir == direction::Up) {
                setPixmap(red[Up][currentframe]);
            } else if (dir == direction::Down) {
                setPixmap(red[Down][currentframe]);
            } else if (dir == direction::Left) {
                setPixmap(red[Left][currentframe]);
            } else if (dir == direction::Right) {
                setPixmap(red[Right][currentframe]);
            }
        }
        else if(color==ghostColor::Pink)
        {
            if (dir == direction::Up) {
                setPixmap(pink[Up][currentframe]);
            } else if (dir == direction::Down) {
                setPixmap(pink[Down][currentframe]);
            } else if (dir == direction::Left) {
                setPixmap(pink[Left][currentframe]);
            } else if (dir == direction::Right) {
                setPixmap(pink[Right][currentframe]);
            }
        }
        else if(color==ghostColor::Orange)
        {
            if (dir == direction::Up) {
                setPixmap(orange[Up][currentframe]);
            } else if (dir == direction::Down) {
                setPixmap(orange[Down][currentframe]);
            } else if (dir == direction::Left) {
                setPixmap(orange[Left][currentframe]);
            } else if (dir == direction::Right) {
                setPixmap(orange[Right][currentframe]);
            }
        }
    }else if(condition==ghostCondition::Panic)
    {
        setPixmap(peacful[currentframe]);
    }
    else if(condition==ghostCondition::Running)
    {
        setPixmap(eyes);
    }
}

void Gh0st::animateGhost()
{
    currentframe = (currentframe + 1) % 2;
    setGhostPic();
}

void Gh0st::moveUp()
{
    dir=direction::Up;
    ycor--;
    setPos(xcor * GameObject::Width, ycor * GameObject::Width);
    animateGhost();
}

void Gh0st::moveDown()
{
    dir=direction::Down;
    ycor++;
    setPos(xcor * GameObject::Width, ycor * GameObject::Width);
    animateGhost();
}

void Gh0st::moveLeft()
{
    dir=direction::Left;
    xcor--;
    setPos(xcor * GameObject::Width, ycor * GameObject::Width);
    animateGhost();
}

void Gh0st::moveRight()
{
    dir=direction::Right;
    xcor++;
    setPos(xcor * GameObject::Width, ycor * GameObject::Width);
    animateGhost();
}
