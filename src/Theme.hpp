#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Resources/Fonts/PIXY10Font.hpp>
#include <YOBA/Resources/Fonts/Vaticanus8Font.hpp>
// #include <YOBA/Resources/Fonts/Unscii16Font.hpp>

namespace pizda {
	using namespace YOBA;

	class Theme {
		public:
			// -------------------------------- Colors --------------------------------

			// Background
			static ARGBColor bg1;
			static ARGBColor bg2;
			static ARGBColor bg3;
			static ARGBColor bg4;
			static ARGBColor bg5;
			static ARGBColor bg6;
			static ARGBColor bg7;
			// Foreground
			static ARGBColor fg1;
			static ARGBColor fg2;
			static ARGBColor fg3;
			static ARGBColor fg4;
			static ARGBColor fg5;
			static ARGBColor fg6;
			static ARGBColor fg7;
			// Overlay
			static ARGBColor overlay;
			// Accent
			static ARGBColor accent1;
			static ARGBColor accent2;
			// Good
			static ARGBColor good1;
			static ARGBColor good2;
			// Bad
			static ARGBColor bad1;
			static ARGBColor bad2;
			static ARGBColor bad3;
			// Red
			static ARGBColor red;
			// Green
			static ARGBColor green1;
			static ARGBColor green2;
			// Blue
			static ARGBColor blue;
			// Magenta
			static ARGBColor magenta1;
			static ARGBColor magenta2;

			// Ocean
			static ARGBColor ocean;
			// Yellow
			static ARGBColor yellow;
			// Ground
			static ARGBColor ground1;
			static ARGBColor ground2;
			// Sky
			static ARGBColor sky1;
			static ARGBColor sky2;

			// -------------------------------- Fonts --------------------------------

			constexpr static PIXY10Font fontNormal {};
			constexpr static Vaticanus8Font fontSmall {};

			// -------------------------------- UI elements --------------------------------

			constexpr static uint16_t elementHeight = 27;
			constexpr static uint16_t cornerRadius = 3;
			constexpr static uint16_t verticalGap = 9;
			constexpr static uint16_t horizontalGap = 7;

			static void setup();
			static void setColorScheme(bool dark);
			static void applyPrimary(TextButton* TextButton);
			static void applySecondary(TextButton* TextButton);
			static void applyCritical(TextButton* TextButton);
			static void applyPlaceholder(TextButton* TextButton);
			static void apply(Slider* slider);
			static void apply(TextField* textField);
			static void apply(ScrollView* scrollView);
			static void apply(Switch* sw);
			static void apply(ProgressBar* progressBar);
			static void apply(TextView* text);
			static void applyPageTitle(TextView* text);
			static void applyElementTitle(TextView* text);
			static void applyDescription(TextView* text);
			static void apply(Divider* divider);
			static void apply(Badge* badge);
			static void apply(Titler* titler);
			static void apply(BottomSheetDialog* dialog);
			static void apply(StackLayoutBottomSheetDialog* dialog);
			static void apply(TitleStackLayoutBottomSheetDialog* dialog);
			static void apply(ColorPickerDialog* dialog);
			static void apply(ColorPicker* colorPicker);
			static void apply(TextAndSwitch* textAndSwitch);

			static void openDialog(BottomSheetDialog* dialog);
			static void closeDialog(BottomSheetDialog* dialog);
	};
}