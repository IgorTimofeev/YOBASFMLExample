#include <SFML/Graphics.hpp>

#include <YOBA/Core.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Resources/Fonts/Unscii16Font.hpp>

#include "Theme.hpp"

void resizeWindow(sf::RenderWindow& window, const sf::Vector2u& size) {
	auto view = window.getView();
	view.setSize(sf::Vector2f(size));
	view.setCenter(view.getSize() / 2.f);
	window.setView(view);
}

int main() {
	using namespace YOBA;
	using namespace pizda;

	constexpr static float renderingScale = 2;
	constexpr static Size resolution { 240, 320 };

	sf::ContextSettings contextSettings {
		.antiAliasingLevel = 8
	};

	sf::RenderWindow window {
		sf::VideoMode({
			static_cast<uint32_t>(static_cast<float>(resolution.getWidth()) * renderingScale),
			static_cast<uint32_t>(static_cast<float>(resolution.getHeight()) * renderingScale)
		}),
		"YOBA | Desktop demo",
		sf::Style::None | sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
		sf::State::Windowed,
		contextSettings
	};

	SFMLRenderingTarget renderingTarget {};
	SFMLRenderer renderer {};

	renderingTarget.setup(&window, resolution, renderingScale);
	renderer.setTarget(&renderingTarget);

	Theme::setup();

	Application application {};
	application.setRenderer(&renderer);
	application.setBackgroundColor(&Theme::bg1);

	StackLayout rows {};
	rows.setGap(10);
	rows.setMargin({ 15 });
	application += &rows;

	TextView titleText {};
	Theme::applyPageTitle(&titleText);
	titleText.setText("PFD options");
	rows += &titleText;

	Button button {};
	Theme::applyPrimary(&button);
	button.setText("PULL UP");
	rows += &button;

	TextField textField {};
	Theme::apply(&textField);
	textField.setPlaceholder("Type something");
	rows += &textField;

	TextField numericTextField {};
	Theme::apply(&numericTextField);
	numericTextField.setPlaceholder("123");
	numericTextField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric);
	rows += &numericTextField;

	Slider slider {};
	Theme::apply(&slider);
	slider.setValue(0.5f);
	rows += &slider;

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

				if(mouseEvent->button == sf::Mouse::Button::Left) {
					PointerDownEvent pointerDownEvent {
						Point(
							static_cast<int32_t>(static_cast<float>(mouseEvent->position.x) / renderingTarget.getRenderingScale()),
							static_cast<int32_t>(static_cast<float>(mouseEvent->position.y) / renderingTarget.getRenderingScale())
						)
					};

					application.pushEvent(&pointerDownEvent);
				}
			}
			else if (event->is<sf::Event::MouseButtonReleased>()) {
				auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();

				if(mouseEvent->button == sf::Mouse::Button::Left) {
					PointerUpEvent pointerUpEvent {
						Point(
							static_cast<int32_t>(static_cast<float>(mouseEvent->position.x) / renderingTarget.getRenderingScale()),
							static_cast<int32_t>(static_cast<float>(mouseEvent->position.y) / renderingTarget.getRenderingScale())
						)
					};

					application.pushEvent(&pointerUpEvent);
				}
			}
			else if (event->is<sf::Event::MouseMoved>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				auto mouseEvent = event->getIf<sf::Event::MouseMoved>();

				PointerDragEvent pointerDragEvent {
					Point(
						static_cast<int32_t>(static_cast<float>(mouseEvent->position.x) / renderingTarget.getRenderingScale()),
						static_cast<int32_t>(static_cast<float>(mouseEvent->position.y) / renderingTarget.getRenderingScale())
					)
				};

				application.pushEvent(&pointerDragEvent);
			}
			else if (event->is<sf::Event::Resized>()) {
				auto resizedEvent = event->getIf<sf::Event::Resized>();

				resizeWindow(window, resizedEvent->size);
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		application.invalidateRender();
		application.tick();
		application.render();

		window.display();
	}
}