#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int LENGHT = 30, HEIGHT = 20;
int S = 16;
int W = S * LENGHT;
int H = S * HEIGHT;

int dir, num = 4;

struct Snake {
    int x, y;
} snake[100];


struct FoodPos {
    int x, y;
} FP;

void Tick(){
    for (int i = num; i>0; --i){
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

    if (dir == 0) snake[0].y += 1;
    if (dir == 1) snake[0].x -= 1;
    if (dir == 2) snake[0].x += 1;
    if (dir == 3) snake[0].y -= 1;

    if ((snake[0].x == FP.x) && (snake[0].y == FP.y)) {
        num ++;
        FP.x = rand() % LENGHT;
        FP.y = rand() % HEIGHT;
    }

    if (snake[0].x > LENGHT) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = LENGHT;
    if (snake[0].y > HEIGHT) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = HEIGHT;

    for (int i = 1; i < num; i++)
     if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)  num = i;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(W, H), "Snake Game!");

    Texture t1,t2,t3;

    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/green.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;
    float timer = 0, delay = 0.1;

    FP.x = 10;
    FP.y = 10;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right))  dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;

        if (timer > delay) {timer = 0; Tick();}

    window.clear();

    for (int i = 0; i < LENGHT; i++)
        for (int j = 0; j < HEIGHT; j++)
            { sprite1.setPosition(i * S, j * S);  window.draw(sprite1); }

    for (int i = 0; i < num; i++)
        { sprite2.setPosition(snake[i].x * S, snake[i].y * S);  window.draw(sprite2); }

    sprite3.setPosition(FP.x * S,  FP.y * S); window.draw(sprite3);

    window.display();
    }
    return 0;
}
