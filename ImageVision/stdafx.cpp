// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ImageVision.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


__global g;

#ifdef _HALCON
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}
#endif

CString show_roi_msg(UINT id)
{
	switch (id)
	{
	case TROI_RECT:return L"�뻭�����������ģ���";
	case TCHAR_RECT:return L"�뻭��������ַ�ģ���";
	case BROI_RECT:return L"�뻭�ײ��������ģ���";
	case BCHAR_RECT:return L"�뻭�ײ�����ַ�ģ���";
	case TDROI_RECT1:return L"�뻭���һ�¿�һ����";
	case TDROI_RECT2:return L"�뻭���һ�¿׶�����";
	case BDROI_RECT1:return L"�뻭������¿�һ����";
	case BDROI_RECT2:return L"�뻭������¿׶�����";
	case TNROI_RECT:return L"�뻭���һ�ų���";
	case BNROI_RECT:return L"�뻭������ų���";
	default:return L""; break;
	}
}

CSerialPort port;