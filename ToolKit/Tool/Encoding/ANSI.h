///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Convert other encoding string to be ANSI string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef ANSI_H
#define ANSI_H

#include "Tool/Common/SystemType.h"
#include "EncodeType.h"

namespace System
{
	namespace Encoding
	{
		class ANSI
		{
		public:
			typedef System::Int32 Index;
			typedef System::Int32 Length;
			typedef System::SByte SCharacter;
			typedef System::SByteArray SCharArray;
			typedef System::WByte WCharacter;
			typedef System::WByteArray WCharArray;
			typedef ENCODE_TYPE_ENUM EncodeType;
			typedef std::string StdString;
			typedef std::wstring WStdString;

		private:
			// Forbid construct the ANSI
			ANSI() {	}

			// Forbid destructe the ANSI
			~ANSI() {	}

			// Forbid the object copying
			ANSI(const ANSI& Another) {	}

			// Forbid the obejct assignment
			ANSI& operator=(const ANSI& Another) {	}

		public:
			// Get mutilbytes from Unicode array Notice: count must contain '\0'
			static StdString GetString(WCharArray UnicodeBuffer, 
				Index iPos, 
				Length iCount);

			// Get mutilbytes from Unicode string
			static StdString GetString(WStdString UnicodeString);

			// Get mutilbytes from multibyte array Notice: count must contain '\0'
			static StdString GetString(SCharArray MultibyteBuffer,
				Index iPos,
				Length iCount,
				EncodeType eEncodeType = ENCODE_ANSI);

			// Get mutilbytes from multibyte string
			static StdString GetString(StdString strMultiString,EncodeType eEncodeType = ENCODE_ANSI);

		private:
			// Convert UTF8 to Mutilbytes
			static StdString UTF8ToANSI(StdString UTF8String);

			// Convert Unicode to Mutilbytes
			static StdString UnicodeToANSI(WStdString UnicodeString);
		};
	}
}

#endif // ANSI_H