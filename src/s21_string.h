#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#ifndef NULL
/**
 * @brief An integer constant expression with the value 0 cast
 * to the type void*
 */
#define NULL ((void *)0)
#endif  // NULL

#ifndef _SIZE_T
#define _SIZE_T unsigned long
/**
 * @brief An unsigned integer type that can store the maximum size
 * of a theoretically possible object of any type
 */
typedef _SIZE_T size_t;
#endif  // _SIZE_T

/**
 * @brief Searches for the first occurrence of the character c (unsigned type)
 * in the first n bytes of the string pointed to by str.
 *
 * @param str Pointer to the object to be examined.
 * @param c Character to search for.
 * @param n Number of bytes to examine.
 * @return Pointer to the location of the byte, or a null pointer if no such
 * byte is found.
 */
void *s21_memchr(const void *str, int c, size_t n);

/**
 * @brief Compares the first n bytes of str1 and str2.
 *
 * @param str1 Pointer to the object to compare.
 * @param str2 Pointer to the object to compare.
 * @param n Number of bytes to examine.
 * @return Negative value if str1 appears before str2 in lexicographical order.
 * Zero if str1 and str2 compare equal, or if count is zero.
 * Positive value if str1 appears after str2 in lexicographical order.
 */
int s21_memcmp(const void *str1, const void *str2, size_t n);

/**
 * @brief Copies n bytes from src to dest.
 *
 * @param dest Pointer to the object to copy to.
 * @param src Pointer to the object to copy from.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 */
void *s21_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Function to copy n bytes from src to dest.
 *
 * @param dest Pointer to the object to copy to.
 * @param src Pointer to the ob.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 */
void *s21_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Copies the character c (an unsigned type) to the first
 * n characters of the string pointed to by str.
 *
 * @param str Pointer to the object to fill.
 * @param c Byte to fill.
 * @param n Number of bytes to fill.
 * @return Pointer to str.
 */
void *s21_memset(void *str, int c, size_t n);

/**
 * @brief Appends the string pointed to by src to the end of the string
 * pointed to by dest.
 *
 * @param dest Pointer to the cstring to append to.
 * @param src Pointer to the cstring to copy from.
 * @return Pointer to dest.
 */
char *s21_strcat(char *dest, const char *src);

/**
 * @brief Appends the string pointed to by src to the end of the string
 * pointed to by dest, up to n characters long.
 *
 * @param dest Pointer to the cstring to append to.
 * @param src  Pointer to the cstring to copy from.
 * @param n Number of characters to copy.
 * @return Pointer to dest.
 */
char *s21_strncat(char *dest, const char *src, size_t n);

/**
 * @brief Searches for the first occurrence of the character c (unsigned type)
 * in the string pointed to by str.
 *
 * @param str Pointer to cstring to be analyzed.
 * @param c Character to search for.
 * @return Pointer to the found character in str;
 * NULL pointer otherwise.
 */
char *s21_strchr(const char *str, int c);

/**
 * @brief Compares the string pointed to by str1 with the string pointed to by
 * str2.
 *
 * @param str1 Pointer to the cstring to compare.
 * @param str2 Pointer to the cstring to compare.
 * @return Negative value if str1 appears before str2 in lexicographical order.
 * Zero if str1 and str2 equal
 * Positive value if str1 appears after str2 in lexicographical ordef.
 */
int s21_strcmp(const char *str1, const char *str2);

/**
 * @brief Compares at most the first n bytes of str1 and str2.
 *
 * @param str1 Pointer to the cstring to compare.
 * @param str2 Pointer to the cstring to compare.
 * @param n Number of characters to compare
 * @return Negative value if str1 appears before str2 in lexicographical order.
 * Zero if str1 and str2 equal
 * Positive value if str1 appears after str2 in lexicographical ordef.
 */
int s21_strncmp(const char *str1, const char *str2, size_t n);

/**
 * @brief Copies the string pointed to by src to dest.
 *
 * @param dest Pointer to the character array to write to
 * @param src Pointer to the cstring to copy from
 * @return Pointer to dest
 */
char *s21_strcpy(char *dest, const char *src);

/**
 * @brief Copies up to n characters from the string pointed to by src to dest.
 *
 * @param dest Pointer to the character array to copy to
 * @param src Pointer to the cstring to copy from
 * @param n Number of characters to copy
 * @return Pointer to dest
 */
char *s21_strncpy(char *dest, const char *src, size_t n);

/**
 * @brief Calculates the length of the initial segment of str1,
 * which consists entirely of characters not in str2.
 *
 * @param str1 Pointer to the cstring to be analyzed
 * @param str2 Pointer to the cstring that contains the characters to search for
 * @return The length of the maximum initial segment
 */
