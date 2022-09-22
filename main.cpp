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

  �� ����Ʈ����� ��� ����� �Ǵ� ������ ������ ���� "�ִ� �״��" �����˴ϴ�. �� 
  � ��쿡�� �ۼ��ڴ� �� ����Ʈ������ ������� ���� ���ؿ� ���� å���� ���� �ʽ��ϴ�.

  ���� ���� ������ �ؼ��ϴ� ��쿡 ���Ͽ� ������� ���� ���α׷��� �����ϴ� ��� �뵵�� �� ����Ʈ��� 
  ����ϰ� �����Ӱ� ���� �� ������� �� �ִ� ������ �������Գ� �ο��˴ϴ�.

  1. �� ����Ʈ������ ��ó�� �߸� ǥ���ϰų� ���� ����Ʈ��� �ڽ��� �ۼ��ߴٰ� �����ؼ��� �� �˴ϴ�. ��ǰ�� 
     �� ����Ʈ��� ����ϴ� ��� �䱸 ������ �ƴ����� ��ǰ ������ ���� ������ �־� �ֽø� �����ϰڽ��ϴ�.
  2. ������ �ҽ� ������ �ݵ�� ��Ȯ�ϰ� ǥ�õǾ�� �ϸ� ���� ����Ʈ����� ���εǵ��� �߸� ǥ���ؼ��� �� �˴ϴ�.
  3. ��� �ҽ� ���� �� �� ������ �����ϰų� ������ �� �����ϴ�.

  =============================================================================================================
*/


#ifdef _WIN32
#	pragma warning( disable : 4786 )		// stl warning ���ֱ�
#	pragma warning( disable : 4996 )		// crt secure warning
#endif

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <locale.h>
#include "UnAlz.h"
#include "UnAlzUtils.h"

#include <sys/timeb.h>


BOOL	g_bPipeMode=FALSE;

void Copyright()
{
//	printf("unalz v0.20 (2004/10/22) \n");
//	printf("unalz v0.22 (2004/10/27) \n");
//	printf("unalz v0.23 (2004/10/30) \n");
//	printf("unalz v0.31 (2004/11/27) \n");
//	printf("unalz v0.4 (2005/06/18) \n");
//	printf("unalz v0.5 (2005/07/09) \n");
//	printf("unalz v0.51 (2005/07/24) \n");
//	printf("unalz v0.52 (2005/07/27) \n");
//	printf("unalz v0.53 (2005/10/15) \n");
//	printf("unalz v0.54 (2005/11/21) \n");
//	printf("unalz v0.55 (2006/03/10) \n");
//	printf("unalz v0.60 (2006/12/31) \n");
//	printf("unalz v0.61 (2007/02/10) \n");
//	printf("unalz v0.62 (2008/04/04) \n");
//	printf("unalz v0.63 (2009/01/09) \n");
//	printf("unalz v0.64 (2009/01/20) \n");
	printf("unalz v0.65 (2009/04/01) \n");
	printf("Copyright(C) 2004-2009 by kippler@gmail.com (http://www.kipple.pe.kr) \n");
}


