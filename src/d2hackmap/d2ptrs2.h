#ifdef INIT_D2PTR_ADDR
  #define D2VARADDR(dll,addr1,name1,t1)     dll##_p##name1=(t1 *)(addr1-##dll##_ADDR+(DWORD)addr_##dll);
  #define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) dll##_##name1=(t1 (t2 *) t3)(addr1-##dll##_ADDR+(DWORD)addr_##dll);
  #define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) dll##_##name1=(t1 (t2 *) t3)GetProcAddress(addr_##dll,(LPCSTR)str1);
  #define D2ASMPTR(dll,addr1,name1)        dll##_v##name1=addr1-##dll##_ADDR+(DWORD)addr_##dll;
#else
	#ifdef DECLARE_D2PTR_VARIBLE
		#define D2VARADDR(dll,addr1,name1,t1)     t1 *dll##_p##name1;
		#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) t1 (t2 * dll##_##name1) t3;
		#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) t1 (t2 * dll##_##name1) t3;
		#define D2ASMPTR(dll,addr1,name1)        DWORD dll##_v##name1;
	#else
		#ifdef EXPORT_D2PTR_NAME_ADDRESS
			#define D2VARADDR(dll,addr1,name1,t1)     {addr1,#dll,#name1},
			#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) {addr1,#dll,#name1},
			#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) {addr1,#dll,#name1},
			#define D2ASMPTR(dll,addr1,name1)        {addr1,#dll,#name1},
		#else
			#define D2VARADDR(dll,addr1,name1,t1)     extern t1 *dll##_p##name1;
			#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) extern t1 (t2 * dll##_##name1) t3;
			#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) extern t1 (t2 * dll##_##name1) t3;
			#define D2ASMPTR(dll,addr1,name1)        extern DWORD dll##_v##name1;
		#endif
	#endif
#endif

#define d2multi_ADDR 0x6F9D0000
	D2VARADDR(d2multi,0x6F9E9C60, EditboxPreferences,    void *)  //6F9E9C5C+4
	D2VARADDR(d2multi,0x6FA09CC0, GameListControl,       D2EditBox *)
#undef d2multi_ADDR

#define d2mcpclient_ADDR 0x6FA20000
#undef d2mcpclient_ADDR
//------------ Newly added pointers which will be moved to d2ptrs.h in batch -------------

#define d2common_ADDR 0x6FD50000
	D2FUNCNAME(d2common,0x6FD80F80,10589,getUnitSize,int,__stdcall,(UnitAny *pUnit))
#undef d2common_ADDR

#define storm_ADDR 0x6FBF0000
	D2FUNCNAME(storm,0x6FC1A0B0,266,openMpq,int,__stdcall,(LPCSTR lpFileName,int dwPriority,int dwFlags,void *mpq))
	D2FUNCNAME(storm,0x6FC2C2B0,422,regQueryValue,int,__stdcall,(char *keyName,char *valueName,int arg,char *buf,int len))
#undef storm_ADDR

//----------------------------------------

#undef D2FUNCADDR
#undef D2FUNCNAME
#undef D2VARADDR
#undef D2ASMPTR
