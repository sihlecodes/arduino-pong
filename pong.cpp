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

#define MIN_SERVE_ANGLE 150
#define MAX_SERVE_ANGLE 210

#define MAX_ALLOWED_PHYSICS_FRAME_DELTA 1.0 / 60

Vector2 ball;
float   ball_speed = BALL_SPEED;
Vector2 ball_direction(1, 0);

Vector2 player_paddle;
Vector2 player_paddle_velocity;

Vector2 ai_paddle;
Vector2 ai_paddle_velocity;

Timer timer(600);

void Pong::setup(OLED& oled) {
  uint16_t width = oled.width();
  uint16_t height = oled.height();
  uint16_t paddle_center_y = (height - PADDLE_HEIGHT) / 2;
  uint16_t ai_paddle_x = width - PADDLE_MARGIN;

  ball.set(ai_paddle_x - BALL_RADIUS * 2, height / 2);
  ball_direction.from_angle(random(MIN_SERVE_ANGLE, MAX_SERVE_ANGLE) * DEG_TO_RAD);

  player_paddle.set(PADDLE_MARGIN, paddle_center_y);
  ai_paddle.set(ai_paddle_x, paddle_center_y);

  // Render a single frame so that the paddles show while
  // the count down is ticking
  Pong::render(oled);
  timer.start();
}

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

float get_collision_angle(float y, float lbound, float min_angle, float max_angle) {
  float variation = random() * 1.0 / RANDOM_MAX - 0.5;
  float ubound = lbound + PADDLE_HEIGHT;

  float target = clamp(y + variation, lbound, ubound);
  float angle = map(target, lbound, ubound, min_angle, max_angle);

  return angle;
}

void update(OLED &oled, bool is_up_pressed, bool is_down_pressed) {
  player_paddle_velocity.y = 0;

  if (is_up_pressed)
    player_paddle_velocity.y -= PADDLE_SPEED;

  if (is_down_pressed)
    player_paddle_velocity.y += PADDLE_SPEED;

  float distance = ball.y - (ai_paddle.y + PADDLE_HEIGHT / 2);

  if (abs(distance) > AI_CHASE_RANGE)
    ai_paddle_velocity.y = AI_VELOCITY_FACTOR * (distance > 0) ? PADDLE_SPEED : -PADDLE_SPEED;
}

void physics_update(OLED& oled, float delta, bool is_up_pressed, bool is_down_pressed) {
  float width = oled.width();
  float height = oled.height();

  ball.x += ball_direction.x * ball_speed * delta;
  ball.y += ball_direction.y * ball_speed * delta;
  ball.y = clamp(ball.y, BALL_RADIUS, height - BALL_RADIUS);

  player_paddle.y += player_paddle_velocity.y * delta;
  player_paddle.y = clamp(player_paddle.y, 0, height - PADDLE_HEIGHT);

  ai_paddle.y += ai_paddle_velocity.y * delta;
  ai_paddle.y = clamp(ai_paddle.y, 0, height - PADDLE_HEIGHT);

  if ((ball.y - BALL_RADIUS) <= 0 || (ball.y + BALL_RADIUS) >= height)
    ball_direction.y = -ball_direction.y;

  if (ball.x <= 0)
    GameOver::declare("LOSER");

  else if (ball.x >= width)
    GameOver::declare("WINNER");

  else if (collides(ball, player_paddle)) {
    float angle = get_collision_angle(ball.y, player_paddle.y, -PI/3, PI/3);
    ball_direction.from_angle(angle);
  }

  else if (collides(ball, ai_paddle)) {
    float angle = get_collision_angle(ball.y, ai_paddle.y, PI * 4/3, PI * 2/3);
    ball_direction.from_angle(angle);
  }

  ball_speed += BALL_ACCELERATION * delta;
}

void Pong::loop(OLED& oled, bool is_up_pressed, bool is_down_pressed) {
  if (GameOver::is_declared()) {
    GameOver::show(oled);
    return;
  }

  update(oled, is_up_pressed, is_down_pressed);

  float frame_time = timer.get_delta() / 1000.0;

  while (frame_time > 0 && !GameOver::is_declared()) {
    float delta = min(frame_time, MAX_ALLOWED_PHYSICS_FRAME_DELTA);
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