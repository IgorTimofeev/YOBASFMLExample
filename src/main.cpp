
#include <chrono>
#include <string>
#include <functional>

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

	MarginLayout rowsMarginLayout {{ 15 }};
	scrollView += &rowsMarginLayout;

	StackLayout rows {};
	rows.setGap(10);
	rowsMarginLayout += &rows;

	const auto addTitle1 = [&rows](const std::string_view text) -> TextView* {
		const auto textView = new TextView {};
		Theme::applyPageTitle(textView);
		textView->setText(text);

		rows += textView;

		return textView;
	};

	const auto addTitle2 = [&rows](const std::string_view text) -> TextView* {
		const auto marginLayout = new MarginLayout {{ 0, 0, 0, -5 }};
		rows += marginLayout;

		const auto textView = new TextView {};
		Theme::applyTitle(textView);
		textView->setText(text);
		*marginLayout += textView;

		return textView;
	};

	const auto addDivider = [&rows]() -> Divider* {
		const auto divider1 = new Divider {};
		Theme::apply(divider1);

		rows += divider1;

		return divider1;
	};

	const auto addButton = [&rows](const std::string_view text, const std::function<void()>& onClick) -> Button* {
		const auto button = new Button {};
		Theme::applyPrimary(button);
		button->setText(text);
		button->setOnClick(onClick);

		rows += button;

		return button;
	};

	addTitle1("Heresy counter")->setHorizontalAlignment(Alignment::center);

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

	addButton("Preorder", [&seven] {
		seven.setValue(seven.getValue() + 1);
	});

	// -------------------------------- Badges --------------------------------

	addDivider();
	addTitle1("Badges");

	RelativeStackLayout badgesStackLayout {
		Orientation::horizontal,
		10
	};

	rows += &badgesStackLayout;

	const auto addImageWithBadge = [&badgesStackLayout](const Image* image, const std::string_view badgeText) {
		const auto imageAndBadgeLayout = new Layout {};
		imageAndBadgeLayout->setHorizontalAlignment(Alignment::start);
		badgesStackLayout += imageAndBadgeLayout;

		const auto imageView = new ImageView { image };
		*imageAndBadgeLayout += imageView;

		const auto marginLayout = new MarginLayout {{ 0, -3, -3, 0 }};
		*imageAndBadgeLayout += marginLayout;

		const auto badge = new Badge {};
		Theme::apply(badge);
		badge->setAlignment(Alignment::end, Alignment::start);
		badge->setText(badgeText);
		*marginLayout += badge;
	};

	addImageWithBadge(&Images::menuIconDev, "1");
	addImageWithBadge(&Images::menuIconMFD, "2");
	addImageWithBadge(&Images::menuIconMFDAutopilot, "3");
	addImageWithBadge(&Images::menuIconPersonalization, "4");

	// -------------------------------- Switches --------------------------------

	addDivider();
	addTitle1("Switches");

	const auto addTextAndSwitch = [&rows](const std::string_view text, const Color* switchColor, const bool isActive) -> Switch* {
		const auto textAndSwitchLayout = new RelativeStackLayout {
			Orientation::horizontal,
			10
		};

		rows += textAndSwitchLayout;

		const auto textView = new TextView {};
		Theme::applyDescription(textView);
		textView->setVerticalAlignment(Alignment::center);
		textView->setText(text);
		*textAndSwitchLayout += textView;

		const auto sw = new Switch {};
		Theme::apply(sw);
		sw->setVerticalAlignment(Alignment::center);
		sw->setCheckedColor(switchColor);
		sw->setActive(isActive);
		textAndSwitchLayout->setAutoSize(sw);
		*textAndSwitchLayout += sw;

		return sw;
	};

	const auto darkThemeSwitch = addTextAndSwitch("Dark theme", &Theme::accent1, true);

	darkThemeSwitch->setOnIsActiveChanged([&darkThemeSwitch] {
		Theme::setColorScheme(darkThemeSwitch->isActive());
	});

	addTextAndSwitch("Large penis", &Theme::sky1, true);

	// -------------------------------- Sliders --------------------------------

	addDivider();
	const auto slidersTitle = addTitle1("Sliders");

	const auto addSlider = [&rows]() -> Slider* {
		const auto slider = new Slider {};

		Theme::apply(slider);
		slider->setTickLabelBuilder(Slider::int32TickLabelBuilder);

		rows += slider;

		return slider;
	};

	addTitle2("Page padding");

	const auto pagePaddingSlider = addSlider();
	pagePaddingSlider->setMinimumValue(0);
	pagePaddingSlider->setMaximumValue(50);
	pagePaddingSlider->setValue(rowsMarginLayout.getMargin().getLeft());

	pagePaddingSlider->setOnValueChanged([&rowsMarginLayout, pagePaddingSlider] {
		rowsMarginLayout.setMargin({
			static_cast<uint16_t>(pagePaddingSlider->getValue())
		});
	});

	addTitle2("Title scale");

	const auto titleScaleSlider = addSlider();
	titleScaleSlider->setFillColor(&Theme::sky1);
	titleScaleSlider->setMinimumValue(1);
	titleScaleSlider->setMaximumValue(10);
	titleScaleSlider->setValue(slidersTitle->getFontScale());

	titleScaleSlider->setOnValueChanged([&slidersTitle, titleScaleSlider] {
		slidersTitle->setFontScale(static_cast<uint8_t>(titleScaleSlider->getValue()));
	});

	// -------------------------------- Text fields --------------------------------


	addDivider();
	addTitle1("Text fields");

	addTitle2("Regular");

	TextField textField1 {};
	Theme::apply(&textField1);
	textField1.setPlaceholder("Abc");
	rows += &textField1;

	addTitle2("Numeric");

	TextField textField2 {};
	Theme::apply(&textField2);
	textField2.setPlaceholder("123");
	textField2.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);
	rows += &textField2;

	// -------------------------------- Animations --------------------------------

	addDivider();
	addTitle1("Animations");

	ProgressBar progressBar {};
	Theme::apply(&progressBar);
	progressBar.setFillColor(&Theme::bad1);
	progressBar.setValue(0);
	rows += &progressBar;

	TextView progressText {};
	Theme::applyDescription(&progressText);
	progressText.setAlignment(Alignment::center);
	rows += &progressText;

	const auto updateProgressText = [&progressText, &progressBar] {
		char textBuffer[32];

		std::snprintf(
			textBuffer,
			sizeof(textBuffer),
			"Casino depo pumped out at %d%%",
			static_cast<uint8_t>(progressBar.getValue() * 100)
		);

		progressText.setText(textBuffer);
	};

	updateProgressText();

	FloatAnimation progressAnimation {};
	progressAnimation.setFrom(0);
	progressAnimation.setTo(1);
	progressAnimation.setDuration(3'000'000);

	progressAnimation.setOnTick([&progressBar, &progressAnimation, &updateProgressText] {
		progressBar.setValue(progressAnimation.getProgress());

		updateProgressText();
	});

	addButton("Hack", [&progressAnimation] {
		progressAnimation.stop();
		progressAnimation.start();
	});

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

		// -------------------------------- YOBA tick handling & rendering --------------------------------

		const auto FPSMeasurementStart = std::chrono::steady_clock::now();

		application.invalidate();
		application.tick();
		application.render();

		const auto FPSMeasurementDurationUs =
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - FPSMeasurementStart)
			.count();

		// -------------------------------- SFML rendering  --------------------------------

		// Rendering FPS counter
		SFWindow.clear(sf::Color::Black);
		SFWindow.draw(renderingTarget.getSprite());

		char FPSTextBuffer[32];
		std::snprintf(FPSTextBuffer, sizeof(FPSTextBuffer), "%lld FPS", 1'000'000 / FPSMeasurementDurationUs);

		sf::Text FPSText {
			SFFont,
			FPSTextBuffer,
			15
		};

		FPSText.setPosition({ 10, 10 });
		FPSText.setStyle(sf::Text::Bold);
		FPSText.setFillColor(sf::Color::Magenta);
		SFWindow.draw(FPSText);

		// Showing all changes in window
		SFWindow.display();
	}
}
