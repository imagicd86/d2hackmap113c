// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#define _CRT_SECURE_NO_DEPRECATE        // ȥ���������������ȫ���
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "d2vars.h"
#include "d2structs.h"
#include "common.h"

#define FUNCTION_DECLARE
#include "global.h"
#undef FUNCTION_DECLARE

#include "d2callstub.h"

#define VARIABLE_DEFINE
#include "global.h"
#undef VARIABLE_DEFINE

