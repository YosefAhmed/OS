#include <inc/lib.h>

struct Page{
	int state;
	int sizeInPages;
};
struct Page MEMORY_LIST[(USER_HEAP_MAX-USER_HEAP_START)/PAGE_SIZE];


//int RoundUp(float n) {
//    cprintf("KAKAKA\n");
//    int intNum = (int)n;
//    cprintf("HNHNHN\n");
//    if (n == (float)intNum) {
//        return intNum;
//    }
//    return intNum + 1;
//}
//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
void* malloc(uint32 size)
{

	if(sys_isUHeapPlacementStrategyFIRSTFIT()==1){
		//1) FIRST FIT strategy

		int found = 1;
		int sizeInPages = size/PAGE_SIZE ;
		if(size % PAGE_SIZE != 0)
			sizeInPages++;

		int x = 0;
		for (int i = 0; i < sizeof(MEMORY_LIST)/sizeof(MEMORY_LIST[0]); ) {
			found = 1;
			if(MEMORY_LIST[i].state == 0){
				for (int j = i; j < i+sizeInPages; j++) {
					x=j;
					if(MEMORY_LIST[j].state == 1){
						i=j + MEMORY_LIST[j].sizeInPages;
						found = 0;
						break;
					}
				}
				if(found == 1){
					MEMORY_LIST[i].sizeInPages = sizeInPages;
					MEMORY_LIST[i].state = 1;
					sys_allocateMem(i*PAGE_SIZE+USER_HEAP_START, sizeInPages);
					return (void*)(uint32*)((i*PAGE_SIZE)+USER_HEAP_START);
				}
			}
			else{
				i += MEMORY_LIST[i].sizeInPages;
			}
		}
		return NULL;
	}
	else if(sys_isUHeapPlacementStrategyBESTFIT()==1){
		//2) BEST FIT strategy
		int found = 0;
		int sizeInPages = size/PAGE_SIZE ;
		if(size % PAGE_SIZE != 0)
			sizeInPages++;
		int start = -1, end = -1, startPage = -1, minSpace = 2147483647;
		cprintf("size in pages: %d\n",sizeInPages);
		for (int i = 0; i < sizeof(MEMORY_LIST)/sizeof(MEMORY_LIST[0]); ) {
			if(MEMORY_LIST[i].state == 0){

				start = i;
//				startPage = start;
				int j = i;
				cprintf("start: %d,\tend: %d,\tstartPage; %d,\tmin: %d,\n",start,end,startPage,minSpace);
				while(j < sizeof(MEMORY_LIST)/sizeof(MEMORY_LIST[0])){
					end = j;
					cprintf("J: %d\n",j);
//					cprintf("%d - State -> %d\n",j,MEMORY_LIST[j].state);
					if(MEMORY_LIST[j].state == 1){
						if((end-start) < sizeInPages){
							cprintf(" --- NOT SUTABLE --- %d\n",j);
							i=j + MEMORY_LIST[j].sizeInPages;
							break;
						}
//						if((end-start) < minSpace){
//							minSpace = end-start;
//							startPage = start;
//							found = 1;
//						}
					}
					else {
//						cprintf("////////////////// 7amada \\\\\\\\\\\\\\\\ \n");
						if((end-start) == sizeInPages){
							int c=end;
							while(MEMORY_LIST[c].state == 0 ){
//							cprintf("+++++++++++++++ Maiada +++++++++++++++++ \n");
								if(c-end > end-start)
									break;
								c++;
							}
								cprintf("c : %d\n",c);
							if(c-end < minSpace){
								cprintf("\n---- FOUND ---\n");
								minSpace = c-end;
								startPage = start;
								break;
								found = 1;
							}
							i=c + MEMORY_LIST[c].sizeInPages;
//							found = 1;
//							MEMORY_LIST[startPage].sizeInPages = sizeInPages;
//						    MEMORY_LIST[startPage].state = 1;
//							sys_allocateMem(startPage*PAGE_SIZE+USER_HEAP_START, sizeInPages);
//							return (void*)(uint32*)((startPage*PAGE_SIZE)+USER_HEAP_START);						}
						}
						j++;
					}
				}
			}
			else{
				i += MEMORY_LIST[i].sizeInPages;
			}
		}
		if(found == 1){
			MEMORY_LIST[startPage].sizeInPages = sizeInPages;
			MEMORY_LIST[startPage].state = 1;
			sys_allocateMem(startPage*PAGE_SIZE+USER_HEAP_START, sizeInPages);
			cprintf("------ Allocated -------\n");
			return (void*)(uint32*)((startPage*PAGE_SIZE)+USER_HEAP_START);
		}
		return NULL;
	}
	return NULL;
}

// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{
	int PageIndex =((int)virtual_address-USER_HEAP_START)/PAGE_SIZE;
	int sizeInPages = MEMORY_LIST[PageIndex].sizeInPages;
//	cprintf("Calculated index = %d\n",PageIndex );
	MEMORY_LIST[PageIndex].sizeInPages = 0;
	MEMORY_LIST[PageIndex].state = 0;
	sys_freeMem((uint32)virtual_address, sizeInPages);
}


//==================================================================================//
//============================== BONUS FUNCTIONS ===================================//
//==================================================================================//
//===============
// [1] realloc():
//===============

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to malloc().
//	A call with new_size = zero is equivalent to free().

//  Hint: you may need to use the sys_moveMem(uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		which switches to the kernel mode, calls moveMem(struct Env* e, uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		in "memory_manager.c", then switch back to the user mode here
//	the moveMem function is empty, make sure to implement it.

void *realloc(void *virtual_address, uint32 new_size)
{
	panic("this function is not required...!!");
	return 0;
}


//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address)
{
	panic("this function is not required...!!");
}

void expand(uint32 newSize)
{
	panic("this function is not required...!!");
}
void shrink(uint32 newSize)
{
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address)
{
	panic("this function is not required...!!");
}
