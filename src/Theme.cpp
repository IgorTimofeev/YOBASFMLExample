#include "Theme.hpp"

namespace pizda {
	ARGBColor Theme::bg1 {};
	ARGBColor Theme::bg2 {};
	ARGBColor Theme::bg3 {};
	ARGBColor Theme::bg4 {};
	ARGBColor Theme::bg5 {};
	ARGBColor Theme::bg6 {};
	ARGBColor Theme::bg7 {};
	ARGBColor Theme::fg1 {};
	ARGBColor Theme::fg2 {};
	ARGBColor Theme::fg3 {};
	ARGBColor Theme::fg4 {};
	ARGBColor Theme::fg5 {};
	ARGBColor Theme::fg6 {};
	ARGBColor Theme::fg7 {};
	ARGBColor Theme::overlay {};
	ARGBColor Theme::accent1 {};
	ARGBColor Theme::accent2 {};
	ARGBColor Theme::good1 {};
	ARGBColor Theme::good2 {};
	ARGBColor Theme::bad1 {};
	ARGBColor Theme::bad2 {};
	ARGBColor Theme::bad3 {};
	ARGBColor Theme::red {};
	ARGBColor Theme::green1 {};
	ARGBColor Theme::green2 {};
	ARGBColor Theme::blue {};
	ARGBColor Theme::magenta1 {};
	ARGBColor Theme::magenta2 {};
	ARGBColor Theme::ocean {};
	ARGBColor Theme::yellow {};
	ARGBColor Theme::ground1 {};
	ARGBColor Theme::ground2 {};
	ARGBColor Theme::sky1 {};
	ARGBColor Theme::sky2 {};

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
			bg1 = { 0xFF000000 };
			bg2 = { 0xFF0C0C0C };
			bg3 = { 0xFF1C1C1C };
			bg4 = { 0xFF2C2C2C };
			bg5 = { 0xFF3C3C3C };
			bg6 = { 0xFF4C4C4C };
			bg7 = { 0xFF5C5C5C };

			fg1 = { 0xFFF0F0F0 };
			fg2 = { 0xFFCCCCCC };
			fg3 = { 0xFF999999 };
			fg4 = { 0xFF888888 };
			fg5 = { 0xFF777777 };
			fg6 = { 0xFF666666 };
			fg7 = { 0xFF555555 };

