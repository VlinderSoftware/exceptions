#ifndef exceptions_details_prologue_h
#define exceptions_details_prologue_h

#ifndef EXCEPTIONS_API
#ifdef EXCEPTIONS_EXPORTS
#define EXCEPTIONS_API __declspec(dllexport)
#else
#define EXCEPTIONS_API __declspec(dllimport)
#endif
#endif

#endif


