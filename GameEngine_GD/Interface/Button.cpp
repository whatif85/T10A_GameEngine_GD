#include "Button.h"

Button::Button() {}

Button::Button(sf::Vector2f size, sf::Color color, std::string text)
{
    bPressed = false;
    bReleased = false;
    bClicked = false;
    bHighlighted = false;

    defaultColor = sf::Color(color);
    highlightedColor = sf::Color(defaultColor.r + 50, defaultColor.g + 50, defaultColor.b + 50, 255);
    // TODO: What happens if the default color is 50 less than max
    // std::min()

    buttonBG.setSize(size);
    buttonBG.setFillColor(defaultColor);
    buttonBG.setPosition(sf::Vector2f(0, 0));

    buttonText.setCharacterSize(12);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(sf::Vector2f(0, 0));
    buttonText.setString(text);
}

Button::~Button() {}

bool Button::IsHighlighted()
{
    return this->bHighlighted;
}

void Button::Highlight(sf::RenderWindow* window)
{
    bHighlighted = buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

    // this->buttonBG.setFillColor(this->bHighlighted ? sf::Color(this->highlightedColor) : sf::Color(this->defaultColor));

    if (bHighlighted == true)
    {
        buttonBG.setFillColor(sf::Color(highlightedColor));
    }
    else
    {
        buttonBG.setFillColor(sf::Color(defaultColor));
    }
}

void Button::Update(sf::Event event, float deltaTime)
{
    CheckPressed(event);
}

void Button::Render(sf::RenderWindow* window, float deltaTime)
{
    window->draw(buttonBG);
    window->draw(buttonText);
    window->display();
}

void Button::CheckPressed(sf::Event event)
{
    if (this->bHighlighted == true)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            this->bPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (this->bPressed == false)
            {
                this->bClicked = false;
            }
        }

        if (this->bPressed == true)
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                this->bReleased = true;
                this->bClicked = true;
            }
        }
        else
        {
            this->bReleased = false;
            this->bClicked = false;
        }
    }
}
