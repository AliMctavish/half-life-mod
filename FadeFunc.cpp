#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFadeFunc : public CBaseEntity
{
public:
	void Spawn() override;

private:
	bool KeyValue(KeyValueData* pkvd) override;
	void FadeIn();
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
	void FadeOut();
	int m_printMode = at_console;
	CBaseEntity* e = nullptr;
	bool m_clicked = false;
};

LINK_ENTITY_TO_CLASS(fade_function, CFadeFunc)

void CFadeFunc::Spawn()
{
	PRECACHE_MODEL("models/zombie.mdl");
	SET_MODEL(edict(), "models/zombie.mdl");
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSHSTEP;
	pev->rendermode = kRenderTransTexture;
	pev->renderamt = 128;
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_FLY;
	SetThink(&CFadeFunc::FadeIn);
	pev->nextthink = gpGlobals->time;
	e = UTIL_FindEntityByTargetname(e, "test");
}


bool CFadeFunc::KeyValue(KeyValueData* pkvd)
{
	if (FStrEq(pkvd->szKeyName, "printMode"))
	{
		m_printMode = atoi(pkvd->szValue);
		pkvd->fHandled = true;
		return true;
	}
	else
		return CBaseEntity::KeyValue(pkvd);
}

void CFadeFunc::FadeIn()
{
	CBaseEntity* player = CBaseEntity::Instance(g_engfuncs.pfnPEntityOfEntIndex(1));
	auto distance = player->pev->origin - pev->origin;
	pev->velocity = distance;
	float nor = atan2(distance.x, distance.y) * -1;
	pev->angles = Vector(0, (nor * 50) + 70, 0);
	pev->renderamt++;

	if (pev->renderamt >= 255)
		SetThink(&CFadeFunc::FadeOut);

	if (Intersects(player))
	{
		player->pev->health--;
		ALERT((ALERT_TYPE)m_printMode, "your health is decreasing !n\\");
		ALERT((ALERT_TYPE)m_printMode, "health : %f", pev->health);
	}


	if (m_clicked)
		e->pev->velocity.z++;

	pev->nextthink = gpGlobals->time + 0.0001;
}

void CFadeFunc::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	if (pActivator->IsPlayer() && e != nullptr)
		m_clicked = true;
}

void CFadeFunc::FadeOut()
{
	pev->renderamt--;
	if (pev->renderamt <= 0)
		SetThink(&CFadeFunc::FadeIn);

	pev->nextthink = gpGlobals->time + 0.0001;
}