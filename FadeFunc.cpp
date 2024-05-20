#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFadeFunc : public CBaseEntity
{
public:
	void Spawn() override;
	void Think() override;
private:
	float looper;
	void FadeIn();
	void FadeOut();
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
}

void CFadeFunc::Think()
{
	ALERT(at_console, "the universe is expanding");
	pev->nextthink = gpGlobals->time + 1;
}

void CFadeFunc::FadeIn()
{
	pev->renderamt++;

	if (pev->renderamt >= 255)
		SetThink(&CFadeFunc::FadeOut);


	pev->nextthink = gpGlobals->time + 0.001;
}

void CFadeFunc::FadeOut()
{
	pev->renderamt--;
	if (pev->renderamt <= 0)
		SetThink(&CFadeFunc::FadeIn);

	pev->nextthink = gpGlobals->time + 0.001;
}
