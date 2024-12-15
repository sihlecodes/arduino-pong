#include "Arduino.h"
#include <Adafruit_SH110X.h>
#include "pong.h"

#define BALL_RADIUS 2
#define BALL_SPEED 50

#define PADDLE_MARGIN 5
#define PADDLE_SPEED 50
#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 20

Vector2 ball;
Vector2 player_paddle;
Vector2 ai_paddle;

double ball_acceleration = 1;
double ball_speed = 50;

Vector2 ball_direction(1, 0);
Vector2 player_paddle_velocity;

Size pong_area;

unsigned long current, last;
const double maxDelta = 1.0 / 60;

bool has_served;

bool collides(double ball_x, double ball_y, double paddle_x, double paddle_y) {
  return (
    ball_x >= paddle_x &&
    ball_x <= (paddle_x + PADDLE_WIDTH) &&
    ball_y >= paddle_y &&
    ball_y <= (paddle_y + PADDLE_HEIGHT)
  );
}

double get_collision_angle(double ball_y, double paddle_y) {
  return ((ball_y - paddle_y) / PADDLE_HEIGHT - 0.5) * PI/1.5;
}

void end_game() {

}

void declare_loser(OLED& oled) {
  end_game();
  Serial.println("You lose!");
}

void declare_winner(OLED& oled) {
  end_game();
  Serial.println("You win!");
}

void Pong::setup(OLED& oled, uint16_t width, uint16_t height) {
  has_served = false;

  uint16_t center_y = (height - PADDLE_HEIGHT) / 2;

  ball.set(width / 2, height / 2); 
  pong_area.set(width, height);

  player_paddle.set(PADDLE_MARGIN, center_y);
  ai_paddle.set(width - PADDLE_MARGIN, center_y);

  // Serial.print("ball_x: ");
  // Serial.println(ball.x);

  // Serial.print("ball_y: ");
  // Serial.println(ball.y);

  last = millis();
  Pong::render(oled);
}

void update(OLED &oled, bool is_up_pressed, bool is_down_pressed) {
  player_paddle_velocity.y = 0;

  if (is_up_pressed) {
    player_paddle_velocity.y -= PADDLE_SPEED;
    // Serial.print("UP: ");
    // Serial.println(player_paddle_velocity.y);
  }

  if (is_down_pressed) {
    player_paddle_velocity.y += PADDLE_SPEED;
    // Serial.print("DOWN: ");
    // Serial.println(player_paddle_velocity.y);
  }
}

void physics_update(OLED& oled, double delta, bool is_up_pressed, bool is_down_pressed) {
  ball.x += ball_direction.x * ball_speed * delta;
  ball.y += ball_direction.y * ball_speed * delta;

  if ((ball.y - BALL_RADIUS) <= 0 || (ball.y + BALL_RADIUS) >= pong_area.height)
      ball_direction.y = -ball_direction.y;

  player_paddle.y += player_paddle_velocity.y * delta;

  if (ball.x + BALL_RADIUS <= 0) {
    declare_loser(oled);
    return;
  }

  else if (ball.x + BALL_RADIUS >= pong_area.width) {
    declare_winner(oled);
    return;
  }
  
  else if (collides(ball.x - BALL_RADIUS, ball.y - BALL_RADIUS, player_paddle.x, player_paddle.y)) {
    ball_direction.from_angle(get_collision_angle(ball.y, player_paddle.y));
    return;
  }

  else if (collides(ball.x + BALL_RADIUS, ball.y + BALL_RADIUS, ai_paddle.x,  ai_paddle.y)) {
    ball_direction.from_angle(get_collision_angle(ball.y, ai_paddle.y));
    ball_direction.x = -ball_direction.x;
    return;
  }

  ball_speed += ball_acceleration * delta;
}

void Pong::loop(OLED& oled, bool is_up_pressed, bool is_down_pressed) {
  current = millis();
  double frameTime = (current - last) / 1000.0;
  last = current;

  update(oled, is_up_pressed, is_down_pressed);
  
  while (frameTime > 0) {
    double delta = min(frameTime, maxDelta);

    physics_update(oled, delta, is_up_pressed, is_down_pressed);

    frameTime -= delta;
  }

  render(oled);
}

void Pong::render(OLED& oled) {
  oled.clearDisplay();
  
  oled.fillCircle(ball.x, ball.y, BALL_RADIUS, SH110X_WHITE);
  oled.fillRect(ai_paddle.x, ai_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
  oled.fillRect(player_paddle.x, player_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
  oled.display();
}