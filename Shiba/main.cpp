#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>



using namespace sf;
using namespace std;

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

const int max_main_menu = 3;
const int window_width = 400;
const int window_height = 533;
const int background_width = 400;
const int background_height = 533;
const int character_width = 80;
const int character_height = 80;
const int platform_width = 68;
const int platform_height = 14;
const int button_width = 30;
const int button_height = 18;
const int level[4]= {10,8,6,4};

// Render window
RenderWindow app(VideoMode(window_width, window_height), "Bonk Game!");

// Texture
Texture t1,t2,t3_1,t3_2,t4,t5,menu_bkg,about_bkg;

//Sprite
Sprite sBackground, sPlat, sPers_left, sPers_right, sGameOver, sBonk, menu_background,bkg_about;

// Font
Font font;

//Text
Text Highest_ScoreText,play_again,ScoreText,game_over,final_score,final_highscore,back_to_menu, back_to_menu_about;

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

//check mouse inside text
bool mouse_inside_text (Text spr)
{
    Vector2i mousePos = Mouse::getPosition(app);
    if( mousePos.x > spr.getPosition().x
            && mousePos.x < spr.getPosition().x + spr.getGlobalBounds().width
            && mousePos.y > spr.getPosition().y && mousePos.y < spr.getPosition().y + spr.getGlobalBounds().height
      )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//check mouse inside sprite
bool mouse_inside_sprite(Sprite spr)
{
    Vector2i mousePos = Mouse::getPosition(app);
    if( mousePos.x > spr.getPosition().x
            && mousePos.x < spr.getPosition().x + spr.getGlobalBounds().width
            && mousePos.y > spr.getPosition().y && mousePos.y < spr.getPosition().y + spr.getGlobalBounds().height
      )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// MainMenu
class MainMenu
{
public:
    MainMenu(float width, float height);
    Text get_button(int pos)
    {
        return mainMenu[pos];
    }
    void set_hover(int pos);
    void Default(int pos);
    ~MainMenu();
private:
    Font font_menu;
    Text mainMenu[max_main_menu];
};

MainMenu::MainMenu(float width, float height)
{

    font_menu.loadFromFile("font/al-seana.ttf");
    //Play
    mainMenu[0].setFont(font_menu);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(30);
    mainMenu[0].setFillColor(Color::Black);
    mainMenu[0].setPosition(120,160);
    //About
    mainMenu[1].setFont(font_menu);
    mainMenu[1].setString("About");
    mainMenu[1].setCharacterSize(30);
    mainMenu[1].setFillColor(Color::Black);
    mainMenu[1].setPosition(200,260);
    //Quit
    mainMenu[2].setFont(font_menu);
    mainMenu[2].setString("Quit");
    mainMenu[2].setCharacterSize(30);
    mainMenu[2].setFillColor(Color::Black);
    mainMenu[2].setPosition(300,360);
}

MainMenu::~MainMenu()
{

}
void MainMenu::set_hover(int pos)
{
    mainMenu[pos].setFillColor(Color::Blue);
}
void MainMenu::Default(int pos)
{
    mainMenu[pos].setFillColor(Color::Black);
}
void load_all_img()
{
    t1.loadFromFile("images/background_real.png");
    t2.loadFromFile("images/platform.png");
    t3_1.loadFromFile("images/dog2_left.png");
    t3_2.loadFromFile("images/dog2_right.png");
    t4.loadFromFile("images/GameOver_fix.png");
    t5.loadFromFile("images/bonk_img_resize.jpg");
    menu_bkg.loadFromFile("images/bkg_menu.png");
    about_bkg.loadFromFile("images/bkg_about.png");
}
void sprite_img()
{
    sBackground.setTexture(t1),
    sPlat.setTexture(t2),
    sPers_left.setTexture(t3_1),
    sPers_right.setTexture(t3_2),
    sGameOver.setTexture(t4),
    sBonk.setTexture(t5);
    menu_background.setTexture(menu_bkg);
    bkg_about.setTexture(about_bkg);
}
void load_font()
{
    font.loadFromFile("font/al-seana.ttf");
}
void load_text(Text& text,int Size,Color color,int pos_x,int pos_y,std::string descreption)
{
    text.setFont(font);
    text.setCharacterSize(Size);
    text.setColor(color);
    text.setPosition(pos_x,pos_y);
    text.setString(descreption);
}
void load_all_text()
{
    load_text(ScoreText,30,Color::Black,10,0,std::to_string(Score));
    load_text(Highest_ScoreText,20,Color::White,200,0,std::to_string(Highest_Score));
//    load_text(Restart,30,Color::Black,80,480,"Press F to restart!");
    load_text(game_over,40,Color::Black,120,30,"Game Over!");
    load_text(final_score,30,Color::Black,120,85,"");
    load_text(final_highscore,30,Color::Black,80,130,"");
    load_text(back_to_menu,30,Color::Black,80,450,"Menu");
    load_text(play_again,30,Color::Black,250,450,"Play again!");
    load_text(back_to_menu_about,30,Color::Black,10,0,"Back to menu");
}
void load_sound()
{
    buffer.loadFromFile("sound/jump.wav");
    jump.setBuffer(buffer);
    buffer_1.loadFromFile("sound/bonk.wav");
    bonk.setBuffer(buffer_1);
}
void set_up()
{
    app.setFramerateLimit(60);
    load_all_img();
    sprite_img();
    load_font();
    load_all_text();
    load_sound();
}
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
    N=0;
}
void draw_lose_screen()
{
    app.clear(Color::White);
    app.draw(sBackground);
    app.draw(game_over);
    final_score.setString("Your score: " + std::to_string(Score));
    final_highscore.setString("Your high score: " + std::to_string(Highest_Score));
    app.draw(final_score);
    app.draw(final_highscore);
    sBonk.setPosition(0,180);
    app.draw(sBonk);
    app.draw(back_to_menu);
    app.draw(play_again);
    app.display();
}
void run()
{
    set_start();
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
            if(mouse_inside_text(back_to_menu))
            {
                back_to_menu.setColor(Color::Blue);
                if(Mouse::isButtonPressed(Mouse::Left))
                    return ;
            }
            else back_to_menu.setColor(Color::Black);
            if(mouse_inside_text(play_again))
            {
                play_again.setColor(Color::Blue);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    run();
                    return ;
                }
            }
            else play_again.setColor(Color::Black);
            draw_lose_screen();
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

        //setscore
        if(y==h&&dy<-2.0)
        {
            Score++;
            ScoreText.setString("Score: " + std::to_string(Score));
            if(Score>Highest_Score)
            {
                Highest_Score=Score;
//                Highest_ScoreText.setString("Highest Score: " + std::to_string(Highest_Score));
            }
        }

        //set next y position
        dy+=0.19;
        y+=dy;

        //lose screen
        if (y>window_height)
        {
            Game = false ;
            bonk.play();
            draw_lose_screen();
            continue;
        }

        //fix platform position
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

        //check jump
        for (int i=0; i<level[N]; i++)
            if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
                    && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))
            {
                dy=-10;
                jump.play();
            }
        N = min(3,Score/1000);
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
//        app.draw(Highest_ScoreText);
        app.display();
    }
}
void run_game()
{
    run();
}
void run_about()
{
    while(app.isOpen())
        {
        Event event;
        while(app.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                app.close();
            }
            if(mouse_inside_text(back_to_menu_about))
            {
                back_to_menu_about.setColor(Color::Blue);
                if(Mouse::isButtonPressed(Mouse::Left))
                    return ;
            }
            else back_to_menu_about.setColor(Color::Black);
            app.clear();
            app.draw(bkg_about);
            app.draw(back_to_menu_about);
            app.display();
        }
    }
}
int main()
{
    srand(time(0));
    set_up();
    MainMenu Menu(app.getSize().x,app.getSize().y);
    while(app.isOpen())
    {
        Event event;
        while(app.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                app.close();
            }
            for(int i=0; i<max_main_menu; i++)
            {
                if(mouse_inside_text(Menu.get_button(i)))
                {
                    Menu.set_hover(i);
                    if(Mouse::isButtonPressed(Mouse::Left))
                    {
                        if(i==0)
                            run_game();
                        else if(i==1)
                            run_about();
                        else if(i==2)
                            app.close();
                        break ;
                    }
                }
                else Menu.Default(i);
            }
            app.clear();
            app.draw(menu_background);
            for(int i=0; i<max_main_menu; i++)
            {
                app.draw(Menu.get_button(i));
            }
            app.display();
        }
    }
    return 0;
}
