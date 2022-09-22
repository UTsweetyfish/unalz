/*
  UNALZ : read and extract module for ALZ format.

  LICENSE (zlib License)
  Copyright (C) 2004-2009 kippler@gmail.com , http://www.kipple.pe.kr

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  �� ����Ʈ����� ��� ������ �Ǵ� ������ ������ ���� "�ִ� �״��" �����˴ϴ�. �� 
  � ��쿡�� �ۼ��ڴ� �� ����Ʈ������ ������� ���� ���ؿ� ���� å���� ���� �ʽ��ϴ�.

  ���� ���� ������ �ؼ��ϴ� ��쿡 ���Ͽ� ������� ���� ���α׷��� �����ϴ� ��� �뵵�� �� ����Ʈ��� 
  ����ϰ� �����Ӱ� ���� �� ������� �� �ִ� ������ �������Գ� �ο��˴ϴ�.

  1. �� ����Ʈ������ ��ó�� �߸� ǥ���ϰų� ���� ����Ʈ��� �ڽ��� �ۼ��ߴٰ� �����ؼ��� �� �˴ϴ�. ��ǰ�� 
     �� ����Ʈ��� ����ϴ� ��� �䱸 ������ �ƴ����� ��ǰ �������� ���� ������ �־� �ֽø� �����ϰڽ��ϴ�.
  2. ������ �ҽ� ������ �ݵ�� ��Ȯ�ϰ� ǥ�õǾ�� �ϸ� ���� ����Ʈ����� ���εǵ��� �߸� ǥ���ؼ��� �� �˴ϴ�.
  3. ��� �ҽ� ���� �� �� ������ �����ϰų� ������ �� �����ϴ�.

  =============================================================================================================
*/



////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// unalz ���� ��ƿ ����
/// 
/// @author   kippler@gmail.com
/// @date     2005-06-23 ���� 9:55:34
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _UNALZ_UTILS_H_
#define _UNALZ_UTILS_H_


#include "UnAlz.h"




time_t	dosTime2TimeT(UINT32 dostime);
int		ListAlz(CUnAlz* pUnAlz, const char* src);





#endif // _UNALZ_UTILS_H_