			overlay = { 0x88000000 };
			accent1 = { 0xFFffd200 };
			accent2 = { 0xFF997e53 };
			good1 = { 0xFF1db153 };
			good2 = { 0xFF28DA69 };
			bad1 = { 0xFFf24949 };
			bad2 = { 0xFF962828 };
			bad3 = { 0xFF4b1313 };
			red = { 0xFFff0000 };
			green1 = { 0xFF00FF00 };
			green2 = { 0xFF007F00 };
			blue = { 0xFF0000FF };
			magenta1 = { 0xFFFF00FF };
			magenta2 = { 0xFFAA00AA };
			ocean = { 0xFF00FFFF };
			yellow = { 0xFFffd200 };
			ground1 = { 0xFF97b838 };
			ground2 = { 0xFFdef2a2 };
			sky1 = { 0xFF317fcb };
			sky2 = { 0xFFaed1f2 };
		}
		else {
			bg1 = { 0xFFF0F0F0 };
			bg2 = { 0xFFE0E0E0 };
			bg3 = { 0xFFD0D0D0 };
			bg4 = { 0xFFC0C0C0 };
			bg5 = { 0xFFB0B0B0 };
			bg6 = { 0xFFA0A0A0 };
			bg7 = { 0xFF000000 };

			fg1 = { 0xFF000000 };
			fg2 = { 0xFF111111 };
			fg3 = { 0xFF222222 };
			fg4 = { 0xFF333333 };
			fg5 = { 0xFF444444 };
			fg6 = { 0xFF555555 };
			fg7 = { 0xFF666666 };

			overlay = { 0x88000000 };
			accent1 = { 0xFFffd200 };
			accent2 = { 0xFF997e53 };
			good1 = { 0xFF1db153 };
			good2 = { 0xFF28DA69 };
			bad1 = { 0xFFf24949 };
			bad2 = { 0xFF962828 };
			bad3 = { 0xFF4b1313 };
			red = { 0xFFff0000 };
			green1 = { 0xFF00FF00 };
			green2 = { 0xFF007F00 };
			blue = { 0xFF0000FF };
			magenta1 = { 0xFFFF00FF };
			magenta2 = { 0xFFAA00AA };
			ocean = { 0xFF00FFFF };
			yellow = { 0xFFffd200 };
			ground1 = { 0xFF97b838 };
			ground2 = { 0xFFdef2a2 };
			sky1 = { 0xFF317fcb };
			sky2 = { 0xFFaed1f2 };
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

	void Theme::apply(Titler* titler) {
		titler->setGap(4);
		applyElementTitle(&titler->titleTextView);
	}

	void Theme::apply(BottomSheetDialog* dialog) {
		// Background
		dialog->backgroundShape.setFillColor(&Theme::bg2);
		
		// Overlay
		dialog->overlayShape.setFillColor(&Theme::overlay);
		
		dialog->overlayShape.setOnPointerEvent([dialog] {
			Application::getCurrent()->invokeLater([dialog] {
				closeDialog(dialog);
			});
		});
	}

	void Theme::apply(StackLayoutBottomSheetDialog* dialog) {
		apply(static_cast<BottomSheetDialog*>(dialog));

		// Scroll view
		apply(&dialog->contentScrollView);
	}
	
	void Theme::apply(TitleStackLayoutBottomSheetDialog* dialog) {
		apply(static_cast<StackLayoutBottomSheetDialog*>(dialog));

		// Title
		applyPageTitle(&dialog->titleTextView);
	}

	void Theme::apply(ColorPickerDialog* dialog) {
		apply(static_cast<TitleStackLayoutBottomSheetDialog*>(dialog));
		
		// Color palette
		dialog->colorPalette.setHeight(120);
		dialog->colorPalette.setHandleColor(&fg1);
		dialog->colorPalette.setPixelSize(4);

		// Text fields
		dialog->textFieldRow.setGap(6);

		apply(&dialog->hueTitler);
		apply(&dialog->hueTextField);
		dialog->hueTextField.setTextMargin(8);

		apply(&dialog->saturationTitler);
		apply(&dialog->saturationTextField);
		dialog->saturationTextField.setTextMargin(dialog->hueTextField.getTextMargin());

		apply(&dialog->brightnessTitler);
		apply(&dialog->brightnessTextField);
		dialog->brightnessTextField.setTextMargin(dialog->hueTextField.getTextMargin());

		apply(&dialog->hexTitler);
		apply(&dialog->hexTextField);
		dialog->hexTextField.setTextMargin(dialog->hueTextField.getTextMargin());
		dialog->textFieldRow.setRelativeSize(&dialog->hexTitler, 1.5);

		// Confirm button
		applyPrimary(&dialog->confirmButton);
	}

	void Theme::apply(ColorPicker* colorPicker) {
		colorPicker->setHeight(elementHeight);
		colorPicker->setCornerRadius(cornerRadius);

		colorPicker->setDefaultBorerColor(&bg4);
		colorPicker->setActiveBorerColor(&fg1);

		colorPicker->setDialogOpener([] {
			const auto dialog = new ColorPickerDialog();
			apply(dialog);

			openDialog(dialog);

			return dialog;
		});

		colorPicker->setDialogCloser([](ColorPickerDialog* dialog) {
			Application::getCurrent()->invokeLater([dialog] {
				closeDialog(dialog);
			});
		});
	}

	void Theme::openDialog(BottomSheetDialog* dialog) {
		*Application::getCurrent() += dialog;
	}

	void Theme::closeDialog(BottomSheetDialog* dialog) {
		// Maybe dialog is not in application layout anymore
		dialog->removeFromParent();

		delete dialog;
	}
}
