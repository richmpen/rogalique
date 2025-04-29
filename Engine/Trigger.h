#pragma once

namespace EngineCore {

	class ColliderComponent;
	class Trigger {
	public:
		Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) :
			first(newFirst), second(newSecond) {

		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
	};
}