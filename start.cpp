#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Gravity_Source {
  sf::Vector2f pos;
  float gravity;
  sf::CircleShape circle;

public:
  Gravity_Source(float posX, float posY, float gravity)
      : pos(posX, posY), gravity(gravity) {
    circle.setRadius(16);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::Red);
  }

  void render(sf::RenderWindow &window) { window.draw(circle); }
  sf::Vector2f getpos() const { return pos; }
  float getGravity() const { return gravity; }
};

class Particle {
  sf::Vector2f pos;
  sf::Vector2f velocity;
  sf::CircleShape circle;

public:
  Particle(float posX, float posY, float velX, float velY)
      : pos(posX, posY), velocity(velX, velY) {
    circle.setRadius(5);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::White);
  }

  void update(const Gravity_Source &s) {
    float dx = s.getpos().x - pos.x;
    float dy = s.getpos().y - pos.y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist < 5)
      dist = 5;
    float inv = 1.f / dist;
    float nx = inv * dx;
    float ny = inv * dy;
    float drop = inv * inv;
    float aX = nx * s.getGravity() * drop;
    float aY = ny * s.getGravity() * drop;
    velocity.x += aX;
    velocity.y += aY;
    pos += velocity;
  }

  void render(sf::RenderWindow &window) {
    circle.setPosition(pos);
    window.draw(circle);
  }
};

int main() {
  int modeWidth = 1920, modeHeight = 1080;
  sf::RenderWindow window(sf::VideoMode(modeWidth, modeHeight),
                          "Gravity Orbit Simulation");
  window.setFramerateLimit(60);

  float gravity = 80000.0f;
  int numParticles = 20;
  const float centerX = (int)(modeWidth / 2), centerY = (int)(modeHeight / 2);

  // Font
  sf::Font font;
  if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
    cerr << "Font not found!\n";
    return -1;
  }

  // --- UI Panel ---
  sf::RectangleShape panel(sf::Vector2f(300, 150));
  panel.setPosition(10, 10);
  panel.setFillColor(sf::Color(40, 40, 40, 200));
  panel.setOutlineThickness(2);
  panel.setOutlineColor(sf::Color::White);

  // --- Labels & Text ---
  sf::Text gravityLabel("Gravity Strength:", font, 18);
  gravityLabel.setPosition(20, 25);
  sf::Text gravityText(to_string((int)gravity), font, 18);
  gravityText.setPosition(190, 25);

  sf::Text particleLabel("Num Particles:", font, 18);
  particleLabel.setPosition(20, 70);
  sf::Text particleText(to_string(numParticles), font, 18);
  particleText.setPosition(180, 70);

  sf::Text infoText("Click field & press Enter to apply", font, 14);
  infoText.setPosition(20, 115);

  // --- Input Box Backgrounds ---
  sf::RectangleShape gravityBox(sf::Vector2f(100, 25));
  gravityBox.setPosition(185, 25);
  gravityBox.setFillColor(sf::Color(60, 60, 60));
  gravityBox.setOutlineThickness(2);
  gravityBox.setOutlineColor(sf::Color::White);

  sf::RectangleShape particleBox(sf::Vector2f(100, 25));
  particleBox.setPosition(175, 70);
  particleBox.setFillColor(sf::Color(60, 60, 60));
  particleBox.setOutlineThickness(2);
  particleBox.setOutlineColor(sf::Color::White);

  bool editingGravity = false;
  bool editingParticles = false;

  Gravity_Source src(centerX, centerY, gravity);
  vector<Particle> particles;

  auto createParticles = [&]() {
    particles.clear();
    for (int i = 0; i < numParticles; i++) {
      float angle = i * (360.0f / numParticles) * 3.14159f / 180.f;
      float radius = 100 + rand() % 300;
      float posX = centerX + cos(angle) * radius;
      float posY = centerY + sin(angle) * radius;
      float speed = sqrt(src.getGravity() / radius);
      float velX = -sin(angle) * speed;
      float velY = cos(angle) * speed;
      particles.emplace_back(posX, posY, velX, velY);
    }
  };

  createParticles();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f m(mousePos.x, mousePos.y);

        if (gravityBox.getGlobalBounds().contains(m)) {
          editingGravity = true;
          editingParticles = false;
        } else if (particleBox.getGlobalBounds().contains(m)) {
          editingGravity = false;
          editingParticles = true;
        } else {
          editingGravity = editingParticles = false;
        }
      }

      if (event.type == sf::Event::TextEntered) {
        if (editingGravity) {
          auto str = gravityText.getString();
          if (event.text.unicode == '\b' && str.getSize() > 0)
            str.erase(str.getSize() - 1, 1);
          else if ((event.text.unicode >= '0' && event.text.unicode <= '9') ||
                   event.text.unicode == '.')
            str += static_cast<char>(event.text.unicode);
          gravityText.setString(str);
        } else if (editingParticles) {
          auto str = particleText.getString();
          if (event.text.unicode == '\b' && str.getSize() > 0)
            str.erase(str.getSize() - 1, 1);
          else if (event.text.unicode >= '0' && event.text.unicode <= '9')
            str += static_cast<char>(event.text.unicode);
          particleText.setString(str);
        }
      }

      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        try {
          gravity = stof(gravityText.getString().toAnsiString());
          numParticles = stoi(particleText.getString().toAnsiString());
          src = Gravity_Source(centerX, centerY, gravity);
          createParticles();
        } catch (...) {
          cerr << "Invalid input!\n";
        }
      }
    }

    // --- Highlight active input ---
    gravityBox.setOutlineColor(editingGravity ? sf::Color::Cyan
                                              : sf::Color::White);
    particleBox.setOutlineColor(editingParticles ? sf::Color::Cyan
                                                 : sf::Color::White);

    // --- Draw everything ---
    window.clear(sf::Color::Black);
    src.render(window);
    for (auto &p : particles) {
      p.update(src);
      p.render(window);
    }

    // UI elements
    window.draw(panel);
    window.draw(gravityBox);
    window.draw(particleBox);
    window.draw(gravityLabel);
    window.draw(gravityText);
    window.draw(particleLabel);
    window.draw(particleText);
    window.draw(infoText);

    window.display();
  }
  return 0;
}
