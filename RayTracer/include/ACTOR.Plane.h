#ifndef __ACTOR_PLANE_H_
#define __ACTOR_PLANE_H_

namespace GameCore
{
	class Plane : public CORE::Entity
	{
	public:
		Plane();
		~Plane();

		void initialize();
		void initialize(CORE::VECTOR &position, CORE::VALUE size = 1.0);
		void update();
	};
}

#endif