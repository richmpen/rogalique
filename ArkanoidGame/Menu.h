#pragma once
#include "SFML/Graphics.hpp"
#include "Text.h"
#include <list>
#include <functional>


namespace Rogalique
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText;
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Blue;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<MenuItem> childrens;

		std::function<void(MenuItem& item)> onPressCallback;

		MenuItem* parent = nullptr;
	};

	class Menu
	{
	public:
		void Init(const MenuItem& item);

		void Update(float deltaTime);

		void Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);

		void PressOnSelectedItem();
		void GoBack();
		
		void SwitchToPreviousMenuItem();
		void SwitchToNextMenuItem();

		MenuItem& GetCurrentContext();

	private:
		void InitMenuItem(MenuItem& item);
		void SelectMenuItem(MenuItem& item);

	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};
}
