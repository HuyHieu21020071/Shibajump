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
{
    int x,y;
};

const int window_width = 400;
const int window_height = 533;
const int background_width = 400;
const int background_height = 533;
const int character_width = 80;
const int character_height = 80;
const int platform_width = 68;
const int platform_height = 14;
const int level[4]= {10,8,6,4};

// Render window
RenderWindow app(VideoMode(window_width, window_height), "Bonk Game!");

// Texture
Texture t1,t2,t3_1,t3_2,t4,t5;

//Sprite
Sprite sBackground, sPlat, sPers_left, sPers_right, sGameOver, sBonk;
// Font
Font font;

//Text
Text Highest_ScoreText, Restart, ScoreText;

//Sound
SoundBuffer buffer,buffer_1;
Sound jump,bonk;

//level
int N = 0;

//Score
int Score=0, Highest_Score=0;

//Character_position
int x,y,h;

//Platform_position
point plat[20];

//Game_condition
bool Game,first,isRight;

//Velocity
float dy;

void set_start()
{
    Game=true;
    first=true;
    for(int i=0; i<level[N]; i++)
    {
        plat[i].x=rand()%(background_width-platform_width);
        plat[i].y=rand()%(background_height);
    }
    plat[0].y=300;
    plat[0].x=100;
    x=100,y=200,h=200;
    dy=0;
    Score=0;
    isRight = true;
}
void run()
{
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
                set_start();
            }
            continue;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            isRight = true;
            x+=3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            isRight = false;
            x-=3;
        }
        if (x>background_width)
            x=0;
        if (x<-40)
            x=background_width-character_width;
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
        if (y>window_height)
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
            for (int i=0; i<level[N]; i++)
            {
                y=h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>background_height)
                {
                    plat[i].y=0;
                    plat[i].x=rand()%(background_width-platform_width);
                }
            }

        for (int i=0; i<level[N]; i++)
            if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
                    && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))
            {
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
        for (int i=0; i<level[N]; i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            app.draw(sPlat);
        }
        app.draw(ScoreText);
        app.draw(Highest_ScoreText);
        app.display();
    }
}

int main()
{
    srand(time(0));
    app.setFramerateLimit(60);
    t1.loadFromFile("images/background2.jpg");
    t2.loadFromFile("images/platform.png");
    t3_1.loadFromFile("images/dog2_left.png");
    t3_2.loadFromFile("images/dog2_right.png");
    t4.loadFromFile("images/GameOver_fix.png");
    t5.loadFromFile("images/bonk_img_resize.jpg");

    sBackground.setTexture(t1),
    sPlat.setTexture(t2),
    sPers_left.setTexture(t3_1),
    sPers_right.setTexture(t3_2),
    sGameOver.setTexture(t4),
    sBonk.setTexture(t5);

    font.loadFromFile("font/arial.ttf");

    ScoreText.setFont(font);
    ScoreText.setCharacterSize(20);
    ScoreText.setFillColor(Color::Red);


    Highest_ScoreText.setFont(font);
    Highest_ScoreText.setCharacterSize(20);
    Highest_ScoreText.setFillColor(Color::Red);
    Highest_ScoreText.setPosition (200,0);

    Restart.setFont(font);
    Restart.setCharacterSize(30);
    Restart.setFillColor(Color::Black);
    Restart.setString("Press F to restart!");
    Restart.setPosition(80,480);

    buffer.loadFromFile("sound/jump.wav");

    jump.setBuffer(buffer);

    buffer_1.loadFromFile("sound/bonk.wav");

    bonk.setBuffer(buffer_1);

    set_start();
    run();
    return 0;
}
