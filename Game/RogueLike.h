#pragma once

#include "ShapeNode.h"
#include "SpriteNode.h"
#include "Actor2d.h"
#include "TileMap.h"
#include <vector>
#include "Player.h"
#include "Projectile.h"
#include "Button.h"

class MainMenu;

class RogueLike : public ControlNode
{
private:
	bool levelInit;

	std::vector<TileMap*> levels;
	int activeLevelIndex;

	float cameraX;
	float cameraY;

    int mouseX;
    int mouseY;

	Player* player1;
	Player* player2;
	float player1DeltaX;
	float player1DeltaY;
	float player2DeltaX;
	float player2DeltaY;

	Actor2d* npc1;
	Actor2d* npc2;
	Actor2d* npc3;
	Actor2d* npc4;

	std::vector<Projectile*> projectiles;

    Button* buttonMainMenu;
    MainMenu* mainMenu;

	void CreateLevel();
	void CreatePlayers();
	void CreateNPCs();

public:

	RogueLike();
	~RogueLike();

    void SetMainMenu(MainMenu* mainMenu);
	int AddLevel(TileMap* newLevel);

	void Update();
	void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override;

    void OnMouseMove(Message* msg) override;
    void OnMouseClick(Message* msg) override;
};


/*
 

[2020-10-26]
 
Actor2d
	+ ->Player
	+ ->Monster
	+ ->NPC
	+ ->Object(torch, gate, switch, anything we act with)

	What do they have ?

	-HP
	- Mana
	- Other Stats
	- Location(where it is at the moment)
	- LocationNext(where it will be when it arrives)
	- LocationInbetween(in transition location - depends on the travel speed of the character)
	- Direction(N, SE...)
	- Active / Dead(IsAlive)
	- Sprite
	- AnimationPlayer ?



	A lenyeg, hogy minden actor - t hozzaadunk a level - hez.
	Private pointer - ek lesznek a fontosabbakhoz(pl : player1, player2).

	Lehet 1 Actor class - szal is megoldani es lenne egy Type mezo(npc, monsta, switch, palya elem).
	De igazibol ezek "reagalnanak" a palyara.
	Minden frame - ben az osszes update - eli a kis state - jet es egy uj state - et allit be.
	De ez azt jelenti, hogy ezeknek az actor - oknak "tudniuk kell" egymasrol.

	Vagy a level - en keresztul, vagy egy kulon levelstate object - en keresztul tudnanak cuccokat lekerdezni egymasrol.
	Hogy gyorsitsunk lehetne egy "map" ahol letaroljuk az eppen foglalt poziciokat peldaul.

	->Amikor a playert letrehozzuk akkor meg kell adni a levelt a constructorban hogy hova tartozik.
	Ezutan amikor akar valamit az actor, azt a level object - en keresztul lekerdezheti.

	LevelObject-ek:

	Ezek lehetnenek nem uniform objectek, azaz a meretuk lehetne tetszoleges (haz pl.), de lehetnenek nagy meretuek, amiket tile-olunk.
    Pl: viz, lava, sav az a palya minden reszere az igazi palya ala festene magat.

    Shadow, reflection:
    Ez is egy kulon actor lehetne. Eloszor a vizet rendereljuk, majd lekerdezzuk a player-t, hogy milyen "pozban" van, rarakjuk fejjel lefele a vizre,
    majd rendereljuk a tobbi reszet a palyanak.



    Palya rajzolas:

    Kell definialni egy "bounding box"-ot a kepernyo kozepetol. Ez lenne a visible area. Ezt lehetne allitani is a kodbol.
    Ezutan a palya azon elemeit rajzolnank ki ami legalabb egy kicsit ide belog.

    Kirajzolaskor display-elnenk egy piros rectangle-t ami ennek a bounding box-nak felel meg. Majd csinalnank egy elotesztelest.

    Ez csak a statikus objektumokat fedne csak le.
    Erre jonnenek ra az actor-ok.

    De ugyanez lenne a helyzet -> ha az actor nem latszik -> don't bother.
    Nem tudom mennyi frame-et nyernenk ezzel, hiszen a graphicscontext mar ezt megcsinalja nekunk (lehet hogy egy nagyobb overhead aran).
    Csak a visibility-t kene allitgatni es kesz. (persze jo lenne ha nem minden getter/setter segitsegevel lenne elerve).

    Viselkedes: lennenek kulonbozo behaviour-ok amiket hozza lehet rendelni az actorokhoz.
    Pl: PlayerBehaviour: az ember iranyitja a karaketert
        NPCBehaviour: csak acsorog es van egy idle animation-je, vagy csak maszkal ket pont kozott neha
        MonsterMildBehaviour: csak maszkal es megtamad ha eszrevesz, nem kovet tovabb ha kimesz a latoterebol
        MonsterDormantBehaviour: mint egy gargoyle alszik amig eleg kozel nem mesz es akkor felebred
        MonsterAgressiveBehaviour: chasing-el az egesz palyan

    AwerenessArea:
        Monsztak eseten az az area amiben eszrevesznek. Bossoknal nagyobb stb.
        NPC-knel az az area amibe belelepsz, akkor megszolitanak
        De egy "actor" lehet egy tooltip is ami csak bizonyos korulmenyek kozott jelenik meg (player segitseg: pl: itt ez a kapcsolo, meg nem lattal ilyet).
        A player character beszelhet magaban. Leirhatja a gondolatait.
    DrawAwerenessArea:
        Kirajzolja egy-egy actor awereness aurajat -> debug segitseg.


	AnimatedSprite
      +-> AnitmationPlayer
    Mi lenne az ertelme igy csinalni (Godot-modi)




[2020-10-27]

  AnimPlay get PlayerSpriteNode to update with current picture (set texture atlas & index)

  PlayerSpriteNode needs to be added to the scene.
  Not necessarily under the level shapenode

  We actually need to control in which order we draw things
  --> LevelDrawer need to draw the stuff.

  waterTileMap gets draw first
  floorTileMap gets drawn after

  utana vegigmegyunk a falakon/objecteken/lenyeken
  mindenen ami kiall a foldbol


  RougeLike egy orchastrator-nak kene csak lennie.
    - Megcsinalja a Level2d-t
    - Megcsinalja az actorokat
    - Megkeri a levelt, hogy Drawing-oljon mindent ki

  A Level2d meg:
    - tarolja a Tilemap-et
    - tarolja az actorokat
  
  Kinek a kezeben van a billentyuzet figyeles? Gondolom a RougeLike-eban



  RogueLike -> LevelManager

  LevelManager creates a Level2D, creates Actors.
  Level2D is a ShapeNode, where we override the Draw method.
  LevelManager can set the visibility of Level2D to false, show the loading screen, keep whatever data about the player and the level about and load the new level.
  LevelManager is a node and adds the correct Level2D to the scene.

  Nem! Kell egy LevelState object. Amit a LevelLoader keszit/randomizal/tolt be (varos, fo palyak).
  A LevelLoader-ben lesznek a rule-ok, hogy hogyan toltson be egy palyat.
  A LevelState-et kapja meg a Level2d ami egy ShapeNode.

  Level2d ez a class fogja kirajzolni a cuccokat (uj nev: LevelDrawer/LevelRenderer)
  Ennek a Draw funkcioja megkapja a LevelState-et es az Actorokat.
  Arguably az Actorok (a palya reszei), kiveve a playerek.




*/