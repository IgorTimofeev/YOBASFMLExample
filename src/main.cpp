
#include <YOBA/Core.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>

#include "Resources/SelectedAirspeedImage.hpp"
#include "Resources/NavDisplayImage.hpp"
#include "Theme.hpp"

int main() {
	using namespace YOBA;
	using namespace pizda;

	constexpr static float renderingScale = 2;
	constexpr static Size resolution { 240, 320 };

	sf::RenderWindow window {
		sf::VideoMode({
			static_cast<uint32_t>(static_cast<float>(resolution.getWidth()) * renderingScale),
			static_cast<uint32_t>(static_cast<float>(resolution.getHeight()) * renderingScale)
		}),
		"YOBA | Desktop demo",
		sf::Style::None | sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
		sf::State::Windowed,
		sf::ContextSettings {
			.antiAliasingLevel = 8
		}
	};

	SFMLSpriteRenderingTarget renderingTarget {};
	renderingTarget.setup(resolution, renderingScale);

	RGB888BufferedRenderer renderer {};
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

	TextView titleTextView {};
	Theme::applyPageTitle(&titleTextView);
	titleTextView.setHorizontalAlignment(Alignment::center);
	titleTextView.setText("Heresy counter");
	rows += &titleTextView;

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

	Slider slider {};
	Theme::apply(&slider);
	slider.setValue(0.5f);
	rows += &slider;

	ProgressBar progressBar {};
	Theme::apply(&progressBar);
	progressBar.setFillColor(&Theme::sky1);
	progressBar.setValue(0.75f);
	rows += &progressBar;

	RelativeStackLayout switchRow {};
	switchRow.setOrientation(Orientation::horizontal);
	rows += &switchRow;

	TextView switchRowText {};
	Theme::apply(&switchRowText);
	switchRowText.setVerticalAlignment(Alignment::center);
	switchRowText.setText("Razyob mode");
	switchRow += &switchRowText;

	Switch switchRowSw {};
	Theme::apply(&switchRowSw);
	switchRowSw.setVerticalAlignment(Alignment::center);
	switchRow += &switchRowSw;
	switchRow.setAutoSize(&switchRowSw);

	StackLayout imagesRow {};
	imagesRow.setOrientation(Orientation::horizontal);
	imagesRow.setGap(10);
	rows += &imagesRow;

	SelectedAirspeedImage image1 {};
	ImageView imageView1 {};
	imageView1.setImage(&image1);
	imagesRow += &imageView1;

	NavDisplayImage image2 {};
	ImageView imageView2 {};
	imageView2.setImage(&image2);
	imagesRow += &imageView2;

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				const auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

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
				const auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();

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
				const auto mouseEvent = event->getIf<sf::Event::MouseMoved>();

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

		application.invalidateRender();
		application.tick();
		application.render();

		window.clear(sf::Color::Black);
		window.draw(renderingTarget.getSprite());
		window.display();
	}
}