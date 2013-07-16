#ifndef __ACTOR_CUBE_H_
#define __ACTOR_CUBE_H_

namespace GameCore
{
	class Cube : public CORE::Entity
	{
	public:
		Cube();
		~Cube();

		void initialize();
		void initialize(CORE::VECTOR &position, CORE::VALUE size = 1.0);
		void update();

		bool hitByRay(CORE::RAY &ray, CORE::RAYHIT* outputHit = NULL);
	private:
		//vector<CORE::VERTEX> sidesIndices;
	};
}

#endif