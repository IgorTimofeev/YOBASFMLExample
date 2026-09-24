#pragma once

#include <string>

#include <YOBA/Core.hpp>
#include <SFML/Graphics.hpp>

namespace pizda {
	using namespace YOBA;

	class TextureSpriteAndImage {
		public:
			void setup(const std::string_view path);

			sf::Texture texture {};
			sf::Sprite sprite { texture };
			SFMLImage image {};
	};

	class Images {
		public:
			static TextureSpriteAndImage menuIconDev;
			static TextureSpriteAndImage menuIconMFD;
			static TextureSpriteAndImage menuIconMFDAutopilot;
			static TextureSpriteAndImage menuIconPersonalization;

			static void setup();
	};
}