size_t s21_strcspn(const char *str1, const char *str2);

/**
 * @brief Searches the internal array for the error number errnum and
 * returns a pointer to the string containing the error message.
 *
 * @param errnum Integral value reffering to an error code
 * @return Pointer to a cstring corresponding to the s21_sys_errlist error code
 */
char *s21_strerror(int errnum);

/**
 * @brief Calculates the length of the string str, not including the terminating
 * null character.
 *
 * @param str Pointer to the cstring to be examined
 * @return The length of the cstring
 */
size_t s21_strlen(const char *str);

/**
 * @brief Finds the first character in str1 that matches any character specified
 * in str2.
 *
 * @param str1 Pointer to the cstring to be analyzed
 * @param str2 Pointer to the cstring that contains the characters to search for
 * @return Pointer to the first character in dest or null pointer
 * if no such character exists
 */
char *s21_strpbrk(const char *str1, const char *str2);

/**
 * @brief Searches for the last occurrenceof the character c
 * (unsigned type) in the string pointed to by str.
 *
 * @param str Pointer to the cstring to be analyzed
 * @param c Character to search for
 * @return Pointer to the found character
 */
char *s21_strrchr(const char *str, int c);

/**
 * @brief Calculates the length of the initial segment of str1,
 * which consists entirely of the characters of str2.
 *
 * @param str1 Pointer to the cstring to be analyzed
 * @param str2 Pointer to the cstring that contains the characters to search for
 * @return The length of the maximum initial segment of str1
 */
size_t s21_strspn(const char *str1, const char *str2);

/**
 * @brief Finds the first occurrence of the entire string needle (not including
 * the terminating null character) that appears in the string haystack.
 *
 * @param haystack Pointer to the cstring to examine
 * @param needle Pointer to the cstring to search for
 * @return Pointer to the first character of the found substring in str or null
 * if such substring is not found
 */
char *s21_strstr(const char *haystack, const char *needle);

/**
 * @brief Splits the string str into a series of tokens separated by delim.
 *
 * @param str Pointer to the cstring to tokenize
 * @param delim Pointer to the cstring identifying delimiters
 * @return Pointer to the beginning of the next token or null if there are no
 * more tokens
 */
char *s21_strtok(char *str, const char *delim);

/**
 * @brief Returns a copy of string (str) converted to uppercase.
 *
 * @param str Pointer to the cstring to convert
 * @return Pointer to allocated memory with uppercase cstring pointed by str.
 * (needs to be freed)
 */
void *s21_to_upper(const char *str);

/**
 * @brief Returns a copy of string (str) converted to lowercase. In case
 * of any error, return NULL
 *
 * @param str Pointer to the cstring to convert
 * @return Pointer to allocated memory with lowercase cstring pointed by str.
 * (needs to be freed)
 */
void *s21_to_lower(const char *str);

/**
 * @brief Returns a new string in which a specified string (str) is inserted at
 * a specified index position (start_index) in the given string (src). In case
 * of any error, return NULL
 *
 * @param src Pointer to the cstring to insert to
 * @param str Pointer to the cstring to insert from
 * @param start_index Index position in src to insert str
 * @return Pointer to allocated memory with inserted str into src.
 * (needs to be freed)
 */
void *s21_insert(const char *src, const char *str, size_t start_index);

/**
 * @brief Returns a new string in which all leading and trailing occurrences of
 * a set of specified characters (trim_chars) from the given string (src) are
 * removed. In case of any error, return NULL
 *
 * @param src Pointer to the cstring to be trimmed
 * @param trim_chars Pointer to the cstring that contains the characters by wich
 * trimmed
 * @return Pointer to allocated memory with trimmed src. (needs to be freed)
 */
void *s21_trim(const char *src, const char *trim_chars);

/**
 * @brief Sends formatted output to a string pointed to, by str.
 *
 * @param buff Pointer to a character array to write to
 * @param format Pointer to a cstring specifying how to interpret the data
 * @param ... Arguments specifying data to print.
 * @return Number of characters written to buffer or an EOF if an encoding error
 */
int s21_sprintf(char *buff, const char *format, ...);

/**
 * @brief Reads formatted input from a string
 *
 * @param str Pointer to cstring to read from
 * @param format Pointer to cstring specifying how to read the input
 * @param ... Receiving arguments
 * @return Number of receiving arguments successfully assigned or an EOF if
 * input faliure occurs before the first receiving argument
 */
int s21_sscanf(const char *str, const char *format, ...);

#if defined(__APPLE__)

#define S21_ERRLIST_SIZE 107

