#include "pong.h"

#define BALL_RADIUS 2
#define BALL_SPEED 50
#define BALL_ACCELERATION 2

#define PADDLE_MARGIN 5
#define PADDLE_SPEED 50
#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 20

#define AI_CHASE_RANGE 9
#define AI_VELOCITY_FACTOR 0.9

#define COLLISION_ANGLE_FACTOR 0.6
#define MAX_DELTA 1.0 / 60

Vector2 ball;
double  ball_speed = BALL_SPEED;
Vector2 ball_direction(1, 0);

Vector2 player_paddle;
Vector2 player_paddle_velocity;

Vector2 ai_paddle;
Vector2 ai_paddle_velocity;

Size game_area;

unsigned long current, last;

bool collides(const Vector2& ball, const Vector2& paddle) {
  Vector2 edge(ball);

  if (ball.x < paddle.x)
    edge.x = paddle.x;
  
  else if (ball.x > paddle.x + PADDLE_WIDTH)
    edge.x = paddle.x + PADDLE_WIDTH;

  if (ball.y < paddle.y)
    edge.y = paddle.y;

  else if (ball.y > paddle.y + PADDLE_HEIGHT)
    edge.y = paddle.y + PADDLE_HEIGHT;
  
  Vector2 difference(ball.x - edge.x, ball.y - edge.y);

  return difference.magnitude() <= BALL_RADIUS;
}

double get_collision_angle(double ball_y, double paddle_y) {
  return ((ball_y - paddle_y) / PADDLE_HEIGHT - 0.5) * PI * COLLISION_ANGLE_FACTOR;
}

double map(double value, double in_min, double in_max, double out_min, double out_max) {
  double percentage = (value - in_min) / (in_max - in_min);
  return out_min + (out_max - out_min) * percentage;
}

void Pong::setup(const OLED& oled) {
  uint16_t width = oled.width();
  uint16_t height = oled.height();
  uint16_t paddle_center_y = (height - PADDLE_HEIGHT) / 2;

  ball.set(width / 2, height / 2); 
  game_area.set(width, height);

  player_paddle.set(PADDLE_MARGIN, paddle_center_y);
  ai_paddle.set(width - PADDLE_MARGIN, paddle_center_y);

  last = millis();
}

void update(OLED &oled, bool is_up_pressed, bool is_down_pressed) {
  player_paddle_velocity.y = 0;

  if (is_up_pressed)
    player_paddle_velocity.y -= PADDLE_SPEED;

  if (is_down_pressed)
    player_paddle_velocity.y += PADDLE_SPEED;

  double distance = ball.y - (ai_paddle.y + PADDLE_HEIGHT / 2);

  if (abs(distance) > AI_CHASE_RANGE)
    ai_paddle_velocity.y = AI_VELOCITY_FACTOR * (distance > 0) ? PADDLE_SPEED : -PADDLE_SPEED;
}

void physics_update(OLED& oled, double delta, bool is_up_pressed, bool is_down_pressed) {
  ball.x += ball_direction.x * ball_speed * delta;
  ball.y += ball_direction.y * ball_speed * delta;
  ball.y = clamp(ball.y, BALL_RADIUS, game_area.height - BALL_RADIUS);

  player_paddle.y += player_paddle_velocity.y * delta;
  player_paddle.y = clamp(player_paddle.y, 0, game_area.height - PADDLE_HEIGHT);

  ai_paddle.y += ai_paddle_velocity.y * delta;
  ai_paddle.y = clamp(ai_paddle.y, 0, game_area.height - PADDLE_HEIGHT);

  if ((ball.y - BALL_RADIUS) <= 0 || (ball.y + BALL_RADIUS) >= game_area.height)
    ball_direction.y = -ball_direction.y;

  if (ball.x <= 0)
    Serial.println("LOSER");

  else if (ball.x >= game_area.width)
    Serial.println("WINNER");
  
  else if (collides(ball, player_paddle)) {
    double angle = map(ball.y,
      player_paddle.y, player_paddle.y + PADDLE_HEIGHT, -PI/3, PI/3);
      
    ball_direction.from_angle(angle);
  }

  else if (collides(ball, ai_paddle)) {
    double angle = map(ball.y,
     ai_paddle.y, ai_paddle.y + PADDLE_HEIGHT, PI * 4/3., PI * 2/3.);

    ball_direction.from_angle(angle);
  }

  ball_speed += BALL_ACCELERATION * delta;
}

void Pong::loop(OLED& oled, bool is_up_pressed, bool is_down_pressed) {
  current = millis();
  double frame_time = (current - last) / 1000.0;
  last = current;

  update(oled, is_up_pressed, is_down_pressed);
  
  while (frame_time > 0) {
    double delta = min(frame_time, MAX_DELTA);
    physics_update(oled, delta, is_up_pressed, is_down_pressed);
    frame_time -= delta;
  }

  render(oled);
}

void Pong::render(OLED& oled) {
  oled.clearDisplay();

  oled.fillRect(player_paddle.x, player_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
  oled.fillCircle(ball.x, ball.y, BALL_RADIUS, SH110X_WHITE);
  oled.fillRect(ai_paddle.x, ai_paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, SH110X_WHITE);
  oled.display();
}