void Usage()
{
	Copyright();

	printf("\n");
	/*
#ifdef _UNALZ_ICONV
		printf("USAGE : unalz [ -utf8 | -cp949 | -euc-kr ] sourcefile.alz [dest path] \n");
#	ifdef _UNALZ_UTF8
		printf("        -utf8  : convert filename's codepage to UTF-8 (default)\n");
		printf("        -cp949 : convert filename's codepage to CP949\n");
		printf("        -euc-kr: convert filename's codepage to EUC-KR\n");
#	else
		printf("        -utf8  : convert filename's codepage to UTF-8\n");
		printf("        -cp949 : convert filename's codepage to CP949 (default)\n");
		printf("        -euc-kr: convert filename's codepage to EUC-KR\n");
#	endif // _UNALZ_UTF8
#else		// no iconv
	printf("USAGE : unalz sourcefile.alz [dest path] \n");
#endif // _UNALZ_ICONV
	*/

	printf("Usage : unalz [<switches>...] archive.alz [<file names to extract>...]\n");

	printf("\n");
	printf("<switches>\n");
#ifdef _UNALZ_ICONV
#	ifdef _UNALZ_UTF8
		printf("  -utf8        : convert filename's codepage to UTF-8 (default)\n");
		printf("  -cp949       : convert filename's codepage to CP949\n");
		printf("  -euc-kr      : convert filename's codepage to EUC-KR\n");
#	else
		printf("  -utf8        : convert filename's codepage to UTF-8\n");
		printf("  -cp949       : convert filename's codepage to CP949 (default)\n");
		printf("  -euc-kr      : convert filename's codepage to EUC-KR\n");
#	endif // _UNALZ_UTF8
#endif // _UNALZ_ICONV
		printf("  -l           : list contents of archive\n");
		printf("  -d directory : set output directory\n");
		printf("  -p           : extract files to pipe, no messages\n");
		printf("  -pwd <pwd>   : set password\n");

}





void UnAlzCallback(const char* szFileName, INT64 nCurrent, INT64 nRange, void* param, BOOL* bHalt)
{
	if(g_bPipeMode) return;		// slient

#define MSG_BUF_LEN	1024
	// progress
	static char  szMessage[MSG_BUF_LEN]={0};
	static INT64 nPrevPercent = -1;
	INT64	percent;

	// ���ϸ� ���..
	if(szFileName)
	{
		printf("\n");
#ifdef _WIN32
		_snprintf(szMessage, MSG_BUF_LEN, "unalziiiing : %s (%I64dbytes) ", szFileName, nRange);
#else
		snprintf(szMessage, MSG_BUF_LEN, "unalziiiing : %s (%lldbytes) ", szFileName, nRange);
#endif
		printf("%s.", szMessage);
		fflush(stdout);
		nPrevPercent = -1;
		return;
	}

	percent = nCurrent*100/nRange;

	if(nPrevPercent/10==percent/10) return; 	// �ʹ� ���� ������Ʈ ����..
	nPrevPercent = percent;

	printf(".");
	fflush(stdout);

}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	if(argc<2)
	{
		Usage();
		return 0;
	}

	CUnAlz	unalz;
	char* source=NULL;
	const char* destpath=".";
	const char* destcodepage=NULL;
	char* password=NULL;
	int   count;
	BOOL  listMode = FALSE;
	vector<string>	filelist;

	/*	old method
	for (count=1 ; count < argc && argv[count][0] == '-'; ++count)
	{
#ifdef _UNALZ_ICONV
		// utf8 �ɼ� ó��
		if(strcmp(argv[count], "-utf8")==0)
		{
			destcodepage = "UTF-8";				// utf-8 support
		}
		else if(strcmp(argv[count], "-cp949")==0)
		{
			destcodepage = "CP949";				// cp949 
		}
		else if(strcmp(argv[count], "-euc-kr")==0)
		{
			destcodepage = "EUC-KR";			// EUC-KR
		}
		else
#endif
		if(strcmp(argv[count], "-l")==0 || strcmp(argv[count], "-list")==0)
		{
			listMode = TRUE;
		}
	}

#ifdef _UNALZ_ICONV
	if(count>=argc)	{Usage();return 0;}		// �ɼǸ� ���� ��¼���..
	if(destcodepage) unalz.SetDestCodepage(destcodepage);
#endif

	// �ҽ� ����
	source=argv[count];						
	count++;

	// ��� ���
	if(count<argc)							
	{
		destpath = argv[count];
		count++;
	}
	*/

	for (count=1 ; count < argc; count++)
	{
#ifdef _UNALZ_ICONV
		// utf8 �ɼ� ó��
		if(strcmp(argv[count], "-utf8")==0)
		{
			destcodepage = "UTF-8";				// utf-8 support
		}
		else if(strcmp(argv[count], "-cp949")==0)
		{
			destcodepage = "CP949";				// cp949 
		}
		else if(strcmp(argv[count], "-euc-kr")==0)
		{
			destcodepage = "EUC-KR";			// EUC-KR
		}
		else
#endif
		if(strcmp(argv[count], "-l")==0 || strcmp(argv[count], "-list")==0)
		{
			listMode = TRUE;
		}
		else if(strcmp(argv[count], "-p")==0)
		{
			g_bPipeMode = TRUE;
		}
		else if(strcmp(argv[count], "-d")==0)		// dest dir
		{
			count++;
			if(count>=argc)	{Usage();return 0;}	// dest dir �� ���� �������� �ʾҴ�..
			destpath = argv[count];
		}
		else if(strcmp(argv[count], "-pwd")==0)		// pwd
		{
			count++;
			if(count>=argc)	{Usage();return 0;}	// dest dir �� ���� �������� �ʾҴ�..
			password = argv[count];
		}
		else									// �ɼ��� �ƴ� ���
		{
			if(source==NULL)					// �ҽ� ���� ���
			{
				source=argv[count];							
			}
			else								// ����Ǯ ���� 
			{
				filelist.push_back(argv[count]);
			}
		}
	}

	if(source==NULL) {Usage();return 0;}		// �ɼǸ� ���� ��¼���..

