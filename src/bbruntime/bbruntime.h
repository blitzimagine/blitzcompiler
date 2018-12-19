/*

Platform neutral runtime library.

To be statically linked with an appropriate gxruntime driver.

*/

#ifndef BBRUNTIME_H
#define BBRUNTIME_H

void bbruntime_link(void(*rtSym)(std::string sym));

void bbruntime_panic(const char* err);

#endif
