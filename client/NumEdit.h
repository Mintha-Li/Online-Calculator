#pragma once
#include <afxwin.h>
class CNumEdit :
	public CEdit
{
public:
	CNumEdit(void);
	~CNumEdit(void);

public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void setRange(double min, double max);

protected:
	DECLARE_MESSAGE_MAP()

private:
	double maxValue;
	double minValue;
};

