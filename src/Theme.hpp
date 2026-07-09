#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Resources/Fonts/PIXY10Font.hpp>
// #include <YOBA/Resources/Fonts/Vaticanus8Font.hpp>
// #include <YOBA/Resources/Fonts/Unscii16Font.hpp>

namespace pizda {
	using namespace YOBA;

	class Theme {
		public:
			// -------------------------------- Colors --------------------------------

			// Background
			constexpr static RGB888Color bg1 { 0x000000 };
			constexpr static RGB888Color bg2 { 0x0C0C0C };
			constexpr static RGB888Color bg3 { 0x1C1C1C };
			constexpr static RGB888Color bg4 { 0x2C2C2C };
			constexpr static RGB888Color bg5 { 0x3C3C3C };
			constexpr static RGB888Color bg6 { 0x4C4C4C };
			constexpr static RGB888Color bg7 { 0x5C5C5C };
			// Foreground
			constexpr static RGB888Color fg1 { 0xF0F0F0 };
			constexpr static RGB888Color fg2 { 0xCCCCCC };
			constexpr static RGB888Color fg3 { 0x999999 };
			constexpr static RGB888Color fg4 { 0x888888 };
			constexpr static RGB888Color fg5 { 0x777777 };
			constexpr static RGB888Color fg6 { 0x666666 };
			constexpr static RGB888Color fg7 { 0x555555 };
			// Accent
			constexpr static RGB888Color accent1{ 0xffd200 };
			constexpr static RGB888Color accent2 { 0x997e53 };
			// Good
			constexpr static RGB888Color good1 { 0x1db153 };
			constexpr static RGB888Color good2 { 0x28DA69 };
			// Bad
			constexpr static RGB888Color bad1 { 0xf24949 };
			constexpr static RGB888Color bad2 { 0x962828 };
			constexpr static RGB888Color bad3 { 0x4b1313 };
			// Red
			constexpr static RGB888Color red { 0xff0000 };
			// Green
			constexpr static RGB888Color green1 { 0x00FF00 };
			constexpr static RGB888Color green2 { 0x007F00 };
			// Blue
			constexpr static RGB888Color blue { 0x0000FF };
			// Magenta
			constexpr static RGB888Color magenta1 { 0xFF00FF };
			constexpr static RGB888Color magenta2 { 0xAA00AA };
			// Ocean
			constexpr static RGB888Color ocean { 0x00FFFF };
			// Yellow
			constexpr static RGB888Color yellow { 0xffd200 };
			// Ground
			constexpr static RGB888Color ground1 { 0x97b838 };
			constexpr static RGB888Color ground2 { 0xdef2a2 };
			// Sky
			constexpr static RGB888Color sky1 { 0x317fcb };
			constexpr static RGB888Color sky2 { 0xaed1f2 };

			// -------------------------------- Fonts --------------------------------

			constexpr static PIXY10Font fontNormal {};

			// -------------------------------- UI elements --------------------------------

			constexpr static uint16_t elementHeight = 27;
			constexpr static uint16_t cornerRadius = 3;
			constexpr static uint16_t verticalGap = 9;
			constexpr static uint16_t horizontalGap = 7;

			static void setup();
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
			static void applyTitle(TextView* text);
			static void applyDescription(TextView* text);
	};
}