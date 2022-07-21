// CDC2.h: interface for the CDC2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDC2_H__59172D66_76DE_49F4_ADBF_BFE563B3B5E8__INCLUDED_)
#define AFX_CDC2_H__59172D66_76DE_49F4_ADBF_BFE563B3B5E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDC2 : public CDC  
{
public:
	CDC2();
	virtual ~CDC2();
	CSize GetSize();
	void SetSize(CSize size);
	CSize msize;
};

#endif // !defined(AFX_CDC2_H__59172D66_76DE_49F4_ADBF_BFE563B3B5E8__INCLUDED_)
