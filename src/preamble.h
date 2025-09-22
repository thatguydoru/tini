/*
   Copyright 2025 James O. Torres

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __TINI_PREAMBLE_H__
#define __TINI_PREAMBLE_H__

#if __STDC_VERSION__ < 202311
	#define nullptr NULL
#endif

#define tini_interface_def(id, funcs) \
	typedef struct id##VTable { funcs } id##VTable; \
	typedef struct id { void* self; const id##VTable* vtable; } id;

#endif
