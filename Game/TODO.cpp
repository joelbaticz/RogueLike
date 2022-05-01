/*
2020-01-20:
		//canvasNode->GetRectangle(); "Get's the control's rectangular area in client coordinates. It means X, Y values are 0."
		//canvasNode->GetClientRect(); "Get's the control's rectangular client area (without frames, scrollbars and whatnot) in client coordinates."
		//canvasNode=>RectToScreen(); "Projects a rectangular client area to screen coordinates. Only masses with X and Y coordinates."
		//canvasNode->RectToClient(); "Projects a rectangular screen area to client coordinates."
		//renderer->GetCurrentClippingRect();
		//renderer->SetClippingRect(); "Sets a clipping rectangle. Screen or client coordinates?"

		//In windows you need to acquire a Graphics context and you call DrawLine, DrawRectangle with it.
		//It means you can draw knowing only the client relative coordinates. I guess it gets the Device Context for you. ClientDC or DC depends on
		//the control itself.
		//I guess the renderer should do graphics in screen coordinates and the "graphics context" should translate for you.
		//CreateGraphics could be a method in the canvas which you need to acquire at the Draw call and dispose of it every frame.
		//In Java this Graphics thin is passed on to the draw method as a parameter that you can use already preset for you.
		//And it lives inside the Control.

		//We can do that the Renderer will only have ScreenDrawLine, ScreenDrawRectangle and the rest. It would use the currently set pencolor,
		//fillcolor and clipping area. Obviously it would use screen coordinates.

		//The Graphics Context on the other hand would work take in client coordinates and translate them to screen coordinates.
		//This added complexity would not be present when we are directly drawing to the screen.
		//The Graphics Context would only be used to draw the UI elements. The game itself would only use the screen or only would draw into a texture
		//anyways. Not sure about the client to screen translation penalties, but clipping is needed even when we are drawing to an image/texture.


		//ClipToParentRectangle inkabb a CanvasNode resze kene legyen, semmint a RenderingEngine-e
		//Ahhoz, hogy ne minden frame-en szamoljuk ki a ClippingWindow-t ahhoz azt le kellene tarolni es csak a SetSize, SetLocation-nel ujra kiszamolni
		//Valamint jo lenne ha a drawing client coordinatakban tortenne amit egy object (vagy a CanvasNode maga) transzlalna screen coordokba.
		//Viszont ez az egesz ClipToParent csak a UI-hoz kell igazibol!
		//Az actual game logic-hoz Sprite/Tile drawing es 3D-s cuccok azokhoz nem kell.
		//Tehat a Sprite/SpriteNinePatch nem kene, hogy CancasNode legyen es ezek csak screencoord-ban szamolnak?
		//A Scene hasznalhat Sprite-okat es Canvas item-eket.

		//---2019-12-24
		//Rectangle rectScreen = Rectangle(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight());
		//Rectangle* pRectScreen = &rectScreen;
		//pRectScreen = RenderingEngine::ClipToParentRectangle(this->GetParent(), pRectScreen);
		//RenderingEngine::SetClippingRectangle(pRectScreen);
		//---


*/



/*
2020-12-30:

Archi (2D only)
=====

	RendererOptions/RenderingOptions: provides the factory and the renderer with info
		- RendererType (software/hardware/bit depth)
		- Dimensions: width/height
		- Created by GameEngine based on main's request about width/height
		- Later the GameEngine will read info from Configuration
	RendererFactory: provides one of the renderers based on RenderingOptions

	RendererSoftware8Bit:
	RendererSoftware16Bit:
	RendererSoftware32Bit:
	RendererSDL:
	RendererOpenGL:
		- provides rendering functions to be able to draw primitives and textures
		- only for UI and Sprite operations for now
		- provides functionality to be able replace/resize main window
		- provides methods to restart the rendering engine with options changed and to return to the caller which can display
		  message about the success of action and provide a limited window accept the settings

	RendererBase:
		- technically an interface that highlights which functions need to be implemented by the concrete classes
		- stores some information about the renderer (common things), but not implementation specific details (like access to the framebutter_

*/

/*
2020-12-27:

- Implement Triangle based quad/texture rendering
  In the GraphicsContext-DrawTexture it is already tried and working, but kinda slow
  Alternatively could use SDL_Surface/Texture rendering for quads

- Implement 32bit rendering -> move away from software rendering

- DONE: Fix GetLocation/GetSize bullcrap -> don't need these.
  Probably don't need the SetX/SetY/SetWidth/SetHeight either, just need to call ResetGraphics/Context after something was changed,
  so Bounds and ClippingRects will be recalculated

- Fix GetColor/SetColor misery.
  It's only 4 bytes anyways, so having 1 set method with color values should be fine.

- Figure out a way, so more complex UI element can draw themselves completely, so don't need to mess with how child items are modified/added/removed/colors changed etc.

- Fix window minimization/maximization

- Think out how RootNode and RootScene should be handled (probably I only need one or the other, but not both)
  Should have AddScene, RemoveScene, SwapScene I guess

*/

