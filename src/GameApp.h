//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef GAME_APP_H
#define GAME_APP_H

class GameApp
{
public:
	static void LoadDemo(int width, int height);
	static void UpdateDemo();
	static void DrawDemo();
	
	GameApp();
	GameApp(const GameApp &) = delete;
	GameApp & operator = (const GameApp &) = delete;
	~GameApp();

private:
	static GameApp *privGameApp();

	Camera *pCam3D;
	GraphicsObject_TextureLight *pSphereLight;
	GraphicsObject_TextureLight *pSpaceFrigateLight;
	Texture *pSpaceFrigateTex;
	Texture *pSphereTex;
	Model *pModelSpaceFrigate;
	Model *pModelSphere;
	ShaderObject *pShaderObject_textureLight;
};

#endif

//---  End of File ---
