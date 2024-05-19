#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "explode.h"


class TestMyAss : public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
	void Think() override;

private:
	bool IsTriggerd = false;
};

LINK_ENTITY_TO_CLASS(trigger_my_ass, TestMyAss)

void TestMyAss::Spawn()
{
	pev->nextthink = gpGlobals->time;
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_TRIGGER;
	SET_MODEL(edict(), STRING(pev->model));
}


void TestMyAss::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	pActivator->pev->origin.x++;
	if (pActivator->IsPlayer())
	{
		ALERT(at_console, "%s\n", "print me !");
		ALERT(at_console, "%f\n", pActivator->pev->origin.x);
		pActivator->pev->health = 100;
	}
}

void TestMyAss::Think()
{
	UTIL_Sparks(pev->origin);
	pev->nextthink = gpGlobals->time + 0.2;
}

