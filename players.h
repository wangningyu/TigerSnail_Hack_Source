#ifndef _PLAYERS_H
#define _PLAYERS_H

#include "includes.h"
#include "gamespec.h"

/*
	TigerSnail Hack: Source

	Developed by sk0r / Czybik
	Credits: sk0r, OllyDbg, Source SDK

	Version: 0.5
	Visit: http://sk0r.sytes.net
	Mail Czybik_Stylez<0x40>gmx<0x2E>de

	File: players.h: Player manager interface
*/

//======================================================================
//Amount of client slots
#define MAX_CLIENTS 64

//ID translation and validity macros
#define MID_TO_EID(id) (id + 1)
#define EID_TO_MID(id) (id - 1)
#define VALID_MID(id) ((id >= 0) && (id < _countof(this->m_sPlayerData)))
#define VALID_EID(id) ((id > 0) && (id < _countof(this->m_sPlayerData) + 1))

//Drawing
#define LINE_DISTANCE 25
#define LINE_OFFSET(v) (v * LINE_DISTANCE)
#define PLAYER_TEAM_VISIBLE PLAYER_TEAM_SPEC

#define COLOR_OVERWRITE_NO this->m_sNoColorOverwrite
#define COLOR_OVERWRITE_GREY this->m_sGreyColor
//======================================================================

//======================================================================
typedef int EPLAYERID; //Engine entity id
typedef size_t MPLAYERID; //Manager entity id
//======================================================================

//======================================================================
enum player_team_e {
	PLAYER_TEAM_SPEC,
	PLAYER_TEAM_T,
	PLAYER_TEAM_CT
};
//======================================================================

//======================================================================
struct player_data_s { //Player related data
	bool bSlotUsed;
	bool bIsLocal;
	bool bVisible;
	bool bHudInfoAvailable;
	_C_BaseEntity* pEntity;
	_player_info_t sHudInfo;
	std::string szCurWeapon;
	int iTeam;
	Vector vScreenPos;
	bool bScreenPosValid;
	int iEngineId;
};
//======================================================================

//======================================================================
class CPlayerMgr {
private:
	player_data_s m_sPlayerData[MAX_CLIENTS];
	color24 m_sTeamColors[3];
	color24 m_sTeamPlayerModelColors[3];
	color32_s m_sNoColorOverwrite;
	color32_s m_sGreyColor;

	bool CalcScreen(const Vector& vWorldPos, Vector& vScreenPos);
	bool UpdateCurWeapon(const MPLAYERID uiEntIndex);
	bool IsVisible(const MPLAYERID uiEntIndex);
public:
	CPlayerMgr() { this->Reset(); this->m_sNoColorOverwrite.a = 0xFF; this->m_sGreyColor.r = this->m_sGreyColor.g = this->m_sGreyColor.b = 200; this->m_sGreyColor.a = 0; }
	~CPlayerMgr() {}

	void SetTeamColor(const byte ucSlot, const color24& sColor) { if (ucSlot >= 3) return; this->m_sTeamColors[ucSlot] = sColor; }
	void SetTeamPlayerModelColor(const byte ucSlot, const color24& sColor) { if (ucSlot >= 3) return; this->m_sTeamPlayerModelColors[ucSlot] = sColor; }

	void Reset(void);

	bool UpdateSlot(const EPLAYERID iEntIndex);
	bool UpdateSlot(const MPLAYERID uiEntIndex);

	inline size_t Count(void);

	player_data_s* Slot(const EPLAYERID iEntIndex);
	player_data_s* Slot(const MPLAYERID uiEntIndex);
	player_data_s* Local(void);

	bool IsPlaying(const EPLAYERID iEntIndex);
	bool IsPlaying(const MPLAYERID uiEntIndex);
	bool IsLocal(const MPLAYERID uiEntIndex) { if (!VALID_MID(uiEntIndex)) return false; return this->m_sPlayerData[uiEntIndex].bIsLocal; }

	float GetDistance(const MPLAYERID uiPlayerSrc, const MPLAYERID uiPlayerDst);

	bool DrawInfo(const MPLAYERID uiEntIndex, const std::string& szText, const byte ucLineId, const color32_s& clrColor/*, const bool bCentered*/);
	bool DrawName(const MPLAYERID uiEntIndex, const byte ucLineId/*, const bool bCentered*/);
	bool DrawDistance(const MPLAYERID uiEntIndex, const byte ucLineId/*, const bool bCentered*/);
	bool DrawWeapon(const MPLAYERID uiEntIndex, const byte ucLineId/*, const bool bCentered*/);
	bool DrawSteamID(const MPLAYERID uiEntIndex, const byte ucLineId/*, const bool bCentered*/);
	bool DrawHealth(const MPLAYERID uiEntIndex, const byte ucLineId/*, const bool bCentered*/);

	bool SetPlayerModelColor(const MPLAYERID uiEntIndex, const bool bEnable = true);

	int GetLocalPlayerTeam(void) { player_data_s* pLocalPlayerData = this->Local(); if (pLocalPlayerData) return pLocalPlayerData->iTeam; return -1; }

	inline color24 MakeColor24(int r, int g, int b)
	{ 
		color24 sColor;
		
		sColor.r = r;
		sColor.g = g;
		sColor.b = b;

		return sColor;
	}
};
//======================================================================

#endif
