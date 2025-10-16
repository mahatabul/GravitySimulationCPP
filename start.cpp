#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Gravity_Source {

  sf::Vector2f pos;
  float gravity;
  sf::CircleShape circle;

  Gravity_Source(int posX, int posY, float gravity) {
    pos.x = posX;
    pos.y = posY;
    this->gravity = gravity;
    circle.setRadius(4);
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::White);
  }

  void render(sf::RenderWindow &window) { window.draw(circle); }
  sf::Vector2f getpos() { return pos; }
  float getGravity() { return gravity; }
};

class Particle {

  sf::Vector2f pos;
  sf::Vector2f velocity;
  sf::CircleShape circle;

  Particle(int posX, int posY,int velX, int velY) {
    pos.x = posX;
    pos.y = posY;
    velocity.x = velX;
    velocity.y = velY;
    circle.setRadius(4);
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::White);
  }

  void render(sf::RenderWindow &window) { window.draw(circle); }
  void update(const Gravity_Source &s){
    
  }
};


int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Gravity visualize");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }

    window.clear();
    // draw calls
    window.display();
  }

  return 0;
}
