#include "extdll.h"
#include "util.h"
#include "cbase.h"


class Trampoline : public CBaseEntity
{
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
	void Touch(CBaseEntity* pOther) override;
};

LINK_ENTITY_TO_CLASS(trigger_trampoline, Trampoline);

void Trampoline::Spawn()
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_TRIGGER;
	SET_MODEL(edict(), STRING(pev->model));
}

void Trampoline::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	if (pActivator->IsPlayer())
	{
		ALERT(at_console, "damn maaaaan");
	}
}

void Trampoline::Touch(CBaseEntity* pOther)
{
	if (pOther->IsPlayer())
	{
		pOther->pev->velocity.x+= 500;
		ALERT(at_console, "mother fuckeriuos");
	}
}
