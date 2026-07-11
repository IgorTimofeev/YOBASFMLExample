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
			static RGB888Color bg1;
			static RGB888Color bg2;
			static RGB888Color bg3;
			static RGB888Color bg4;
			static RGB888Color bg5;
			static RGB888Color bg6;
			static RGB888Color bg7;
			// Foreground
			static RGB888Color fg1;
			static RGB888Color fg2;
			static RGB888Color fg3;
			static RGB888Color fg4;
			static RGB888Color fg5;
			static RGB888Color fg6;
			static RGB888Color fg7;
			// Accent
			static RGB888Color accent1;
			static RGB888Color accent2;
			// Good
			static RGB888Color good1;
			static RGB888Color good2;
			// Bad
			static RGB888Color bad1;
			static RGB888Color bad2;
			static RGB888Color bad3;
			// Red
			static RGB888Color red;
			// Green
			static RGB888Color green1;
			static RGB888Color green2;
			// Blue
			static RGB888Color blue;
			// Magenta
			static RGB888Color magenta1;
			static RGB888Color magenta2;
			// Ocean
			static RGB888Color ocean;
			// Yellow
			static RGB888Color yellow;
			// Ground
			static RGB888Color ground1;
			static RGB888Color ground2;
			// Sky
			static RGB888Color sky1;
			static RGB888Color sky2;

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
			static void applyPrimary(Button* button);
			static void applySecondary(Button* button);
			static void applyCritical(Button* button);
			static void applyPlaceholder(Button* button);
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
	};
}