/*
2019-09-14:

- Go thru all entities/files and get rid of bullcrap (clean up Headers and CPPs)
  Done:
  main, GameEngine, LogEngine, RenderingEngine, EventManager,
  

- Fix up headers, so they are not included everywhere (even tho pragma once helps)
  Add namespace to commonly used stuff, like std::

- Think thru software rendering and what entities/assets we are going to use
- 2D/3D sprites (a 3D szeru sprite forgatast meg lehet oldani Vec2D-vel is)
- Introduct Vec2-3-4 (all size, location, width, height should be based on it?)
- Because we correctly used OOP only Location and Size should be modified to accomodate Vecs
  Everything else like Nodes and downward will be using that :)
- Decided which Assets (hierarchy) and Controls we gonna have. Which ones are redundant or overlapping
- Texture, GPUTexture, TextureAtlas, Sprite -> define these perfectly
- Think thru loading/creating Assets.
  Can we just create/instantiate an empty Font? Never register it with the AssetManager?
  Or we can only acquire it thru the AssetManager?
  The Asset (Font or whatever) will try to register itself with the AssetManager?
- Mini resources, like Color, Size or Location should be registered as well with the AssetManager?
- When to Garbage Collect? How do we know if we need to do clean up? At the end of the Scene we call GC?

2019-10-15:
- In the Node we can speed things up by defining and making public some fields (parent, firstChild, prevSibling, nextSibling)
  2 way chained list instead of forward looking chained list
- In the Rectangle instead of using Location and Size just store X, Y, Width, Height.
  This way we don't have to call GetX, GetY, SetWidth etc...
- In the CanvasNode instead of using Location and Size just store X, Y, ...

2019-12-31:
- Hint to the renderer that we wanna use OpenGL rendering backend (SDL_HINT_RENDER_DRIVER),
  so we can use result = SDL_GL_SetSwapInterval(-1); to enable/disable VSYNC 


Texture::TextureAtlas
or
TextureAtlas::Texture

Currently TextureAtlas is a wrapper class around my Texture (it's extension technically).
Csak a texture-ben talalhato sorok es oszlopok vannak benne meghatarozva es
van egy GetTextureRectangle ami a rect-et adja vissza egy adott kepecskehez.
A drawing eljarasok a Texture-on alapulnak.

A Sprite es a SpriteNinePatch min operaljon?
Currently TextureAtlas-on, mert a Ui-hoz hasznaljuk.

Elvileg az OpenGL-lel is lehet glVertex2i-t rajzoltatni.
Tehat az egesz 3d engine hasznalhatna integereket.

Resources/assets that can be created on the fly without AssetManager:
Location
Size
Rectangle

These are inherited from Resources (resourceId).

Assets should only be created by the AssetManager (like TextureAtlas):
Ezek:
Texture/TextureAtlas
Palette
Color
Font (from textureatlas - a default-ot mi krealjuk)

These are inherited from LoadableResource/Resources.
(should be ManagedResource or CountedResource vagy Assets and Resources)

2020-01-03:
A rectangle mivel heap-bol es verembol is allokalhato (Rectangle() vagy new Rect()),
ezert nem kene hasznalni Location-t es Size-t.
Azokat a verembol vagy a heap-bol allokalna???
Ha nincsenek ezek es a constructorba adok at mindent akkor nem szivok veluk.
Tovabba, ha publikusak lennenek az X, Y, W, H fieldek, akkor nem kene kuzdeni a Get/Set function-okkel.
A CanvasNode tovabbra is hasznalna Get/Set-et a Location-re, Size-ra es a Rectangle-ra.
O mindig letrehozna a sajat heap-bol allokalt Rectangle-jat es belemasolna az ertekeket (perzisztens data).

2020-01-04:
A Control-ok tudnak generalni event-eket. Minden control-nal fel lehet iratkozni kulonbozo eventekre. Csak egy CallBack function-t kell megadni.
Pont mint WinForm-sban. Igy nem kell millio node-ot vegigbongeszni, hogy le vagy fel kuldozgetjuk az event-eket.
Nezzunk bele a CEGUI-ba!

Furthermore: nagyon dodgy-nak tunik, hogy normalized device koordinatakat hasznaljunk ( -1 -> +1 ) foleg a UI-hoz. A Screen coordinatak sokkal jobban hangzanak.



Extra stuff for later:
- Implement OptionsManager
  OptionsManager::GetOption("MasterVolume");
- Implement SDL's AudioEngine
- Destroy scene objects when exiting (GC stuff)
  Destroy images/textures in GPU
- Call UnInits in subsystems when exiting. AssetManager::UnInit();
- Implement ChangeScene in GameEngine
  static Node* ChangeScene(Node* newScene);
  Changes the scene and continues the loop with that. Gets back the old scene
  Everybody is notified who are added to the SceneTree or left the tree.



*/