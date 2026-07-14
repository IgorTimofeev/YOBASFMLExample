
#include <chrono>
#include <string>
#include <functional>
#include <cmath>

#include <YOBA/Core.hpp>
#include <YOBA/Rendering.hpp>
#include <YOBA/UI.hpp>

#include "Resources/Images.hpp"
#include "Theme.hpp"

int main() {
	using namespace YOBA;
	using namespace pizda;

	// -------------------------------- SFML window --------------------------------

	constexpr static float virtualScreenRenderingScale = 2;
	constexpr static Size virtualScreenResolution { 240, 320 };

	sf::RenderWindow SFWindow {
		sf::VideoMode({
			static_cast<uint32_t>(static_cast<float>(virtualScreenResolution.getWidth()) * virtualScreenRenderingScale),
			static_cast<uint32_t>(static_cast<float>(virtualScreenResolution.getHeight()) * virtualScreenRenderingScale)
		}),
		"YOBA | Desktop demo",
		sf::Style::None | sf::Style::Titlebar | sf::Style::Close,
		sf::State::Windowed,
		sf::ContextSettings {
			.antiAliasingLevel = 4
		}
	};

	SFWindow.setFramerateLimit(60);

	sf::Font SFFont("C:\\Windows\\Fonts\\arial.ttf");

	// -------------------------------- YOBA renderer & rendering target --------------------------------

	SFMLSpriteRenderingTarget renderingTarget {};
	renderingTarget.setup(virtualScreenResolution, virtualScreenRenderingScale);

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
	scrollView += &rows;

	MarginTransform rowsTransform {{ 15 }};
	rows.setLayoutTransform(&rowsTransform);

	const auto addPageTitle = [&rows](const std::string_view text) -> TextView* {
		const auto textView = new TextView {};
		Theme::applyPageTitle(textView);
		textView->setText(text);

		rows += textView;

		return textView;
	};

	const auto addElementWithTitle = [&rows](const std::string_view title, Element* element) -> TextView* {
		const auto titleAndElementLayout = new StackLayout {
			4
		};

		const auto textView = new TextView {};
		Theme::applyElementTitle(textView);
		textView->setText(title);
		*titleAndElementLayout += textView;

		*titleAndElementLayout += element;

		rows += titleAndElementLayout;

		return textView;
	};

	const auto addDivider = [&rows]() -> Divider* {
		const auto divider1 = new Divider {};
		Theme::apply(divider1);

		rows += divider1;

		return divider1;
	};

	const auto addButton = [&rows](const std::string_view text) -> Button* {
		const auto button = new Button {};
		Theme::applyPrimary(button);
		button->setText(text);

		rows += button;

		return button;
	};

	// -------------------------------- OWLCAT, GIVE ME $$$ --------------------------------

	addPageTitle("Heresy counter")->setHorizontalAlignment(Alignment::center);

	SevenSegment seven {};
	seven.setActiveColor(&Theme::fg1);
	seven.setInactiveColor(&Theme::bg4);
	seven.setSegmentThickness(3);
	seven.setSegmentLength(10);
	seven.setDigitCount(4);
	seven.setHorizontalAlignment(Alignment::center);
	rows += &seven;

	TextView owlcatTextView {};
	Theme::applyDescription(&owlcatTextView);
	owlcatTextView.setWrappingEnabled(true);
	owlcatTextView.setText("Following their work on Rogue Trader, Owlcat Games developed a narrative-heavy RPG where players command an Imperial Inquisitor");
	// textView1.setText("Чета я сомневаюсь, что русский текст адекватно перенесется посимвольно-пиздато с тире в одном флаконе, но вообще как знать, это ж по идее просто байты");
	owlcatTextView.setTextAlignment(Alignment::center);
	rows += &owlcatTextView;

	addButton("Preorder")->setOnClick([&seven] {
		seven.setValue(seven.getValue() + 1);
	});

	// -------------------------------- Sliders --------------------------------

	addDivider();
	addPageTitle("Sliders");

	const auto newSlider = []() -> Slider* {
		const auto slider = new Slider {};

		Theme::apply(slider);
		slider->setTickLabelBuilder(Slider::int32TickLabelBuilder);

		return slider;
	};

	const auto pagePaddingSlider = newSlider();
	pagePaddingSlider->setFillColor(&Theme::sky1);
	pagePaddingSlider->setMinimumValue(0);
	pagePaddingSlider->setMaximumValue(50);
	pagePaddingSlider->setValue(rowsTransform.getMargin().getLeft());

	pagePaddingSlider->setOnValueChanged([&rowsTransform, pagePaddingSlider] {
		rowsTransform.setMargin({
			static_cast<uint16_t>(std::round(pagePaddingSlider->getValue()))
		});
	});

	addElementWithTitle("Page padding", pagePaddingSlider);

	const auto fontScaleSlider = newSlider();
	fontScaleSlider->setFillColor(&Theme::magenta1);
	fontScaleSlider->setTickCount(5);
	fontScaleSlider->setMinimumValue(1);
	fontScaleSlider->setMaximumValue(5);
	fontScaleSlider->setValue(pagePaddingSlider->getTickLabelFontScale());

	fontScaleSlider->setOnValueChanged([fontScaleSlider, pagePaddingSlider] {
		const auto fontScale = static_cast<uint8_t>(std::round(fontScaleSlider->getValue()));

		pagePaddingSlider->setTickLabelFontScale(fontScale);
		fontScaleSlider->setTickLabelFontScale(fontScale);
	});

	addElementWithTitle("Font scale", fontScaleSlider);

	// -------------------------------- Badges --------------------------------

	addDivider();
	addPageTitle("Badges");

	WrapLayout badgesLayout { 10 };
	rows += &badgesLayout;

	const auto addImageWithBadge = [&badgesLayout](const Image* image, const std::string_view badgeText) {
		const auto imageAndBadgeLayout = new Layout {};
		imageAndBadgeLayout->setHorizontalAlignment(Alignment::start);
		badgesLayout += imageAndBadgeLayout;

		const auto imageView = new ImageView { image };
		*imageAndBadgeLayout += imageView;

		const auto badge = new Badge {};
		Theme::apply(badge);
		badge->setAlignment(Alignment::end, Alignment::start);
		badge->setText(badgeText);
		*imageAndBadgeLayout += badge;

		const auto transform = new TranslateTransform {{ 5, -5 }};
		badge->setRenderingTransform(transform);
	};

	addImageWithBadge(&Images::menuIconDev, "1");
	addImageWithBadge(&Images::menuIconMFD, "2");
	addImageWithBadge(&Images::menuIconMFDAutopilot, "3");
	addImageWithBadge(&Images::menuIconPersonalization, "4");

	// -------------------------------- Switches --------------------------------

	addDivider();
	addPageTitle("Switches");

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
		sw->setActiveColor(switchColor);
		sw->setActive(isActive);
		textAndSwitchLayout->setAutoSize(sw);
		*textAndSwitchLayout += sw;

		return sw;
	};

	const auto themeSwitch = addTextAndSwitch("Dark theme", &Theme::accent1, true);

	themeSwitch->setOnIsActiveChanged([&themeSwitch] {
		Theme::setColorScheme(themeSwitch->isActive());
	});

	addTextAndSwitch("Large penis", &Theme::sky1, true);

	// -------------------------------- Selectors --------------------------------

	addDivider();
	addPageTitle("Selectors");

	// Creating selector
	Selector selector {};
	selector.setHeight(30);

	const auto selectorTitle = addElementWithTitle("Text alignment", &selector);

	// Assigning callback that will be called on any item selected
	selector.setOnSelectionChanged([&selector, selectorTitle] {
		switch (selector.getSelectedIndex()) {
			case 0: selectorTitle->setTextAlignment(Alignment::start); break;
			case 1: selectorTitle->setTextAlignment(Alignment::center); break;
			default: selectorTitle->setTextAlignment(Alignment::end); break;
		}
	});

	// Adding rectangle to fill out selector background behind its items
	RectangularShape selectorBackgroundRectangle {};
	selectorBackgroundRectangle.setCornerRadius(Theme::cornerRadius);
	selectorBackgroundRectangle.setFillColor(&Theme::bg3);
	selector += &selectorBackgroundRectangle;

	// Adding item layout that will automatically stretch its children
	RelativeStackLayout selectorItemLayout { Orientation::horizontal, 2 };
	MarginTransform selectorItemsLayoutMarginTransform {{ 2 }};
	selectorItemLayout.setLayoutTransform(&selectorItemsLayoutMarginTransform);
	selector += &selectorItemLayout;
	// Telling selector that it should use exactly this layout for... laying out its items
	selector.setItemLayout(&selectorItemLayout);

	// Creating custom SelectorItem that will be rendered as plain text
	class MySelectorItem : public SelectorItem, public TextElement {
		public:
			MySelectorItem(const std::string_view text) {
				setText(text);
			}

		protected:
			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				renderer->fillRectangle(bounds, Theme::cornerRadius, isActive() ? &Theme::fg1 : &Theme::bg3);

				renderer->putText(
					bounds.getCenter() - Theme::fontNormal.getSize(getText()).getCenter(),
					&Theme::fontNormal,
					isActive() ? &Theme::bg1 : &Theme::fg1,
					getText()
				);
			}
	};

	// Adding custom items to selector
	selector.addItem(new MySelectorItem("Left"));
	selector.addItem(new MySelectorItem("Center"));
	selector.addItem(new MySelectorItem("Right"));

	// Selecting first item in list
	selector.setSelectedIndex(0);

	// -------------------------------- Text fields --------------------------------

	addDivider();
	addPageTitle("Text fields");

	TextField textField1 {};
	Theme::apply(&textField1);
	textField1.setPlaceholder("Abc");

	addElementWithTitle("Regular", &textField1);

	TextField textField2 {};
	Theme::apply(&textField2);
	textField2.setPlaceholder("123");
	textField2.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);

	addElementWithTitle("Numeric", &textField2);

	// -------------------------------- Animations --------------------------------

	addDivider();
	addPageTitle("Animations");

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
			"Casino pumped out by %d%%",
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

	ScaleTransform scaleButtonTransform {};

	addButton("Hack")->setOnClick([&progressAnimation] {
		progressAnimation.stop();
		progressAnimation.start();
	});

	auto scaleButton = addButton("Toggle scale");
	Theme::applyPlaceholder(scaleButton);
	scaleButton->setRenderingTransform(&scaleButtonTransform);
	scaleButton->setToggle(true);

	ScaleTransformAnimation scaleButtonAnimation {};
	scaleButtonAnimation.setTarget(scaleButton);
	scaleButtonAnimation.setTransform(&scaleButtonTransform);
	scaleButtonAnimation.setDuration(250'000);

	scaleButton->setOnClick([&scaleButtonAnimation, &scaleButton, &scaleButtonTransform] {
		scaleButtonAnimation.stop();

		scaleButtonAnimation.setFrom(scaleButtonTransform.getScale());
		scaleButtonAnimation.setTo(scaleButton->isActive() ? Vector2F(0.9f) : Vector2F(1, 1));
		scaleButtonAnimation.start();
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
			else if (event->is<sf::Event::MouseWheelScrolled>()) {
				const auto mouseWheelScrolledEvent = event->getIf<sf::Event::MouseWheelScrolled>();

				MouseWheelEvent mouseWheelEvent {
					Point(
						static_cast<int32_t>(static_cast<float>(mouseWheelScrolledEvent->position.x) / renderingTarget.getRenderingScale()),
						static_cast<int32_t>(static_cast<float>(mouseWheelScrolledEvent->position.y) / renderingTarget.getRenderingScale())
					),
					static_cast<int32_t>(mouseWheelScrolledEvent->delta) * 20
				};

				application.pushEvent(&mouseWheelEvent);
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
