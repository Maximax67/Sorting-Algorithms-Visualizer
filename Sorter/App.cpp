#include "App.h"

int App::run() {
	sf::RenderWindow window(sf::VideoMode(1290, 720), "Sorter Program", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	Controller::init();
	Interface::init(window);

	sf::Image icon;
	if (icon.loadFromMemory(&iconImageData, sizeof(iconImageData))) {
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	while (window.isOpen()) {
		sf::Event newEvent;
		while (window.pollEvent(newEvent)) {
			if (newEvent.type == sf::Event::Closed) {
				Interface::destroy();
				window.close();
				return 0;
			}
			Interface::processEvent(newEvent);
		}

		sf::Time diffTime = clock.restart();
		Interface::update(window, diffTime);

		window.clear();

		Interface::draw(window);
		window.display();
	}

	return 0;
}
