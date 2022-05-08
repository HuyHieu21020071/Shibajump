#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
using namespace sf;
/*
	*      ----Size of images----
	*    background.png size: 400 * 533
	*    doodle.png     size:  80 *  80
	*    platform.png   size:  68 *  14
*/

struct point
{ int x,y;};

int main()
{
    srand(time(0));
    RenderWindow app(VideoMode(400, 533), "Bonk Game!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3_1,t3_2,t4,t5;
    t1.loadFromFile("images/background2.jpg");
    t2.loadFromFile("images/platform.png");
    t3_1.loadFromFile("images/dog2_left.png");
    t3_2.loadFromFile("images/dog2_right.png");
    t4.loadFromFile("images/GameOver_fix.png");
    t5.loadFromFile("images/bonk_img_resize.jpg");

    Sprite sBackground(t1), sPlat(t2), sPers_left(t3_1), sPers_right(t3_2), sGameOver(t4), sBonk(t5);
//
    Font font;
    font.loadFromFile("font/arial.ttf");

    Text ScoreText;
    ScoreText.setFont(font);
    ScoreText.setCharacterSize(20);
    ScoreText.setFillColor(Color::Red);

    Text Highest_ScoreText;
    Highest_ScoreText.setFont(font);
    Highest_ScoreText.setCharacterSize(20);
    Highest_ScoreText.setFillColor(Color::Red);
    Highest_ScoreText.setPosition (200,0);

    Text Restart;
    Restart.setFont(font);
    Restart.setCharacterSize(30);
    Restart.setFillColor(Color::Black);
    Restart.setString("Press F to restart!");
    Restart.setPosition(80,480);

    SoundBuffer buffer;
    buffer.loadFromFile("sound/jump.wav");

    Sound jump;
    jump.setBuffer(buffer);

    SoundBuffer buffer_1;
    buffer_1.loadFromFile("sound/bonk.wav");
    Sound bonk;
    bonk.setBuffer(buffer_1);

    int Score=0,Highest_Score=0;
    bool first = true;
    point plat[20];
    bool Game = true;
    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()%350;
       plat[i].y=rand()%533;
      }
    plat[0].y=400;
    plat[0].x=100;
    int x=100,y=300,h=200;
    float dy=0;
    bool isRight = true;
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
    if (Game==false)
    {
        if(Keyboard::isKeyPressed(Keyboard::F))
        {
            Game=true;
            first=true;
            for(int i=0;i<10;i++)
            {
                plat[i].x=rand()%350;
                plat[i].y=rand()%533;
            }
            plat[0].y=400;
            plat[0].x=100;
            x=100,y=300,h=200;
            dy=0;
            Score=0;
        }
        continue;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
            isRight = true;
            x+=3;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
            isRight = false;
            x-=3;
    }
    if (x>400)
        x=0;
    if (x<-40)
        x=400-80;
    if(y==h&&dy<-2.0)
    {
        Score++;
        ScoreText.setString("Score: " + std::to_string(Score));
        if(Score>Highest_Score)
        {
            Highest_Score=Score;
            Highest_ScoreText.setString("Highest Score: " + std::to_string(Highest_Score));
        }
    }
    dy+=0.2;
    y+=dy;
    if (y>500)
    {
        Game = false ;
        app.clear(Color::White);
        bonk.play();
        app.draw(sGameOver);
        sBonk.setPosition(0,200);
        app.draw(sBonk);
        app.draw(Restart);
        app.display();
        continue;
    }

    if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y>533) {
            plat[i].y=0;
            plat[i].x=rand()%350;
            }
    }

    for (int i=0;i<10;i++)
     if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
      && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0)) {
          dy=-10;
          jump.play();
      }

    app.clear(Color::Black);
    app.draw(sBackground);
    if(isRight==true)
    {
        sPers_right.setPosition(x,y);
        app.draw(sPers_right);
    }
    else
    {
        sPers_left.setPosition(x,y);
        app.draw(sPers_left);
    }
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }
    app.draw(ScoreText);
    app.draw(Highest_ScoreText);
    app.display();
}
    return 0;
}