static const char *const s21_sys_errlist[S21_ERRLIST_SIZE] = {
    [0] = "Undefined error: 0",
    [1] = "Operation not permitted",
    [2] = "No such file or directory",
    [3] = "No such process",
    [4] = "Interrupted system call",
    [5] = "Input/output error",
    [6] = "Device not configured",
    [7] = "Argument list too long",
    [8] = "Exec format error",
    [9] = "Bad file descriptor",
    [10] = "No child processes",
    [11] = "Resource deadlock avoided",
    [12] = "Cannot allocate memory",
    [13] = "Permission denied",
    [14] = "Bad address",
    [15] = "Block device required",
    [16] = "Resource busy",
    [17] = "File exists",
    [18] = "Cross-device link",
    [19] = "Operation not supported by device",
    [20] = "Not a directory",
    [21] = "Is a directory",
    [22] = "Invalid argument",
    [23] = "Too many open files in system",
    [24] = "Too many open files",
    [25] = "Inappropriate ioctl for device",
    [26] = "Text file busy",
    [27] = "File too large",
    [28] = "No space left on device",
    [29] = "Illegal seek",
    [30] = "Read-only file system",
    [31] = "Too many links",
    [32] = "Broken pipe",
    [33] = "Numerical argument out of domain",
    [34] = "Result too large",
    [35] = "Resource temporarily unavailable",
    [36] = "Operation now in progress",
    [37] = "Operation already in progress",
    [38] = "Socket operation on non-socket",
    [39] = "Destination address required",
    [40] = "Message too long",
    [41] = "Protocol wrong type for socket",
    [42] = "Protocol not available",
    [43] = "Protocol not supported",
    [44] = "Socket type not supported",
    [45] = "Operation not supported",
    [46] = "Protocol family not supported",
    [47] = "Address family not supported by protocol family",
    [48] = "Address already in use",
    [49] = "Can't assign requested address",
    [50] = "Network is down",
    [51] = "Network is unreachable",
    [52] = "Network dropped connection on reset",
    [53] = "Software caused connection abort",
    [54] = "Connection reset by peer",
    [55] = "No buffer space available",
    [56] = "Socket is already connected",
    [57] = "Socket is not connected",
    [58] = "Can't send after socket shutdown",
    [59] = "Too many references: can't splice",
    [60] = "Operation timed out",
    [61] = "Connection refused",
    [62] = "Too many levels of symbolic links",
    [63] = "File name too long",
    [64] = "Host is down",
    [65] = "No route to host",
    [66] = "Directory not empty",
    [67] = "Too many processes",
    [68] = "Too many users",
    [69] = "Disc quota exceeded",
    [70] = "Stale NFS file handle",
    [71] = "Too many levels of remote in path",
    [72] = "RPC struct is bad",
    [73] = "RPC version wrong",
    [74] = "RPC prog. not avail",
    [75] = "Program version wrong",
    [76] = "Bad procedure for program",
    [77] = "No locks available",
    [78] = "Function not implemented",
    [79] = "Inappropriate file type or format",
    [80] = "Authentication error",
    [81] = "Need authenticator",
    [82] = "Device power is off",
    [83] = "Device error",
    [84] = "Value too large to be stored in data type",
    [85] = "Bad executable (or shared library)",
    [86] = "Bad CPU type in executable",
    [87] = "Shared library version mismatch",
    [88] = "Malformed Mach-o file",
    [89] = "Operation canceled",
    [90] = "Identifier removed",
    [91] = "No message of desired type",
    [92] = "Illegal byte sequence",
    [93] = "Attribute not found",
    [94] = "Bad message",
    [95] = "EMULTIHOP (Reserved)",
    [96] = "No message available on STREAM",
    [97] = "ENOLINK (Reserved)",
    [98] = "No STREAM resources",
    [99] = "Not a STREAM",
    [100] = "Protocol error",
    [101] = "STREAM ioctl timeout",
    [102] = "Operation not supported on socket",
    [103] = "Policy not found",
    [104] = "State not recoverable",
    [105] = "Previous owner died",
    [106] = "Interface output queue is full"};

#else

#define S21_ERRLIST_SIZE 134

