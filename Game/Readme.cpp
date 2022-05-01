/*
2019-09-14
Assets:

-Resource : something that has a resource name / id, trackable by the AssetManager(e.g.: Color)
- LoadableResource : something that has a filename and need be initialized to use(font, image, texture)
- Texture : is an image that needs to be loaded(and handled->palette sync)
- Font : can be generated from a texture(image) with monospaced fonts, can be generated from a texture and
an array of widths and heights(not monospaced), can be generated from a TTF.
The glyphs will be rendered in the required size to a texture(image).
All chars will be generated when loading->no hasle later
Maybe later we can add effects(shadow, outline, extra texture) on them
- Sounds / Music
- GPUTexture: there will be an image(Texture) associated with it.When An object with this texture is drawn
the RenderingEngine will load up the associated image to the GPU and if the related texture havn't changed
it will use the GPUTexture instead(there should be a flag indicating this)

*/




/*
OLD:

Godot-ban:

Node
Script

CanvasItem extends Node
Visibility
Material

Node2d extends CanvasItem
Transform
Z Index

Sprite extends Node2D
Texture
NormalMap
Offset
Centered (bool)
Offset (int, int)
Flip H (bool)
Flip V (bool)
Animation
Region



Valahol kene lennie:
position
scale
rotate() -nek is
translate() -> ugyan az a processkor szoktak meghivni

_ready() - amikor bekerul a scene tree-be
_process(delta) - called every frame (delta hany second telt el az uccso
call ota)



WorldRoot
+-> MySprite extends Sprite ! :o

van Control is! -> gondolom minden ami mouse eventet szed

timer-t a tick()-hez szokas kotni.

van meg:
on_AnimatedSprite_animoation_finished()





Animation:
- name (to show in editor)
- delay (hany sec van a frameek kozott
- current frame
- xoffset (tween) for every frame
- yoffset
ugy tunik h animation-ben benne vannak az actual spriteok
Tehat kvazi SorcFireballNE es Enemy1WalkSW
Es kvazi ezt az objektet rakjuk bele a Gameobjectbe
Animation is coming from JSON
delays[8]
frames[8] - sprite nevek
xoffsets[8]

StaticObj vs Animated

EntityManager - a resource-bol megkapott Sprite-okat ide regisztraljuk...



ARCHI:

	GameEngine:
		Init (constructor): sets up sdl, window, renderer, o is feljelentkezik a MessageBus-nak broadcast
				receiving-re? Valszeg igen, kulonben honnan tudna, hogy le kell lonie magat...
		Get...  functions to GetRenderer obj or window (basic get/set functions)
				nem vagyunk szingleton-ok, tehat mindenkinek kellene tudnia az GameRenderer-rol peldaul
				es azt hogyan tudnak megkapni? minden obj-nak kell egy peldany a GameRenderer-bol?

	MessageBus
		RegisterObject (for receiving broadcasted messages)
		BroadcastMessage


	ResourceFactory/AssetManager: [responsible to load assets and give back objects instead: spritesheet, sprite, sound]
		Init (constructor): beallitja a resource dir-t a kulonbozo assetekhez es feljelentkezik a MessageBus-nal, hogy
			  melyik funcion-jet hasznalja a broadcast-ra. Pl itt kapja meg a Shutdown signal-t

	ComponentFactory / ResorceManager: [responsible to hold objects]
		Init (constructor): gondolom lefoglal egy memoriat (egy listat) az object-ek szamara es feljelentkezik a MessageBus-nal.
			  Amikor Shutdown-t kap, akkor elkuldi az object-eknek a kill signalt. DE NEM EZT CSINALJA A
			  MESSAGEBUS-ra valo feliratkozas?
		RegisterObject: berakja ezt az objektet a listaba

	SceneIterator: az active scene kap egy update messaget (frameenkent) es az vegigkuldi ezt a message-t
				 a scene osszes tagjanak: a HUD-nak, a PlayerObj-nak, az Actor-oknak...stb

	BaseObject: [mindenki belole szarmazik]
		Alapban minden objekt ebbol szarmazik: alapvetoen lekerdezi a GE-tol a GameRederer-t (hisz ennek
		fogunk rajzolasi parancsokat kuldeni), feliratkozik a MessageBus-nal, hogy kapjon broadcast message-eket




	GameLoop:
		sorrendben meghivja a kovetkezoket:
		GameEngine.beginFrame: letorli a render targetet

		MessageBus.Broadcast(update); --> mindenki erre megkapja a FRAME_UPDATE message-t es hogy az utobbi
			FRAME_UPDATE ota mennyi delta ido telt el. Az objekt ProcessMessage-je meghivja erre az update
			function-jet az objectnek.



		GameEngine.drawFrame (min operal ez a function? kvazi egy SpriteList-et kap es gyorsan kirajzolja,
			vagy amit eddig osszemolyoltak az objectek a framebufferen azt csak megjeleniti?
			Mikor es hogy torlom a frame buffert?
			A main csak meghivja a GameEngine-t hogy torolje a framebuffert, vagy egy Message-t kuld a MessageBus-nak,
			hogy notifikalja a GE-t, hogy kene egy BeginFrame, amire az letorli a rendertargetet







Scene - Level: a palya amin jatszunk (asszem statikus), csak egy map amin maszkalunk, ahol definialjuk, hogy
			   hol mi van. Lesz egy LoadScene ahol kezdetben csak a maparray-t adjuk vissza. A level tartalmazza
			   hogy melyik tile-ra lephetunk. Ez (meg akkor is ha subtile-ok vannak), akkor egy masik
			   array, kvazi bool array, ahol go/nogo az ertek.
			   A jatek editorban kvazi lerakhatjuk az obstacle-oket erre az array-re.

Actors:			Lehet egy NPC, lehet egy door, lehet akar egy plant a sarokban. Gondolom minden amivel
				interactal-ni lehet.



Main:
		Creates GameEngine object (constructor)
		Call GameEngine.loadScene
		Call GameEngine.startLoop
		When it returns:
		GameEngine.destroy

GameEngine [a collection of other SubSystems and glue to hold them together]:
		Constructor:
			Create other subsystems: MessageBus, ResourceEngine, Logging shit, RENDERING ENGINE
			Subscribe with MessageBus (ez azert kell, mert barki kuldhet egy gameexit msg-t, ami csak annyit
			csinal, hogy a GameLoop-ban a kondition-t ugy allitja be, hogy vegeterjen a gameloop). Erre
			az visszater a main-be es lerombolja az engine-t.
		LoadScene...
			Nemtom most hogy hogyan kene megcsinalni, talan csak bedrotozom, hogy mit csinaljon.
			Egyelore a main-ben lesz az Initial scene creation. Kesobb egy scn filet toltok be, ami-ben minden
			benne van: az object-ek, a sprite-jaik, az action-ok, a palyaresz, minden.
			Ezt felhasznalva a game engine tudja, h: "krealnia kell 1 fohost, az ezt es ezt a spriteatlas-t
			hasznalja, ezert be kell toltenie, stb stb.
			Egyelore a main.cpp-ben lesz egy function, ami megmondja a GameEngine-nek, hogy
			miket krealjon es hogy mi legyen ha interakciozunk...

			Kvazi ez az elejen lehet a Main.cpp-ben egy CreateWorld (CreateFirstScene), ami megcsinalja
			az objecteket es regisztral egy FirstSceneUpdateCallback procedurat, amit frame-enkent fog az engine
			meghivni. Ez a procedure megnezi a message-jeit. Ha talal olyat, hogy CLICK message es a MyButton3
			kuldte, akkor az az exit lesz...

		GameLoop:
			Sorrendben meghivja a SubSystem-eket (kvazi mint egy OS-nel :D),
			InputEngine.ProcessInputs, SceneEngine.updateworld, MessageBus.broadcastThoseDamnMessages (rakd
			bele a mailing slot-jaikba a kibasz message-eket),
			RenderEngine.presentFrame

			Asszem jobb, ha amikor a MessageBus SendBroadcastMessage-jet, vagy SendDirectMessage meghivja egy
			object, akkor a MailBox-jaba az adott object-nek belerakja a cuccot es visszaadja a vezerlest
			a meghivottnak. Ekkor a MessageBus-nak nem kell a broadcast-jat meghivni frame-enkent.
			Viszont a MessageBus.update-jet meghivjuk, ami erre megnezi hogy van-e neki message. ha van
			pl: EXIT msg, akkor mindenknek elkuldi az EXIT msg es kilep.
			Amikor a GameEngine-t destroy-aljuk, akkor a clean up utolso lepese, h a message engine letorli
			a message buffereket (MailBox). Lehet lehetne PREPARE_FOR_EXIT msg es akkor a messagebus mar
			nem rakja bele a message-eket a mailboxokba...
			A cuccoknak meg a prepare for exit-re mar ki kellene lepnie.

			A GameLoop-nak tudnia kene, hogy milyen object-ek leteznek a rendszer-ben. Mind grafikai, mind
			mas object-ek, pl: scene. Es mindnek szepen meg kene hivnia az update proc-jat. Ez talan ugy
			tudom megoldani, hogy megiscsak letezik a ComponentEngine (objectengine???) ahov mindenki
			beregisztral (a baseobject vagy node ami mindennek az alapja akkor alapban beregisztralna a
			MessageBus-nal es a ComponentEngine-nel). Nyilvan, mert nem a GameEngine-be kellene beregisztralni
			az object-eket, mert o nem kene hogy felelos legyen ertuk. Inkabb van egy entity ami nyilvantart
			mindenkit. Ennek a ComponentEngine-nek kellene eloszor mukodesbe lepnie, hiszen o a nyilvantarto
			adatbazisa mindennek. Meh, ez ugyanaz, mint a ResourceManager az OS-eknel. Az is kvazi az elso ami
			letrejon.

		LoggingEngine:
			Ez az elso amit a rendszer init-el (hehe, pont mint egy OS-nel :D), hogy a rendszer elkezdhesse
			a loggolast. Init-kor a LoggingEngine kap X darab flag-et, hogy miket kell loggolnia es miket
			nem kell kiirni az output-ra. A logging engine-t a main-bol (vagy a progin belul barhonnan)
			be lehetne allitani egy SetLoggingFlags function-nal. Egy GetLoggingFlags-szel meg lekerdezni a
			current-et. Vagy AddFlag es RemoveFlag...

Scene:
		Tartalmazza az osszes object-et. A menu is pl egy scene, ami tartalmazza a hatteret es a 3 gombot.
		Amikor klikkelunk, akkor kapunk egy uzit h milyen action tortent. Kilepes, ujabb scene betoltese stb.
		Gondolom lesz benne: AddPlayer, AddObject, AddMap, AddDialog...

Tehat a Main menu, a Level 1, Level 2 mind mind lehetne egy cpp file (kvazi scene).
Valahogy meghivnak egymast. Pl ha a Main menun a New Game-re klikkelunk, akkor a Level 1 Init kezdodik.
Ez kvazi display-el egy loading screen-t (a general loading screen lehet egy kulon cpp file, ami parameter
ekkel nyomul, kvazi: updateProgressbar stb) es  betolteti a kis cuccait ami kell, megcsinalja az object-eket
stb, majd definial egy callback-et, amit a GE hiv meg ha tortenik valami.
Ha pl egy gombot megnyomunk (persze az alap feature-k kezelve lennenek, pl: benyomodik a gomb stb), de a
click esemenyre hogy mit csinalna akkor azt nekunk kell mindenhol kulon megirni.
Lennenek nagyobb blokkok: pl: enemy reactions stb, de hogy pl mi tortenik az utolso game veget jelzo kapcsolo
megnyomasakor, az mas kerdes...
Kvazi a "special behaviour"-t mindig nekunk kell lekezelni.
Pl: letrehozok egy gombot es specify-olnom kell, hogy az OnClick esemenye a progink/cpp-nk melyik
function-jet fogja vegrehajtani.
Vagy: letrehozok egy objectumot, ami egy kapcsolo. Ha raklikkelunk (in sight az object), akkor
meghiv egy specko function-t, ami megnezi, hogy a player character mellette all-e es ha nem akkor nem
csinal semmit, ha igen, akkor aktivalodik (on-ra kapcsol). A level-t igazgato kod ezt a kapcsolot fogja
nezegetni minden update-kor, hogy aktivalva lett-e mar.
Ha aktivalva lett, akkor belekezd a sajat cuccainak a kitakaritasaba (a player object-et megtartja, ami
nyilvantartja a kulbozo ertekeit a karcsinak (pl XP es a targyait), de amugy mindent kinyir es vagy
betolti a menut megint, vagy egy uj palya init kodjat...



Tehat:

  main.cpp(init gameengine stb, itt a gameengine-nek beallitunk egy "start here" function pointer-t. Majd
			elinditjuk a gameengine-t)
  gameengine.cpp
	+
	|
	+--> main menu (a gameengine atpasszolja sajat magat a scene-nek, mire az elkezdi ezeket:
					loading screen, setup, beallitja hogy melyik button onclick-je melyik
					function-ra mutasson es vegul mindent visible-re rak. ezutan visszaterunk a game engine
					loopjaba, ahol az megint kezdi elorol (input, gameworld update, render)
					A MainMenu hivhat masik scene-t (level-t), mire az a level visszahivhat a main menu-be.
					A main menu kaphat mondjuk egy player objektumot, hogy kirajzolja a statjait a karinak,
					vagy achievementeket, vagy barmit amit a jatekos object-ben tarolunk.







*/