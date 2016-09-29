
#include"zlib.h"
#include<stdio.h>
#include<iostream>
using namespace std;




int main()
{
	
	
	char orgStr[125]= "hello hello hello hello hello.. hello" ;
	char compressionStr[125] = {};
	char deCompresionStr[125] = {};

	std::cout << " unCompression contents are: " << orgStr << "  length: " << strlen(orgStr) << endl;


	//Ñ¹Ëõ
	z_stream deflatStream;
	deflatStream.zalloc = Z_NULL;
	deflatStream.zfree = Z_NULL;
	deflatStream.opaque = Z_NULL;

	deflatStream.next_in = (Bytef*)orgStr;
	deflatStream.avail_in = (uInt)strlen(orgStr) + 1;
	deflatStream.next_out = (Bytef*)compressionStr;
	deflatStream.avail_out = (uInt)sizeof(compressionStr);

	deflateInit(&deflatStream, Z_BEST_COMPRESSION);
	deflate(&deflatStream,Z_FINISH);
	deflateEnd(&deflatStream);
	std::cout << "Compression contents are: " << compressionStr << "  length: " << deflatStream.total_out << endl;

	//½âÑ¹
	z_stream inflatStream;
	inflatStream.zalloc = Z_NULL;
	inflatStream.zfree = Z_NULL;
	inflatStream.opaque = Z_NULL;

	inflatStream.next_in = (Bytef*)compressionStr;
	inflatStream.avail_in = (uInt)((char*)deflatStream.next_out - compressionStr);
	inflatStream.next_out = (Bytef*)deCompresionStr;
	inflatStream.avail_out = (uInt)sizeof(deCompresionStr);

	inflateInit(&inflatStream);
	inflate(&inflatStream, Z_NO_FLUSH);
	inflateEnd(&inflatStream);
	std::cout << "deCompression content are: " << deCompresionStr << "  length: " << strlen(deCompresionStr) << endl;


	if (strcmp(orgStr,deCompresionStr))
	{
	cout << "zlib compression libary is bad." << endl;
	}
	else
	{
	cout << "zlib compression libary is amazing." << endl;
	}



	
	system("PAUSE");

	return 0;
}