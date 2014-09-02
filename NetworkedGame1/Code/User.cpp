#include "User.hpp"
#include "Connection.hpp"
#include "Primitives/Color3b.hpp"

User::User()
{

}

GamePacket User::sendInput()
{
	if (m_userType == USER_REMOTE)
	{
		return GamePacket();
	}
	else
	{
		Color3b tempColor = Color3b(m_unit.m_color);
		GamePacket outPacket = {2, tempColor.r, tempColor.g, tempColor.b, m_unit.m_position.x, m_unit.m_position.y};
		g_serverConnection->sendPacket(outPacket);
	}
}

void User::update(float deltaSeconds)
{
	m_unit.update(deltaSeconds);
	sendInput();
}

void User::render()
{
	m_unit.render();
}