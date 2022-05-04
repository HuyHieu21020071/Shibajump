#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
using namespace sf;


struct point
{ int x,y;};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);


/*
	*      ----Size of images----
	*    background.png size: 400 * 533
	*    doodle.png     size:  80 *  80
	*    platform.png   size:  68 *  14
*/
    Texture t1,t2,t3_1,t3_2,t4;
    t1.loadFromFile("images/background2.jpg");
    t2.loadFromFile("images/platform.png");
    t3_1.loadFromFile("images/dog2_left.png");
    t3_2.loadFromFile("images/dog2_right.png");
    t4.loadFromFile("images/GameOver1.png");

    Sprite sBackground(t1), sPlat(t2), sPers_left(t3_1), sPers_right(t3_2), sGameOver(t4);
//
    Font font;
    font.loadFromFile("font/arial.ttf");
    Text ScoreText;
    ScoreText.setFont(font);
    ScoreText.setCharacterSize(40);
    ScoreText.setFillColor(Color::Black);
    int Score;

    point plat[20];
    SoundBuffer buffer;
    buffer.loadFromFile("sound/jump.wav");
    Sound sound;
    sound.setBuffer(buffer);
    bool Game = true;
    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
      }

    int x=100,y=100,h=200;
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
    if(Game==false) continue;
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
    }
    dy+=0.2;
    y+=dy;
    if (y>500)
    {
        Game = false ;
        app.draw(sGameOver);
        app.display();
        continue;
    }

    if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
    }

    for (int i=0;i<10;i++)
     if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
      && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0)) {
          dy=-10;
          sound.play();
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
    app.draw(ScoreText);
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }

    app.display();
}

    return 0;
}
