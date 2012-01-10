#include "StdAfx.h"
#include "PublishRecord.h"

CPublishRecord::CPublishRecord(string str)
{
	fromString(str);
}

CPublishRecord::CPublishRecord()
{
}

CPublishRecord::~CPublishRecord(void)
{
}

string	CPublishRecord::toString()
{
	string	result;
	map<string, string>::iterator	iter;

	for ( iter = paras.begin(); iter != paras.end(); iter++ )
	{
		result += (*iter).first;
		result += "^";
		result += (*iter).second;
		result += "|";
	}
	return result;
}

void CPublishRecord::fromString(string str)
{
	int		b, e, m;
	string	k, v;

	b = 0;
	m = 0;
	e = str.find('|');

	while ( e != -1 )
	{
		m = str.find('^', b);
		if ( m != -1 )
		{
			k = str.substr(b, m-b);
			v = str.substr(m+1, e-m-1);
			paras[k] = v;
		}
		b = e+1;
		e = str.find('|', b);
	}
}

CString CPublishRecord::get(string key)
{
	string v = paras[key];
	return v.c_str();
}

void CPublishRecord::set(string key, CString value)
{
	string	v(value.GetBuffer());
	value.ReleaseBuffer();
	paras[key] = v;
}