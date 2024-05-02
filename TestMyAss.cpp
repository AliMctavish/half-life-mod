#include "extdll.h"
#include "util.h"
#include "cbase.h"


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
	pev->nextthink = gpGlobals->time + 0.2;

	if (IsTriggerd)
		pev->velocity.x++;
	else
		pev->velocity.z++;
}

void TestMyAss::Touch(CBaseEntity* pOther)
{
	if (pOther->IsPlayer())
	{
		ALERT(at_console, "the universe is expanding");
		IsTriggerd = !IsTriggerd;
	}
}
