#include "extdll.h"
#include "util.h"
#include "cbase.h"


class Trampoline : public CBaseEntity
{
	void Spawn() override;
	void Touch(CBaseEntity* pOther) override;
};

LINK_ENTITY_TO_CLASS(trigger_trampoline, Trampoline);

void Trampoline::Spawn()
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_TRIGGER;
	SET_MODEL(edict(), STRING(pev->model));
}

void Trampoline::Touch(CBaseEntity* pOther)
{
	if (pOther->IsPlayer())
	{
		pOther->pev->velocity.z+= 500;
		ALERT(at_console, "mother fuckeriuos");
	}
}
