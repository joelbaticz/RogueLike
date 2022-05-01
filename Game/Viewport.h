#pragma once
#include "Math.h"
#include "ControlNode.h"
#include "Level.h"
#include "Camera3D.h"
#include "AssetManager.h"

class Viewport : public ControlNode
{
private:
	Level*			renderedLevel;
	Math::Mat4		worldMatrix;
	float			cameraRotationX;
	float			cameraRotationY;
	float			cameraRotationZ;
	float			cameraPositionX;
	float			cameraPositionY;
	float			cameraPositionZ;
	float			cameraScaling;

	Camera3D*		camera;

	int				triangleCount;

	bool			isSelectionChanged;
	LevelObject*	selectedObject;

	int				mouseX;
	int				mouseY;

	Color*			backgroundColor = AssetManager::CreateColor(255, 10, 32, 64);
	Color*			focusColor = AssetManager::CreateColor(255, 255, 192, 32);
	Color*			playerColor = AssetManager::CreateColor(255, 255, 0, 0);
	Color*			statsBackgroundColor = AssetManager::CreateColor(255, 64, 64, 64);
	Color*			statsForegroundColor = AssetManager::CreateColor(255, 255, 255, 255);

	float			screenWidth;
	float			screenHeight;
	Texture*		texture;

	void DisplayDrawError(GraphicsContext* g);
	void DisplayLevel(GraphicsContext* g);
	void DisplayPerformanceStats(GraphicsContext* g);
	void DisplayPlayerStats(GraphicsContext* g);

	void HandleEditing(Message* msg);
	void HandleCameraOptions(Message* msg);
public:
	Viewport();
	~Viewport();

	virtual void Update();

	void SetCamera(Camera3D* camera);
	void SetRenderedLevel(Level* renderedLevel);
	void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override;
	void PerformHitTest(int x, int y);
	void OnKeyDown(Message* msg);
	void OnMouseClick(Message* msg) override;
};

// Remarks:
// - For now the Viewport is just a surface which draws itself onto the FrameBuffer
// - Later it could be a ToolWindow itself or can be added to a ToolWindow
// - Also later the Viewport can get a LevelRenderer object which actually sits in between the Level and the Camera
//    +-> This based on the Camera settings can assist to selects which objects will need to be actually drawn and 
//        with what detail (LOD + Texture Mapping Level).
//    +-> Also uses RenderingOptions, to decide what kind of output we are interested in (Vertices, Triangles, Shaded Triangles, Texured Triangles),
//        culling options, backface elimination, if a triangle needs to be drawn with transparency (or just block coloring)
//    +-> Later the LevelRenderer and the Viewport won't be drawing straight to the FrameBuffer, but to an arbitrary rendering target and will just
//        draw this buffer to the framebuffer when screenrefresh needed.
//        This way the whole rendering of the level can be shifted to another core entirely
// - Also later the RenderingEngine could provide rendering of VertexBufferObjects on multiple threads and with SIMD extensions
//    +-> to achieve this we will need to have as many FrameBuffers and Z-Buffers as the number of rendering threads and stich them together into one
// - Also later the whole UI rendering thing could be moved to render Triangles shapes with Texture coordinates -> only one baclemd need to be optimized
