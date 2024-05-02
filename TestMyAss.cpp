#include "extdll.h"
#include "util.h"
#include "cbase.h"


class TestMyAss : public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
	void Think() override;
};

LINK_ENTITY_TO_CLASS(trigger_my_ass, TestMyAss)

void TestMyAss::Spawn()
{
	// do nothing sir !
	//ALERT(at_console, "%s\n", STRING(pev->message));
	pev->nextthink = gpGlobals->time;
	//SET_MODEL(edict(), STRING(pev->model));
}


void TestMyAss::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	if (pActivator->IsPlayer())
	{
		//pActivator->pev->health++;
		pActivator->pev->takedamage++;
	}

}

void TestMyAss::Think()
{
	UTIL_Sparks(pev->origin);
	pev->nextthink = gpGlobals->time + 0.2;
}
