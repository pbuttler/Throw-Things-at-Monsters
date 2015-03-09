#include <vix_game.h>
#include <vector>
#include "gameobject.h"
#include "player.h"
#include "Item.h"
#include "Enemy.h"

#define GLRENDERER ((GLRenderer*)m_renderer)

using namespace Vixen;

typedef std::vector<Item*> ItemList;
typedef std::vector<Enemy*> EnemyList;

class TestGame : public IGame
{
public:
	TestGame();

	virtual void VOnStartup(void)    override;
	virtual void VOnUpdate(float dt) override;
	virtual void VOnRender(float dt) override;
	virtual void VOnShutdown(void)   override;

public:
	BMFont*		font;
	Texture*    playerTex;
	Texture*    splatTex;
	Texture*    itemTex;
	Texture*	enemyTex;
	Texture*    heartTex;
	Texture*    barInnerTex;
	Texture*    barOuterTex;
	Player      p;
	ItemList    items;
	EnemyList   enemies;
	
};

TestGame::TestGame()
	: IGame()
{
	
}

void TestGame::VOnStartup(void)
{

	GLRENDERER->VSetClearColor(Colors::Black);

	srand(time(NULL));

	font = m_content.LoadFont(VTEXT("Consolas_24.fnt"));
	playerTex = m_content.LoadTexture(VTEXT("player.png"));
	itemTex = m_content.LoadTexture(VTEXT("rock.png"));
	enemyTex = m_content.LoadTexture(VTEXT("enemy.png"));
	splatTex = m_content.LoadTexture(VTEXT("zombie_splat.png"));
	heartTex = m_content.LoadTexture(VTEXT("heart.png"));
	barInnerTex = m_content.LoadTexture(VTEXT("bar_inner.png"));
	barOuterTex = m_content.LoadTexture(VTEXT("bar_outer.png"));
	p.SetTexture(playerTex);
	p.SetOrigin(Vector2(16, 16));
	p.SetPosition(Vector2(20,20));

	Item* item = new Item("Rock", 1.0, 1.0, 1.0);
	item->SetTexture(itemTex);
	item->SetPosition(Vector2(100,100));
	item->SetOrigin(Vector2(16, 16));
	items.push_back(item);

	// set up enemy
	Enemy* enemy1 = new Enemy("", 1, p, splatTex);
	for(int i = 0; i < 10; i++)
	{
		int rX = rand() % 800;
		int rY = rand() % 600;
		enemy1->SetPosition(Vector2(rX, rY));
		enemy1->SetTexture(enemyTex);
		enemy1->SetOrigin(Vector2(16, 16));
		enemies.push_back(enemy1);
		enemy1 = new Enemy("", 1, p, splatTex);
	}
	
}

void TestGame::VOnUpdate(float dt)
{

	if(m_keyboard->SingleKeyPress(IKEY::F1)) {
		static bool fs = false;
		fs = !fs;
		m_window->VSetFullscreen(fs);
	}
	if(m_keyboard->SingleKeyPress(IKEY::F2)) {
		//revive all zombies, for testing
		for(auto& e : enemies)
			e->revive();
	}
	p.VHandleInput(m_keyboard, m_mouse, dt);
	p.VUpdate(dt);

	for(auto& item : items) {
		item->VUpdate(dt);
		Rect r = p.GetBounds();
		Rect t = item->GetBounds();
		if(item->GetActive()) {
			if(r.Intersects(t)) {
				if(item->GetOnGround()) {
					USStream ss;
					ss << "Picked up: " << item->GetName();
					DebugPrintF(ss.str().c_str());
					p.PickUpItem(item);
				}
			}
		}
	}

	for(auto& e : enemies) {
		if(e->IsAlive())
		{
			e->seekPlayer(p);
			e->VUpdate(dt);
			if(e->GetBounds().Intersects(p.GetBounds()))
			{
				e->explode();
				p.TakeDamage();
			}
			Item* lastPThrownItem = p.GetLastThrownItem();
			if(lastPThrownItem) {
					if(lastPThrownItem->GetInAir()) {
					if(e->GetBounds().Intersects(lastPThrownItem->GetBounds())) {
						e->explode();
					}
				}
			}
		}
	}
}

void TestGame::VOnRender(float dt)
{
	
	for(auto& item : items)
		item->VRender(GLRENDERER, dt);

	for(auto& e : enemies)
		e->VRender(GLRENDERER, dt);


	//PLAYER SHOULD BE DRAWN AFTER THE ENEMIES AND ITEMS
	p.VRender(GLRENDERER, dt);

	//USStream ss;
	//ss << "Throw Power: " << p.GetThrowPower() * 50.0f;
	GLRENDERER->Render2DTexture((GLTexture*)barOuterTex, Vector2(20, m_window->VGetClientBounds().h - 40),
		Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, Colors::White, 0.0f);
	GLRENDERER->Render2DTexture((GLTexture*)barInnerTex, Vector2(20, m_window->VGetClientBounds().h - 40),
		Rect(0, 0, (p.GetThrowPower() / 1.0f) * 256.0f, 32), Vector2::Zero, Vector2::Unit, 0.0f, Colors::Green, 0.0f);
	//GLRENDERER->Render2DText(font, ss.str(), Vector2(20, m_window->VGetClientBounds().h - 30), Colors::White);

	for(int i = 0; i < p.GetHP(); i++)
	{
		GLRENDERER->Render2DTexture((GLTexture*)heartTex, Vector2(20 + i*32, m_window->VGetClientBounds().h - 75),
			Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, Colors::White, 0.0f);
	}
}

void TestGame::VOnShutdown(void)
{

}

int main(int argc, char* argv[])
{
	TestGame game;

	return game.Run();
}