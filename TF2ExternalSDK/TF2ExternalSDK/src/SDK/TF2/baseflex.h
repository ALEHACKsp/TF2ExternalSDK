#pragma once
#include "baseanimating.h"

class CBaseFlex : public CBaseAnimating
{
public:
	NETVAR(m_flexWeight, void *, "CBaseFlex", "m_flexWeight");
	NETVAR(m_blinktoggle, int, "CBaseFlex", "m_blinktoggle");
	NETVAR(m_viewtarget, Vec3, "CBaseFlex", "m_viewtarget");
};

