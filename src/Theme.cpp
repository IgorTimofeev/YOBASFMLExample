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
			keyboard->setFont(&fontNormal);
			keyboard->setBackgroundColor(&bg1);

			keyboard->setKeyHeight(24);
			keyboard->setKeyCornerRadius(0);

			keyboard->setHorizontalKeyGap(1);
			keyboard->setVerticalKeyGap(1);

			keyboard->setDefaultKeyBackgroundColor(&bg3);
			keyboard->setDefaultKeyTextColor(&fg1);

			keyboard->setActionKeyBackgroundColor(&bg2);
			keyboard->setActionKeyTextColor(&fg1);

			keyboard->setDisabledKeyBackgroundColor(&bg2);
			keyboard->setDisabledKeyTextColor(&fg6);

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
			bg2 = { 0xE0E0E0 };
			bg3 = { 0xD0D0D0 };
			bg4 = { 0xC0C0C0 };
			bg5 = { 0xB0B0B0 };
			bg6 = { 0xA0A0A0 };
			bg7 = { 0x000000 };

			fg1 = { 0x000000 };
			fg2 = { 0x111111 };
			fg3 = { 0x222222 };
			fg4 = { 0x333333 };
			fg5 = { 0x444444 };
			fg6 = { 0x555555 };
			fg7 = { 0x666666 };

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
		text->setTextColor(&fg1);
		text->setFont(&fontNormal);
	}

	void Theme::applyDescription(TextView* text) {
		text->setTextColor(&fg4);
		text->setFont(&fontNormal);
	}

	void Theme::applyPageTitle(TextView* text) {
		text->setTextColor(&fg1);
		text->setFont(&fontNormal);
		text->setFontScale(2);
	}

	void Theme::applyElementTitle(TextView* text) {
		text->setFont(&fontNormal);
		text->setTextColor(&fg4);
	}

	void Theme::applyPrimary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&accent1);
		button->setDefaultTextColor(&bg1);

		button->setActiveBackgroundColor(&accent2);
		button->setActiveTextColor(&bg1);

		button->setFont(&fontNormal);
	}

	void Theme::applySecondary(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&bg3);
		button->setDefaultTextColor(&fg3);

		button->setActiveBackgroundColor(&bg5);
		button->setActiveTextColor(&fg1);

		button->setFont(&fontNormal);
	}

	void Theme::applyCritical(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(&bad1);
		button->setDefaultTextColor(&fg1);

		button->setActiveBackgroundColor(&bad3);
		button->setActiveTextColor(&fg1);

		button->setFont(&fontNormal);
	}

	void Theme::applyPlaceholder(Button* button) {
		button->setHeight(elementHeight);
		button->setCornerRadius(cornerRadius);

		button->setDefaultBackgroundColor(nullptr);
		button->setDefaultBorderColor(&fg5);
		button->setDefaultTextColor(&fg5);

		button->setActiveBackgroundColor(nullptr);
		button->setActiveBorderColor(&fg1);
		button->setActiveTextColor(&fg1);

		button->setFont(&fontNormal);
	}

	void Theme::apply(Switch* sw) {
		sw->setSize(Size(38, 16));
		sw->setCornerRadius(sw->getSize().getHeight() / 2);

		sw->setTrackColor(&bg3);
		sw->setActiveColor(&accent1);

		sw->setHandleColor(&fg1);

		sw->setAnimationDuration(250'000);
	}

	void Theme::apply(Slider* slider) {
		slider->setMinimumValue(0);
		slider->setMaximumValue(1);

		// Track
		slider->setTrackSize(5);
		slider->setTrackCornerRadius(slider->getTrackSize() / 2);
		slider->setTrackColor(&bg3);

		// Fill
		slider->setFillColor(&accent1);

		// Handle
		slider->setHandleSize({ 2, 10 });
		slider->setHandleCornerRadius(0);
		slider->setHandleColor(&fg1);

		// Tick
		slider->setTickCount(10);
		slider->setBigTickStep(5);
		slider->setTickOffset(0);
		slider->setBigTickLineLength(5);
		slider->setSmallTickLineLength(3);
		slider->setTickColor(&fg6);

		slider->setTickLabelFont(&fontNormal);
		slider->setTickLabelOffset(1);

		slider->setTickLabelBuilder(Slider::percentTickLabelBuilder);
	}

	void Theme::apply(ProgressBar* progressBar) {
		progressBar->setHeight(5);
		progressBar->setCornerRadius(2);
		progressBar->setTrackColor(&bg3);
		progressBar->setFillColor(&accent1);
	}

	void Theme::apply(ScrollView* scrollView) {
		scrollView->setScrollBarSize(3);
		scrollView->setScrollBarCornerRadius(1);
		scrollView->setScrollBarOffset(3);
		scrollView->setScrollBarThumbColor(&bg3);
	}

	void Theme::apply(TextField* textField) {
		textField->setHeight(elementHeight);
		textField->setCornerRadius(cornerRadius);
		textField->setTextMargin(10);

		textField->setDefaultBackgroundColor(&bg3);
		textField->setFocusedBackgroundColor(&bg4);

		textField->setDefaultTextColor(&fg1);
		textField->setFocusedTextColor(&fg1);

		textField->setDefaultBorderColor(&bg4);
		textField->setFocusedBorderColor(&accent1);

		textField->setPlaceholderColor(&fg5);
		textField->setCursorColor(&accent1);

		textField->setFont(&fontNormal);
	}

	void Theme::apply(Divider* divider) {
		divider->setOrientation(Orientation::horizontal);
		divider->setHeight(5);
		divider->setFillColor(&bg4);
	}

	void Theme::apply(Badge* badge) {
		badge->setHeight(14);
		badge->setCornerRadius(badge->getSize().getHeight() / 2);
		badge->setTextMargin(Margin(5, 0, 5, 0));

		badge->setFillColor(&bad1);
		badge->setTextColor(&fg1);

		badge->setFont(&fontSmall);
	}
}
