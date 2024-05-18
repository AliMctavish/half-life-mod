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
	void Touch(CBaseEntity* pOther) override;

private:
	bool IsTriggerd = false;
};

LINK_ENTITY_TO_CLASS(trigger_my_ass, TestMyAss)

void TestMyAss::Spawn()
{
	// do nothing sir !
	// ALERT(at_console, "%s\n", STRING(pev->message));
	pev->nextthink = gpGlobals->time;
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_TRIGGER;
	SET_MODEL(edict(), STRING(pev->model));
}


void TestMyAss::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	if (pActivator->IsPlayer())
	{
		ALERT(at_console, "%s\n", "print me !");
		pActivator->pev->health = 100;
	}
}

void TestMyAss::Think()
{
	UTIL_Sparks(pev->origin);

	ALERT(at_console, "this is testmyass timer for think method");

	pev->nextthink = gpGlobals->time + 0.2;
}

void TestMyAss::Touch(CBaseEntity* pOther)
{
	if (pOther->IsPlayer())
	{
		ALERT(at_console, "teeeez");
		ExplosionCreate(pev->origin, pev->origin, edict(), 40, true);
		IsTriggerd = !IsTriggerd;
	}
}
