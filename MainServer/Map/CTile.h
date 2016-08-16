#ifndef _CTILE_
#define _CTILE_

#include <map>
#include <list>
#include <mutex>
#include <math.h>

#include "../GameCharacter/CPlayer.h"
#include "../GameCharacter/CNPC.h"

typedef std::map<int, CCharacter*> CharacterMap;
typedef std::map<int, CPlayer*> PlayerMap;
typedef std::map<int, CNPC*> NPCMap;
typedef std::list<CCharacter*> CharacterList;
typedef std::list<CPlayer*> PlayerList;
typedef std::list<CNPC*> NPCList;

class CTile
{
	std::mutex m_mxThis;

	//CharacterMap m_mCharacter;

	PlayerMap m_mPlayer;
	NPCMap m_mNPC;

public:
	CTile() {}

	void Add(CCharacter *pCharacter);
	void Remove(CCharacter *pCharacter);

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	// Remember to run m_Access.Release on each used object in the list.
	void GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list);

	void SendPacket(CCharacter *pCharacter, Packet& packet);

	void SendMoveAction(CCharacter *pCharacter, char byX, char byY, 
		Packet& createPacket, Packet& deletePacket, Packet& movePacket);
};

#endif