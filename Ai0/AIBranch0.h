// AIBranch0.h: interface for the AIBranch0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIBRANCH0_H__DFACA325_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
#define AFX_AIBRANCH0_H__DFACA325_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AIBranch0  
{
public:
	AIBranch0();
	virtual ~AIBranch0();
	
	byte Player;
	word NIndex;

	bool IsBuilder();
	bool IsArcher();

	//bool GetPunchResult(AIBranch* Enemy, int& Give, int& Take);

};

#endif // !defined(AFX_AIBRANCH0_H__DFACA325_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
