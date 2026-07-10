
#include <chrono>
#include <string>

#include <YOBA/Core.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>

#include "Resources/Images.hpp"
#include "Theme.hpp"

int main() {
	using namespace YOBA;
	using namespace pizda;

	// -------------------------------- SFML window --------------------------------

	constexpr static float renderingScale = 2;
	constexpr static Size resolution { 240, 320 };

	sf::RenderWindow SFWindow {
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

	sf::Font SFFont("C:\\Windows\\Fonts\\arial.ttf");

	// -------------------------------- YOBA renderer & rendering target --------------------------------

	SFMLSpriteRenderingTarget renderingTarget {};
	renderingTarget.setup(resolution, renderingScale);

	RGB888BufferedRenderer renderer {};
	renderer.setTarget(&renderingTarget);

	// -------------------------------- Tons of UI components --------------------------------

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

	TextView textView1 {};
	Theme::applyDescription(&textView1);
	textView1.setWrappingEnabled(true);
	textView1.setText("Following their work on Rogue Trader, Owlcat Games developed a narrative-heavy RPG where players command an Imperial Inquisitor");
	textView1.setTextAlignment(Alignment::center);
	rows += &textView1;

	Button button1 {};
	Theme::applyPrimary(&button1);
	button1.setText("Preorder");

	button1.setOnClick([&seven] {
		seven.setValue(seven.getValue() + 1);
	});

	rows += &button1;

	Divider divider1 {};
	Theme::apply(&divider1);
	rows += &divider1;

	TextField textField {};
	Theme::apply(&textField);
	textField.setPlaceholder("Type something");
	rows += &textField;

	TextView marginSliderTitle {};
	Theme::applyTitle(&marginSliderTitle);
	marginSliderTitle.setText("Margin");
	rows += &marginSliderTitle;

	Slider marginSlider {};
	Theme::apply(&marginSlider);
	marginSlider.setMinimumValue(0);
	marginSlider.setMaximumValue(50);
	marginSlider.setValue(rows.getMargin().getLeft());

	marginSlider.setOnValueChanged([&] {
		rows.setMargin({ static_cast<uint16_t>(marginSlider.getValue()) });
	});

	marginSlider.setTickLabelBuilder(Slider::int32TickLabelBuilder);

	rows += &marginSlider;

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

	WrapLayout imagesWrapLayout {};
	imagesWrapLayout.setGap(10);
	rows += &imagesWrapLayout;

	std::array<const Image*, 29> _images {
		&Images::menuIconADIRS,
		&Images::menuIconAutopilotSettings,
		&Images::menuIconAxes,
		&Images::menuIconDev,
		&Images::menuIconFlightPlan,
		&Images::menuIconMFD,
		&Images::menuIconMFDAutopilot,
		&Images::menuIconMFDAutopilotEngage,
		&Images::menuIconMFDAutopilotFlightDirector,
		&Images::menuIconMFDAutopilotGyro,
		&Images::menuIconMFDBaro,
		&Images::menuIconMFDCamera,
		&Images::menuIconMFDCameraReset,
		&Images::menuIconMFDLights,
		&Images::menuIconMFDLightsCabin,
		&Images::menuIconMFDLightsLanding,
		&Images::menuIconMFDLightsNavigation,
		&Images::menuIconMFDLightsStrobe,
		&Images::menuIconMFDMetricUnits,
		&Images::menuIconMFDND,
		&Images::menuIconMFDPFD,
		&Images::menuIconMFDTrim,
		&Images::menuIconMotors,
		&Images::menuIconPersonalization,
		&Images::menuIconPower,
		&Images::menuIconSpectrumScan,
		&Images::menuIconTransceiver,
		&Images::menuIconWaypoints,
		&Images::menuIconWiFi
	};

	for (auto image : _images) {
		auto imageView = new ImageView {};
		imageView->setImage(image);
		imagesWrapLayout += imageView;
	}

	auto a = new Control();
	a->setHeight(450);
	imagesWrapLayout += a;

	// -------------------------------- Main loop with SFML event handling --------------------------------

	while (SFWindow.isOpen()) {
		while (const auto event = SFWindow.pollEvent()) {
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

				auto view = SFWindow.getView();
				view.setSize(sf::Vector2f(resizedEvent->size));
				view.setCenter(view.getSize() / 2.f);
				SFWindow.setView(view);
			}
			else if (event->is<sf::Event::Closed>()) {
				SFWindow.close();
			}
		}

		// -------------------------------- YOBA UI tick handling & rendering --------------------------------

		auto FPSStart = std::chrono::steady_clock::now();

		application.invalidateRender();
		application.tick();
		application.render();

		auto FPSElapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - FPSStart);

		// -------------------------------- SFML rendering  --------------------------------

		// Rendering FPS counter
		SFWindow.clear(sf::Color::Black);
		SFWindow.draw(renderingTarget.getSprite());

		char FPSText[32];
		std::snprintf(FPSText, sizeof(FPSText), "%lld", 1'000'000 / FPSElapsed.count());

		sf::Text text {
			SFFont,
			FPSText,
			30
		};

		text.setPosition({ 10, 10 });
		text.setStyle(sf::Text::Bold);
		text.setFillColor(sf::Color::Magenta);
		SFWindow.draw(text);

		// Showing all changes in window
		SFWindow.display();
	}
}