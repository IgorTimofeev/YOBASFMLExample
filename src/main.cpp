#include <SFML/Graphics.hpp>

#include <YOBA/Core.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Resources/Fonts/Unscii16Font.hpp>

#include "MenuIconAutopilotSettingsImage.hpp"
#include "Theme.hpp"

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

	SFMLWindowRenderingTarget renderingTarget {};
	RGB888BufferedRenderer renderer {};

	renderingTarget.setup(&window, resolution, renderingScale);
	renderer.setTarget(&renderingTarget);

	Theme::setup();

	Application application {};
	application.setRenderer(&renderer);
	application.setBackgroundColor(&Theme::bg1);

	ScrollView scrollView {};
	Theme::apply(&scrollView);
	application += &scrollView;

	StackLayout rows {};
	rows.setGap(10);
	rows.setMargin({ 15 });
	scrollView += &rows;

	TextView titleText {};
	Theme::applyPageTitle(&titleText);
	titleText.setHorizontalAlignment(Alignment::center);
	titleText.setText("Heresy counter");
	rows += &titleText;

	SevenSegment seven {};
	seven.setActiveColor(&Theme::fg1);
	seven.setInactiveColor(&Theme::bg4);
	seven.setSegmentThickness(3);
	seven.setSegmentLength(10);
	seven.setDigitCount(4);
	seven.setHorizontalAlignment(Alignment::center);
	rows += &seven;

	TextView descriptionText {};
	Theme::applyDescription(&descriptionText);
	descriptionText.setWrappingEnabled(true);
	descriptionText.setText("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966");
	rows += &descriptionText;

	Button button {};
	Theme::applyPrimary(&button);
	button.setText("PULL UP");

	button.setOnClick([&seven] {
		seven.setValue(seven.getValue() + 1);
	});

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

	RelativeStackLayout switchRow {};
	switchRow.setOrientation(Orientation::horizontal);
	rows += &switchRow;

	TextView switchRowText {};
	Theme::apply(&switchRowText);
	switchRowText.setVerticalAlignment(Alignment::center);
	switchRowText.setText("Pimpo4ka");
	switchRow += &switchRowText;

	Switch switchRowSw {};
	Theme::apply(&switchRowSw);
	switchRowSw.setVerticalAlignment(Alignment::center);
	switchRow += &switchRowSw;
	switchRow.setAutoSize(&switchRowSw);

	MenuIconAutopilotSettingsImage img {};
	ImageView imageView {};
	imageView.setImage(&img);
	rows += &imageView;

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

				if (mouseEvent->button == sf::Mouse::Button::Left) {
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

				if (mouseEvent->button == sf::Mouse::Button::Left) {
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

				auto view = window.getView();
				view.setSize(sf::Vector2f(resizedEvent->size));
				view.setCenter(view.getSize() / 2.f);
				window.setView(view);
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		// renderer.clear(&Theme::fg1);
		// renderer.renderFilledRectangle({ 0, 0, 100, 50 }, &Theme::magenta1);
		// renderer.flush();

		application.invalidateRender();
		application.tick();
		application.render();

		window.display();
	}
}