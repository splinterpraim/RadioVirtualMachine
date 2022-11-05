#ifndef COMMON_HPP
#define COMMON_HPP
//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.

#define RT   "\033[0m"      /* Reset */
#define BK   "\033[30m"      /* Black */
#define RD     "\033[31m"      /* Red */
#define GN   "\033[32m"      /* Green */
#define YW  "\033[33m"      /* Yellow */
#define BE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define CMN_LITTLE_ENDIAN 1
#define CMN_BIG_ENDIAN 0

#define STR(x) #x
// #define ADD_LINE_FILE(m,l,f) m " (line " STR(l) " in file "  STR(f) ")"
#define ADD_LINE_FILE(m,l,f) m " (in file " f ":" STR(l) ")"

#define ERR_STR_(m) RD "Error: " RT m
#define ERR_STR(m)  ADD_LINE_FILE(ERR_STR_(m), __LINE__,__FILE__) 
#define RVM_ERR_STR(m)  "RVM: " ERR_STR(m)
#define FC_ERR_STR(m)  "FC: " ERR_STR(m) 

#define SET_GREEN(m) GN m RT
#define SET_RED(m) RD m RT






#define RL_TYPE_INT 0
#define RL_TYPE_FLOAT 1
#define RL_TYPE_STRING 2

#endif //COMMON_HPP
