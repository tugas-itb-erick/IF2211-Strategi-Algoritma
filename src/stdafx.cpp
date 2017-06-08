// stdafx.cpp : source file that includes just the standard includes
// SampleBot.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

int Min2(int e, int f){
	if (e<0)
		return f;
	else
	{
		if (f<0)
			return e;
		else
		{
			if (e<f)
				return e;
			else
				return f;
		}
	}
}

int MinDistance(int a, int b, int c){
	return Min2(Min2(a,b),c);
}
