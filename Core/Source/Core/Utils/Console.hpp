#pragma once

namespace Core::Console
{
	namespace Foreground
	{
		inline const char* BLACK = "\x1B[30m";
		inline const char* RED = "\x1B[31m";
		inline const char* GREEN = "\x1B[32m";
		inline const char* YELLOW = "\x1B[33m";
		inline const char* BLUE = "\x1B[34m";
		inline const char* MAGENTA = "\x1B[35m";
		inline const char* CYAN = "\x1B[36m";
		inline const char* WHITE = "\x1B[37m";
		inline const char* BRIGHT_BLACK = "\x1B[90m";
		inline const char* BRIGHT_RED = "\x1B[91m";
		inline const char* BRIGHT_GREEN = "\x1B[92m";
		inline const char* BRIGHT_YELLOW = "\x1B[93m";
		inline const char* BRIGHT_BLUE = "\x1B[94m";
		inline const char* BRIGHT_MAGENTA = "\x1B[95m";
		inline const char* BRIGHT_CYAN = "\x1B[96m";
		inline const char* BRIGHT_WHITE = "\x1B[97m";
	}

	namespace Background
	{
		inline const char* BLACK = "\x1B[40m";
		inline const char* RED = "\x1B[41m";
		inline const char* GREEN = "\x1B[42m";
		inline const char* YELLOW = "\x1B[43m";
		inline const char* BLUE = "\x1B[44m";
		inline const char* MAGENTA = "\x1B[45m";
		inline const char* CYAN = "\x1B[46m";
		inline const char* WHITE = "\x1B[47m";
		inline const char* BRIGHT_BLACK = "\x1B[100m";
		inline const char* BRIGHT_RED = "\x1B[101m";
		inline const char* BRIGHT_GREEN = "\x1B[102m";
		inline const char* BRIGHT_YELLOW = "\x1B[103m";
		inline const char* BRIGHT_BLUE = "\x1B[104m";
		inline const char* BRIGHT_MAGENTA = "\x1B[105m";
		inline const char* BRIGHT_CYAN = "\x1B[106m";
		inline const char* BRIGHT_WHITE = "\x1B[107m";
	}
}