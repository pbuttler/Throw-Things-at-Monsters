#include <vix_game.h>
#include "gameobject.h"
#include "player.h"

#define GLRENDERER ((GLRenderer*)m_renderer)

using namespace Vixen;

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
	Player      p;
};

TestGame::TestGame()
	: IGame()
{
	
}

void TestGame::VOnStartup(void)
{
	font = m_content.LoadFont(VTEXT("Consolas_24.fnt"));
	p.SetTexture(m_content.LoadTexture(VTEXT("player.png")));
	p.SetOrigin(Vector2(16, 16));
	p.SetPosition(Vector2(20,20));

}

void TestGame::VOnUpdate(float dt)
{
	p.VHandleInput(m_keyboard, m_mouse);
	p.VUpdate(dt);
}

void TestGame::VOnRender(float dt)
{
	p.VRender(GLRENDERER, dt);
	
}

void TestGame::VOnShutdown(void)
{

}

int main(int argc, char* argv[])
{
	TestGame game;

	return game.Run();
}