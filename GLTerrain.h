#ifndef GLTERRAIN_H_
#define GLTERRAIN_H_
#include "windows.h"
#include "gl/GL.h"
#include <string>
	class GLTerrain
	{
	public:
		GLTerrain();
		~GLTerrain();
		int Init(int width=0,int height=0);
		void InitSettings();
		int LoadTexture();
		int LoadTexture2();
		int CreateRawMesh();
		int CreateMesh();
		int DrawTerrain();
		void DrawTerrainNet();
		void SetScale(float scale=1.0f){m_scale=scale;}
	protected:
		std::string GetHDataFile();
	private:
		float m_scale;
		int m_Width;
		int m_Height;
		int m_texWidth;
		int m_texHeight;
		GLubyte *m_hmap;
		GLuint m_grassTexture;
		GLuint m_waterTexture;
	};

#endif