static const char *const s21_sys_errlist[S21_ERRLIST_SIZE] = {
    [0] = "Success",
    [1] = "Operation not permitted",
    [2] = "No such file or directory",
    [3] = "No such process",
    [4] = "Interrupted system call",
    [5] = "Input/output error",
    [6] = "No such device or address",
    [7] = "Argument list too long",
    [8] = "Exec format error",
    [9] = "Bad file descriptor",
    [10] = "No child processes",
    [11] = "Resource temporarily unavailable",
    [12] = "Cannot allocate memory",
    [13] = "Permission denied",
    [14] = "Bad address",
    [15] = "Block device required",
    [16] = "Device or resource busy",
    [17] = "File exists",
    [18] = "Invalid cross-device link",
    [19] = "No such device",
    [20] = "Not a directory",
    [21] = "Is a directory",
    [22] = "Invalid argument",
    [23] = "Too many open files in system",
    [24] = "Too many open files",
    [25] = "Inappropriate ioctl for device",
    [26] = "Text file busy",
    [27] = "File too large",
    [28] = "No space left on device",
    [29] = "Illegal seek",
    [30] = "Read-only file system",
    [31] = "Too many links",
    [32] = "Broken pipe",
    [33] = "Numerical argument out of domain",
    [34] = "Numerical result out of range",
    [35] = "Resource deadlock avoided",
    [36] = "File name too long",
    [37] = "No locks available",
    [38] = "Function not implemented",
    [39] = "Directory not empty",
    [40] = "Too many levels of symbolic links",
    [41] = "Unknown error 41",
    [42] = "No message of desired type",
    [43] = "Identifier removed",
    [44] = "Channel number out of range",
    [45] = "Level 2 not synchronized",
    [46] = "Level 3 halted",
    [47] = "Level 3 reset",
    [48] = "Link number out of range",
    [49] = "Protocol driver not attached",
    [50] = "No CSI structure available",
    [51] = "Level 2 halted",
    [52] = "Invalid exchange",
    [53] = "Invalid request descriptor",
    [54] = "Exchange full",
    [55] = "No anode",
    [56] = "Invalid request code",
    [57] = "Invalid slot",
    [58] = "Unknown error 58",
    [59] = "Bad font file format",
    [60] = "Device not a stream",
    [61] = "No data available",
    [62] = "Timer expired",
    [63] = "Out of streams resources",
    [64] = "Machine is not on the network",
    [65] = "Package not installed",
    [66] = "Object is remote",
    [67] = "Link has been severed",
    [68] = "Advertise error",
    [69] = "Srmount error",
    [70] = "Communication error on send",
    [71] = "Protocol error",
    [72] = "Multihop attempted",
    [73] = "RFS specific error",
    [74] = "Bad message",
    [75] = "Value too large for defined data type",
    [76] = "Name not unique on network",
    [77] = "File descriptor in bad state",
    [78] = "Remote address changed",
    [79] = "Can not access a needed shared library",
    [80] = "Accessing a corrupted shared library",
    [81] = ".lib section in a.out corrupted",
    [82] = "Attempting to link in too many shared libraries",
    [83] = "Cannot exec a shared library directly",
    [84] = "Invalid or incomplete multibyte or wide character",
    [85] = "Interrupted system call should be restarted",
    [86] = "Streams pipe error",
    [87] = "Too many users",
    [88] = "Socket operation on non-socket",
    [89] = "Destination address required",
    [90] = "Message too long",
    [91] = "Protocol wrong type for socket",
    [92] = "Protocol not available",
    [93] = "Protocol not supported",
    [94] = "Socket type not supported",
    [95] = "Operation not supported",
    [96] = "Protocol family not supported",
    [97] = "Address family not supported by protocol",
    [98] = "Address already in use",
    [99] = "Cannot assign requested address",
    [100] = "Network is down",
    [101] = "Network is unreachable",
    [102] = "Network dropped connection on reset",
    [103] = "Software caused connection abort",
    [104] = "Connection reset by peer",
    [105] = "No buffer space available",
    [106] = "Transport endpoint is already connected",
    [107] = "Transport endpoint is not connected",
    [108] = "Cannot send after transport endpoint shutdown",
    [109] = "Too many references: cannot splice",
    [110] = "Connection timed out",
    [111] = "Connection refused",
    [112] = "Host is down",
    [113] = "No route to host",
    [114] = "Operation already in progress",
    [115] = "Operation now in progress",
    [116] = "Stale file handle",
    [117] = "Structure needs cleaning",
    [118] = "Not a XENIX named type file",
    [119] = "No XENIX semaphores available",
    [120] = "Is a named type file",
    [121] = "Remote I/O error",
    [122] = "Disk quota exceeded",
    [123] = "No medium found",
    [124] = "Wrong medium type",
    [125] = "Operation canceled",
    [126] = "Required key not available",
    [127] = "Key has expired",
    [128] = "Key has been revoked",
    [129] = "Key was rejected by service",
    [130] = "Owner died",
    [131] = "State not recoverable",
    [132] = "Operation not possible due to RF-kill",
    [133] = "Memory page has hardware error",
};

#endif  // defined(__APPLE__)

#endif  // SRC_S21_STRING_H__
