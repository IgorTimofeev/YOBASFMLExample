#include "Theme.hpp"

namespace pizda {
	RGB888Color Theme::bg1 {};
	RGB888Color Theme::bg2 {};
	RGB888Color Theme::bg3 {};
	RGB888Color Theme::bg4 {};
	RGB888Color Theme::bg5 {};
	RGB888Color Theme::bg6 {};
	RGB888Color Theme::bg7 {};
	RGB888Color Theme::fg1 {};
	RGB888Color Theme::fg2 {};
	RGB888Color Theme::fg3 {};
	RGB888Color Theme::fg4 {};
	RGB888Color Theme::fg5 {};
	RGB888Color Theme::fg6 {};
	RGB888Color Theme::fg7 {};
	RGB888Color Theme::accent1 {};
	RGB888Color Theme::accent2 {};
	RGB888Color Theme::good1 {};
	RGB888Color Theme::good2 {};
	RGB888Color Theme::bad1 {};
	RGB888Color Theme::bad2 {};
	RGB888Color Theme::bad3 {};
	RGB888Color Theme::red {};
	RGB888Color Theme::green1 {};
	RGB888Color Theme::green2 {};
	RGB888Color Theme::blue {};
	RGB888Color Theme::magenta1 {};
	RGB888Color Theme::magenta2 {};
	RGB888Color Theme::ocean {};
	RGB888Color Theme::yellow {};
	RGB888Color Theme::ground1 {};
	RGB888Color Theme::ground2 {};
	RGB888Color Theme::sky1 {};
	RGB888Color Theme::sky2 {};

	void Theme::setup() {
		setColorScheme(true);

		// Keyboard
		KeyboardController::setOnShow([](Keyboard* keyboard) {
			keyboard->setFont(&Theme::fontNormal);
			keyboard->setBackgroundColor(&Theme::bg1);

			keyboard->setKeyHeight(24);
			keyboard->setKeyCornerRadius(0);

			keyboard->setHorizontalKeySpacing(1);
			keyboard->setVerticalKeySpacing(1);

			keyboard->setDefaultKeyBackgroundColor(&Theme::bg3);
			keyboard->setDefaultKeyTextColor(&Theme::fg1);

			keyboard->setActionKeyBackgroundColor(&Theme::bg2);
			keyboard->setActionKeyTextColor(&Theme::fg1);

			keyboard->setDisabledKeyBackgroundColor(&Theme::bg2);
			keyboard->setDisabledKeyTextColor(&Theme::fg6);

			keyboard->setNumericLayoutBuilder([] {
				return new NumericKeyboardLayout();
			});

			keyboard->setCharactersLayoutBuilder([] {
				return new CharactersKeyboardLayout();
			});

			keyboard->setCyclicLayoutBuilders({
				[] {
					return new EnglishKeyboardLayout();
				},
				[] {
					return new RussianKeyboardLayout();
				}
			});
		});
	}

	void Theme::setColorScheme(const bool dark) {
		if (dark) {
			bg1 = { 0x000000 };
			bg2 = { 0x0C0C0C };
			bg3 = { 0x1C1C1C };
			bg4 = { 0x2C2C2C };
			bg5 = { 0x3C3C3C };
			bg6 = { 0x4C4C4C };
			bg7 = { 0x5C5C5C };

			fg1 = { 0xF0F0F0 };
			fg2 = { 0xCCCCCC };
			fg3 = { 0x999999 };
			fg4 = { 0x888888 };
			fg5 = { 0x777777 };
			fg6 = { 0x666666 };
			fg7 = { 0x555555 };

			accent1 = { 0xffd200 };
			accent2 = { 0x997e53 };
			good1 = { 0x1db153 };
			good2 = { 0x28DA69 };
			bad1 = { 0xf24949 };
			bad2 = { 0x962828 };
			bad3 = { 0x4b1313 };
			red = { 0xff0000 };
			green1 = { 0x00FF00 };
			green2 = { 0x007F00 };
			blue = { 0x0000FF };
			magenta1 = { 0xFF00FF };
			magenta2 = { 0xAA00AA };
			ocean = { 0x00FFFF };
			yellow = { 0xffd200 };
			ground1 = { 0x97b838 };
			ground2 = { 0xdef2a2 };
			sky1 = { 0x317fcb };
			sky2 = { 0xaed1f2 };
		}
		else {
			bg1 = { 0xF0F0F0 };
			bg2 = { 0xCCCCCC };
			bg3 = { 0x999999 };
			bg4 = { 0x888888 };
			bg5 = { 0x777777 };
			bg6 = { 0x666666 };
			bg7 = { 0x555555 };

			fg1 = { 0x000000 };
			fg2 = { 0x0C0C0C };
			fg3 = { 0x1C1C1C };
			fg4 = { 0x2C2C2C };
			fg5 = { 0x3C3C3C };
			fg6 = { 0x4C4C4C };
			fg7 = { 0x5C5C5C };

			accent1 = { 0xffd200 };
			accent2 = { 0x997e53 };
			good1 = { 0x1db153 };
			good2 = { 0x28DA69 };
			bad1 = { 0xf24949 };
			bad2 = { 0x962828 };
			bad3 = { 0x4b1313 };
			red = { 0xff0000 };
			green1 = { 0x00FF00 };
			green2 = { 0x007F00 };
			blue = { 0x0000FF };
			magenta1 = { 0xFF00FF };
			magenta2 = { 0xAA00AA };
			ocean = { 0x00FFFF };
			yellow = { 0xffd200 };
			ground1 = { 0x97b838 };
			ground2 = { 0xdef2a2 };
			sky1 = { 0x317fcb };
			sky2 = { 0xaed1f2 };
		}
	}

