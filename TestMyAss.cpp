#include "extdll.h"
#include "util.h"
#include "cbase.h"


class TestMyAss : public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(trigger_my_ass, TestMyAss)

void TestMyAss::Spawn()
{
	// do nothing sir !
	ALERT(at_console, "%s\n", STRING(pev->message));
}


void TestMyAss::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	if (pActivator->IsPlayer())
	{
		pActivator->pev->health++;
		edict_t *ed;
		FIND_ENTITY_BY_CLASSNAME(ed, "Help");
		ALERT(at_console, "triggerd !!!!!!");
		ALERT(at_console, "the objects has been triggerd");
		// pCaller->pev->scale = 33.3f;
	}
}
