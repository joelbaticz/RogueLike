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