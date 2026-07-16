
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

	ARGBBufferedRenderer renderer {};
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

	const auto addPageTitle = [&rows](const std::string_view text, TextView& textView) {
		Theme::applyPageTitle(&textView);
		textView.setText(text);

		rows += &textView;
	};

	const auto addPageDivider = [&rows](Divider& divider) {
		Theme::apply(&divider);
		rows += &divider;
	};

	class TitleAndElement : public StackLayout {
		public:
			TitleAndElement(const std::string_view title, Element* element) {
				setGap(4);

				Theme::applyElementTitle(&titleTextView);
				titleTextView.setText(title);
				*this += &titleTextView;

				*this += element;
			}

			TextView titleTextView {};
	};

	// -------------------------------- OWLCAT, GIVE ME $$$ --------------------------------

	TextView heresyTitle {};
	heresyTitle.setHorizontalAlignment(Alignment::center);
	addPageTitle("Heresy counter", heresyTitle);

	SevenSegment sevenSegment {};
	sevenSegment.setActiveColor(&Theme::fg1);
	sevenSegment.setInactiveColor(&Theme::bg4);
	sevenSegment.setSegmentThickness(3);
	sevenSegment.setSegmentLength(10);
	sevenSegment.setDigitCount(4);
	sevenSegment.setHorizontalAlignment(Alignment::center);
	rows += &sevenSegment;

	// Promo text
	TextView owlcatTextView {};
	Theme::applyDescription(&owlcatTextView);
	owlcatTextView.setWrappingEnabled(true);
	owlcatTextView.setText("Following their work on Rogue Trader, Owlcat Games developed a narrative-heavy RPG where players command an Imperial Inquisitor");
	// textView1.setText("Чета я сомневаюсь, что русский текст адекватно перенесется посимвольно-пиздато с тире в одном флаконе, но вообще как знать, это ж по идее просто байты");
	owlcatTextView.setTextAlignment(Alignment::center);
	rows += &owlcatTextView;

	// Preorder button
	Button preorderButton {};
	Theme::applyPrimary(&preorderButton);
	preorderButton.setText("Preorder");

	preorderButton.setOnClick([&sevenSegment] {
		sevenSegment.setValue(sevenSegment.getValue() + 1);
	});

	rows += &preorderButton;

	// -------------------------------- Sliders --------------------------------

	Divider slidersDivider {};
	Theme::apply(&slidersDivider);
	rows += &slidersDivider;

	TextView slidersTitle {};
	addPageTitle("Sliders", slidersTitle);

	Slider pagePaddingSlider {};
	Theme::apply(&pagePaddingSlider);
	pagePaddingSlider.setFillColor(&Theme::sky1);
	pagePaddingSlider.setMinimumValue(0);
	pagePaddingSlider.setMaximumValue(50);
	pagePaddingSlider.setValue(rowsTransform.getMargin().getLeft());

	pagePaddingSlider.setOnValueChanged([&rowsTransform, &pagePaddingSlider] {
		rowsTransform.setMargin({
			static_cast<uint16_t>(std::round(pagePaddingSlider.getValue()))
		});
	});

	pagePaddingSlider.setTickLabelBuilder(Slider::int32TickLabelBuilder);

	TitleAndElement pagePaddingSliderTitle { "Page padding", &pagePaddingSlider };
	rows += &pagePaddingSliderTitle;

	Slider fontScaleSlider {};
	Theme::apply(&fontScaleSlider);
	fontScaleSlider.setFillColor(&Theme::magenta1);
	fontScaleSlider.setTickCount(5);
	fontScaleSlider.setMinimumValue(1);
	fontScaleSlider.setMaximumValue(5);
	fontScaleSlider.setValue(pagePaddingSlider.getTickLabelFontScale());

	fontScaleSlider.setOnValueChanged([&fontScaleSlider, &pagePaddingSlider] {
		const auto fontScale = static_cast<uint8_t>(std::round(fontScaleSlider.getValue()));

		pagePaddingSlider.setTickLabelFontScale(fontScale);
		fontScaleSlider.setTickLabelFontScale(fontScale);
	});

	fontScaleSlider.setTickLabelBuilder(Slider::int32TickLabelBuilder);

	TitleAndElement fontScaleSliderTitle { "Font scale", &fontScaleSlider };
	rows += &fontScaleSliderTitle;

	// -------------------------------- Badges --------------------------------

	Divider badgesDivider {};
	addPageDivider(badgesDivider);

	TextView badgesTitle {};
	addPageTitle("Badges", badgesTitle);

	WrapLayout badgesLayout { 10 };
	rows += &badgesLayout;

	class ImageAndBadge : public Layout {
		public:
			ImageAndBadge(const Image* image, const std::string_view badgeText) {
				// Image
				imageView.setImage(image);
				*this += &imageView;

				// Badge
				Theme::apply(&badge);
				badge.setAlignment(Alignment::end, Alignment::start);
				badge.setText(badgeText);

				badgeTransform.setOffset({ 5, -5 });
				badge.setRenderingTransform(&badgeTransform);

				*this += &badge;
			}

			ImageView imageView {};

			Badge badge {};
			TranslateTransform badgeTransform {};
	};

	ImageAndBadge imagesAndBadges[4] {
		{ &Images::menuIconDev, "1"},
		{ &Images::menuIconMFD, "2"},
		{ &Images::menuIconMFDAutopilot, "3"},
		{ &Images::menuIconPersonalization, "4"},
	};

	for (auto& imageAndBadge : imagesAndBadges)
		badgesLayout += &imageAndBadge;

	// -------------------------------- Switches --------------------------------

	Divider switchesDivider {};
	addPageDivider(switchesDivider);

	TextView switchesTitle {};
	addPageTitle("Switches", switchesTitle);

	class TextAndSwitch : public RelativeStackLayout {
		public:
			TextAndSwitch(const std::string_view text, const Color* switchColor) {
				setOrientation(Orientation::horizontal);
				setGap(10);

				// Text
				Theme::applyDescription(&textView);
				textView.setVerticalAlignment(Alignment::center);
				textView.setText(text);
				*this += &textView;

				// Switch
				Theme::apply(&swtch);
				swtch.setVerticalAlignment(Alignment::center);
				swtch.setActiveColor(switchColor);
				swtch.setActive(true);
				setAutoSize(&swtch);
				*this += &swtch;
			}

			TextView textView {};
			Switch swtch {};
	};

	// Theme
	TextAndSwitch themeTextAndSwitch { "Dark theme", &Theme::accent1 };
	rows += &themeTextAndSwitch;

	themeTextAndSwitch.swtch.setOnIsActiveChanged([&themeTextAndSwitch] {
		Theme::setColorScheme(themeTextAndSwitch.swtch.isActive());
	});

	// Large penis
	TextAndSwitch largePenisTextAndSwitch { "Large penis", &Theme::sky1 };

	largePenisTextAndSwitch.swtch.setOnIsActiveChanged([&largePenisTextAndSwitch] {
		largePenisTextAndSwitch.textView.setText(largePenisTextAndSwitch.swtch.isActive() ? "8========D" : ":--->");
	});

	rows += &largePenisTextAndSwitch;

	// -------------------------------- Spinners --------------------------------

	Divider spinnersDivider {};
	addPageDivider(spinnersDivider);

	TextView spinnersTitle {};
	addPageTitle("Spinners", spinnersTitle);

	RelativeStackLayout spinnersLayout {
		Orientation::horizontal,
		10
	};

	spinnersLayout.setHeight(30);

	rows += &spinnersLayout;

	ProgressSpinner spinner1 {};
	spinner1.setThickness(1);
	spinner1.setTrackColor(&Theme::bg4);
	spinner1.setFillColor(&Theme::bad1);
	spinner1.setValue(0.5f);
	spinnersLayout += &spinner1;

	ProgressSpinner spinner2 {};
	spinner2.setThickness(1);
	spinner2.setTrackColor(&Theme::bg4);
	spinner2.setFillColor(&Theme::fg1);
	spinner2.setValue(0.5f);
	spinnersLayout += &spinner2;

	IndeterminateSpinner spinner3 {};
	spinner3.setThickness(3);
	spinner3.setTrackColor(&Theme::ground1);
	spinner3.setFillColor(&Theme::ground2);
	spinner3.setRotationSpeed(Math::toRadians(360));
	spinnersLayout += &spinner3;

	IndeterminateSpinner spinner4 {};
	spinner4.setThickness(3);
	spinner4.setTrackColor(&Theme::sky1);
	spinner4.setFillColor(&Theme::sky2);
	spinner4.setRotationSpeed(Math::toRadians(720));
	spinnersLayout += &spinner4;

	Slider spinnersSlider {};
	Theme::apply(&spinnersSlider);
	spinnersSlider.setFillColor(&Theme::fg1);
	spinnersSlider.setValue(0.5);

	spinnersSlider.setOnValueChanged([&spinner1, &spinner2, &spinnersSlider] {
		spinner1.setValue(spinnersSlider.getValue());
		spinner2.setValue(1.f - spinnersSlider.getValue());
	});

	spinnersSlider.setTickLabelBuilder(Slider::percentTickLabelBuilder);

	TitleAndElement spinnersSliderTitle { "Progress", &spinnersSlider };
	rows += &spinnersSliderTitle;

	// -------------------------------- Selectors --------------------------------

	Divider selectorsDivider {};
	addPageDivider(selectorsDivider);

	TextView selectorsTitle {};
	addPageTitle("Selectors", selectorsTitle);

	// Creating selector
	Selector selector {};
	selector.setHeight(30);

	TitleAndElement selectorTitle { "Text alignment", &selector };
	rows += &selectorTitle;

	// Assigning callback that will be called on any item selected
	selector.setOnSelectionChanged([&selector, &selectorTitle] {
		switch (selector.getSelectedIndex()) {
			case 0: selectorTitle.titleTextView.setTextAlignment(Alignment::start); break;
			case 1: selectorTitle.titleTextView.setTextAlignment(Alignment::center); break;
			default: selectorTitle.titleTextView.setTextAlignment(Alignment::end); break;
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
	MySelectorItem selectorItems[] {
		{ "Left" },
		{ "Center" },
		{ "Right" },
	};

	for (auto& selectorItem : selectorItems)
		selector.addItem(&selectorItem);

	// Selecting first item in list
	selector.setSelectedIndex(0);

	// -------------------------------- Text fields --------------------------------

	Divider textFieldsDivider {};
	addPageDivider(textFieldsDivider);

	TextView textFieldsTitle {};
	addPageTitle("Text fields", textFieldsTitle);

	// Regular
	TextField regularTextField {};
	Theme::apply(&regularTextField);
	regularTextField.setPlaceholder("Abc");

	TitleAndElement regularTextFieldTitle { "Regular", &regularTextField };
	rows += &regularTextFieldTitle;

	// Numeric
	TextField numericTextField {};
	Theme::apply(&numericTextField);
	numericTextField.setPlaceholder("123");
	numericTextField.setKeyboardLayoutOptions(KeyboardLayoutOptions::numeric | KeyboardLayoutOptions::allowSigned);

	TitleAndElement numericTextFieldTitle { "Numeric", &numericTextField };
	rows += &numericTextFieldTitle;

	// -------------------------------- Animations --------------------------------

	Divider animationsDivider {};
	addPageDivider(animationsDivider);

	TextView animationsTitle {};
	addPageTitle("Animations", animationsTitle);

	// -------------------------------- Progress button --------------------------------

	ProgressBar progressBar {};
	Theme::apply(&progressBar);
	progressBar.setFillColor(&Theme::good1);
	progressBar.setValue(1.0f);
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
			"Secrets remaining: %d%%",
			static_cast<uint8_t>(progressBar.getValue() * 100)
		);

		progressText.setText(textBuffer);
	};

	updateProgressText();

	FloatAnimation progressAnimation {};
	progressAnimation.setFrom(1.0f);
	progressAnimation.setTo(0.0f);
	progressAnimation.setDuration(3'000'000);

	progressAnimation.setOnTick([&progressBar, &progressAnimation, &updateProgressText] {
		progressBar.setValue(progressAnimation.getValue());

		updateProgressText();
	});

	// -------------------------------- Dialog button --------------------------------

	class Dialog : public RelativeStackLayout {
		public:
			Dialog() {
				// Overlay
				overlayShape.setFillColor(&overlayColor);
				*this += &overlayShape;

				// Content and background
				setAutoSize(&contentAndBackgroundLayout);
				*this += &contentAndBackgroundLayout;

				// Background
				backgroundRectangle.setFillColor(&Theme::bg2);
				contentAndBackgroundLayout += &backgroundRectangle;

				// Content
				contentLayout.setGap(10);

				contentLayoutMarginTransform.setMargin({ 15 });
				contentLayout.setLayoutTransform(&contentLayoutMarginTransform);

				contentAndBackgroundLayout += &contentLayout;

				// Title
				Theme::applyPageTitle(&titleTextView);
				contentLayout += &titleTextView;

				// Slide animation
				slideAnimation.setDuration(250'000);
				slideAnimation.setTarget(&contentAndBackgroundLayout);
			}

			RectangularShape overlayShape {};
			ARGBColor overlayColor { 0x99, 0x00, 0x00, 0x00 };

			Layout contentAndBackgroundLayout {};
			RectangularShape backgroundRectangle {};

			MarginTransform contentLayoutMarginTransform {};
			StackLayout contentLayout {};

			TextView titleTextView {};

			SizeAnimation slideAnimation {};

			void show() {
				*Application::getCurrent() += this;

				slideAnimation.setFrom({ Size::computed, 0 });
				slideAnimation.setTo({ Size::computed, Size::computed });
				slideAnimation.setOnStateChanged(nullptr);
				slideAnimation.start();
			}

			void hide(const std::function<void()>& onHide) {
				slideAnimation.setFrom({ Size::computed, Size::computed });
				slideAnimation.setTo({ Size::computed, 0 });

				slideAnimation.setOnStateChanged([this, onHide](const AnimationState state) {
					if (state != AnimationState::completed)
						return;

					auto myFunc = [this, onHide] {
						*Application::getCurrent() -= this;

						onHide();
					};

					Application::getCurrent()->invokeLater(myFunc);
				});

				slideAnimation.start();
			}
	};

	class ConfirmationDialog : public Dialog {
		public:
			void setup(
				const Image* icon,
				const std::string_view title,
				const std::string_view description,
				const std::function<void(const bool confirmed)>& onActionPerformed
			) {
				// Title
				titleTextView.setText(title);

				// Icon & description
				iconAndDescriptionLayout.setOrientation(Orientation::horizontal);
				iconAndDescriptionLayout.setGap(10);
				contentLayout += &iconAndDescriptionLayout;

				// Icon
				iconImageView.setVerticalAlignment(Alignment::start);
				iconImageView.setImage(icon);
				iconAndDescriptionLayout.setAutoSize(&iconImageView);
				iconAndDescriptionLayout += &iconImageView;

				// Description
				Theme::applyDescription(&descriptionTextView);
				descriptionTextView.setWrappingEnabled(true);
				descriptionTextView.setText(description);
				iconAndDescriptionLayout += &descriptionTextView;

				// Confirm
				Theme::applyPrimary(&confirmButton);
				confirmButton.setText("Confirm");

				confirmButton.setOnClick([onActionPerformed] {
					onActionPerformed(true);
				});

				contentLayout += &confirmButton;

				// Cancel
				Theme::applySecondary(&cancelButton);
				cancelButton.setText("Cancel");

				cancelButton.setOnClick([onActionPerformed] {
					onActionPerformed(false);
				});

				contentLayout += &cancelButton;
			}

			RelativeStackLayout iconAndDescriptionLayout {};
			ImageView iconImageView {};
			TextView descriptionTextView {};

			Button confirmButton {};
			Button cancelButton {};
	};

	Button dialogsButton {};
	Theme::applyCritical(&dialogsButton);
	dialogsButton.setText("Delete secrets");

	dialogsButton.setOnClick([&progressAnimation] {
		const auto dialog = new ConfirmationDialog {};

		dialog->setup(
			&Images::menuIconMFD,
			"Retard alert",
			"Are you sure want to delete QueenSnakePrn.mov? This action is permanent.",
			[dialog, &progressAnimation](const bool confirmed) {
				dialog->hide([dialog, confirmed, &progressAnimation] {
					if (confirmed) {
						progressAnimation.stop();
						progressAnimation.start();
					}

					Application::getCurrent()->invokeLater([dialog] {
						delete dialog;
					});
				});
			}
		);

		dialog->show();
	});

	rows += &dialogsButton;

	// -------------------------------- Scale button --------------------------------

	Button scaleButton {};
	Theme::applyPlaceholder(&scaleButton);
	scaleButton.setToggle(true);
	scaleButton.setText("Toggle scale");

	ScaleTransform scaleButtonTransform {};
	scaleButton.setRenderingTransform(&scaleButtonTransform);

	ScaleTransformAnimation scaleButtonAnimation {};
	scaleButtonAnimation.setTarget(&scaleButton);
	scaleButtonAnimation.setTransform(&scaleButtonTransform);
	scaleButtonAnimation.setDuration(250'000);

	scaleButton.setOnClick([&scaleButtonAnimation, &scaleButton, &scaleButtonTransform] {
		scaleButtonAnimation.stop();

		scaleButtonAnimation.setFrom(scaleButtonTransform.getScale());
		scaleButtonAnimation.setTo(scaleButton.isActive() ? Vector2F(0.9f) : Vector2F(1.f));
		scaleButtonAnimation.start();
	});

	rows += &scaleButton;

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
			else if (event->is<sf::Event::Closed>()) {
				SFWindow.close();
			}
		}

		// -------------------------------- YOBA tick handling & rendering --------------------------------

		const auto FPSMeasurementStart = std::chrono::steady_clock::now();

		application.invalidate();
		application.tick();
		application.updateLayout();
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