	void Theme::apply(TextView* text) {
		text->setTextColor(&Theme::fg1);
		text->setFont(&Theme::fontNormal);
	}

	void Theme::applyDescription(TextView* text) {
		text->setTextColor(&Theme::fg3);
		text->setFont(&Theme::fontNormal);
	}

	void Theme::applyPageTitle(TextView* text) {
		text->setTextColor(&Theme::fg1);
		text->setFont(&Theme::fontNormal);
		text->setFontScale(2);
	}

	void Theme::applyElementTitle(TextView* text) {
		text->setFont(&Theme::fontNormal);
		text->setTextColor(&Theme::fg3);
	}

	void Theme::applyPrimary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::accent1);
		button->setDefaultTextColor(&Theme::bg1);

		button->setActiveBackgroundColor(&Theme::accent2);
		button->setActiveTextColor(&Theme::bg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applySecondary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::bg3);
		button->setDefaultTextColor(&Theme::fg3);

		button->setActiveBackgroundColor(&Theme::bg5);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applyCritical(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&Theme::bad1);
		button->setDefaultTextColor(&Theme::fg1);

		button->setActiveBackgroundColor(&Theme::bad3);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::applyPlaceholder(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(nullptr);
		button->setDefaultBorderColor(&Theme::fg5);
		button->setDefaultTextColor(&Theme::fg5);

		button->setActiveBackgroundColor(nullptr);
		button->setActiveBorderColor(&Theme::fg1);
		button->setActiveTextColor(&Theme::fg1);

		button->setFont(&Theme::fontNormal);
	}

	void Theme::apply(Switch* sw) {
		sw->setSize(Size(38, 16));
		sw->setCornerRadius(sw->getSize().getHeight() / 2);

		sw->setTrackColor(&Theme::bg3);
		sw->setCheckedColor(&Theme::accent1);

		sw->setHandleColor(&Theme::fg1);

		sw->setAnimationDuration(250'000);
	}

	void Theme::apply(Slider* slider) {
		slider->setMinimumValue(0);
		slider->setMaximumValue(1);

		// Track
		slider->setTrackSize(5);
		slider->setTrackCornerRadius(slider->getTrackSize() / 2);
		slider->setTrackColor(&Theme::bg3);

		// Fill
		slider->setFillColor(&Theme::accent1);

		// Handle
		slider->setHandleSize({ 2, 10 });
		slider->setHandleCornerRadius(0);
		slider->setHandleColor(&Theme::fg1);

		// Tick
		slider->setTickCount(10);
		slider->setBigTickStep(5);
		slider->setTickOffset(0);
		slider->setBigTickLineLength(5);
		slider->setSmallTickLineLength(3);
		slider->setTickColor(&Theme::fg6);

		slider->setTickLabelFont(&Theme::fontNormal);
		slider->setTickLabelOffset(1);

		slider->setTickLabelBuilder(Slider::percentTickLabelBuilder);
	}

	void Theme::apply(ProgressBar* progressBar) {
		progressBar->setHeight(5);
		progressBar->setCornerRadius(2);
		progressBar->setTrackColor(&Theme::bg3);
		progressBar->setFillColor(&Theme::accent1);
	}

	void Theme::apply(ScrollView* scrollView) {
		scrollView->setScrollBarSize(3);
		scrollView->setScrollBarCornerRadius(1);
		scrollView->setScrollBarOffset(3);
		scrollView->setScrollBarThumbColor(&Theme::bg3);
	}

	void Theme::apply(TextField* textField) {
		textField->setHeight(elementHeight);
		textField->setCornerRadius(cornerRadius);
		textField->setTextMargin(10);

		textField->setDefaultBackgroundColor(&Theme::bg3);
		textField->setFocusedBackgroundColor(&Theme::bg4);

		textField->setDefaultTextColor(&Theme::fg1);
		textField->setFocusedTextColor(&Theme::fg1);

		textField->setDefaultBorderColor(&Theme::bg4);
		textField->setFocusedBorderColor(&Theme::accent1);

		textField->setPlaceholderColor(&Theme::fg5);
		textField->setCursorColor(&Theme::accent1);

		textField->setFont(&Theme::fontNormal);
	}

	void Theme::apply(Divider* divider) {
		divider->setOrientation(Orientation::horizontal);
		divider->setHeight(5);
		divider->setFillColor(&Theme::bg4);
	}

	void Theme::apply(Badge* badge) {
		badge->setHeight(14);
		badge->setCornerRadius(badge->getSize().getHeight() / 2);
		badge->setTextMargin(Margin(5, 0, 5, 0));

		badge->setFillColor(&Theme::bad1);
		badge->setTextColor(&Theme::fg1);

		badge->setFont(&Theme::fontSmall);
	}
}
