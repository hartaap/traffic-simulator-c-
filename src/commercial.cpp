#include "commercial.hpp"

Commercial::Commercial(const std::string& buildingName,
                       const std::pair<int, int>& location,
                       const std::string& type)
    : Building(buildingName, location, type), type_(type) {
  std::string lowertype = type;
  // Compare two strings in a case-insensitive manner
  std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (lowertype == "gym") {
    maxPersonCapacity_ = 25;
    maxCarCapacity_ = 10;
  } else if (lowertype == "restaurant") {
    maxPersonCapacity_ = 30;
    maxCarCapacity_ = 8;
  } else if (lowertype == "shop") {
    maxPersonCapacity_ = 35;
    maxCarCapacity_ = 30;
  } else {
    throw std::invalid_argument("Invalid type");
  }
}

void Commercial::Draw(sf::RenderWindow& window, int cellSize){

  sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
  int x = location_.first;
  int y = location_.second;

  if (type_ == "Shop") {
    
    cellShape.setFillColor(sf::Color(255, 200, 100)); 
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(2.0f); 
    cellShape.setPosition(x * cellSize, y * cellSize);

  
    window.draw(cellShape);

    sf::Font font;
    if (!font.loadFromFile("details/Silkscreen/Silkscreen-Bold.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

   
    sf::Text labelText("Shop", font, 14);
    labelText.setPosition((x) * cellSize, (y) * cellSize);
    labelText.setFillColor(sf::Color::Black);
    window.draw(labelText);

    sf::Texture shopTexture;
    if (!shopTexture.loadFromFile("details/shop.png")) {
      
        std::cerr << "Failed to load shop image." << std::endl;
        return;
    }

    sf::Sprite shopSprite(shopTexture);
    shopSprite.setScale(0.12f, 0.12f);
    shopSprite.setPosition((x) * cellSize+10, (y - 0.5f) * cellSize + 43); 
    window.draw(shopSprite);

    

  } else if (type_ == "Gym") {
   
    cellShape.setFillColor(sf::Color(0, 255, 255)); 
    cellShape.setPosition(x * cellSize, y * cellSize);

    window.draw(cellShape);
  
    sf::Font font;
    if (!font.loadFromFile("details/Silkscreen/Silkscreen-Bold.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }
    sf::Text labelText("Gym", font, 11);
    labelText.setPosition(((x) * cellSize)+8, (y) * cellSize+1);
    labelText.setFillColor(sf::Color::Black);
    window.draw(labelText);

    sf::Texture gymTexture;
    if (!gymTexture.loadFromFile("details/gym.png")) {
        std::cerr << "Failed to load gym image." << std::endl;
        return;
    }

    sf::Sprite gymSprite(gymTexture);
    gymSprite.setScale(0.25f, 0.25f);
    gymSprite.setPosition((x) * cellSize+4, (y - 0.5f) * cellSize + 40); 
    window.draw(gymSprite);


  } else if (type_ == "Restaurant") {
    
    
    cellShape.setFillColor(sf::Color(200, 100, 100));
    cellShape.setOutlineColor(sf::Color::Black); 
    cellShape.setOutlineThickness(2.0f); 
    cellShape.setPosition(x * cellSize, y * cellSize);

  
    window.draw(cellShape);

    
    sf::Font font;
    if (!font.loadFromFile("details/Silkscreen/Silkscreen-Bold.ttf")) {
      
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

 
    sf::Text labelText("Restaurant", font, 6);
    labelText.setPosition(((x) * cellSize)-1, (y) * cellSize); 
    labelText.setFillColor(sf::Color::Black);
    window.draw(labelText);

    
    sf::Texture pizzaTexture;
    if (!pizzaTexture.loadFromFile("details/restaurant.png")) {
        std::cerr << "Failed to load pizza image." << std::endl;
        return;
    }

    sf::Sprite pizzaSprite(pizzaTexture);
    pizzaSprite.setScale(0.17f,0.17f);
    pizzaSprite.setPosition((x) * cellSize, (y - 0.5f) * cellSize + 31);
    window.draw(pizzaSprite);

  }
}
 
std::string Commercial::GetType() const {
    std::string lowertype = type_;
    // Compare two strings in a case-insensitive manner again
    std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(),
                  [](unsigned char c) { return std::tolower(c); });

    if (lowertype == "gym") {
      return "Gym";
    } else if (lowertype == "restaurant") {
      return "Restaurant";
    } else {
      return "Shop";
    }
}

  


