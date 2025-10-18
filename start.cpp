#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace std;
class Gravity_Source {

  sf::Vector2f pos;
  float gravity;
  sf::CircleShape circle;

public:
  Gravity_Source(int posX, int posY, float gravity) {
    pos.x = posX;
    pos.y = posY;
    this->gravity = gravity;
    circle.setRadius(16);
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::Red);
  }

  void render(sf::RenderWindow &window) { window.draw(circle); }
  sf::Vector2f getpos() { return pos; }
  float getGravity() { return gravity; }
};

class Particle {

  sf::Vector2f pos;
  sf::Vector2f velocity;
  sf::CircleShape circle;

public:
  Particle(int posX, int posY, int velX, int velY) {
    pos.x = posX;
    pos.y = posY;
    velocity.x = velX;
    velocity.y = velY;
    circle.setRadius(7);
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::White);
  }

  void render(sf::RenderWindow &window) {
    circle.setPosition(pos);
    window.draw(circle);
  }

  void update(Gravity_Source &s) {
    float distanceX = s.getpos().x - pos.x;
    float distanceY = s.getpos().y - pos.y;

    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    float inv_distance = 1.f / distance;
    float normalizedX = inv_distance * distanceX;
    float normalizedY = inv_distance * distanceY;

    float dropOFF = inv_distance * inv_distance;
    float accelerateX = normalizedX * s.getGravity() * dropOFF;
    float accelerateY = normalizedY * s.getGravity() * dropOFF;

    velocity.x += accelerateX;
    velocity.y += accelerateY;

    pos.x += velocity.x;
    pos.y += velocity.y;
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gravity Orbit Simulation");
  window.setFramerateLimit(60);
  int screenX = 950,screenY = 540;
  Gravity_Source src(screenX, screenY, 80000.0f);

  vector<Particle> particles;

  for (int i = 0; i < 20; i++) {
    float angle = i * (360.0f / 10) * 3.14159f / 180.f; 
    float radius = 100 + rand() % 300;             
    float posX = screenX + cos(angle) * radius;
    float posY = screenY + sin(angle) * radius;

   
    float speed = sqrt(src.getGravity() / radius);

  
    float velX = -sin(angle) * speed * (0.8f + (rand() % 40) / 100.f);
    float velY = cos(angle) * speed * (0.8f + (rand() % 40) / 100.f);

    particles.emplace_back(posX, posY, velX, velY);
  }


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }

    

    window.clear(sf::Color::Black);
    src.render(window);

    for (auto &p : particles) {
      p.update(src);
      p.render(window);
    }

    window.display();
  }

  return 0;
}