#ifdef _UNALZ_ICONV
	if(destcodepage) unalz.SetDestCodepage(destcodepage);
#endif


	if(g_bPipeMode==FALSE)
		Copyright();						// copyright ǥ��

	// pipe mode setting
	unalz.SetPipeMode(g_bPipeMode);

	// ���� ����
	if(unalz.Open(source)==FALSE)
	{
		if(unalz.GetLastErr()==CUnAlz::ERR_CORRUPTED_FILE)
		{
			printf("It's corrupted file.\n");		// �׳� ��� Ǯ��..
		}
		else
		{
			printf("file open error : %s\n", source);
			printf("err code(%d) (%s)\n", unalz.GetLastErr(), unalz.GetLastErrStr());
			return 0;
		}
	}

	if (listMode)
	{
		return ListAlz(&unalz, source);
	}
	else
	{
		if(unalz.IsEncrypted())
		{
			if(password)						// command line ���� ��ȣ�� �����Ǿ��� ���.
			{
				unalz.SetPassword(password);
			}
			else
			{
				char temp[256];
				char pwd[256];
				printf("Enter Password : ");
				fgets(temp,256,stdin);
				sscanf(temp, "%s\n", pwd);		// remove \n
				unalz.SetPassword(pwd);
			}
		}

		if(g_bPipeMode==FALSE)
			printf("\nExtract %s to %s\n", source, destpath);

		// callback �Լ� ����
		unalz.SetCallback(UnAlzCallback, (void*)NULL);

		if (filelist.empty()==false)		// ���� �����ϱ�.
		{
			vector<string>::iterator i;
			for(i=filelist.begin();i<filelist.end();i++)
			{
				if(unalz.SetCurrentFile(i->c_str())==FALSE)
				{
					if(g_bPipeMode==FALSE)
						printf("filename not matched : %s\n", i->c_str());
				}
				else
					unalz.ExtractCurrentFile(destpath);
			}
		}
		else								// ��� ���� ��Ǯ��.
		{
			if(unalz.ExtractAll(destpath)==FALSE)
			{
				if(g_bPipeMode==FALSE)
				{
					printf("\n");
					printf("extract %s to %s failed.\n", source, destpath);
					printf("err code(%d) (%s)\n", unalz.GetLastErr(),
						   unalz.GetLastErrStr());
				}
			}
		}
		if(g_bPipeMode==FALSE)
			printf("\ndone.\n");
	}

	return 0;
}
