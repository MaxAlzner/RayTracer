#ifndef __ACTOR_DIAMOND_H_
#define __ACTOR_DIAMOND_H_

namespace GameCore
{
	class Diamond : public CORE::Entity
	{
	public:
		Diamond();
		~Diamond();

		void initialize();
		void initialize(CORE::VECTOR &position, CORE::VALUE size = 1.0);
		void update();
	};
}

#endif