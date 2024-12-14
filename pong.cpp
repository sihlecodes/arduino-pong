#include <Adafruit_SH110X.h>
#include "pong.h"

#define BALL_RADIUS 2

Vector2 ball;
Vector2 player_paddle(5, 10);
Vector2 ai_paddle;

Vector2 ball_velocity(30, 30); 
Vector2 player_paddle_velocity;

Size pong_area;

unsigned long current, last;
const double maxDt = 1.0 / 60;

void Pong::start(OLED& oled, uint16_t width, uint16_t height) {
  ball.set(width / 2, height / 2); 
  pong_area.set(width, height - 4);
  ai_paddle.set(width - 5, 15);

  Serial.print("ball_x: ");
  Serial.println(ball.x);

  Serial.print("ball_y: ");
  Serial.println(ball.y);

  Serial.println("End start!");

  last = millis();
  Pong::render(oled);
}

void Pong::render_ui(OLED& oled) {
  oled.drawLine(0, pong_area.height, pong_area.width, pong_area.height, SH110X_WHITE);
  // oled.drawLine
}

void Pong::update(OLED& oled, bool is_up_pressed, bool is_down_pressed) {
  current = millis();
  double frameTime = (current - last) / 1000.0;
  last = current;

  player_paddle_velocity.y = 0;

  #define PADDLE_SPEED 5
  #define PADDLE_WIDTH 2
  #define PADDLE_HEIGHT 20

  if (is_up_pressed) {
    player_paddle_velocity.y -= PADDLE_SPEED;
    Serial.print("UP: ");
    Serial.println(player_paddle_velocity.y);
  }

  if (is_down_pressed) {
    player_paddle_velocity.y += PADDLE_SPEED;
    Serial.print("DOWN: ");
    Serial.println(player_paddle_velocity.y);
  }
  
  while (frameTime > 0) {
    double delta = min(frameTime, maxDt);

    ball.x += ball_velocity.x * delta;
    ball.y += ball_velocity.y * delta;

    if ((ball.x + BALL_RADIUS) <= 0 || (ball.x + BALL_RADIUS) >= pong_area.width) {
      ball_velocity.x = -ball_velocity.x;
    }
    
    else if ((ball.x - BALL_RADIUS) <= player_paddle.x &&
         ball.y >= player_paddle.y &&
         ball.y <= player_paddle.y + PADDLE_HEIGHT) {
      ball_velocity.x = -ball_velocity.x;
    }
    
    frameTime -= delta;
  }

  Serial.print("ball_x: ");
  Serial.println(ball.x);

  Serial.print("ball_y: ");
  Serial.println(ball.y);

  // if ((ball.x - BALL_RADIUS) < 0) {
  //   ball.set(pong_area.width / 2, pong_area.height / 2);
  //   Serial.println(ball.x);
  //   oled.setCursor(50, 5);
  //   oled.print("Game over!");
  //   oled.display();
  //   delay(2000);
  //   return;
  // }

  if ((ball.y - BALL_RADIUS) <= 0 || (ball.y + BALL_RADIUS) >= pong_area.height)
    ball_velocity.y = -ball_velocity.y;

  player_paddle.y += player_paddle_velocity.y;
}

void Pong::render(OLED& oled) {
  oled.clearDisplay();
  
  oled.fillCircle(ball.x, ball.y, BALL_RADIUS, SH110X_WHITE);
  oled.fillRect(ai_paddle.x, ai_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
  oled.fillRect(player_paddle.x, player_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
}