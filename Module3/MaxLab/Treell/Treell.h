#pragma once

#ifdef TREELL_EXPORTS
#define TREELL_API __declspec(dllexport)
#else
#define TREELL_API __declspec(dllimport)
#endif

extern "C" TREELL_API void *CreateTreell(const char *name);

extern "C" TREELL_API void GenerateDefault(void* treell);
extern "C" TREELL_API void LoadFromFile(void* treell);
extern "C" TREELL_API void Store2File(void* treell);
extern "C" TREELL_API void View(void* treell);

extern "C" TREELL_API void TaskIt(void* treell, void (*task)(void *stream, void *node));