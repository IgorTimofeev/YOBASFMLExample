#include "Resources/Images.hpp"

namespace pizda {
	void TextureSpriteAndImage::setup(const std::string_view path) {
		if (!texture.loadFromFile(path))
			return;

		sprite.setTexture(texture, true);
		image.setSprite(&sprite);
	}

	TextureSpriteAndImage Images::menuIconDev {};
	TextureSpriteAndImage Images::menuIconMFD {};
	TextureSpriteAndImage Images::menuIconMFDAutopilot {};
	TextureSpriteAndImage Images::menuIconPersonalization {};

	void Images::setup() {
		menuIconDev.setup("resources/images/MenuIconDev.png");
		menuIconMFD.setup("resources/images/MenuIconMFD.png");
		menuIconMFDAutopilot.setup("resources/images/MenuIconMFDAutopilot.png");
		menuIconPersonalization.setup("resources/images/MenuIconPersonalization.png");
	}
}
