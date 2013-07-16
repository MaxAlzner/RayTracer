#ifndef __CORE_SCENE_H_
#define __CORE_SCENE_H_

namespace CORE
{
	class Scene
	{
	public:
		Scene();
		~Scene();
	
		virtual void onInitialize();
		virtual void onUninitialize();
		virtual void onFrame(int* video, float* zBuffer, int width, int height, Mesh** onScreen = NULL);
		virtual void onTick();

		void setCamera(Camera* cam);
			
		vector<Entity*> actors;
		vector<Light*> lights;
		Camera* camera;
		Entity* mouseHoveringOver;
	protected:
	};
}

#endif